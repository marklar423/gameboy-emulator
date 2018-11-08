#include <stdbool.h>

#include "constants.h"
#include "objects.h"


#pragma once

void populateLoadInstructions(Hardware *hardware, InstructionMappingList *mappings);

void populateLoadOperands(InstructionMappingList *mappings);
void populateLoadDestinations(InstructionMappingList *mappings);
void populateLoadNextSPs(Hardware *hardware, InstructionMappingList *mappings);

