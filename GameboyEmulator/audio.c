
#include "audio.h"
#include <soundio.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static const float PI = 3.1415926535f;
static float seconds_offset = 0.0f;

static float pitch = 50.0f;
static float start_pitch = 50.0f;
static float end_pitch = 500.0f;
float sweep_seconds = 10.0f;

static void write_callback(struct SoundIoOutStream *outstream, int frame_count_min, int frame_count_max)
{
	const struct SoundIoChannelLayout *layout = &outstream->layout;
	float float_sample_rate = outstream->sample_rate;
	float seconds_per_frame = 1.0f / float_sample_rate;
	struct SoundIoChannelArea *areas;
	int frames_left = frame_count_max;
	int err;



	float total_inc = end_pitch - start_pitch;
	float inc_per_second = total_inc / sweep_seconds;
	float inc_per_frame = inc_per_second * seconds_per_frame;

	while (frames_left > 0) {
		int frame_count = frames_left;

		if ((err = soundio_outstream_begin_write(outstream, &areas, &frame_count))) {
			fprintf(stderr, "%s\n", soundio_strerror(err));
			exit(1);
		}

		if (!frame_count) break;


		float radians_per_second = pitch * 2.0f * PI;

		int wave_frame = 0;

		for (int frame = 0; frame < frame_count; frame += 1) {
			float frames_per_cycle = float_sample_rate / pitch;
			float duty_cycles = 0.5;
			float high_frames = frames_per_cycle * duty_cycles;
			float low_frames = frames_per_cycle - high_frames;
			float volume = 0.05f;

			float sample = 1.0f; //sinf((seconds_offset + frame * seconds_per_frame) * radians_per_second);
		
			if (wave_frame++ > high_frames) {
				if (wave_frame < frames_per_cycle)
					sample = -1.0f;
				else
					wave_frame = 0;
			}
			
			sample *= volume;

			for (int channel = 0; channel < layout->channel_count; channel += 1) {
				float *ptr = (float*)(areas[channel].ptr + areas[channel].step * frame);
				*ptr = sample;
			}

			if (pitch < end_pitch) pitch += inc_per_frame;
		}

		seconds_offset = fmodf(seconds_offset + seconds_per_frame * frame_count, 1.0f);

		if ((err = soundio_outstream_end_write(outstream))) {
			fprintf(stderr, "%s\n", soundio_strerror(err));
			exit(1);
		}

		frames_left -= frame_count;
	}
}

void playSampleAudio() {
	int err;
	struct SoundIo *soundio = soundio_create();
	if (!soundio) {
		fprintf(stderr, "out of memory\n");
		return 1;
	}

	if ((err = soundio_connect(soundio))) {
		fprintf(stderr, "error connecting: %s", soundio_strerror(err));
		return 1;
	}

	soundio_flush_events(soundio);

	int default_out_device_index = soundio_default_output_device_index(soundio);
	if (default_out_device_index < 0) {
		fprintf(stderr, "no output device found");
		return 1;
	}

	struct SoundIoDevice *device = soundio_get_output_device(soundio, default_out_device_index);
	if (!device) {
		fprintf(stderr, "out of memory");
		return 1;
	}

	fprintf(stderr, "Output device: %s\n", device->name);

	struct SoundIoOutStream *outstream = soundio_outstream_create(device);
	outstream->format = SoundIoFormatFloat32NE;
	outstream->write_callback = write_callback;

	if ((err = soundio_outstream_open(outstream))) {
		fprintf(stderr, "unable to open device: %s", soundio_strerror(err));
		return 1;
	}

	if (outstream->layout_error)
		fprintf(stderr, "unable to set channel layout: %s\n", soundio_strerror(outstream->layout_error));

	if ((err = soundio_outstream_start(outstream))) {
		fprintf(stderr, "unable to start device: %s", soundio_strerror(err));
		return 1;
	}

	for (;;)
		soundio_wait_events(soundio);

	soundio_outstream_destroy(outstream);
	soundio_device_unref(device);
	soundio_destroy(soundio);
}