#pragma once


#include "constants.h"
#include "objects.h"

void populateJumpInstructions(InstructionMappingList *mappings);

void populateJumpCalculations(InstructionMappingList *mappings);

void populateJumpNextPC(InstructionMappingList *mappings);

void populateJumpFlagConditions(InstructionMappingList *mappings);
