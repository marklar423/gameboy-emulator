#pragma once

#include <assert.h>

void joinBytes(const unsigned char *leastSignificant, const unsigned char *mostSignificant, int *result);

void splitBytes(int *value, const unsigned char *leastSignificant, const unsigned char *mostSignificant);

#define THROW_ERROR(x) assert(0 && x)

#define SET_BIT_IF(conditionPointer, bitValue, destination) destination = (*(conditionPointer)) ? destination | bitValue : destination & ~(bitValue)