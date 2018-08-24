
#include <assert.h>
#include <windows.h>
#include "cpu.h"
#include "cpu_load.h"
#include "cpu_jump.h"
#include "cpu_alu.h"
#include "cpu_ram.h"
#include "util.h"

Hardware* initCpu(GameRom *rom, bool populateDefaultValues) {
	Hardware *hardware = calloc(1, sizeof(Hardware));

	hardware->rom = rom;
	hardware->registers = calloc(1, sizeof(Registers));
	hardware->registers->PC = ROM_LOCATION_EXEC_START;
	hardware->cachedValues = calloc(1, sizeof(CachedOpValues));
	hardware->cachedResults = calloc(1, sizeof(CachedOpResults));
	hardware->resultInfo = calloc(1, sizeof(ResultInfo));

	int ramSize = RAM_LOCATION_WORK_RAM_SWITCHABLE_END - RAM_LOCATION_WORK_RAM_FIXED + 1;
	hardware->workRam = calloc(ramSize, sizeof(unsigned char));

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
	}

	return hardware;
}

OperandMappings* initMappings(Hardware *hardware) {
	OperandMappings *mappings = malloc(sizeof(OperandMappings));

	mappings->operands1 = calloc(NUM_OPCODES, sizeof(GBValue *));
	mappings->operands2 = calloc(NUM_OPCODES, sizeof(GBValue *));
	mappings->results = calloc(NUM_OPCODES, sizeof(int *));
	mappings->destinations = calloc(NUM_OPCODES, sizeof(GBValue *));
	mappings->nextPCs = calloc(NUM_OPCODES, sizeof(int *));
	mappings->nextSPs = calloc(NUM_OPCODES, sizeof(int *));
	mappings->flagConditions = calloc(NUM_OPCODES, sizeof(FlagCondition *));
	mappings->flagResults = calloc(NUM_OPCODES, sizeof(FlagResult *));
	mappings->opSizeBytes = calloc(NUM_OPCODES, sizeof(char));

	initJumpFlagConditions(hardware, mappings->flagConditions);

	initLoadOperands1(hardware, mappings->operands1);
	initALUOperands1(hardware, mappings->operands1);
	initALUOperands2(hardware, mappings->operands2);

	initALUResults(hardware, mappings->results);

	initLoadDestinations(hardware, mappings->destinations);
	initALUDestinations(hardware, mappings->destinations);

	initLoadOpSizes(hardware, mappings->opSizeBytes);
	initALUOpSizes(hardware, mappings->opSizeBytes);
	initJumpOpSizes(hardware, mappings->opSizeBytes);

	initJumpNextPC(hardware, mappings->nextPCs);

	initALUFlagResults(hardware, mappings->flagResults);

	return mappings;
}

void tickCpu(Hardware *hardware, OperandMappings *mappings) {
	unsigned char* instruction = getRamAddress(hardware, hardware->registers->PC);
	processInstruction(hardware, mappings, instruction);
}

void processInstruction(Hardware *hardware, OperandMappings *mappings, const unsigned char *instruction) {
	//get the operation size to calculate the next PC address
	char opSize = mappings->opSizeBytes[*instruction];
	opSize = opSize < 1 ? 1 : opSize;

	int nextPCAddressValue = hardware->registers->PC + opSize;
	
	populateCachedValues(hardware, nextPCAddressValue);

	//should we process this operation?
	bool shouldExecute = true;

	FlagCondition *flagCondition = mappings->flagConditions[*instruction];	

	if (flagCondition != NULL) {
		shouldExecute = ((hardware->registers->F & flagCondition->condition) == flagCondition->condition);
		if (flagCondition->negate) shouldExecute = !shouldExecute;
	}

	if (shouldExecute == true) {

		GBValue *operand1, *operand2, *destination;
		
		switch (*instruction) {
		case OpCode_NOP:
			//do nothing
			break;

		default:
			//get the operands
			operand1 = mappings->operands1[*instruction];
			operand2 = mappings->operands2[*instruction];

			//do the operation
			int resultValue;
			int *result = mappings->results[*instruction];
			if (result != NULL) {
				populateCachedResults(hardware->cachedResults, operand1, operand2);
				resultValue = *result;
			}
			else resultValue = GBValueToInt(operand1);
			
			//process flags
			FlagResult *flagResult = mappings->flagResults[*instruction];
			processFlags(hardware, operand1, operand2, &resultValue, flagResult);
			
			//process program counter
			int *nextPC = mappings->nextPCs[*instruction];
			if (nextPC != NULL) nextPCAddressValue = *nextPC;
			
			//process stack pointer
			int *nextSP = mappings->nextSPs[*instruction];
			if (nextSP != NULL) hardware->registers->SP = *nextSP;

			//send the result to the right destination
			destination = mappings->destinations[*instruction];
			processDestination(hardware, &resultValue, destination);

			//special cases
			if (*instruction == OpCode_LD_A_MEM_HLI || *instruction == OpCode_LD_MEM_HLI_A) {
				hardware->cachedValues->HL++;
				splitBytes(&(hardware->cachedValues->HL), &(hardware->registers->L), &(hardware->registers->H));
			}
			else if (*instruction == OpCode_LD_A_MEM_HLD || *instruction == OpCode_LD_MEM_HLD_A) {
				hardware->cachedValues->HL--;
				splitBytes(&(hardware->cachedValues->HL), &(hardware->registers->L), &(hardware->registers->H));
			}

			/*sprintf_s(log, 50, "Unknown opcode %X\n", *instruction);
			OutputDebugString(log);
			THROW_ERROR("Unkown Opcode");*/
			break;
		}
	}

	hardware->registers->PC = nextPCAddressValue;
}

