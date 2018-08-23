#include <stdio.h>

#include "cpu_load.h"
#include "cpu_ram.h"
#include "util.h"


void initLoadOperands1(Hardware *hardware, GBValue **operands1) {
	operands1[OpCode_LDH_MEM_a8_A] =
		operands1[OpCode_LD_A_A] =
		operands1[OpCode_LD_B_A] =
		operands1[OpCode_LD_C_A] =
		operands1[OpCode_LD_D_A] =
		operands1[OpCode_LD_E_A] =
		operands1[OpCode_LD_H_A] =
		operands1[OpCode_LD_L_A] =
		operands1[OpCode_LD_MEM_BC_A] =
		operands1[OpCode_LD_MEM_C_A] =
		operands1[OpCode_LD_MEM_DE_A] =
		operands1[OpCode_LD_MEM_HLD_A] =
		operands1[OpCode_LD_MEM_HLI_A] =
		operands1[OpCode_LD_MEM_HL_A] =
		operands1[OpCode_LD_MEM_a16_A] = createGBByteValue(&(hardware->registers->A));

	operands1[OpCode_LD_A_B] =
		operands1[OpCode_LD_B_B] =
		operands1[OpCode_LD_C_B] =
		operands1[OpCode_LD_D_B] =
		operands1[OpCode_LD_E_B] =
		operands1[OpCode_LD_H_B] =
		operands1[OpCode_LD_L_B] =
		operands1[OpCode_LD_MEM_HL_B] = createGBByteValue(false, &(hardware->registers->B));

	operands1[OpCode_LD_A_C] =
		operands1[OpCode_LD_B_C] =
		operands1[OpCode_LD_C_C] =
		operands1[OpCode_LD_D_C] =
		operands1[OpCode_LD_E_C] =
		operands1[OpCode_LD_H_C] =
		operands1[OpCode_LD_L_C] =
		operands1[OpCode_LD_MEM_HL_C] = createGBByteValue(false, &(hardware->registers->C));

	operands1[OpCode_LD_A_D] =
		operands1[OpCode_LD_B_D] =
		operands1[OpCode_LD_C_D] =
		operands1[OpCode_LD_D_D] =
		operands1[OpCode_LD_E_D] =
		operands1[OpCode_LD_H_D] =
		operands1[OpCode_LD_L_D] =
		operands1[OpCode_LD_MEM_HL_D] = createGBByteValue(&(hardware->registers->D));

	operands1[OpCode_LD_A_E] =
		operands1[OpCode_LD_B_E] =
		operands1[OpCode_LD_C_E] =
		operands1[OpCode_LD_D_E] =
		operands1[OpCode_LD_E_E] =
		operands1[OpCode_LD_H_E] =
		operands1[OpCode_LD_L_E] =
		operands1[OpCode_LD_MEM_HL_E] = createGBByteValue(&(hardware->registers->E));

	operands1[OpCode_LD_A_H] =
		operands1[OpCode_LD_B_H] =
		operands1[OpCode_LD_C_H] =
		operands1[OpCode_LD_D_H] =
		operands1[OpCode_LD_E_H] =
		operands1[OpCode_LD_H_H] =
		operands1[OpCode_LD_L_H] =
		operands1[OpCode_LD_MEM_HL_H] = createGBByteValue(&(hardware->registers->H));

	operands1[OpCode_LD_A_L] =
		operands1[OpCode_LD_B_L] =
		operands1[OpCode_LD_C_L] =
		operands1[OpCode_LD_D_L] =
		operands1[OpCode_LD_E_L] =
		operands1[OpCode_LD_H_L] =
		operands1[OpCode_LD_L_L] =
		operands1[OpCode_LD_MEM_HL_L] = createGBByteValue(&(hardware->registers->L));

	operands1[OpCode_LD_MEM_a16_SP] = createGBWordValue(&(hardware->registers->SP));

	operands1[OpCode_LD_A_d8] =
		operands1[OpCode_LD_B_d8] =
		operands1[OpCode_LD_C_d8] =
		operands1[OpCode_LD_D_d8] =
		operands1[OpCode_LD_E_d8] =
		operands1[OpCode_LD_H_d8] =
		operands1[OpCode_LD_L_d8] =
		operands1[OpCode_LD_MEM_HL_d8] = createGBByteValue(&(hardware->cachedValues->immediateByte));

	operands1[OpCode_LD_BC_d16] =
		operands1[OpCode_LD_DE_d16] =
		operands1[OpCode_LD_HL_d16] =
		operands1[OpCode_LD_SP_d16] = createGBWordValue(&(hardware->cachedValues->immediateWord));

	operands1[OpCode_LD_SP_HL] = createGBWordValue(&(hardware->cachedValues->HL));
	operands1[OpCode_LD_A_MEM_a16] = createGBBytePointer(&(hardware->cachedValues->memoryImmediateWord));
	operands1[OpCode_LDH_A_MEM_a8] = createGBBytePointer(&(hardware->cachedValues->highMemoryImmediateByte));
	operands1[OpCode_LD_A_MEM_C] = createGBBytePointer(&(hardware->cachedValues->highMemoryC));

	operands1[OpCode_LD_A_MEM_HL] =
		operands1[OpCode_LD_B_MEM_HL] =
		operands1[OpCode_LD_C_MEM_HL] =
		operands1[OpCode_LD_D_MEM_HL] =
		operands1[OpCode_LD_E_MEM_HL] =
		operands1[OpCode_LD_H_MEM_HL] =
		operands1[OpCode_LD_L_MEM_HL] =
		operands1[OpCode_LD_A_MEM_HLD] =
		operands1[OpCode_LD_A_MEM_HLI] = createGBBytePointer(&(hardware->cachedValues->memoryHL));

	operands1[OpCode_LD_A_MEM_BC] = createGBBytePointer(&(hardware->cachedValues->memoryBC));
	operands1[OpCode_LD_A_MEM_DE] = createGBBytePointer(&(hardware->cachedValues->memoryDE));

	operands1[OpCode_LD_HL_SP_Pr8] = createGBWordValue(&(hardware->cachedValues->SPPlusImmediateByteSigned));
}

