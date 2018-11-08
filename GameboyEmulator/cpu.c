
#include <assert.h>
#include <windows.h>
#include "cpu.h"
#include "cpu_load.h"
#include "cpu_jump.h"
#include "cpu_alu.h"
#include "ram.h"
#include "cpu_bitwise.h"
#include "cpu_cycles.h"
#include "cpu_interrupts.h"
#include "util.h"


void processInstruction(Hardware *hardware, InstructionMapping *mappings, int instruction);
int getImmediateWord(Hardware *hardware, int startAddress);
unsigned char getImmediateByte(Hardware *hardware, int address);
void populateComputedValues(Hardware *hardware, int nextPCAddressValue);
void populateOperationResults(Hardware *hardware, OperationResults *results, GBValue *operands1, GBValue *operands2, unsigned char previousFlags);
void processDestination(Hardware *hardware, int *result, GBValue *destination);
void processFlags(Hardware *hardware, GBValue *operand1, GBValue *operand2, int *result, FlagResult *flagResult);
void decimalAdjustValue(unsigned char *value, unsigned char *flags);
void transferOAM(Hardware *hardware, int startAddress, unsigned char* oamTable);

Hardware* initCPU(GameRom *rom, bool populateDefaultValues) {
	Hardware *hardware = createHardware();

	hardware->registers->PC = ROM_LOCATION_EXEC_START;
	hardware->rom = rom;

	if (populateDefaultValues == true) {
		hardware->registers->A = 0x1; // GBC = 0x11
		hardware->registers->F = 0xB0;
		hardware->registers->B = 0x0;
		hardware->registers->C = 0x13;
		hardware->registers->D = 0x00;
		hardware->registers->E = 0xD8;
		hardware->registers->H = 0x01;
		hardware->registers->L = 0x4D;
		hardware->registers->SP = 0xFFFE;
		hardware->registers->globalInterruptsEnabled = true;

		/**(hardware->ramAddresses[0xFF05)) = 0x00; //TIMA
		*(hardware->ramAddresses[0xFF06)) = 0x00; //TMA
		*(hardware->ramAddresses[0xFF07)) = 0x00; //TAC*/
		/*hardware->soundData->chan1_FrequencySweep = 0x80; //NR10
		hardware->soundData->chan1_PatternLength = 0xBF; //NR11
		hardware->soundData->chan1_VolumeSweep = 0xF3; //NR12
		hardware->soundData->chan1_FrequencyHighSettings = 0xBF; //NR14
		hardware->soundData->chan2_PatternLength = 0x3F; //NR21
		hardware->soundData->chan2_VolumeSweep = 0x00; //NR22
		hardware->soundData->chan2_FrequencyHighSettings = 0xBF; //NR24
		hardware->soundData->chan3_OnOff = 0x7F; //NR30
		hardware->soundData->chan3_Length = 0xFF; //NR31
		hardware->soundData->chan3_Volume = 0x9F; //NR32
		hardware->soundData->chan3_FrequencyLow = 0xBF; //NR33*/
		/*(hardware->ramAddresses[0xFF20)) = 0xFF; //NR41
		*(hardware->ramAddresses[0xFF21)) = 0x00; //NR42
		*(hardware->ramAddresses[0xFF22)) = 0x00; //NR43
		*(hardware->ramAddresses[0xFF23)) = 0xBF; //NR30*/
		hardware->soundData->masterVolume = 0x77; //NR50
		hardware->soundData->channelLeftRightEnable = 0xF3; //NR51 
		hardware->soundData->soundEnable = 0xF1; //0xF1 - GB, 0xF0 - SGB; NR52
		hardware->videoData->lcdControl = 0x91;
		hardware->videoData->lcdStatus = 0x1;
		hardware->videoData->scrollY = 0x00;
		hardware->videoData->scrollX = 0x00;
		hardware->videoData->lcdYCoord = SCREEN_TOTAL_LINES - 1;
		hardware->videoData->lcdYCompare = 0x00;
		hardware->videoData->bgPalette = 0xFC;
		hardware->videoData->objPalette0 = 0xFF; 
		hardware->videoData->objPalette1 = 0xFF;
		hardware->videoData->windowY = 0x00;
		hardware->videoData->windowX = 0x00;
		hardware->registers->enabledInterrupts = 0x00;
		hardware->ioData->joypadData = 0xCF;
		hardware->timerData->control = 0xF8;

		hardware->soundData->chan1_currentTick =
			hardware->soundData->chan2_currentTick =
			hardware->soundData->chan3_currentTick = 1;

		populateRamAddresses(hardware);
	}

	return hardware;
}

