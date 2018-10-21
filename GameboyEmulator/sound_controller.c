
#include "sound_controller.h"
#include "util.h"

static float pitch = 50.0f;
static float start_pitch = 50.0f;
static float end_pitch = 500.0f;
static float sweep_seconds = 3.0f;
static bool reverse_sweep = false;

static float total_inc, inc_per_second, inc_per_frame;
static float seconds_per_frame;

static int wave_frame = 0;

void initSound() {
	seconds_per_frame = 1.0f / AUDIO_SAMPLE_RATE;
	total_inc = end_pitch - start_pitch;
	inc_per_second = total_inc / sweep_seconds;
	inc_per_frame = inc_per_second * seconds_per_frame;
}


float tickSound(Hardware *hardware) {
	float sample = 0.0f;

	/*float float_sample_rate = AUDIO_SAMPLE_RATE;
	float frames_per_cycle = float_sample_rate / pitch;
	float duty_cycles = 0.5;
	float high_frames = frames_per_cycle * duty_cycles;
	float low_frames = frames_per_cycle - high_frames;
	float volume = 0.05f;


	if (wave_frame++ > high_frames) {
		if (wave_frame < frames_per_cycle)
			sample = -1.0f;
		else
			wave_frame = 0;
	}

	sample *= volume;
	
	if (!reverse_sweep) {
		if (pitch < end_pitch) pitch += inc_per_frame;
		else reverse_sweep = true;
	}
	else {
		if (pitch > start_pitch) pitch -= inc_per_frame;
		else reverse_sweep = false;
	}*/

	SoundData *soundData = hardware->soundData;

	if (soundData->soundOnOff && soundData->chan3_OnOff) {
		float frequencyRaw = joinBytes(soundData->chan3_FrequencyLow, soundData->chan3_FrequencyHighSettings & 0x7);
		float frequency = 65536.0f / (2048.0f - frequencyRaw);

		float float_sample_rate = AUDIO_SAMPLE_RATE;
		float frames_per_cycle = float_sample_rate / frequency;
		int frames_per_sample = frames_per_cycle / (SOUND_WAVE_PATTERN_SIZE * 2);
		
		float tick_float = soundData->chan3_currentTick;
		float sampleIndexRaw = (tick_float / frames_per_cycle) * (SOUND_WAVE_PATTERN_SIZE * 2);
		int sampleIndex = (int)sampleIndexRaw % (SOUND_WAVE_PATTERN_SIZE * 2);

		unsigned char sampleCombined = soundData->chan3_WaveData[sampleIndex / 2];		
		unsigned char sample4Bit;
		
		bool useHighBits =  (sampleIndex % 2 == 0);
		if (useHighBits) sample4Bit = (sampleCombined & 0xF0) >> 4;
		else sample4Bit = sampleCombined & 0x0F;
		
		sample = sample4Bit / 15.0f;

		SoundFlag volume = soundData->chan3_Volume & SOUND_FLAG_CHAN3_VOLUME_MASK;
		if (volume == SOUND_FLAG_CHAN3_VOLUME_HALF) sample *= 0.5;
		else if (volume == SOUND_FLAG_CHAN3_VOLUME_QUARTER) sample *= 0.25;

		soundData->chan3_currentTick++;
	}
	else {
		soundData->chan3_currentTick = 1;
	}

	return sample;
}