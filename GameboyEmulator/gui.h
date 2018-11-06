#pragma once



#include "objects.h"

typedef void(*guiCallback)();

void createGUIWindow(char *title);

void setGUICallbacks(guiCallback updateLoopCallback, guiCallback drawFrameCallback);

void runMainLoop(float targetFPS);

void getInputState(InputState *inputState);