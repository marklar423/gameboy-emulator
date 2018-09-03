
#include "objects.h"

GameRom* createGameRom(unsigned char *romBytes, long romLength) {
	GameRom *rom = malloc(sizeof(GameRom));
	rom->romBytes = romBytes;
	rom->romLength = romLength;

	return rom;
}

GBValue* createGBValue(bool is16Bit, bool isSplitValue, bool isByteSigned, char *byteValue, char *byteValue2, int *wordValue) {
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

	return createGBPointerValue(is16Bit, isSplitValue, isByteSigned, byteValuePointer, byteValue2Pointer, wordValuePointer);
}


GBValue* createGBPointerValue(bool is16Bit, bool isSplitValue, bool isByteSigned, char **byteValuePointer, char **byteValue2Pointer, int **wordValuePointer) {
	GBValue *value = malloc(sizeof(GBValue));

	value->isWordValue = is16Bit;
	value->isSplitValue = isSplitValue;
	value->isByteSigned = isByteSigned;
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
		else convertedValue = (value->isByteSigned) ? (char) **(value->byteValue) : **(value->byteValue);
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
	hardware->cachedResults = calloc(1, sizeof(CachedOpResults));
	hardware->resultInfo = calloc(1, sizeof(ResultInfo));
	hardware->ioData = calloc(1, sizeof(IOData));

	int workRamSize = RAM_LOCATION_WORK_RAM_SWITCHABLE_END - RAM_LOCATION_WORK_RAM_FIXED + 1;
	hardware->workRam = calloc(workRamSize, sizeof(unsigned char));

	int highRamSize = RAM_LOCATION_HRAM_END - RAM_LOCATION_HRAM + 1;
	hardware->highRam = calloc(highRamSize, sizeof(unsigned char));
	
	hardware->videoData = calloc(1, sizeof(VideoData));

	int vramSize = RAM_LOCATION_VRAM_END - RAM_LOCATION_VRAM + 1;
	hardware->videoData->vRam = calloc(vramSize, sizeof(unsigned char));

	int oamSize = RAM_LOCATION_OAM_END - RAM_LOCATION_OAM + 1;
	hardware->videoData->oamTable = calloc(oamSize, sizeof(unsigned char));
	hardware->videoData->lineVisibleSprites = calloc(VISIBLE_SPRITES_PER_LINE, sizeof(unsigned char*));

	hardware->soundData = calloc(1, sizeof(SoundData));

	return hardware;
}