#pragma once

#include "constants.h"
#include "objects.h"
#include <stdbool.h>


void processInterrupts(Hardware *hardware);

void setRequestedInterrupt(Hardware *hardware, InterruptFlag flag, bool requested);