
#include "sound_controller.h"
#include "util.h"
#include <math.h>


float getPulseChannelSample(unsigned char frequencyLow, unsigned char frequencyHighSettings, 
							unsigned char patternLength, unsigned char volumeSweep, int* tick);
float getChannel3Sample(SoundData *soundData);
float getChannel4Sample(SoundData *soundData);

float getPulseVolume(unsigned char pulseVolumeSweepRegister, int tick);
float getPulseDutyPercentage(unsigned char pulseDuty);
float getFrequency(unsigned char frequencyLow, unsigned char frequencyHigh);
int getChannel4Rand(int lastRandom, bool sevenBitMode);

AudioSample tickSound(Hardware *hardware) {
	SoundData *soundData = hardware->soundData;
	
	float mixedSampleRight = 0.0f, mixedSampleLeft = 0.0f;

	if (soundData->soundEnable) {
		float sample1 = getPulseChannelSample(soundData->chan1_FrequencyLow, soundData->chan1_FrequencyHighSettings,
			soundData->chan1_PatternLength, soundData->chan1_VolumeSweep, &soundData->chan1_currentTick);

		float sample2 = getPulseChannelSample(soundData->chan2_FrequencyLow, soundData->chan2_FrequencyHighSettings,
			soundData->chan2_PatternLength, soundData->chan2_VolumeSweep, &soundData->chan2_currentTick);

		float sample3 = getChannel3Sample(soundData);
		float sample4 = getChannel4Sample(soundData);

		if (soundData->channelLeftRightEnable & SOUND_MASK_ENABLE_LEFT_CHAN_1) mixedSampleLeft += sample1;
		if (soundData->channelLeftRightEnable & SOUND_MASK_ENABLE_LEFT_CHAN_2) mixedSampleLeft += sample2;
		if (soundData->channelLeftRightEnable & SOUND_MASK_ENABLE_LEFT_CHAN_3) mixedSampleLeft += sample3;
		if (soundData->channelLeftRightEnable & SOUND_MASK_ENABLE_LEFT_CHAN_4) mixedSampleLeft += sample4;

		if (soundData->channelLeftRightEnable & SOUND_MASK_ENABLE_RIGHT_CHAN_1) mixedSampleRight += sample1;
		if (soundData->channelLeftRightEnable & SOUND_MASK_ENABLE_RIGHT_CHAN_2) mixedSampleRight += sample2;
		if (soundData->channelLeftRightEnable & SOUND_MASK_ENABLE_RIGHT_CHAN_3) mixedSampleRight += sample3;
		if (soundData->channelLeftRightEnable & SOUND_MASK_ENABLE_RIGHT_CHAN_4) mixedSampleRight += sample4;
				
		float volumeRight = (float)(soundData->masterVolume & SOUND_MASK_MASTER_VOLUME_RIGHT) / 7.0f;
		float volumeLeft = (float) ((soundData->masterVolume & SOUND_MASK_MASTER_VOLUME_LEFT) >> 4) / 7.0f;

		mixedSampleRight *= volumeRight;
		mixedSampleLeft *= volumeLeft;
	}

	AudioSample sample;
	sample.leftSample = mixedSampleLeft;
	sample.rightSample = mixedSampleRight;

	return sample;
}

float getPulseChannelSample(unsigned char frequencyLow, unsigned char frequencyHighSettings,
							unsigned char patternLength, unsigned char volumeSweep, int* tick) {
	float sample = 0.0f;
	float volume = getPulseVolume(volumeSweep, *tick);

	if (volume) {
		float frequency = getFrequency(frequencyLow, frequencyHighSettings);

		float sampleRate = AUDIO_SAMPLE_RATE;
		float framesPerWave = sampleRate / frequency;
		float dutyCycles = getPulseDutyPercentage(patternLength);
		float highSamples = framesPerWave * dutyCycles;

		int currentTick = *tick;
		int waveIndex = (currentTick % (int)framesPerWave);

		if (waveIndex < highSamples) sample = 1.0f;

		sample *= volume;

		*tick += 1;
	}
	else {
		*tick = 1;
	}


	return sample;
}


float getPulseVolume(unsigned char pulseVolumeSweepRegister, int tick) {
	float volume = pulseVolumeSweepRegister & SOUND_MASK_PULSE_VOLUME;
	
	int volumeStepNumber = pulseVolumeSweepRegister & SOUND_MASK_PULSE_VOLUME_SWEEP_STEP;

	if (volumeStepNumber && (volumeStepNumber % tick == 0)) {		
		if (pulseVolumeSweepRegister & SOUND_MASK_PULSE_VOLUME_SWEEP_INCREASE)
			if (volume < 0xF0) volume += 0x10;
		else 
			if (volume > 0x00) volume -= 0x10;
		
	}

	return volume / 0xF0;
}