void populateCachedValues(Hardware *hardware, int nextPCAddressValue) {
	CachedOpValues *cached = hardware->cachedValues;

	getImmediateValue(hardware, hardware->registers->PC + 1, &(cached->immediateByte));
	getImmediateValue16(hardware, hardware->registers->PC + 1, &(cached->immediateWord));

	joinBytes(&(hardware->registers->C), &(hardware->registers->B), &(cached->BC));
	joinBytes(&(hardware->registers->E), &(hardware->registers->D), &(cached->DE));
	joinBytes(&(hardware->registers->L), &(hardware->registers->H), &(cached->HL));
	
	cached->memoryImmediateWord = getRamAddress(hardware, cached->immediateWord);
	cached->highMemoryImmediateByte = getRamAddress(hardware, 0xFF00 + cached->immediateByte);
	cached->highMemoryC = getRamAddress(hardware, 0xFF00 + hardware->registers->C);
	cached->memoryHL = getRamAddress(hardware, cached->HL);
	cached->memoryBC = getRamAddress(hardware, cached->BC);
	cached->memoryDE = getRamAddress(hardware, cached->DE);	
	cached->NextPCAddressPlusImmediateByteSigned = nextPCAddressValue + ((char)cached->immediateByte);
	cached->SPPlusImmediateByteSigned = hardware->registers->SP + ((char)cached->immediateByte);
	cached->SPMinusOne = hardware->registers->SP - 1;
	cached->SPPlusOne = hardware->registers->SP + 1;
	cached->SPPlusTwo = hardware->registers->SP + 2;
	cached->stackValue = getRamAddress(hardware, hardware->registers->SP);
	cached->stackPlusOneValue = getRamAddress(hardware, cached->SPPlusOne);
	cached->stackPlusTwoValue = getRamAddress(hardware, cached->SPPlusTwo);
}


void populateCachedResults(CachedOpResults *results, GBValue *operand1, GBValue *operand2) {
	
	if (operand1 != NULL) {
		int operand1Value = GBValueToInt(operand1);

		if (operand2 != NULL) {
			int operand2Value = GBValueToInt(operand2);

			results->xor = operand1Value ^ operand2Value;
			results->add = operand1Value + operand2Value;
			results->subtract = operand1Value - operand2Value;
		}		
	}
}

void processDestination(Hardware *hardware, int *result, GBValue *destination) {
	if (result != NULL && destination != NULL) {
		int resultValue = *result;

		if (destination->isWordValue) {
			**(destination->wordValue) = resultValue;
		}
		else if (destination->isSplitValue) {
			splitBytes(&resultValue, *(destination->byteValue2), *(destination->byteValue));
		}
		else {
			**(destination->byteValue) = (unsigned char)resultValue;			
		}
	}
}

void processFlags(Hardware *hardware, GBValue *operand1, GBValue *operand2, int *result, FlagResult *flagResult) {
	if (flagResult != NULL && result != NULL) {
		int resultValue = *result;

		hardware->resultInfo->isZero = (resultValue == 0);
		hardware->resultInfo->isAddCarry = (resultValue > 0xFF);
		hardware->resultInfo->isSubBorrow = (resultValue < 0);
		
		if (flagResult->isZero != NULL)		SET_BIT_IF(flagResult->isZero, FLAGS_Z, hardware->registers->F);
		if (flagResult->isSubtract != NULL)	SET_BIT_IF(flagResult->isSubtract, FLAGS_N, hardware->registers->F);
		if (flagResult->isCarry != NULL)	SET_BIT_IF(flagResult->isCarry, FLAGS_CY, hardware->registers->F);

		if (operand1 != NULL && operand2 != NULL) {
			int operand1Value = GBValueToInt(operand1);
			int operand2Value = GBValueToInt(operand2);

			hardware->resultInfo->isAddHalfCarry = ((operand1Value & 0x0F) + (operand2Value & 0x0F) & 0x10) == 0x10;
			hardware->resultInfo->isSubHalfBorrow = ((operand1Value & 0x0F) - (operand2Value & 0x0F)) < 0;

			if (flagResult->isHalfCarry != NULL)		SET_BIT_IF(flagResult->isHalfCarry, FLAGS_H, hardware->registers->F);
		}
	}
}

void getImmediateValue16(Hardware *hardware, int startAddress, int *result) {
	unsigned char *value1 = getRamAddress(hardware, startAddress);
	unsigned char *value2 = getRamAddress(hardware, startAddress + 1);
	joinBytes(value1, value2, result);
}

void getImmediateValue(Hardware *hardware, int address, unsigned char *result1) {
	*result1 = *(getRamAddress(hardware, address));
}