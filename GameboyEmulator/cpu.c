
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
void processDestination(Hardware *hardware, int *result, GBValue *destination);
void processFlags(Hardware *hardware, GBValue *operand1, GBValue *operand2, int *result, FlagResult *flagResult);
void decimalAdjustValue(unsigned char *value, unsigned char *flags);
void transferOAM(Hardware *hardware, int startAddress, unsigned char* oamTable);


int operation_and(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_or(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_xor(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_add(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_subtract(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_getBit(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_setBit(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_resetBit(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_swapNibbles(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_rotateLeft(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_rotateRight(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_rotateLeftCarry(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_rotateRightCarry(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_shiftLeft(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_shiftRightLogical(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags);
int operation_shiftRightArithmetic(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags);

unsigned char computed_immediateByte(Hardware *hardware);
int computed_immediateWord(Hardware *hardware);
unsigned char computed_highMemoryImmediateByte(Hardware *hardware);
unsigned char computed_memoryImmediateWord(Hardware *hardware);
unsigned char computed_highMemoryC(Hardware *hardware);
unsigned char computed_memoryHL(Hardware *hardware);
unsigned char computed_memoryBC(Hardware *hardware);
unsigned char computed_memoryDE(Hardware *hardware);
int computed_AF(Hardware *hardware);
int computed_BC(Hardware *hardware);
int computed_DE(Hardware *hardware);
int computed_HL(Hardware *hardware);
unsigned char computed_APlusCarry(Hardware *hardware);
unsigned char computed_AMinusCarry(Hardware *hardware);
int computed_NextPCAddressPlusImmediateByteSigned(Hardware *hardware);
int computed_SPPlusOne(Hardware *hardware);
int computed_SPPlusTwo(Hardware *hardware);
int computed_SPMinusOne(Hardware *hardware);
int computed_SPMinusTwo(Hardware *hardware);
unsigned char computed_stackValue(Hardware *hardware); //value on top of stack
unsigned char computed_stackPlusOneValue(Hardware *hardware); //second-to-top value in stack
unsigned char computed_stackMinusOneValue(Hardware *hardware); //one value beyond top of stack (new value)
unsigned char computed_stackMinusTwoValue(Hardware *hardware); //two values beyond top of stack (new value)
int computed_stackWordValue(Hardware *hardware);

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


	hardware->computedFunctions->immediateByte = computed_immediateByte;
	hardware->computedFunctions->immediateWord = computed_immediateWord;
	hardware->computedFunctions->highMemoryImmediateByte = computed_highMemoryImmediateByte;
	hardware->computedFunctions->memoryImmediateWord = computed_memoryImmediateWord;
	hardware->computedFunctions->highMemoryC = computed_highMemoryC;
	hardware->computedFunctions->memoryHL = computed_memoryHL;
	hardware->computedFunctions->memoryBC = computed_memoryBC;
	hardware->computedFunctions->memoryDE = computed_memoryDE;
	hardware->computedFunctions->AF = computed_AF;
	hardware->computedFunctions->BC = computed_BC;
	hardware->computedFunctions->DE = computed_DE;
	hardware->computedFunctions->HL = computed_HL;
	hardware->computedFunctions->APlusCarry = computed_APlusCarry;
	hardware->computedFunctions->AMinusCarry = computed_AMinusCarry;
	hardware->computedFunctions->NextPCAddressPlusImmediateByteSigned = computed_NextPCAddressPlusImmediateByteSigned;
	hardware->computedFunctions->SPPlusOne = computed_SPPlusOne;
	hardware->computedFunctions->SPPlusTwo = computed_SPPlusTwo;
	hardware->computedFunctions->SPMinusOne = computed_SPMinusOne;
	hardware->computedFunctions->SPMinusTwo = computed_SPMinusTwo;
	hardware->computedFunctions->stackValue =  computed_stackValue;
	hardware->computedFunctions->stackPlusOneValue =  computed_stackPlusOneValue;
	hardware->computedFunctions->stackMinusOneValue = computed_stackMinusOneValue;
	hardware->computedFunctions->stackMinusTwoValue =  computed_stackMinusTwoValue;
	hardware->computedFunctions->stackWordValue = computed_stackWordValue;

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
			hardware->nextPCAddress = nextPCAddressValue;

			//get the operands
			operand1 = mapping->operand1;
			operand2 = mapping->operand2;

			//do the operation
			int resultValue;
			OperationFunction *operation = mapping->operation;
			if (operation != NULL) {
				resultValue = (*operation)(operand1, operand2, hardware->registers->F);
			}
			else resultValue = GBValueToInt(hardware, operand1);
			
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
				int HL = hardware->computedFunctions->HL(hardware);
				HL++;
				splitBytes(hardware->computedFunctions->HL, &(hardware->registers->L), &(hardware->registers->H));
			}
			else if (instruction == OpCode_LD_A_MEM_HLD || instruction == OpCode_LD_MEM_HLD_A) {
				int HL = hardware->computedFunctions->HL(hardware);
				HL--;
				splitBytes(hardware->computedFunctions->HL, &(hardware->registers->L), &(hardware->registers->H));
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

unsigned char computed_immediateByte(Hardware *hardware){
	return getImmediateByte(hardware, hardware->registers->PC + 1);
}

int computed_immediateWord(Hardware *hardware){
	return getImmediateWord(hardware, hardware->registers->PC + 1);
}

unsigned char computed_highMemoryImmediateByte(Hardware *hardware){
	return *getRamAddress(hardware, 0xFF00 + hardware->computedFunctions->immediateByte(hardware));
}

unsigned char computed_memoryImmediateWord(Hardware *hardware){
	return *getRamAddress(hardware, hardware->computedFunctions->immediateWord(hardware));
}

unsigned char computed_highMemoryC(Hardware *hardware){
	return *getRamAddress(hardware, 0xFF00 + hardware->registers->C);
}

unsigned char computed_memoryHL(Hardware *hardware){
	return *getRamAddress(hardware, hardware->computedFunctions->HL(hardware));
}

unsigned char computed_memoryBC(Hardware *hardware){
	return *getRamAddress(hardware, hardware->computedFunctions->BC(hardware));
}

unsigned char computed_memoryDE(Hardware *hardware){
	return *getRamAddress(hardware, hardware->computedFunctions->DE(hardware));
}

int computed_AF(Hardware *hardware){
	return joinBytes(hardware->registers->F, hardware->registers->A);
}

int computed_BC(Hardware *hardware){
	return joinBytes(hardware->registers->C, hardware->registers->B);
}

int computed_DE(Hardware *hardware){
	return joinBytes(hardware->registers->E, hardware->registers->D);
}

int computed_HL(Hardware *hardware){
	return joinBytes(hardware->registers->L, hardware->registers->H);
}

unsigned char computed_APlusCarry(Hardware *hardware){
	return hardware->registers->A + ((hardware->registers->F & FLAGS_CY) == FLAGS_CY);
}

unsigned char computed_AMinusCarry(Hardware *hardware){
	return hardware->registers->A - ((hardware->registers->F & FLAGS_CY) == FLAGS_CY);
}

int computed_NextPCAddressPlusImmediateByteSigned(Hardware *hardware){
	return hardware->nextPCAddress + ((char)hardware->computedFunctions->immediateByte(hardware));
}

int computed_SPPlusOne(Hardware *hardware){
	return hardware->registers->SP + 1;
}

int computed_SPPlusTwo(Hardware *hardware){
	return hardware->registers->SP + 2;
}

int computed_SPMinusOne(Hardware *hardware){
	return hardware->registers->SP - 1;
}

int computed_SPMinusTwo(Hardware *hardware){
	return  hardware->registers->SP - 2;
}

unsigned char computed_stackValue(Hardware *hardware){
	return *getRamAddress(hardware, hardware->registers->SP);
}
 //value on top of stack
unsigned char computed_stackPlusOneValue(Hardware *hardware){
	return *getRamAddress(hardware, hardware->computedFunctions->SPPlusOne(hardware));
}
 //second-to-top value in stack
unsigned char computed_stackMinusOneValue(Hardware *hardware){
	return *getRamAddress(hardware, hardware->computedFunctions->SPMinusOne(hardware));
}
 //one value beyond top of stack (new value)
unsigned char computed_stackMinusTwoValue(Hardware *hardware){
	return *getRamAddress(hardware, hardware->computedFunctions->SPMinusTwo(hardware));
}
 //two values beyond top of stack (new value)
int computed_stackWordValue(Hardware *hardware){
	unsigned char stackValue = hardware->computedFunctions->stackValue(hardware);
	unsigned char stackPlusOneValue = hardware->computedFunctions->stackPlusOneValue(hardware);

	if (stackValue != NULL && stackPlusOneValue != NULL)
		return joinBytes(stackValue, stackPlusOneValue);

	return NULL;
}


int operation_and(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL && operand2 != NULL) return GBValueToInt(hardware, operand1) & GBValueToInt(hardware, operand2);
	return NULL;
}

int operation_or(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL && operand2 != NULL) return GBValueToInt(hardware, operand1) | GBValueToInt(hardware, operand2);
	return NULL;
}

int operation_xor(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL && operand2 != NULL) return GBValueToInt(hardware, operand1) ^ GBValueToInt(hardware, operand2);
	return NULL;
}

int operation_add(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL && operand2 != NULL) return GBValueToInt(hardware, operand1) + GBValueToInt(hardware, operand2);
	return NULL;
}

int operation_subtract(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL && operand2 != NULL) return GBValueToInt(hardware, operand1) - GBValueToInt(hardware, operand2);
	return NULL;
}

int operation_getBit(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL && operand2 != NULL) {
		int operand1Value = GBValueToInt(hardware, operand1);
		int operand2Value = GBValueToInt(hardware, operand2);

		if (operand2Value >= 0 && operand2Value <= 7) {
			int operand1Mask = (1 << operand1Value);
			return operand2Value & operand1Mask;
		}
	}
	return NULL;
}

int operation_setBit(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL && operand2 != NULL) {
		int operand1Value = GBValueToInt(hardware, operand1);
		int operand2Value = GBValueToInt(hardware, operand2);

		if (operand2Value >= 0 && operand2Value <= 7) {
			int operand1Mask = (1 << operand1Value);
			return operand2Value | operand1Mask;
		}	
	}
	return NULL;
}

int operation_resetBit(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL && operand2 != NULL) {
		int operand1Value = GBValueToInt(hardware, operand1);
		int operand2Value = GBValueToInt(hardware, operand2);

		if (operand2Value >= 0 && operand2Value <= 7) {
			int operand1Mask = (1 << operand1Value);
			return operand2Value & ~operand1Mask;
		}
	}
	return NULL;
}

int operation_swapNibbles(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL) {
		int operand1Value = GBValueToInt(hardware, operand1);

		//swap nibbles
		int operand1High = operand1Value & 0xF0;
		int operand1Low = operand1Value & 0x0F;

		return (operand1High >> 4) | (operand1Low << 4);
	}
	return NULL;
}

int operation_rotateLeft(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL) {
		int operand1Value = GBValueToInt(hardware, operand1);

		//start with the base shift
		int result = (unsigned char)operand1Value << 1;

		//loop the ending bits around
		result |= ((operand1Value & 128) >> 7);

		return result;
	}
	return NULL;
}

int operation_rotateRight(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL) {
		int operand1Value = GBValueToInt(hardware, operand1);

		//start with the base shifts
		int result = (unsigned char)operand1Value >> 1;

		//loop the ending bits around
		result |= ((operand1Value & 1) << 7);
		return result;
	}
	return NULL;
}

int operation_rotateLeftCarry(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL) {
		int operand1Value = GBValueToInt(hardware, operand1);

		//start with the base shift
		int result = (unsigned char)operand1Value << 1;
		
		//loop the carry bits around
		int carryBitRight = (previousFlags & FLAGS_CY) >> 4;
		result |= carryBitRight;
		return result;
	}
	return NULL;
}

int operation_rotateRightCarry(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL) {
		int operand1Value = GBValueToInt(hardware, operand1);

		//start with the base shift
		int result = (unsigned char)operand1Value >> 1;
		
		//loop the carry bits around
		int carryBitLeft = (previousFlags & FLAGS_CY) << 3;
		result |= carryBitLeft;
		return result;
	}
	return NULL;
}

int operation_shiftLeft(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL) return ((unsigned char) GBValueToInt(hardware, operand1)) << 1;
	return NULL;
}

int operation_shiftRightLogical(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL) return ((unsigned char) GBValueToInt(hardware, operand1)) >> 1;
	return NULL;
}

int operation_shiftRightArithmetic(Hardware *hardware, GBValue *operand1, GBValue *operand2, unsigned char previousFlags) {
	if (operand1 != NULL) {
		int operand1Value = GBValueToInt(hardware, operand1);
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
		int operand1Value = GBValueToInt(hardware, operand1);

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
			int operand2Value = GBValueToInt(hardware, operand2);

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