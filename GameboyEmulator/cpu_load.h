#include <stdbool.h>

#include "constants.h"
#include "objects.h"


#pragma once

void initLoadOperands1(Hardware *hardware, GBValue **operands1);
void initLoadDestinations(Hardware *hardware, GBValue **destinations);
void initLoadOpSizes(Hardware *hardware, char *opSizeBytes);

