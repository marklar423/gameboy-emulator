#pragma once



#include "objects.h"

typedef void(*guiCallback)();

void createGUIWindow();
void setGUICallbacks(guiCallback updateLoopCallback, guiCallback drawFrameCallback);
void runMainLoop(float targetFPS);