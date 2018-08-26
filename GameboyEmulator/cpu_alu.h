#pragma once

#include "constants.h"
#include "objects.h"


void populateALUInstructions(Hardware *hardware, InstructionMapping *mappings);

void populateALUOperands1(Hardware *hardware, InstructionMapping *mappings);
void populateALUOperands2(Hardware *hardware, InstructionMapping *mappings);
void populateALUResults(Hardware *hardware, InstructionMapping *mappings);
void populateALUDestinations(Hardware *hardware, InstructionMapping *mappings);
void populateALUFlagResults(Hardware *hardware, InstructionMapping *mappings);