void initLoadDestinations(Hardware *hardware, GBValue **destinations) {
	destinations[OpCode_LD_A_A] =
		destinations[OpCode_LD_A_B] =
		destinations[OpCode_LD_A_C] =
		destinations[OpCode_LD_A_D] =
		destinations[OpCode_LD_A_E] =
		destinations[OpCode_LD_A_H] =
		destinations[OpCode_LD_A_L] =
		destinations[OpCode_LD_A_d8] =
		destinations[OpCode_LD_A_MEM_BC] =
		destinations[OpCode_LD_A_MEM_C] =
		destinations[OpCode_LD_A_MEM_DE] =
		destinations[OpCode_LD_A_MEM_HL] =
		destinations[OpCode_LD_A_MEM_HLD] =
		destinations[OpCode_LD_A_MEM_HLI] =
		destinations[OpCode_LD_A_MEM_a16] =
		destinations[OpCode_LDH_A_MEM_a8] = createGBByteValue(&(hardware->registers->A));

	destinations[OpCode_LD_B_A] =
		destinations[OpCode_LD_B_B] =
		destinations[OpCode_LD_B_C] =
		destinations[OpCode_LD_B_D] =
		destinations[OpCode_LD_B_E] =
		destinations[OpCode_LD_B_H] =
		destinations[OpCode_LD_B_L] =
		destinations[OpCode_LD_B_d8] =
		destinations[OpCode_LD_B_MEM_HL] = createGBByteValue(&(hardware->registers->B));

	destinations[OpCode_LD_C_A] =
		destinations[OpCode_LD_C_B] =
		destinations[OpCode_LD_C_C] =
		destinations[OpCode_LD_C_D] =
		destinations[OpCode_LD_C_E] =
		destinations[OpCode_LD_C_H] =
		destinations[OpCode_LD_C_L] =
		destinations[OpCode_LD_C_MEM_HL] =
		destinations[OpCode_LD_C_d8] = createGBByteValue(&(hardware->registers->C));

	destinations[OpCode_LD_D_A] =
		destinations[OpCode_LD_D_B] =
		destinations[OpCode_LD_D_C] =
		destinations[OpCode_LD_D_D] =
		destinations[OpCode_LD_D_E] =
		destinations[OpCode_LD_D_H] =
		destinations[OpCode_LD_D_L] =
		destinations[OpCode_LD_D_MEM_HL] =
		destinations[OpCode_LD_D_d8] = createGBByteValue(&(hardware->registers->D));

	destinations[OpCode_LD_E_A] =
		destinations[OpCode_LD_E_B] =
		destinations[OpCode_LD_E_C] =
		destinations[OpCode_LD_E_D] =
		destinations[OpCode_LD_E_E] =
		destinations[OpCode_LD_E_H] =
		destinations[OpCode_LD_E_L] =
		destinations[OpCode_LD_E_MEM_HL] =
		destinations[OpCode_LD_E_d8] = createGBByteValue(&(hardware->registers->E));

	destinations[OpCode_LD_H_A] =
		destinations[OpCode_LD_H_B] =
		destinations[OpCode_LD_H_C] =
		destinations[OpCode_LD_H_D] =
		destinations[OpCode_LD_H_E] =
		destinations[OpCode_LD_H_H] =
		destinations[OpCode_LD_H_L] =
		destinations[OpCode_LD_H_MEM_HL] =
		destinations[OpCode_LD_H_d8] = createGBByteValue(&(hardware->registers->H));

	destinations[OpCode_LD_L_A] =
		destinations[OpCode_LD_L_B] =
		destinations[OpCode_LD_L_C] =
		destinations[OpCode_LD_L_D] =
		destinations[OpCode_LD_L_E] =
		destinations[OpCode_LD_L_H] =
		destinations[OpCode_LD_L_L] =
		destinations[OpCode_LD_L_MEM_HL] =
		destinations[OpCode_LD_L_d8] = createGBByteValue(&(hardware->registers->L));

	destinations[OpCode_LD_SP_HL] =
		destinations[OpCode_LD_SP_d16] = createGBWordValue(&(hardware->registers->SP));

	destinations[OpCode_LD_MEM_HL_A] =
		destinations[OpCode_LD_MEM_HL_B] =
		destinations[OpCode_LD_MEM_HL_C] =
		destinations[OpCode_LD_MEM_HL_D] =
		destinations[OpCode_LD_MEM_HL_E] =
		destinations[OpCode_LD_MEM_HL_H] =
		destinations[OpCode_LD_MEM_HL_L] =
		destinations[OpCode_LD_MEM_HL_d8] = 
		destinations[OpCode_LD_MEM_HLD_A] = 
		destinations[OpCode_LD_MEM_HLI_A] = createGBBytePointer(&(hardware->cachedValues->memoryHL));

	destinations[OpCode_LD_MEM_BC_A] = createGBBytePointer(&(hardware->cachedValues->memoryBC));
	destinations[OpCode_LD_MEM_DE_A] = createGBBytePointer(&(hardware->cachedValues->memoryDE));

	destinations[OpCode_LD_MEM_C_A] = createGBBytePointer(&(hardware->cachedValues->highMemoryC));

	destinations[OpCode_LD_MEM_a16_A] =
		destinations[OpCode_LD_MEM_a16_SP] = createGBBytePointer(&(hardware->cachedValues->memoryImmediateWord));

	destinations[OpCode_LDH_MEM_a8_A] = createGBBytePointer(&(hardware->cachedValues->highMemoryImmediateByte));

	destinations[OpCode_LD_BC_d16] = createGBSplitByteValue(&(hardware->registers->B), &(hardware->registers->C));
	destinations[OpCode_LD_DE_d16] = createGBSplitByteValue(&(hardware->registers->D), &(hardware->registers->E));
	
	destinations[OpCode_LD_HL_SP_Pr8] =
		destinations[OpCode_LD_HL_d16] = createGBSplitByteValue(&(hardware->registers->H), &(hardware->registers->L));
}

void initLoadOpSizes(Hardware *hardware, char *opSizeBytes) {
	opSizeBytes[OpCode_LDH_MEM_a8_A] =
		opSizeBytes[OpCode_LD_A_d8] =
		opSizeBytes[OpCode_LD_B_d8] =
		opSizeBytes[OpCode_LD_C_d8] =
		opSizeBytes[OpCode_LD_D_d8] =
		opSizeBytes[OpCode_LD_E_d8] =
		opSizeBytes[OpCode_LD_H_d8] =
		opSizeBytes[OpCode_LD_L_d8] =
		opSizeBytes[OpCode_LDH_A_MEM_a8] =
		opSizeBytes[OpCode_LD_MEM_HL_d8] =
		opSizeBytes[OpCode_LD_HL_SP_Pr8] = 2;

	opSizeBytes[OpCode_LD_BC_d16] =
		opSizeBytes[OpCode_LD_DE_d16] =
		opSizeBytes[OpCode_LD_HL_d16] =
		opSizeBytes[OpCode_LD_SP_d16] =
		opSizeBytes[OpCode_LD_MEM_a16_SP] =
		opSizeBytes[OpCode_LD_A_MEM_a16] = 3;
	
}
