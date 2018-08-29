#pragma once


#include "constants.h"
#include "objects.h"

void populateJumpInstructions(Hardware *hardware, InstructionMapping *mappings);

void populateJumpCalculations(Hardware *hardware, InstructionMapping *mappings);

void populateJumpNextPC(Hardware *hardware, InstructionMapping *mappings);

void populateJumpFlagConditions(Hardware *hardware, InstructionMapping *mappings);
