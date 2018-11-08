#pragma once

#include "constants.h"
#include "objects.h"


// Use this function when writing to RAM might be denied or have other effects, like with MBC

void pushByteToStack(Hardware *hardware, unsigned char value);

void pushWordToStack(Hardware *hardware, int value);

unsigned char popByteFromStack(Hardware *hardware);

void setJoypadDataState(Hardware *hardware);

void populateRamAddresses(Hardware *hardware);

#define getRamAddressValue(hardware, ramAddress) ramAddress->valueFunc != NULL ? ramAddress->valueFunc(hardware, ramAddress) : *(ramAddress->value)
#define writeRamAddressValue(hardware, ramAddress, valueToWrite) if (ramAddress->writeValueFunc != NULL) { ramAddress->writeValueFunc(hardware, ramAddress, valueToWrite); } else { *(ramAddress->value) = valueToWrite; }