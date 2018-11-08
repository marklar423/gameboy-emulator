#pragma once

#include "constants.h"
#include "objects.h"


void populateALUInstructions(InstructionMappingList *mappings);

void populateALUOperands1(InstructionMappingList *mappings);
void populateALUOperands2(InstructionMappingList *mappings);
void populateALUResults(InstructionMappingList *mappings);
void populateALUDestinations(InstructionMappingList *mappings);
void populateALUFlagResults(InstructionMappingList *mappings);