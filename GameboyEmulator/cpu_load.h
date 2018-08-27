#include <stdbool.h>

#include "constants.h"
#include "objects.h"


#pragma once

void populateLoadInstructions(Hardware *hardware, InstructionMapping *mappings);

void populateLoadOperands1(Hardware *hardware, InstructionMapping *mappings);
void populateLoadDestinations(Hardware *hardware, InstructionMapping *mappings);
void populateLoadNextSPs(Hardware *hardware, InstructionMapping *mappings);

