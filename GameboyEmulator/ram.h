#pragma once

#include "constants.h"
#include "objects.h"

unsigned char* getRamAddress(Hardware *hardware, int address);

// Use this function when writing to RAM might be denied or have other effects, like with MBC
void writeRamLocation(Hardware *hardware, unsigned char *location, unsigned char value);

void pushByteToStack(Hardware *hardware, unsigned char value);

void pushWordToStack(Hardware *hardware, int value);

unsigned char popByteFromStack(Hardware *hardware);
