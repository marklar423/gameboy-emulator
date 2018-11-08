#pragma once

#include "constants.h"
#include "objects.h"


void populateALUInstructions(Hardware *hardware, InstructionMappingList *mappings);

void populateALUOperands1(Hardware *hardware, InstructionMappingList *mappings);
void populateALUOperands2(Hardware *hardware, InstructionMappingList *mappings);
void populateALUResults(Hardware *hardware, InstructionMappingList *mappings);
void populateALUDestinations(Hardware *hardware, InstructionMappingList *mappings);
void populateALUFlagResults(Hardware *hardware, InstructionMappingList *mappings);