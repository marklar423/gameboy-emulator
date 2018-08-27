#pragma once

#include "constants.h"
#include "objects.h"

unsigned char* getRamAddress(Hardware *hardware, int address);

void pushByteToStack(Hardware *hardware, unsigned char value);

void pushWordToStack(Hardware *hardware, int value);

unsigned char popByteFromStack(Hardware *hardware);