InstructionMapping* initInstructionMappings(Hardware *hardware) {
	InstructionMappingList *mappingList = calloc(1, sizeof(InstructionMappingList));
	populateInstructionMappingDefaultValues(hardware, mappingList);

	populateJumpInstructions(hardware, mappingList);
	populateLoadInstructions(hardware, mappingList);
	populateALUInstructions(hardware, mappingList);
	populateBitwiseInstructions(hardware, mappingList);
	populateCPUCycleCounts(mappingList);
	populateCPUOpSizes(mappingList);

	return mappingList;
}

void tickCPU(Hardware *hardware, InstructionMappingList *mappings) {

	if (hardware->cpuCyclesToWait <= 1) {		
		processInterrupts(hardware);

		if (!(hardware->pauseCPU)) {
			if (hardware->isOAMDMATriggered) {
				int dmaStartAddress = hardware->videoData->dmaTransfer << 8;
				transferOAM(hardware, dmaStartAddress, hardware->videoData->oamTable);
				hardware->isOAMDMATriggered = false;
			}

			int instruction = getRamAddressValue(hardware, hardware->ramAddresses[hardware->registers->PC]);

			//this ensures "CB xx" instructions get properly executed
			if (hardware->opCodePrefix != 0) {
				//__debugbreak();
				instruction |= hardware->opCodePrefix;
				hardware->opCodePrefix = 0;
			}

			processInstruction(hardware, &mappings->mappings[instruction], instruction);
		}
	}
	else {
		hardware->cpuCyclesToWait--;
	}
}

int debugaddress = -1;// 0x7cb; //0x241

void processInstruction(Hardware *hardware, InstructionMapping *mapping, int instruction) {
	//get the operation size to calculate the next PC address
	char opSize = mapping->sizeBytes;
	opSize = opSize < 1 ? 1 : opSize;

	int nextPCAddressValue = hardware->registers->PC + opSize;
	int cyclesToWait = 1;

		
	//should we process this operation?
	bool shouldExecute = true;

	FlagCondition *flagCondition = mapping->flagCondition;	

	if (flagCondition != NULL) {
		shouldExecute = ((hardware->registers->F & flagCondition->condition) == flagCondition->condition);
		if (flagCondition->negate) shouldExecute = !shouldExecute;
	}
	
	if (shouldExecute) {

		GBValue *operand1, *operand2, *destination;
		
		switch (instruction) {

		case OpCode_DAA:
			decimalAdjustValue(&hardware->registers->A, &hardware->registers->F);
			break;
			
		case OpCode_NOP:
			//do nothing
			break;

		case OpCode_PREFIX_CB:
			hardware->opCodePrefix = OPCODE_PREFIX_CB;
			break;

		case OpCode_DI:
			hardware->registers->globalInterruptsEnabled = false;
			break;

		case OpCode_EI:
			hardware->registers->globalInterruptsEnabled = true;
			break;

		case OpCode_HALT:
			//THROW_ERROR("Unsupported instruction HALT");
			//nextPCAddressValue = hardware->registers->PC;
			hardware->pauseCPU = true;
			break;

		case OpCode_STOP:
			THROW_ERROR("Unsupported instruction STOP");
			break;

		default:
			populateComputedValues(hardware, nextPCAddressValue);

			if (hardware->registers->PC == debugaddress) __debugbreak();

			//if (hardware->registers->PC == 0xC2B6) __debugbreak();
			//if (instruction == OpCode_SCF) __debugbreak();

			//get the operands
			operand1 = mapping->operand1;
			operand2 = mapping->operand2;

			//do the operation
			int resultValue;
			int *result = mapping->result;
			if (result != NULL) {
				populateOperationResults(hardware, hardware->operationResults, operand1, operand2, hardware->registers->F);				
			}
			else {
				resultValue = GBValueToInt(hardware, operand1);
				result = &resultValue;
			}
			
			//process flags
			FlagResult *flagResult = mapping->flagResult;
			processFlags(hardware, operand1, operand2, result, flagResult);
			
			//process program counter
			int *nextPC = mapping->nextPC;
			if (nextPC != NULL) nextPCAddressValue = *nextPC;
			
			//process stack pointer
			int *nextSP = mapping->nextSP;
			if (nextSP != NULL) hardware->registers->SP = *nextSP;

			//send the result to the right destination
			destination = mapping->destination;
			processDestination(hardware, result, destination);

			//special cases
			if (instruction == OpCode_LD_A_MEM_HLI || instruction == OpCode_LD_MEM_HLI_A) {
				hardware->computedValues->HL++;
				splitBytes(hardware->computedValues->HL, &(hardware->registers->L), &(hardware->registers->H));
			}
			else if (instruction == OpCode_LD_A_MEM_HLD || instruction == OpCode_LD_MEM_HLD_A) {
				hardware->computedValues->HL--;
				splitBytes(hardware->computedValues->HL, &(hardware->registers->L), &(hardware->registers->H));
			}
			else if (instruction == OpCode_RETI) {
				hardware->registers->globalInterruptsEnabled = true;
			}

			break;
		}
	}

	//set the next address instruction
	hardware->registers->PC = nextPCAddressValue;
	
	//how many cycles should this instruction take?
	if (mapping->cycleCount != NULL) {
		if (shouldExecute) cyclesToWait = mapping->cycleCount->executeCycles;
		else cyclesToWait = mapping->cycleCount->dontExecuteCycles;
	}
		
	hardware->cpuCyclesToWait = cyclesToWait < 1 ? 1 : cyclesToWait;
}

