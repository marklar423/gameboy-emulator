#pragma once

#include "constants.h"
#include "objects.h"
#include <stdbool.h>

Hardware* initCPU(GameRom *rom, bool populateDefaultValues);

OpMappings *initOpMappings(Hardware *hardware);

void tickCPU(Hardware *hardware, OpMappings *mappings);

void processInstruction(Hardware *hardware, OpMappings *mappings, unsigned char *instruction);

void getImmediateValue16(Hardware *hardware, int startAddress, int *result);

void getImmediateValue(Hardware *hardware, int address, unsigned char *result1);

void populateCachedValues(Hardware *hardware, int nextPCAddressValue);

void populateCachedResults(CachedOpResults *results, GBValue *operands1, GBValue *operands2);

void processDestination(Hardware *hardware, int *result, GBValue *destination);

void processFlags(Hardware *hardware, GBValue *operand1, GBValue *operand2, int *result, FlagResult *flagResult);