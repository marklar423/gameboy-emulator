#pragma once

#include "constants.h"
#include "objects.h"


void initALUOperands1(Hardware *hardware, GBValue **operands1);
void initALUOperands2(Hardware *hardware, GBValue **operands1);
void initALUResults(Hardware *hardware, int **results);
void initALUDestinations(Hardware *hardware, GBValue **destinations);
void initALUFlagResults(Hardware *hardware, FlagResult **flagResults);
void initALUOpSizes(Hardware *hardware, char *opSizeBytes);