float getPulseDutyPercentage(unsigned char pulseDutyRegister) {
	SoundFlag flag = pulseDutyRegister & SOUND_MASK_PULSE_DUTY;

	switch (flag) {
		case SOUND_FLAG_PULSE_DUTY_12_5: return 0.125f;
		case SOUND_FLAG_PULSE_DUTY_25: return 0.25f;
		case SOUND_FLAG_PULSE_DUTY_50: return 0.50f;
		case SOUND_FLAG_PULSE_DUTY_75: return 0.75f;
	}	

	return 0.0f;
}

float getChannel3Sample(SoundData *soundData) {
	float sample = 0.0f;

	if (soundData->chan3_OnOff) {
		float frequency = getFrequency(soundData->chan3_FrequencyLow, soundData->chan3_FrequencyHighSettings);
		
		float sampleRate = AUDIO_SAMPLE_RATE;
		float framesPerWave = sampleRate / frequency;
		float framesPerWaveSample = framesPerWave / ((float) SOUND_WAVE_PATTERNS);

		int currentTick = soundData->chan3_currentTick;
		int waveIndex = (currentTick % (int) framesPerWave);
		int waveSampleIndex = waveIndex / framesPerWaveSample;

		unsigned char sampleCombined = soundData->chan3_WaveData[waveSampleIndex / 2];
		unsigned char sample4Bit;

		bool useHighBits = (waveSampleIndex % 2 == 0);
		if (useHighBits) sample4Bit = (sampleCombined & 0xF0) >> 4;
		else sample4Bit = sampleCombined & 0x0F;

		sample = sample4Bit / 15.0f;

		SoundFlag volume = soundData->chan3_Volume & SOUND_MASK_CHAN3_VOLUME;
		if (volume == SOUND_FLAG_CHAN3_VOLUME_HALF) sample *= 0.5;
		else if (volume == SOUND_FLAG_CHAN3_VOLUME_QUARTER) sample *= 0.25;

		soundData->chan3_currentTick++;
	}
	else {
		soundData->chan3_currentTick = 1;
	}

	return sample;
}

float getChannel4Sample(SoundData *soundData) {
	float sample = 0.0f;

	if (soundData->chan4_VolumeSweep & 0xF0) {
		float shiftFrequency = (soundData->chan4_polynomialCounter & SOUND_MASK_CHAN4_CLOCK_FREQUENCY) >> 4;
		float dividingRatio = (soundData->chan4_polynomialCounter & SOUND_MASK_CHAN4_DIVIDING_RATIO);
		if (dividingRatio == 0) dividingRatio = 0.5f;

		dividingRatio = 524287.5f * (1.0f / dividingRatio);

		float p = powf(2.0f, shiftFrequency + 1);
		float frequency = dividingRatio / p;
		int ticksPerUpdate = AUDIO_SAMPLE_RATE / frequency;

		if (soundData->chan4_currentTick >= ticksPerUpdate) {
			bool sevenBitMode = (soundData->chan4_polynomialCounter & SOUND_MASK_CHAN4_7BIT_MODE);

			int nextRand = getChannel4Rand(soundData->chan4_lastRNGValue, false);
			
			soundData->chan4_lastRNGValue = nextRand;
			sample = ~nextRand & 1;

			soundData->chan4_lastSample = sample;

			soundData->chan4_currentTick = 0;
		}
		else {
			sample = soundData->chan4_lastSample;
		}
	}
	else {
		soundData->chan4_lastRNGValue = 1;
	}

	soundData->chan4_currentTick++;
	
	return sample;
}

int getChannel4Rand(int lastRandom, bool sevenBitMode) {
	int newRandom = lastRandom >> 1;
	bool flipHighBits = (lastRandom ^ newRandom) & 1;

	if (flipHighBits) {
		if (sevenBitMode)
			newRandom |= 0x4040;
		else
			newRandom |= 0x4000;
	}
	return newRandom;
}

float getFrequency(unsigned char frequencyLow, unsigned char frequencyHigh) {
	float frequencyRaw = joinBytes(frequencyLow, frequencyHigh & SOUND_MASK_FREQUENCY_HIGH_BITS);
	float frequency = 131072.0f / (2048.0f - frequencyRaw);
	return frequency;
}