void populateComputedValues(Hardware *hardware, int nextPCAddressValue) {
	ComputedValues *cached = hardware->computedValues;

	cached->immediateByte = hardware->ramAddresses[hardware->registers->PC + 1];
	cached->immediateByte2 = hardware->ramAddresses[hardware->registers->PC + 2];

	int AF = joinBytes(hardware->registers->F, hardware->registers->A);
	int BC = joinBytes(hardware->registers->C, hardware->registers->B);
	int DE = joinBytes(hardware->registers->E, hardware->registers->D);
	cached->HL = joinBytes(hardware->registers->L, hardware->registers->H);

	unsigned char immediateByte = getRamAddressValue(hardware, cached->immediateByte);
	cached->immediateWord = joinBytes(immediateByte, getRamAddressValue(hardware, cached->immediateByte2));

	cached->memoryImmediateWord = hardware->ramAddresses[cached->immediateWord];
	cached->memoryImmediateWordPlusOne = hardware->ramAddresses[cached->immediateWord + 1];
	cached->highMemoryImmediateByte = hardware->ramAddresses[0xFF00 + immediateByte];
	cached->highMemoryC = hardware->ramAddresses[0xFF00 + hardware->registers->C];
	cached->memoryHL = hardware->ramAddresses[cached->HL];
	cached->memoryBC = hardware->ramAddresses[BC];
	cached->memoryDE = hardware->ramAddresses[DE];	
	cached->NextPCAddress = nextPCAddressValue;
	cached->NextPCAddressPlusImmediateByteSigned = nextPCAddressValue + ((char)cached->immediateByte);
	cached->SPMinusOne = hardware->registers->SP - 1;
	cached->SPMinusTwo = hardware->registers->SP - 2;
	cached->SPPlusOne = hardware->registers->SP + 1;
	cached->SPPlusTwo = hardware->registers->SP + 2;
	cached->stackValue = hardware->ramAddresses[hardware->registers->SP];
	cached->stackPlusOneValue = hardware->ramAddresses[cached->SPPlusOne];	
	cached->stackMinusOneValue = hardware->ramAddresses[cached->SPMinusOne];
	cached->stackMinusTwoValue = hardware->ramAddresses[cached->SPMinusTwo];

	
	if (cached->stackValue != NULL && cached->stackPlusOneValue != NULL 
		&& (cached->SPPlusOne >= 0 && cached->SPPlusOne < TOTAL_RAM_SIZE))
		cached->stackWordValue = joinBytes(getRamAddressValue(hardware, cached->stackValue), getRamAddressValue(hardware, cached->stackPlusOneValue));
	else
		cached->stackWordValue = NULL;
}


