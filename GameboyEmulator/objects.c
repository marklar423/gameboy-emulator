
#include "objects.h"

GameRom* createGameRom(unsigned char *romBytes, long romLength) {
	GameRom *rom = malloc(sizeof(GameRom));
	rom->romBytes = romBytes;
	rom->romLength = romLength;

	return rom;
}

GBValue* createGBValue(bool is16Bit, bool isSplitValue, char *byteValue, char *byteValue2, int *wordValue) {
	char **byteValuePointer = NULL, **byteValue2Pointer = NULL;
	int **wordValuePointer = NULL;

	if (byteValue != NULL) {
		byteValuePointer = malloc(sizeof(char **));
		*byteValuePointer = byteValue;
	}

	if (byteValue2 != NULL) {
		byteValue2Pointer = malloc(sizeof(char **));
		*byteValue2Pointer = byteValue2;
	}

	if (wordValue != NULL) {
		wordValuePointer = malloc(sizeof(int **));
		*wordValuePointer = wordValue;
	}

	return createGBPointerValue(is16Bit, isSplitValue, byteValuePointer, byteValue2Pointer, wordValuePointer);
}


GBValue* createGBPointerValue(bool is16Bit, bool isSplitValue, char **byteValuePointer, char **byteValue2Pointer, int **wordValuePointer) {
	GBValue *value = malloc(sizeof(GBValue));

	value->isWordValue = is16Bit;
	value->isSplitValue = isSplitValue;
	value->byteValue = byteValuePointer;
	value->byteValue2 = byteValue2Pointer;
	value->wordValue = wordValuePointer;

	return value;
}

FlagResult* createFlagResult(bool *isZero, bool *isSubtract, bool *isHalf, bool *isCarry) {
	FlagResult *flagResult = malloc(sizeof(FlagResult));

	flagResult->isZero = isZero;
	flagResult->isSubtract = isSubtract;
	flagResult->isHalfCarry = isHalf;
	flagResult->isCarry = isCarry;

	return flagResult;
}

FlagCondition* createFlagCondition(char condition, bool negate) {
	FlagCondition *flagCondition = malloc(sizeof(FlagResult));

	flagCondition->condition = condition;
	flagCondition->negate = negate;

	return flagCondition;
}

int GBValueToInt(GBValue *value) {
	int convertedValue = 0;

	if (value != NULL) {
		if (value->isWordValue) convertedValue = **(value->wordValue);
		else if (value->isSplitValue) convertedValue = joinBytes(**(value->byteValue2), **(value->byteValue));
		else convertedValue = **(value->byteValue);
	}

	return convertedValue;
}

OpCycleCount* createOpCycleCount(int executeCycles, int dontExecuteCycles) {
	OpCycleCount *cycleCount = malloc(sizeof(OpCycleCount));

	cycleCount->executeCycles = executeCycles;
	cycleCount->dontExecuteCycles = dontExecuteCycles;

	return cycleCount;
}

InstructionMapping* createInstructionMappings(int numInstructions) {
	InstructionMapping *instructions = calloc(numInstructions, sizeof(InstructionMapping));
	return instructions;
}

