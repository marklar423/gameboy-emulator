#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "constants.h"


typedef struct _GameRom {
	unsigned char *romBytes;
	long romLength;
	char gameName[15];
} GameRom;


typedef struct _Registers {
	unsigned char A, B, C, D, E, H, L, F;
	int SP, PC;
	bool globalInterruptsEnabled;
	unsigned char enabledInterrupts, requestedInterrupts;
} Registers;

typedef struct _GBValue {
	bool isWordValue, isSplitValue;
	unsigned char **byteValue;
	unsigned char **byteValue2; //used with split bytes. byteValue2 is less significant than byteValue
	int **wordValue;
} GBValue;

typedef struct _CachedOpValues {
	unsigned char immediateByte;
	int immediateWord;
	unsigned char *highMemoryImmediateByte, *memoryImmediateWord;
	unsigned char *highMemoryC;
	unsigned char *memoryHL, *memoryBC, *memoryDE;
	int AF, BC, DE, HL;
	int NextPCAddressPlusImmediateByteSigned;
	int SPPlusImmediateByteSigned, SPPlusOne, SPPlusTwo, SPMinusOne, SPMinusTwo;
	unsigned char *stackValue; //value on top of stack
	unsigned char *stackPlusOneValue; //second-to-top value in stack
	unsigned char *stackMinusOneValue; //one value beyond top of stack (new value)
	unsigned char *stackMinusTwoValue; //two values beyond top of stack (new value)
	int stackWordValue;
} CachedOpValues;

typedef struct _CachedOpResults {
	int xor, add, subtract;
} CachedOpResults;

typedef struct _ResultInfo {
	bool isZero, isAddHalfCarry, isAddCarry, isSubHalfBorrow, isSubBorrow;
} ResultInfo;

typedef struct _Hardware {
	GameRom *rom;
	Registers *registers;
	CachedOpValues *cachedValues;
	CachedOpResults *cachedResults;
	ResultInfo *resultInfo;
	unsigned char *workRam;
	int cyclesToWait;
} Hardware;

typedef struct _FlagResult {
	bool *isZero, *isSubtract, *isHalfCarry, *isCarry;
} FlagResult; //NULL = don't set, true = set to 1, false = set to 0

typedef struct _FlagCondition {
	unsigned char condition;
	bool negate;
} FlagCondition;

typedef struct _OpCycleCount {
	int executeCycles;
	int dontExecuteCycles; //for conditional operations like jump, when the condition is false
} OpCycleCount;

typedef struct _InstructionMapping {
	GBValue *operand1, *operand2, *destination;
	int *result;
	int *nextPC, *nextSP;
	FlagCondition *flagCondition;
	FlagResult *flagResult;
	char sizeBytes; //default is 1
	OpCycleCount *cycleCount; //default is 1 cycle per operation
} InstructionMapping;

GameRom* createGameRom(unsigned char *romBytes, long romLength);

GBValue* createGBValue(bool is16Bit, bool isSplitValue, char *byteValue, char *byteValue2, int *wordValue);
GBValue* createGBPointerValue(bool is16Bit, bool isSplitValue, char **byteValuePointer, char **byteValue2Pointer, int **wordValuePointer);
int GBValueToInt(GBValue *value);

#define createGBByteValue(byteValue) createGBValue(false, false, byteValue, NULL, NULL)
#define createGBWordValue(wordValue) createGBValue(true, false, NULL, NULL, wordValue)
#define createGBSplitByteValue(byteValue, byteValue2) createGBValue(false, true, byteValue, byteValue2, NULL)

#define createGBBytePointer(byteValue) createGBPointerValue(false, false, byteValue, NULL, NULL)
#define createGBWordPointer(wordValue) createGBPointerValue(true, false, NULL, NULL, wordValue)
#define createGBSplitBytePointer(byteValue, byteValue2) createGBPointerValue(false, true, byteValue, byteValue2, NULL)

FlagResult* createFlagResult(bool *isZero, bool *isSubtract, bool *isHalf, bool *isCarry);
FlagCondition* createFlagCondition(char condition, bool negate);

OpCycleCount* createOpCycleCount(int executeCycles, int dontExecuteCycles);

InstructionMapping* createInstructionMappings(int numInstructions);