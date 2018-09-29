
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
void populateCachedValues(Hardware *hardware, int nextPCAddressValue);
void processDestination(Hardware *hardware, int *result, GBValue *destination);
void processFlags(Hardware *hardware, GBValue *operand1, GBValue *operand2, int *result, FlagResult *flagResult);
void decimalAdjustValue(unsigned char *value, unsigned char *flags);
void transferOAM(Hardware *hardware, int startAddress, unsigned char* oamTable);


int operation_and(GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_or(GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_xor(GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_add(GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_subtract(GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_getBit(GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_setBit(GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_resetBit(GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_swapNibbles(GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_rotateLeft(GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_rotateRight(GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_rotateLeftCarry(GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_rotateRightCarry(GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_shiftLeft(GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_shiftRightLogical(GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_shiftRightArithmetic(GBValue *operand1, GBValue *operand2, unsigned char previousFlags);

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

		/**(getRamAddress(hardware, 0xFF05)) = 0x00; //TIMA
		*(getRamAddress(hardware, 0xFF06)) = 0x00; //TMA
		*(getRamAddress(hardware, 0xFF07)) = 0x00; //TAC
		*(getRamAddress(hardware, 0xFF10)) = 0x80; //NR10
		*(getRamAddress(hardware, 0xFF11)) = 0xBF; //NR11
		*(getRamAddress(hardware, 0xFF12)) = 0xF3; //NR12
		*(getRamAddress(hardware, 0xFF14)) = 0xBF; //NR14
		*(getRamAddress(hardware, 0xFF16)) = 0x3F; //NR21
		*(getRamAddress(hardware, 0xFF17)) = 0x00; //NR22
		*(getRamAddress(hardware, 0xFF19)) = 0xBF; //NR24
		*(getRamAddress(hardware, 0xFF1A)) = 0x7F; //NR30
		*(getRamAddress(hardware, 0xFF1B)) = 0xFF; //NR31
		*(getRamAddress(hardware, 0xFF1C)) = 0x9F; //NR32
		*(getRamAddress(hardware, 0xFF1E)) = 0xBF; //NR33
		*(getRamAddress(hardware, 0xFF20)) = 0xFF; //NR41
		*(getRamAddress(hardware, 0xFF21)) = 0x00; //NR42
		*(getRamAddress(hardware, 0xFF22)) = 0x00; //NR43
		*(getRamAddress(hardware, 0xFF23)) = 0xBF; //NR30
		*(getRamAddress(hardware, 0xFF24)) = 0x77; //NR50
		*(getRamAddress(hardware, 0xFF25)) = 0xF3; //NR51 */
		hardware->soundData->soundOnOff = 0xF1; //0xF1 - GB, 0xF0 - SGB; NR52
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
	}

	hardware->operations->and = operation_and;
	hardware->operations->or = operation_or;
	hardware->operations->xor = operation_xor;
	hardware->operations->add = operation_add;
	hardware->operations->subtract = operation_subtract;
	hardware->operations->getBit = operation_getBit;
	hardware->operations->setBit = operation_setBit;
	hardware->operations->resetBit = operation_resetBit;
	hardware->operations->swapNibbles = operation_swapNibbles;
	hardware->operations->rotateLeft = operation_rotateLeft;
	hardware->operations->rotateRight = operation_rotateRight;
	hardware->operations->rotateLeftCarry = operation_rotateLeftCarry;
	hardware->operations->rotateRightCarry = operation_rotateRightCarry;
	hardware->operations->shiftLeft = operation_shiftLeft;
	hardware->operations->shiftRightLogical = operation_shiftRightLogical;
	hardware->operations->shiftRightArithmetic = operation_shiftRightArithmetic;

	return hardware;
}

InstructionMapping* initInstructionMappings(Hardware *hardware) {
	InstructionMapping *mappings = calloc(NUM_OPCODES, sizeof(InstructionMapping));
	
	populateJumpInstructions(hardware, mappings);
	populateLoadInstructions(hardware, mappings);
	populateALUInstructions(hardware, mappings);
	populateBitwiseInstructions(hardware, mappings);
	populateCPUCycleCounts(mappings);
	populateCPUOpSizes(mappings);

	return mappings;
}

void tickCPU(Hardware *hardware, InstructionMapping *mappings) {

	if (hardware->cpuCyclesToWait <= 1) {

		processInterrupts(hardware);

		if (hardware->isOAMDMATriggered) {
			int dmaStartAddress = hardware->videoData->dmaTransfer << 8;
			transferOAM(hardware, dmaStartAddress, hardware->videoData->oamTable);
			hardware->isOAMDMATriggered = false;
		}

		int instruction = *getRamAddress(hardware, hardware->registers->PC);
		
		//this ensures "CB xx" instructions get properly executed
		if (hardware->opCodePrefix != 0) {
			//__debugbreak();
			instruction |= hardware->opCodePrefix;
			hardware->opCodePrefix = 0;
		}

		processInstruction(hardware, &mappings[instruction], instruction);
	}
	else {
		hardware->cpuCyclesToWait--;
	}
}

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
			THROW_ERROR("Unsupported instruction HALT");
			break;

		case OpCode_STOP:
			THROW_ERROR("Unsupported instruction STOP");
			break;

		default:
			populateCachedValues(hardware, nextPCAddressValue);

			//get the operands
			operand1 = mapping->operand1;
			operand2 = mapping->operand2;

			//do the operation
			int resultValue;
			OpResult *operation = mapping->operation;
			if (operation != NULL) {
				resultValue = (*operation)(operand1, operand2, hardware->registers->F);
			}
			else resultValue = GBValueToInt(operand1);
			
			//process flags
			FlagResult *flagResult = mapping->flagResult;
			processFlags(hardware, operand1, operand2, &resultValue, flagResult);
			
			//process program counter
			int *nextPC = mapping->nextPC;
			if (nextPC != NULL) nextPCAddressValue = *nextPC;
			
			//process stack pointer
			int *nextSP = mapping->nextSP;
			if (nextSP != NULL) hardware->registers->SP = *nextSP;

			//send the result to the right destination
			destination = mapping->destination;
			processDestination(hardware, &resultValue, destination);

			//special cases
			if (instruction == OpCode_LD_A_MEM_HLI || instruction == OpCode_LD_MEM_HLI_A) {
				hardware->cachedValues->HL++;
				splitBytes(hardware->cachedValues->HL, &(hardware->registers->L), &(hardware->registers->H));
			}
			else if (instruction == OpCode_LD_A_MEM_HLD || instruction == OpCode_LD_MEM_HLD_A) {
				hardware->cachedValues->HL--;
				splitBytes(hardware->cachedValues->HL, &(hardware->registers->L), &(hardware->registers->H));
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

void populateCachedValues(Hardware *hardware, int nextPCAddressValue) {
	CachedOpValues *cached = hardware->cachedValues;

	cached->immediateByte = getImmediateByte(hardware, hardware->registers->PC + 1);
	cached->immediateWord = getImmediateWord(hardware, hardware->registers->PC + 1);

	cached->AF = joinBytes(hardware->registers->F, hardware->registers->A);
	cached->BC = joinBytes(hardware->registers->C, hardware->registers->B);
	cached->DE = joinBytes(hardware->registers->E, hardware->registers->D);
	cached->HL = joinBytes(hardware->registers->L, hardware->registers->H);
	cached->APlusCarry = hardware->registers->A + ((hardware->registers->F & FLAGS_CY) == FLAGS_CY);
	cached->AMinusCarry = hardware->registers->A - ((hardware->registers->F & FLAGS_CY) == FLAGS_CY);

	cached->memoryImmediateWord = getRamAddress(hardware, cached->immediateWord);
	cached->highMemoryImmediateByte = getRamAddress(hardware, 0xFF00 + cached->immediateByte);
	cached->highMemoryC = getRamAddress(hardware, 0xFF00 + hardware->registers->C);
	cached->memoryHL = getRamAddress(hardware, cached->HL);
	cached->memoryBC = getRamAddress(hardware, cached->BC);
	cached->memoryDE = getRamAddress(hardware, cached->DE);	
	cached->NextPCAddress = nextPCAddressValue;
	cached->NextPCAddressPlusImmediateByteSigned = nextPCAddressValue + ((char)cached->immediateByte);
	cached->SPMinusOne = hardware->registers->SP - 1;
	cached->SPMinusTwo = hardware->registers->SP - 2;
	cached->SPPlusOne = hardware->registers->SP + 1;
	cached->SPPlusTwo = hardware->registers->SP + 2;
	cached->stackValue = getRamAddress(hardware, hardware->registers->SP);
	cached->stackPlusOneValue = getRamAddress(hardware, cached->SPPlusOne);	
	cached->stackMinusOneValue = getRamAddress(hardware, cached->SPMinusOne);
	cached->stackMinusTwoValue = getRamAddress(hardware, cached->SPMinusTwo);

	if (cached->stackValue != NULL && cached->stackPlusOneValue != NULL)
		cached->stackWordValue = joinBytes(*cached->stackValue, *cached->stackPlusOneValue);
	else
		cached->stackWordValue = NULL;
}


int operation_and(GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL && operand2 != NULL) return GBValueToInt(operand1) & GBValueToInt(operand2);
	return NULL;
}

int operation_or(GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL && operand2 != NULL) return GBValueToInt(operand1) | GBValueToInt(operand2);
	return NULL;
}

int operation_xor(GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL && operand2 != NULL) return GBValueToInt(operand1) ^ GBValueToInt(operand2);
	return NULL;
}

int operation_add(GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL && operand2 != NULL) return GBValueToInt(operand1) + GBValueToInt(operand2);
	return NULL;
}

int operation_subtract(GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL && operand2 != NULL) return GBValueToInt(operand1) - GBValueToInt(operand2);
	return NULL;
}

int operation_getBit(GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL && operand2 != NULL) {
		int operand1Value = GBValueToInt(operand1);
		int operand2Value = GBValueToInt(operand2);

		if (operand2Value >= 0 && operand2Value <= 7) {
			int operand1Mask = (1 << operand1Value);
			return operand2Value & operand1Mask;
		}
	}
	return NULL;
}

int operation_setBit(GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL && operand2 != NULL) {
		int operand1Value = GBValueToInt(operand1);
		int operand2Value = GBValueToInt(operand2);

		if (operand2Value >= 0 && operand2Value <= 7) {
			int operand1Mask = (1 << operand1Value);
			return operand2Value | operand1Mask;
		}	
	}
	return NULL;
}

int operation_resetBit(GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL && operand2 != NULL) {
		int operand1Value = GBValueToInt(operand1);
		int operand2Value = GBValueToInt(operand2);

		if (operand2Value >= 0 && operand2Value <= 7) {
			int operand1Mask = (1 << operand1Value);
			return operand2Value & ~operand1Mask;
		}
	}
	return NULL;
}

int operation_swapNibbles(GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL) {
		int operand1Value = GBValueToInt(operand1);

		//swap nibbles
		int operand1High = operand1Value & 0xF0;
		int operand1Low = operand1Value & 0x0F;

		return (operand1High >> 4) | (operand1Low << 4);
	}
	return NULL;
}

int operation_rotateLeft(GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL) {
		int operand1Value = GBValueToInt(operand1);

		//start with the base shift
		int result = (unsigned char)operand1Value << 1;

		//loop the ending bits around
		result |= ((operand1Value & 128) >> 7);

		return result;
	}
	return NULL;
}

int operation_rotateRight(GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL) {
		int operand1Value = GBValueToInt(operand1);

		//start with the base shifts
		int result = (unsigned char)operand1Value >> 1;

		//loop the ending bits around
		result |= ((operand1Value & 1) << 7);
		return result;
	}
	return NULL;
}

int operation_rotateLeftCarry(GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL) {
		int operand1Value = GBValueToInt(operand1);

		//start with the base shift
		int result = (unsigned char)operand1Value << 1;
		
		//loop the carry bits around
		int carryBitRight = (previousFlags & FLAGS_CY) >> 4;
		result |= carryBitRight;
		return result;
	}
	return NULL;
}

int operation_rotateRightCarry(GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL) {
		int operand1Value = GBValueToInt(operand1);

		//start with the base shift
		int result = (unsigned char)operand1Value >> 1;
		
		//loop the carry bits around
		int carryBitLeft = (previousFlags & FLAGS_CY) << 3;
		result |= carryBitLeft;
		return result;
	}
	return NULL;
}

int operation_shiftLeft(GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL) return ((unsigned char) GBValueToInt(operand1)) << 1;
	return NULL;
}

