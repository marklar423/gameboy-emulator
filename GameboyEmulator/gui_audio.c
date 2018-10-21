
#include <soundio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <intrin.h>

#include "gui_audio.h"
#include "mutex.h"
#include "constants.h"

typedef struct _AudioBufferItem {
	void *next;
	float sample;
} AudioBufferItem;

static struct SoundIo *g_soundio;
static struct SoundIoDevice *g_device;
static struct SoundIoOutStream *g_outstream;

static AudioBufferItem *g_audioBufferRead = NULL, *g_audioBufferWrite = NULL;

static int g_bufferSize, g_itemsInBuffer = 0, g_bufferSampleRate;
static MUTEX g_bufferMutex;


void initBuffer(int bufferSize) {
	g_bufferSize = bufferSize;

	AudioBufferItem *lastItem = NULL, *firstItem = NULL;
	AudioBufferItem *items = calloc(bufferSize, sizeof(AudioBufferItem));

	for (int i = 0; i < bufferSize; i++) {
		AudioBufferItem *item = (items + i);
		item->next = lastItem;
		lastItem = item;
		if (!firstItem) firstItem = item;
	}

	g_audioBufferRead = g_audioBufferWrite = lastItem;
	firstItem->next = lastItem; //make the buffer circular
}


bool writeGUIAudioBuffer(float sample) {
	bool success = false;

	if (g_itemsInBuffer < g_bufferSize) {
		g_audioBufferWrite->sample = sample;
		g_audioBufferWrite = g_audioBufferWrite->next;

		TAKE_MUTEX(g_bufferMutex);
		g_itemsInBuffer++;
		RELEASE_MUTEX(g_bufferMutex);

		success = true;
	}

	return success;
}

float readGUIAudioBuffer() {
	float sample = 0.0f;


	if (g_itemsInBuffer) {
		sample = g_audioBufferRead->sample;
		g_audioBufferRead = g_audioBufferRead->next;

		TAKE_MUTEX(g_bufferMutex);
		g_itemsInBuffer--;
		RELEASE_MUTEX(g_bufferMutex);
	}


	return sample;
}


static void writeAudioCallback(struct SoundIoOutStream *outstream, int frame_count_min, int frame_count_max)
{
	const struct SoundIoChannelLayout *layout = &outstream->layout;
	struct SoundIoChannelArea *areas;
	int max_frames_left = frame_count_max;
	int err;

	
	while (max_frames_left > 0) {
		int frame_count = min(g_itemsInBuffer, frame_count_max);

		if ((err = soundio_outstream_begin_write(outstream, &areas, &frame_count))) {
			fprintf(stderr, "%s\n", soundio_strerror(err));			
		}

		if (!frame_count) break;
				
		for (int frame = 0; frame < frame_count; frame++) {

			float sample = readGUIAudioBuffer();

			for (int channel = 0; channel < layout->channel_count; channel += 1) {
				float *ptr = (float*)(areas[channel].ptr + areas[channel].step * frame);
				*ptr = sample;
			}
		}


		if ((err = soundio_outstream_end_write(outstream))) {
			fprintf(stderr, "%s\n", soundio_strerror(err));
		}

		max_frames_left -= frame_count;
	}
}

void initGUIAudio(int bufferSize, int bufferSampleRate) {

	initBuffer(bufferSize);
	g_bufferSampleRate = bufferSampleRate;
	g_bufferMutex = CREATE_MUTEX();

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
	g_outstream->sample_rate = AUDIO_SAMPLE_RATE;

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

	/*for (;;)
		soundio_wait_events(soundio);
	*/
}

void disposeGUIAudio() {
	soundio_outstream_destroy(g_outstream);
	soundio_device_unref(g_device);
	soundio_destroy(g_soundio);
	DISPOSE_MUTEX(g_bufferMutex);
}