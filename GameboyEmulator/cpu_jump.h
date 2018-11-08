#pragma once


#include "constants.h"
#include "objects.h"

void populateJumpInstructions(Hardware *hardware, InstructionMappingList *mappings);

void populateJumpCalculations(Hardware *hardware, InstructionMappingList *mappings);

void populateJumpNextPC(Hardware *hardware, InstructionMappingList *mappings);

void populateJumpFlagConditions(Hardware *hardware, InstructionMappingList *mappings);
