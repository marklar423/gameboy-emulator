#pragma once

#include <assert.h>

int joinBytes(const unsigned char leastSignificant, const unsigned char mostSignificant);

void splitBytes(int value, const unsigned char *leastSignificant, const unsigned char *mostSignificant);

#define THROW_ERROR(x) assert(0 && x)

#define SET_BIT_IF(conditionPointer, bitValue, destination) destination = (*(conditionPointer)) ? destination | bitValue : destination & ~(bitValue)

void printDebugLine(char* line);