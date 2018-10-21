#pragma once



void initGUIAudio(int bufferSize, int bufferSampleRate);

void disposeGUIAudio();

void writeGUIAudioBuffer(float sample);
