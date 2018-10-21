
#include "sound_controller.h"


static float pitch = 50.0f;
static float start_pitch = 50.0f;
static float end_pitch = 500.0f;
static float sweep_seconds = 3.0f;
static bool reverse_sweep = false;

static float total_inc, inc_per_second, inc_per_frame;
static float seconds_per_frame;

static int wave_frame = 0;

void initSound() {
	seconds_per_frame = 1.0f / SOUND_SAMPLE_RATE;
	total_inc = end_pitch - start_pitch;
	inc_per_second = total_inc / sweep_seconds;
	inc_per_frame = inc_per_second * seconds_per_frame;
}

float tickSound(Hardware *hardware) {
	float float_sample_rate = SOUND_SAMPLE_RATE;
	float frames_per_cycle = float_sample_rate / pitch;
	float duty_cycles = 0.5;
	float high_frames = frames_per_cycle * duty_cycles;
	float low_frames = frames_per_cycle - high_frames;
	float volume = 0.05f;

	float sample = 1.0f;

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
	}

	return sample;
}