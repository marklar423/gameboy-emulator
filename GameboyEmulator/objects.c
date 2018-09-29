
#include "objects.h"

GameRom* createGameRom(unsigned char *romBytes, long romLength) {
	GameRom *rom = malloc(sizeof(GameRom));
	rom->romBytes = romBytes;
	rom->romLength = romLength;

	return rom;
}

GBValue* createGBValue(GBValueType type, char *byteValue, char *byteValue2, int *wordValue) {
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

	return createGBPointerValue(type, byteValuePointer, byteValue2Pointer, wordValuePointer);
}


GBValue* createGBPointerValue(GBValueType type, char **byteValuePointer, char **byteValue2Pointer, int **wordValuePointer) {
	GBValue *value = malloc(sizeof(GBValue));

	value->type = type;
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
		switch (value->type) {
		case GBVALUE_WORD:
			convertedValue = **(value->wordValue);
			break;
		case GBVALUE_SPLIT:
			convertedValue = joinBytes(**(value->byteValue2), **(value->byteValue));
			break;
		case GBVALUE_BYTE:
			convertedValue = **(value->byteValue);
			break;
		case GBVALUE_BYTE_SIGNED:
			convertedValue = (char) **(value->byteValue);
			break;
		}
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


Hardware* createHardware() {
	Hardware *hardware = calloc(1, sizeof(Hardware));

	hardware->registers = calloc(1, sizeof(Registers));
	hardware->registers->PC = ROM_LOCATION_EXEC_START;
	hardware->cachedValues = calloc(1, sizeof(CachedOpValues));
	hardware->operations = calloc(1, sizeof(Operations));
	hardware->resultInfo = calloc(1, sizeof(ResultInfo));
	hardware->ioData = calloc(1, sizeof(IOData));	
	hardware->videoData = calloc(1, sizeof(VideoData));	
	hardware->soundData = calloc(1, sizeof(SoundData));
	hardware->inputState = calloc(1, sizeof(InputState));

	return hardware;
}