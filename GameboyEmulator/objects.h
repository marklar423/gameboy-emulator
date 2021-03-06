#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "constants.h"

#include <assert.h>
#include <intrin.h>

typedef struct _CartRomOnly {
	unsigned char ramBytes[ROM_ONLY_RAM_SIZE];
} CartRomOnly;

typedef struct _CartMBC1 {
	unsigned char romBank, ramBank;
	unsigned char ramBytes[MBC1_RAM_SIZE];
	bool ramEnable, isRamBankMode;
} CartMBC1;
typedef struct _GameRom {
	unsigned char *romBytes;
	long romLength;
	char gameName[15];
	CartType cartType;

	CartRomOnly *cartRomOnly;
	CartMBC1 *cartMBC1;

	bool hasExternalRam, hasExternalBattery;
} GameRom;

typedef struct _Config {
	char *romPath;
} Config;


typedef struct _Registers {
	unsigned char A, B, C, D, E, H, L, F;
	int SP, PC;
	bool globalInterruptsEnabled;
	unsigned char enabledInterrupts, requestedInterrupts;
} Registers;

typedef struct _VideoData {
	unsigned char lcdControl, lcdStatus, lcdYCoord, lcdYCompare;
	unsigned char scrollY, scrollX, windowY, windowX;
	unsigned char dmaTransfer, bgPalette, objPalette0, objPalette1;
	unsigned char tileData[VRAM_TOTAL_TILES_SIZE], bgMap1[VRAM_BG_MAP_1_SIZE], bgMap2[VRAM_BG_MAP_2_SIZE];
	unsigned char oamTable[OAM_SIZE];
	unsigned char * lineVisibleSprites[VISIBLE_SPRITES_PER_LINE];
	PixelColor framePixels[SCREEN_HEIGHT][SCREEN_WIDTH]; //2D array, framePixels[y][x], size is framePixels[SCREEN_HEIGHT][SCREEN_WIDTH]
} VideoData;

typedef struct _AudioSample {
	float leftSample, rightSample;
} AudioSample;

typedef struct _SoundData {
	unsigned char masterVolume, channelLeftRightEnable, soundEnable;

	unsigned char chan1_FrequencySweep, chan1_PatternLength, chan1_VolumeSweep;
	unsigned char chan1_FrequencyLow, chan1_FrequencyHighSettings;
	int chan1_currentTick, chan1_VolumeCounter, chan1_lengthCounter;

	unsigned char chan2_PatternLength, chan2_VolumeSweep;
	unsigned char chan2_FrequencyLow, chan2_FrequencyHighSettings;
	int chan2_currentTick, chan2_VolumeCounter, chan2_lengthCounter;

	unsigned char chan3_OnOff, chan3_Length, chan3_Volume;
	unsigned char chan3_FrequencyLow, chan3_FrequencyHighSettings;
	unsigned char chan3_WaveData[SOUND_WAVE_PATTERN_BYTES];
	int chan3_currentTick, chan3_lengthCounter;

	unsigned char chan4_VolumeSweep, chan4_polynomialCounter, chan4_length, chan4_settings;
	int chan4_currentTick, chan4_lastRNGValue;
	float chan4_polynomialShiftCount;
	int chan4_VolumeCounter, chan4_lengthCounter;
} SoundData;

typedef struct _TimerData {
	unsigned char divider, counter, modulo, control;
	int cycleAccumulator, dividerCycleAccumulator;
} TimerData;

typedef struct _IOData {
	unsigned char joypadData, serialTransferData, serialTransferControl;
} IOData;

typedef struct _InputState {
	bool isUpPressed, isDownPressed, isRightPressed, isLeftPressed;
	bool isAPressed, isBPressed, isStartPressed, isSelectPressed;
} InputState;

typedef enum _GBValueType {
	GBVALUE_BYTE = 0,
	GBVALUE_BYTE_SIGNED = 1,
	GBVALUE_WORD = 2,
	GBVALUE_SPLIT = 3
} GBValueType;

