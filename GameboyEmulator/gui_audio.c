
#include "gui_audio.h"
#include <soundio.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <intrin.h>

typedef struct _AudioBufferItem {
	void *next;
	float sample;
} AudioBufferItem;

static struct SoundIo *g_soundio;
static struct SoundIoDevice *g_device;
static struct SoundIoOutStream *g_outstream;
static AudioBufferItem *g_audioBufferHead = NULL, *g_audioBufferEnd = NULL;
static AudioBufferItem *g_unusedBufferHead = NULL;
static int g_bufferSampleRate;

static const float PI = 3.1415926535f;
static float seconds_offset = 0.0f;

static float pitch = 50.0f;
static float start_pitch = 50.0f;
static float end_pitch = 500.0f;
float sweep_seconds = 3.0f;
bool reverse_sweep = false;

void initBuffer(int bufferSize) {
	AudioBufferItem *list = calloc(bufferSize, sizeof(AudioBufferItem));
	g_unusedBufferHead = list;
	
	for (int i = 0; i < bufferSize - 1; i++) {
		list[i].next = &list[i + 1];
	}
}

AudioBufferItem * allocBufferItem() {
	if (g_unusedBufferHead == NULL) g_unusedBufferHead = malloc(sizeof(AudioBufferItem));
	AudioBufferItem *item = g_unusedBufferHead;
	g_unusedBufferHead = g_unusedBufferHead->next;
	item->sample = 0.0f;
	item->next = NULL;
	return item;
}

void freeBufferItem(AudioBufferItem *bufferItem) {
	bufferItem->next = g_unusedBufferHead;
	g_unusedBufferHead = bufferItem;
}

void insertGUIAudioBufferSample(float sample) {
	AudioBufferItem *item = allocBufferItem();
	item->sample = sample;

	if (g_audioBufferHead == NULL) 
		g_audioBufferHead = g_audioBufferEnd = item;
	else 
		g_audioBufferEnd->next = item;
}

float popBufferSample() {
	float sample = 0.0f;
	if (g_audioBufferHead != NULL) {
		AudioBufferItem *item = g_audioBufferHead;

		if (item == g_audioBufferEnd) g_audioBufferEnd = NULL;
		g_audioBufferHead = g_audioBufferHead->next;

		sample = item->sample;
		
		freeBufferItem(item);
	}
	return sample;
}


static void writeAudioCallback(struct SoundIoOutStream *outstream, int frame_count_min, int frame_count_max)
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

			float sample = popBufferSample(); //sinf((seconds_offset + frame * seconds_per_frame) * radians_per_second);
			sample = 1.0f;

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

			if (!reverse_sweep) {
				if (pitch < end_pitch) pitch += inc_per_frame;
				else reverse_sweep = true;				
			}
			else {
				if (pitch > start_pitch) pitch -= inc_per_frame;
				else reverse_sweep = false;
			}
		}

		seconds_offset = fmodf(seconds_offset + seconds_per_frame * frame_count, 1.0f);

		if ((err = soundio_outstream_end_write(outstream))) {
			fprintf(stderr, "%s\n", soundio_strerror(err));
			exit(1);
		}

		frames_left -= frame_count;
	}
}

void initGUIAudio(int bufferSize, int bufferSampleRate) {
	int err;
	g_soundio = soundio_create();
	if (!g_soundio) {
		fprintf(stderr, "out of memory\n");
		return 1;
	}

	if ((err = soundio_connect(g_soundio))) {
		fprintf(stderr, "error connecting: %s", soundio_strerror(err));
		return 1;
	}

	soundio_flush_events(g_soundio);

	int default_out_device_index = soundio_default_output_device_index(g_soundio);
	if (default_out_device_index < 0) {
		fprintf(stderr, "no output device found");
		return 1;
	}

	g_device = soundio_get_output_device(g_soundio, default_out_device_index);
	if (!g_device) {
		fprintf(stderr, "out of memory");
		return 1;
	}

	fprintf(stderr, "Output device: %s\n", g_device->name);

	g_outstream = soundio_outstream_create(g_device);
	g_outstream->format = SoundIoFormatFloat32NE;
	g_outstream->write_callback = writeAudioCallback;

	if ((err = soundio_outstream_open(g_outstream))) {
		fprintf(stderr, "unable to open device: %s", soundio_strerror(err));
		return 1;
	}

	if (g_outstream->layout_error)
		fprintf(stderr, "unable to set channel layout: %s\n", soundio_strerror(g_outstream->layout_error));

	if ((err = soundio_outstream_start(g_outstream))) {
		fprintf(stderr, "unable to start device: %s", soundio_strerror(err));
		return 1;
	}

	initBuffer(bufferSize);
	g_bufferSampleRate = bufferSampleRate;

	/*for (;;)
		soundio_wait_events(soundio);
	*/
}

void disposeGUIAudio() {
	soundio_outstream_destroy(g_outstream);
	soundio_device_unref(g_device);
	soundio_destroy(g_soundio);
}