#pragma once

#include "constants.h"
#include "objects.h"
#include <stdbool.h>

Hardware* initCPU(GameRom *rom, bool populateDefaultValues);

InstructionMapping* initInstructionMappings(Hardware *hardware);

void tickCPU(Hardware *hardware, InstructionMapping *mappings);