void populateOperationResults(Hardware *hardware, OperationResults *results, GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	
	if (operand1 != NULL) {
		int operand1Value = GBValueToInt(hardware, operand1);

		//swap nibbles
		int operand1High = operand1Value & 0xF0;
		int operand1Low = operand1Value & 0x0F;

		results->swapNibbles = (operand1High >> 4) | (operand1Low << 4);
		
		//shifts and rotates
		//start with the base shifts
		results->rotateLeft = results->rotateLeftCarry = 
			results->shiftLeft = (operand1Value << 1) & 0xFF;

		results->rotateRight = results->rotateRightCarry = 
			results->shiftRightLogical = results->shiftRightArithmetic = (operand1Value >> 1);
		
		//loop the ending bits around, for rotates
		results->rotateLeft |= ((operand1Value & 128) >> 7);
		results->rotateRight |= ((operand1Value & 1) << 7);

		//loop the carry bits around, for rotates through carry
		int carryBitRight = (previousFlags & FLAGS_CY) >> 4;
		int carryBitLeft = (previousFlags & FLAGS_CY) << 3;
		results->rotateLeftCarry |= carryBitRight;
		results->rotateRightCarry |= carryBitLeft;

		//change the sign if needed, for arithmetic shift
		results->shiftRightArithmetic |= (operand1Value & 128);

		if (operand2 != NULL) {
			int operand2Value = GBValueToInt(hardware, operand2);

			results->and = operand1Value & operand2Value;
			results->or = operand1Value | operand2Value;
			results->xor = operand1Value ^ operand2Value;
			results->add = operand1Value + operand2Value;
			results->subtract = operand1Value - operand2Value;

			int carry = ((previousFlags & FLAGS_CY) != 0) ? 1 : 0;
			results->addWithCarry = results->add + carry;
			results->subtractWithCarry = results->subtract - carry;


			if (operand1Value >= 0 && operand1Value <= 7) {
				int operand1Mask = (1 << operand1Value);

				results->getBit = operand2Value & operand1Mask;
				results->setBit = operand2Value | operand1Mask;
				results->resetBit = operand2Value & ~operand1Mask;
			}
			else {
				results->getBit = results->setBit = results->resetBit = NULL;
			}
		}		
	}
}

void writeLocation(Hardware *hardware, unsigned char *location, unsigned char value) {
	if (location == &hardware->registers->F) {
		//bits 0-3 are always zero
		*location = (value & 0xF0);
	}
	else {
		*location = value;
	}
}

void processDestination(Hardware *hardware, int *result, GBValue *destination) {
	if (result != NULL && destination != NULL) {
		int resultValue = *result;
		
		if (destination->type == GBVALUE_WORD) {
			**(destination->wordValue) = resultValue;
		}
		else if (destination->type == GBVALUE_SPLIT) {
			unsigned char leastSignificant, mostSignificant;
			splitBytes(resultValue, &leastSignificant, &mostSignificant);
			
			writeLocation(hardware, *(destination->byteValue2), leastSignificant);
			writeLocation(hardware, *(destination->byteValue), mostSignificant);
		}
		else if (destination->type == GBVALUE_BYTE || destination->type == GBVALUE_BYTE_SIGNED) {
			unsigned char byteResult = resultValue % 0x100;
			writeLocation(hardware, *(destination->byteValue), byteResult);
		}
		else if (destination->type == GBVALUE_RAM || destination->type == GBVALUE_RAM_SIGNED) {
			unsigned char byteResult = resultValue % 0x100;
			writeRamAddressValue(hardware, (*destination->ramValue), byteResult);
		}
		else if (destination->type == GBVALUE_RAM_SPLIT) {
			unsigned char leastSignificant, mostSignificant;
			splitBytes(resultValue, &leastSignificant, &mostSignificant);

			writeRamAddressValue(hardware, (*destination->ramValue2), leastSignificant);
			writeRamAddressValue(hardware, (*destination->ramValue), mostSignificant);
		}
	}
}

