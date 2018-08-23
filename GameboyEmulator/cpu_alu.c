
#include "cpu_alu.h"
#include <stdbool.h>

static const bool FALSE_VAL = false;
static const bool TRUE_VAL = true;
static const unsigned char ONE = 1;


void initALUOperands1(Hardware *hardware, GBValue **operands1) {
	operands1[OpCode_XOR_A] =
		operands1[OpCode_XOR_B] = 
		operands1[OpCode_XOR_C] =
		operands1[OpCode_XOR_D] =
		operands1[OpCode_XOR_E] =
		operands1[OpCode_XOR_H] =
		operands1[OpCode_XOR_L] =
		operands1[OpCode_XOR_MEM_HL] =
		operands1[OpCode_XOR_d8] = createGBByteValue(&(hardware->registers->A));

	operands1[OpCode_INC_A] =
		operands1[OpCode_DEC_A] = createGBByteValue(&(hardware->registers->A));
	operands1[OpCode_INC_B] =
		operands1[OpCode_DEC_B] = createGBByteValue(&(hardware->registers->B));
	operands1[OpCode_INC_BC] =
		operands1[OpCode_DEC_BC] = createGBWordValue(&(hardware->cachedValues->BC));
	operands1[OpCode_INC_C] =
		operands1[OpCode_DEC_C] = createGBByteValue(&(hardware->registers->C));
	operands1[OpCode_INC_D] =
		operands1[OpCode_DEC_D] = createGBByteValue(&(hardware->registers->D));
	operands1[OpCode_INC_DE] =
		operands1[OpCode_DEC_DE] = createGBWordValue(&(hardware->cachedValues->DE));
	operands1[OpCode_INC_E] =
		operands1[OpCode_DEC_E] = createGBByteValue(&(hardware->registers->E));
	operands1[OpCode_INC_H] =
		operands1[OpCode_DEC_H] = createGBByteValue(&(hardware->registers->H));
	operands1[OpCode_INC_HL] =
		operands1[OpCode_DEC_HL] = createGBWordValue(&(hardware->cachedValues->HL));
	operands1[OpCode_INC_L] =
		operands1[OpCode_DEC_L] = createGBByteValue(&(hardware->registers->L));
	operands1[OpCode_INC_MEM_HL] =
		operands1[OpCode_DEC_MEM_HL] = createGBBytePointer(&(hardware->cachedValues->memoryHL));
	operands1[OpCode_INC_SP] =
		operands1[OpCode_DEC_SP] = createGBWordValue(&(hardware->registers->SP));
}

void initALUOperands2(Hardware *hardware, GBValue **operands2) {
	operands2[OpCode_XOR_A] = createGBByteValue(&(hardware->registers->A));
	operands2[OpCode_XOR_B] = createGBByteValue(&(hardware->registers->B));
	operands2[OpCode_XOR_C] = createGBByteValue(&(hardware->registers->C));
	operands2[OpCode_XOR_D] = createGBByteValue(&(hardware->registers->D));
	operands2[OpCode_XOR_E] = createGBByteValue(&(hardware->registers->E));
	operands2[OpCode_XOR_H] = createGBByteValue(&(hardware->registers->H));
	operands2[OpCode_XOR_L] = createGBByteValue(&(hardware->registers->L));
	operands2[OpCode_XOR_MEM_HL] = createGBBytePointer(&(hardware->cachedValues->memoryHL));
	operands2[OpCode_XOR_d8] = createGBByteValue(&(hardware->cachedValues->immediateByte));

	operands2[OpCode_DEC_A] =
		operands2[OpCode_DEC_B] =
		operands2[OpCode_DEC_BC] =
		operands2[OpCode_DEC_C] =
		operands2[OpCode_DEC_D] =
		operands2[OpCode_DEC_DE] =
		operands2[OpCode_DEC_E] =
		operands2[OpCode_DEC_H] =
		operands2[OpCode_DEC_HL] =
		operands2[OpCode_DEC_L] =
		operands2[OpCode_DEC_MEM_HL] =
		operands2[OpCode_DEC_SP] = 
		operands2[OpCode_INC_A] =
		operands2[OpCode_INC_B] =
		operands2[OpCode_INC_BC] =
		operands2[OpCode_INC_C] =
		operands2[OpCode_INC_D] =
		operands2[OpCode_INC_DE] =
		operands2[OpCode_INC_E] =
		operands2[OpCode_INC_H] =
		operands2[OpCode_INC_HL] =
		operands2[OpCode_INC_L] =
		operands2[OpCode_INC_MEM_HL] =
		operands2[OpCode_INC_SP] = createGBByteValue(&(ONE));
}

