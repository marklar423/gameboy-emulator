#pragma once


#include "constants.h"
#include "objects.h"

void initJumpNextPC(Hardware *hardware, int **nextPCs);

void initJumpFlagConditions(Hardware *hardware, FlagCondition **flagConditions);

void initJumpOpSizes(Hardware *hardware, char *opSizeBytes);