void processFlags(Hardware *hardware, GBValue *operand1, GBValue *operand2, int *result, FlagResult *flagResult) {
	if (flagResult != NULL && result != NULL) {
		int resultValue = *result;
		int operand1Value = GBValueToInt(hardware, operand1);
		int carry = 0;
		if (result == &hardware->operationResults->addWithCarry || result == &hardware->operationResults->subtractWithCarry) {
			carry = ((hardware->registers->F & FLAGS_CY) != 0) ? 1 : 0;
		}

		if (GBValueIsByte(operand1) && GBValueIsByte(operand2)) {			
			unsigned char byteResult = resultValue % 0x100;
			hardware->resultInfo->isZero = (byteResult == 0);
		}
		else {
			hardware->resultInfo->isZero = (resultValue == 0);
		}

		hardware->resultInfo->isAddCarry = (resultValue > 0xFF);
		hardware->resultInfo->isAddCarry16 = (resultValue > 0xFFFF);		
		hardware->resultInfo->isSubBorrow = (resultValue < 0);
		hardware->resultInfo->isOperand1Bit0Set = (operand1Value & 1) != 0;
		hardware->resultInfo->isOperand1Bit7Set = (operand1Value & 128) != 0;

		if (flagResult->isZero != NULL)		P_SET_BIT_IF(flagResult->isZero, FLAGS_Z, hardware->registers->F);
		if (flagResult->isSubtract != NULL)	P_SET_BIT_IF(flagResult->isSubtract, FLAGS_N, hardware->registers->F);
		if (flagResult->isCarry != NULL)	P_SET_BIT_IF(flagResult->isCarry, FLAGS_CY, hardware->registers->F);

		if (operand1 != NULL && operand2 != NULL) {
			int operand2Value = GBValueToInt(hardware, operand2);

			hardware->resultInfo->isAddHalfCarry = (((operand1Value & 0x0F) + (operand2Value & 0x0F) + carry) & 0x10) != 0;
			hardware->resultInfo->isAddHalfCarry16 = ((operand1Value & 0xFFF) + (operand2Value & 0xFFF) & 0x1000) != 0;
			hardware->resultInfo->isSubHalfBorrow = (((operand1Value & 0x0F) - (operand2Value & 0x0F) - carry)) < 0;
		}

		if (flagResult->isHalfCarry != NULL) P_SET_BIT_IF(flagResult->isHalfCarry, FLAGS_H, hardware->registers->F);
	}
}

int getImmediateWord(Hardware *hardware, int startAddress) {
	unsigned char value1 = getRamAddressValue(hardware, hardware->ramAddresses[startAddress]);
	unsigned char value2 = getRamAddressValue(hardware, hardware->ramAddresses[startAddress + 1]);
	return joinBytes(value1, value2);
}

unsigned char getImmediateByte(Hardware *hardware, int address) {
	return getRamAddressValue(hardware, hardware->ramAddresses[address]);
}

void decimalAdjustValue(unsigned char *value, unsigned char *flags) {
	unsigned char correction = 0;

	unsigned char carryFlag = 0;

	bool isFlagN = (*flags & FLAGS_N) == FLAGS_N,
		isFlagH = (*flags & FLAGS_H) == FLAGS_H,
		isFlagCY = (*flags & FLAGS_CY) == FLAGS_CY;

	if (isFlagH || (!isFlagN && (*value & 0xf) > 9)) {
		correction |= 0x6;
	}

	if (isFlagCY || (!isFlagN && *value > 0x99)) {
		correction |= 0x60;
		carryFlag = FLAGS_CY;
	}

	int result = (isFlagN) ? *value - correction : *value + correction;
	*value = result;
	
	unsigned char zeroFlagZ = (*value == 0) ? FLAGS_Z : 0;

	*flags  &= ~(FLAGS_H | FLAGS_Z | FLAGS_CY);
	*flags |= carryFlag | zeroFlagZ;
}

void transferOAM(Hardware *hardware, int startAddress, unsigned char* oamTable) {
	for (int i = 0; i < OAM_SIZE; i++) {
		oamTable[i] = getRamAddressValue(hardware, hardware->ramAddresses[startAddress]);
		startAddress++;
	}
}