void initALUResults(Hardware *hardware, int **results) {
	results[OpCode_XOR_A] = 
		results[OpCode_XOR_B] =
		results[OpCode_XOR_C] =
		results[OpCode_XOR_D] =
		results[OpCode_XOR_E] =
		results[OpCode_XOR_H] =
		results[OpCode_XOR_L] =
		results[OpCode_XOR_MEM_HL] =
		results[OpCode_XOR_d8] = &(hardware->cachedResults->xor);

	results[OpCode_DEC_A] =
		results[OpCode_DEC_B] =
		results[OpCode_DEC_BC] =
		results[OpCode_DEC_C] =
		results[OpCode_DEC_D] =
		results[OpCode_DEC_DE] =
		results[OpCode_DEC_E] =
		results[OpCode_DEC_H] =
		results[OpCode_DEC_HL] =
		results[OpCode_DEC_L] =
		results[OpCode_DEC_MEM_HL] =
		results[OpCode_DEC_SP] = &(hardware->cachedResults->subtract);

	results[OpCode_INC_A] =
		results[OpCode_INC_B] =
		results[OpCode_INC_BC] =
		results[OpCode_INC_C] =
		results[OpCode_INC_D] =
		results[OpCode_INC_DE] =
		results[OpCode_INC_E] =
		results[OpCode_INC_H] =
		results[OpCode_INC_HL] =
		results[OpCode_INC_L] =
		results[OpCode_INC_MEM_HL] =
		results[OpCode_INC_SP] = &(hardware->cachedResults->add);
}

void initALUDestinations(Hardware *hardware, GBValue **destinations) {
	destinations[OpCode_XOR_A] =
		destinations[OpCode_XOR_B] =
		destinations[OpCode_XOR_C] =
		destinations[OpCode_XOR_D] =
		destinations[OpCode_XOR_E] =
		destinations[OpCode_XOR_H] =
		destinations[OpCode_XOR_L] =
		destinations[OpCode_XOR_MEM_HL] =
		destinations[OpCode_XOR_d8] = createGBByteValue(&(hardware->registers->A));


	destinations[OpCode_INC_A] =
		destinations[OpCode_DEC_A] = createGBByteValue(&(hardware->registers->A));
	destinations[OpCode_INC_B] =
		destinations[OpCode_DEC_B] = createGBByteValue(&(hardware->registers->B));
	destinations[OpCode_INC_BC] =
		destinations[OpCode_DEC_BC] = createGBSplitByteValue(&(hardware->registers->B), &(hardware->registers->C));
	destinations[OpCode_INC_C] =
		destinations[OpCode_DEC_C] = createGBByteValue(&(hardware->registers->C));
	destinations[OpCode_INC_D] =
		destinations[OpCode_DEC_D] = createGBByteValue(&(hardware->registers->D));
	destinations[OpCode_INC_DE] =
		destinations[OpCode_DEC_DE] = createGBSplitByteValue(&(hardware->registers->D), &(hardware->registers->E));
	destinations[OpCode_INC_E] =
		destinations[OpCode_DEC_E] = createGBByteValue(&(hardware->registers->E));
	destinations[OpCode_INC_H] =
		destinations[OpCode_DEC_H] = createGBByteValue(&(hardware->registers->H));
	destinations[OpCode_INC_HL] =
		destinations[OpCode_DEC_HL] = createGBSplitByteValue(&(hardware->registers->H), &(hardware->registers->L));
	destinations[OpCode_INC_L] =
		destinations[OpCode_DEC_L] = createGBByteValue(&(hardware->registers->L));
	destinations[OpCode_INC_MEM_HL] =
		destinations[OpCode_DEC_MEM_HL] = createGBBytePointer(&(hardware->cachedValues->memoryHL));
	destinations[OpCode_INC_SP] =
		destinations[OpCode_DEC_SP] = createGBWordValue(&(hardware->registers->SP));
}

void initALUFlagResults(Hardware *hardware, FlagResult **flagResults) {
	flagResults[OpCode_XOR_A] = 
		flagResults[OpCode_XOR_B] =
		flagResults[OpCode_XOR_C] =
		flagResults[OpCode_XOR_D] =
		flagResults[OpCode_XOR_E] =
		flagResults[OpCode_XOR_H] =
		flagResults[OpCode_XOR_L] =
		flagResults[OpCode_XOR_MEM_HL] =
		flagResults[OpCode_XOR_d8] = createFlagResult(&(hardware->resultInfo->isZero), &FALSE_VAL, &FALSE_VAL, &FALSE_VAL);

	flagResults[OpCode_DEC_A] =
		flagResults[OpCode_DEC_B] =
		flagResults[OpCode_DEC_C] =
		flagResults[OpCode_DEC_D] =
		flagResults[OpCode_DEC_E] =
		flagResults[OpCode_DEC_H] =
		flagResults[OpCode_DEC_L] =
		flagResults[OpCode_DEC_BC] =
		flagResults[OpCode_DEC_DE] =
		flagResults[OpCode_DEC_HL] =
		flagResults[OpCode_DEC_SP] =
		flagResults[OpCode_DEC_MEM_HL] = createFlagResult(&(hardware->resultInfo->isZero), &TRUE_VAL, &(hardware->resultInfo->isSubHalfBorrow), NULL);
	

	flagResults[OpCode_INC_A] =
		flagResults[OpCode_INC_B] =
		flagResults[OpCode_INC_BC] =
		flagResults[OpCode_INC_C] =
		flagResults[OpCode_INC_D] =
		flagResults[OpCode_INC_DE] =
		flagResults[OpCode_INC_E] =
		flagResults[OpCode_INC_H] =
		flagResults[OpCode_INC_HL] =
		flagResults[OpCode_INC_L] =
		flagResults[OpCode_INC_MEM_HL] =
		flagResults[OpCode_INC_SP] = createFlagResult(&(hardware->resultInfo->isZero), &FALSE_VAL, &(hardware->resultInfo->isAddHalfCarry), NULL);
}

void initALUOpSizes(Hardware *hardware, char *opSizeBytes) {
	opSizeBytes[OpCode_XOR_d8] = 2;
}