#pragma once

#include "constants.h"
#include "objects.h"

unsigned char* getRamAddress(Hardware *hardware, int address);

// Use this function when writing to RAM might be denied or have other effects, like with MBC
//void writeRamAddress(Hardware *hardware, int address, unsigned char value); TODO

void pushByteToStack(Hardware *hardware, unsigned char value);

void pushWordToStack(Hardware *hardware, int value);

unsigned char popByteFromStack(Hardware *hardware);