typedef struct _GBValue {
	GBValueType type;
	unsigned char **byteValue;
	unsigned char **byteValue2; //used with split bytes. byteValue2 is less significant than byteValue
	int **wordValue;
} GBValue;

typedef struct _ComputedValues {
	unsigned char immediateByte;
	int immediateWord;
	unsigned char *highMemoryImmediateByte, *memoryImmediateWord, *memoryImmediateWordPlusOne;
	unsigned char *highMemoryC;
	unsigned char *memoryHL, *memoryBC, *memoryDE;
	int AF, BC, DE, HL;
	int NextPCAddress, NextPCAddressPlusImmediateByteSigned;
	int SPPlusOne, SPPlusTwo, SPMinusOne, SPMinusTwo;
	unsigned char *stackValue; //value on top of stack
	unsigned char *stackPlusOneValue; //second-to-top value in stack
	unsigned char *stackMinusOneValue; //one value beyond top of stack (new value)
	unsigned char *stackMinusTwoValue; //two values beyond top of stack (new value)
	int stackWordValue;
} ComputedValues;

typedef struct _OperationResults {
	int and, or, xor, add, subtract, addWithCarry, subtractWithCarry;
	int getBit, setBit, resetBit, swapNibbles;
	int rotateLeft, rotateRight, rotateLeftCarry, rotateRightCarry;
	int shiftLeft, shiftRightLogical, shiftRightArithmetic;
} OperationResults;

typedef struct _ResultInfo {
	bool isZero, isAddHalfCarry, isAddCarry, isSubHalfBorrow, isSubBorrow;
	bool isAddHalfCarry16, isAddCarry16;
	bool isOperand1Bit0Set, isOperand1Bit7Set;
} ResultInfo;

typedef struct _Hardware {
	GameRom *rom;
	Registers *registers;
	VideoData *videoData;
	SoundData *soundData;
	IOData *ioData;
	ComputedValues *computedValues;
	OperationResults *operationResults;
	ResultInfo *resultInfo;
	InputState *inputState;
	TimerData *timerData;
	unsigned char workRam[WORK_RAM_SIZE], highRam[HRAM_SIZE];
	int cpuCyclesToWait, ppuCyclesToWait;
	OpCode opCodePrefix;
	bool isOAMDMATriggered, pauseCPU;
	unsigned char * ramAddresses[TOTAL_RAM_SIZE];
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

GBValue* createGBValue(GBValueType type, unsigned char *byteValue, unsigned char *byteValue2, int *wordValue);
GBValue* createGBPointerValue(GBValueType type, unsigned char **byteValuePointer, unsigned char **byteValue2Pointer, int **wordValuePointer);
int GBValueToInt(GBValue *value);
bool GBValueIsByte(GBValue *value);

#define createGBByteValue(byteValue) createGBValue(GBVALUE_BYTE, byteValue, NULL, NULL)
#define createGBByteValueSigned(signedByteValue) createGBValue(GBVALUE_BYTE_SIGNED, signedByteValue, NULL, NULL)
#define createGBWordValue(wordValue) createGBValue(GBVALUE_WORD, NULL, NULL, wordValue)
#define createGBSplitByteValue(byteValue, byteValue2) createGBValue(GBVALUE_SPLIT, byteValue, byteValue2, NULL)

#define createGBBytePointer(byteValue) createGBPointerValue(GBVALUE_BYTE, byteValue, NULL, NULL)
#define createGBWordPointer(wordValue) createGBPointerValue(GBVALUE_WORD, NULL, NULL, wordValue)
#define createGBSplitBytePointer(byteValue, byteValue2) createGBPointerValue(GBVALUE_SPLIT, byteValue, byteValue2, NULL)

FlagResult* createFlagResult(bool *isZero, bool *isSubtract, bool *isHalf, bool *isCarry);
FlagCondition* createFlagCondition(char condition, bool negate);

OpCycleCount* createOpCycleCount(int executeCycles, int dontExecuteCycles);

InstructionMapping* createInstructionMappings(int numInstructions);

Hardware* createHardware();