#pragma once

#include "constants.h"
#include "objects.h"

void tickPPU(Hardware *hardware, int tick);
void resetFrameStatus(Hardware *hardware);
void clearFramePixels(Hardware *hardware);