int operation_shiftRightLogical(GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL) return ((unsigned char) GBValueToInt(operand1)) >> 1;
	return NULL;
}

int operation_shiftRightArithmetic(GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL) {
		int operand1Value = GBValueToInt(operand1);
		int result = (unsigned char)operand1Value >> 1;
		result |= (operand1Value & 128);
		return result;
	}
	return NULL;
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
			
			writeRamLocation(hardware, *(destination->byteValue2), leastSignificant);
			writeRamLocation(hardware, *(destination->byteValue), mostSignificant);
		}
		else if (destination->type == GBVALUE_BYTE || destination->type == GBVALUE_BYTE_SIGNED) {
			writeRamLocation(hardware, *(destination->byteValue), (unsigned char)resultValue);
		}
	}
}

void processFlags(Hardware *hardware, GBValue *operand1, GBValue *operand2, int *result, FlagResult *flagResult) {
	if (flagResult != NULL && result != NULL) {
		int resultValue = *result;
		int operand1Value = GBValueToInt(operand1);

		hardware->resultInfo->isZero = (resultValue == 0);
		hardware->resultInfo->isAddCarry = (resultValue > 0xFF);
		hardware->resultInfo->isAddCarry16 = (resultValue > 0xFFFF);		
		hardware->resultInfo->isSubBorrow = (resultValue < 0);
		hardware->resultInfo->isOperand1Bit0Set = (operand1Value & 1) == 1;
		hardware->resultInfo->isOperand1Bit7Set = (operand1Value & 128) == 1;

		if (flagResult->isZero != NULL)		P_SET_BIT_IF(flagResult->isZero, FLAGS_Z, hardware->registers->F);
		if (flagResult->isSubtract != NULL)	P_SET_BIT_IF(flagResult->isSubtract, FLAGS_N, hardware->registers->F);
		if (flagResult->isCarry != NULL)	P_SET_BIT_IF(flagResult->isCarry, FLAGS_CY, hardware->registers->F);

		if (operand1 != NULL && operand2 != NULL) {
			int operand2Value = GBValueToInt(operand2);

			hardware->resultInfo->isAddHalfCarry = ((operand1Value & 0x0F) + (operand2Value & 0x0F) & 0x10) == 0x10;
			hardware->resultInfo->isAddHalfCarry16 = ((operand1Value & 0xFFF) + (operand2Value & 0xFFF) & 0x1000) == 0x1000;
			hardware->resultInfo->isSubHalfBorrow = ((operand1Value & 0x0F) - (operand2Value & 0x0F)) < 0;

			if (flagResult->isHalfCarry != NULL)		P_SET_BIT_IF(flagResult->isHalfCarry, FLAGS_H, hardware->registers->F);
		}
	}
}

int getImmediateWord(Hardware *hardware, int startAddress) {
	unsigned char *value1 = getRamAddress(hardware, startAddress);
	unsigned char *value2 = getRamAddress(hardware, startAddress + 1);
	return joinBytes(*value1, *value2);
}

unsigned char getImmediateByte(Hardware *hardware, int address) {
	return *(getRamAddress(hardware, address));
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
		oamTable[i] = *getRamAddress(hardware, startAddress);
		startAddress++;
	}
}