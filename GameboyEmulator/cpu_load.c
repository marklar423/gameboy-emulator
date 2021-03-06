#include <stdio.h>

#include "cpu_load.h"
#include "ram.h"
#include "util.h"


static const bool FALSE_VAL = false;
static const bool TRUE_VAL = true;

void populateLoadInstructions(Hardware *hardware, InstructionMapping *mappings) {
	populateLoadOperands(hardware, mappings);
	populateLoadDestinations(hardware, mappings);
	populateLoadNextSPs(hardware, mappings);
}

void populateLoadOperands(Hardware *hardware, InstructionMapping *mappings) {
	mappings[OpCode_LDH_MEM_a8_A].operand1 =
		mappings[OpCode_LD_A_A].operand1 =
		mappings[OpCode_LD_B_A].operand1 =
		mappings[OpCode_LD_C_A].operand1 =
		mappings[OpCode_LD_D_A].operand1 =
		mappings[OpCode_LD_E_A].operand1 =
		mappings[OpCode_LD_H_A].operand1 =
		mappings[OpCode_LD_L_A].operand1 =
		mappings[OpCode_LD_MEM_BC_A].operand1 =
		mappings[OpCode_LD_MEM_C_A].operand1 =
		mappings[OpCode_LD_MEM_DE_A].operand1 =
		mappings[OpCode_LD_MEM_HLD_A].operand1 =
		mappings[OpCode_LD_MEM_HLI_A].operand1 =
		mappings[OpCode_LD_MEM_HL_A].operand1 =
		mappings[OpCode_LD_MEM_a16_A].operand1 = createGBByteValue(&(hardware->registers->A));

	mappings[OpCode_LD_A_B].operand1 =
		mappings[OpCode_LD_B_B].operand1 =
		mappings[OpCode_LD_C_B].operand1 =
		mappings[OpCode_LD_D_B].operand1 =
		mappings[OpCode_LD_E_B].operand1 =
		mappings[OpCode_LD_H_B].operand1 =
		mappings[OpCode_LD_L_B].operand1 =
		mappings[OpCode_LD_MEM_HL_B].operand1 = createGBByteValue(&(hardware->registers->B));

	mappings[OpCode_LD_A_C].operand1 =
		mappings[OpCode_LD_B_C].operand1 =
		mappings[OpCode_LD_C_C].operand1 =
		mappings[OpCode_LD_D_C].operand1 =
		mappings[OpCode_LD_E_C].operand1 =
		mappings[OpCode_LD_H_C].operand1 =
		mappings[OpCode_LD_L_C].operand1 =
		mappings[OpCode_LD_MEM_HL_C].operand1 = createGBByteValue(&(hardware->registers->C));

	mappings[OpCode_LD_A_D].operand1 =
		mappings[OpCode_LD_B_D].operand1 =
		mappings[OpCode_LD_C_D].operand1 =
		mappings[OpCode_LD_D_D].operand1 =
		mappings[OpCode_LD_E_D].operand1 =
		mappings[OpCode_LD_H_D].operand1 =
		mappings[OpCode_LD_L_D].operand1 =
		mappings[OpCode_LD_MEM_HL_D].operand1 = createGBByteValue(&(hardware->registers->D));

	mappings[OpCode_LD_A_E].operand1 =
		mappings[OpCode_LD_B_E].operand1 =
		mappings[OpCode_LD_C_E].operand1 =
		mappings[OpCode_LD_D_E].operand1 =
		mappings[OpCode_LD_E_E].operand1 =
		mappings[OpCode_LD_H_E].operand1 =
		mappings[OpCode_LD_L_E].operand1 =
		mappings[OpCode_LD_MEM_HL_E].operand1 = createGBByteValue(&(hardware->registers->E));

	mappings[OpCode_LD_A_H].operand1 =
		mappings[OpCode_LD_B_H].operand1 =
		mappings[OpCode_LD_C_H].operand1 =
		mappings[OpCode_LD_D_H].operand1 =
		mappings[OpCode_LD_E_H].operand1 =
		mappings[OpCode_LD_H_H].operand1 =
		mappings[OpCode_LD_L_H].operand1 =
		mappings[OpCode_LD_MEM_HL_H].operand1 = createGBByteValue(&(hardware->registers->H));

	mappings[OpCode_LD_A_L].operand1 =
		mappings[OpCode_LD_B_L].operand1 =
		mappings[OpCode_LD_C_L].operand1 =
		mappings[OpCode_LD_D_L].operand1 =
		mappings[OpCode_LD_E_L].operand1 =
		mappings[OpCode_LD_H_L].operand1 =
		mappings[OpCode_LD_L_L].operand1 =
		mappings[OpCode_LD_MEM_HL_L].operand1 = createGBByteValue(&(hardware->registers->L));

	mappings[OpCode_LD_MEM_a16_SP].operand1 = createGBWordValue(&(hardware->registers->SP));

	mappings[OpCode_LD_A_d8].operand1 =
		mappings[OpCode_LD_B_d8].operand1 =
		mappings[OpCode_LD_C_d8].operand1 =
		mappings[OpCode_LD_D_d8].operand1 =
		mappings[OpCode_LD_E_d8].operand1 =
		mappings[OpCode_LD_H_d8].operand1 =
		mappings[OpCode_LD_L_d8].operand1 =
		mappings[OpCode_LD_MEM_HL_d8].operand1 = createGBByteValue(&(hardware->computedValues->immediateByte));

	mappings[OpCode_LD_BC_d16].operand1 =
		mappings[OpCode_LD_DE_d16].operand1 =
		mappings[OpCode_LD_HL_d16].operand1 =
		mappings[OpCode_LD_SP_d16].operand1 = createGBWordValue(&(hardware->computedValues->immediateWord));

	mappings[OpCode_LD_SP_HL].operand1 = createGBWordValue(&(hardware->computedValues->HL));
	mappings[OpCode_LD_A_MEM_a16].operand1 = createGBBytePointer(&(hardware->computedValues->memoryImmediateWord));
	mappings[OpCode_LDH_A_MEM_a8].operand1 = createGBBytePointer(&(hardware->computedValues->highMemoryImmediateByte));
	mappings[OpCode_LD_A_MEM_C].operand1 = createGBBytePointer(&(hardware->computedValues->highMemoryC));

	mappings[OpCode_LD_A_MEM_HL].operand1 =
		mappings[OpCode_LD_B_MEM_HL].operand1 =
		mappings[OpCode_LD_C_MEM_HL].operand1 =
		mappings[OpCode_LD_D_MEM_HL].operand1 =
		mappings[OpCode_LD_E_MEM_HL].operand1 =
		mappings[OpCode_LD_H_MEM_HL].operand1 =
		mappings[OpCode_LD_L_MEM_HL].operand1 =
		mappings[OpCode_LD_A_MEM_HLD].operand1 =
		mappings[OpCode_LD_A_MEM_HLI].operand1 = createGBBytePointer(&(hardware->computedValues->memoryHL));

	mappings[OpCode_LD_A_MEM_BC].operand1 = createGBBytePointer(&(hardware->computedValues->memoryBC));
	mappings[OpCode_LD_A_MEM_DE].operand1 = createGBBytePointer(&(hardware->computedValues->memoryDE));

	mappings[OpCode_LD_HL_SP_PLUS_r8].operand1 = createGBWordValue(&(hardware->registers->SP));
	mappings[OpCode_LD_HL_SP_PLUS_r8].operand2 = createGBByteValueSigned(&(hardware->computedValues->immediateByte));
	mappings[OpCode_LD_HL_SP_PLUS_r8].result = &hardware->operationResults->add;
	mappings[OpCode_LD_HL_SP_PLUS_r8].flagResult = createFlagResult(&FALSE_VAL, &FALSE_VAL, &(hardware->resultInfo->isAddHalfCarry), &(hardware->resultInfo->isAddCarry));

	mappings[OpCode_POP_AF].operand1 =
		mappings[OpCode_POP_BC].operand1 =
		mappings[OpCode_POP_DE].operand1 =
		mappings[OpCode_POP_HL].operand1 = createGBSplitBytePointer(&(hardware->computedValues->stackPlusOneValue), &(hardware->computedValues->stackValue));

	mappings[OpCode_PUSH_AF].operand1 = createGBWordValue(&(hardware->computedValues->AF));
	mappings[OpCode_PUSH_BC].operand1 = createGBWordValue(&(hardware->computedValues->BC));
	mappings[OpCode_PUSH_DE].operand1 = createGBWordValue(&(hardware->computedValues->DE));
	mappings[OpCode_PUSH_HL].operand1 = createGBWordValue(&(hardware->computedValues->HL));

}

void populateLoadDestinations(Hardware *hardware, InstructionMapping *mappings) {
	mappings[OpCode_LD_A_A].destination =
		mappings[OpCode_LD_A_B].destination =
		mappings[OpCode_LD_A_C].destination =
		mappings[OpCode_LD_A_D].destination =
		mappings[OpCode_LD_A_E].destination =
		mappings[OpCode_LD_A_H].destination =
		mappings[OpCode_LD_A_L].destination =
		mappings[OpCode_LD_A_d8].destination =
		mappings[OpCode_LD_A_MEM_BC].destination =
		mappings[OpCode_LD_A_MEM_C].destination =
		mappings[OpCode_LD_A_MEM_DE].destination =
		mappings[OpCode_LD_A_MEM_HL].destination =
		mappings[OpCode_LD_A_MEM_HLD].destination =
		mappings[OpCode_LD_A_MEM_HLI].destination =
		mappings[OpCode_LD_A_MEM_a16].destination =
		mappings[OpCode_LDH_A_MEM_a8].destination = createGBByteValue(&(hardware->registers->A));

	mappings[OpCode_LD_B_A].destination =
		mappings[OpCode_LD_B_B].destination =
		mappings[OpCode_LD_B_C].destination =
		mappings[OpCode_LD_B_D].destination =
		mappings[OpCode_LD_B_E].destination =
		mappings[OpCode_LD_B_H].destination =
		mappings[OpCode_LD_B_L].destination =
		mappings[OpCode_LD_B_d8].destination =
		mappings[OpCode_LD_B_MEM_HL].destination = createGBByteValue(&(hardware->registers->B));

	mappings[OpCode_LD_C_A].destination =
		mappings[OpCode_LD_C_B].destination =
		mappings[OpCode_LD_C_C].destination =
		mappings[OpCode_LD_C_D].destination =
		mappings[OpCode_LD_C_E].destination =
		mappings[OpCode_LD_C_H].destination =
		mappings[OpCode_LD_C_L].destination =
		mappings[OpCode_LD_C_MEM_HL].destination =
		mappings[OpCode_LD_C_d8].destination = createGBByteValue(&(hardware->registers->C));

	mappings[OpCode_LD_D_A].destination =
		mappings[OpCode_LD_D_B].destination =
		mappings[OpCode_LD_D_C].destination =
		mappings[OpCode_LD_D_D].destination =
		mappings[OpCode_LD_D_E].destination =
		mappings[OpCode_LD_D_H].destination =
		mappings[OpCode_LD_D_L].destination =
		mappings[OpCode_LD_D_MEM_HL].destination =
		mappings[OpCode_LD_D_d8].destination = createGBByteValue(&(hardware->registers->D));

	mappings[OpCode_LD_E_A].destination =
		mappings[OpCode_LD_E_B].destination =
		mappings[OpCode_LD_E_C].destination =
		mappings[OpCode_LD_E_D].destination =
		mappings[OpCode_LD_E_E].destination =
		mappings[OpCode_LD_E_H].destination =
		mappings[OpCode_LD_E_L].destination =
		mappings[OpCode_LD_E_MEM_HL].destination =
		mappings[OpCode_LD_E_d8].destination = createGBByteValue(&(hardware->registers->E));

	mappings[OpCode_LD_H_A].destination =
		mappings[OpCode_LD_H_B].destination =
		mappings[OpCode_LD_H_C].destination =
		mappings[OpCode_LD_H_D].destination =
		mappings[OpCode_LD_H_E].destination =
		mappings[OpCode_LD_H_H].destination =
		mappings[OpCode_LD_H_L].destination =
		mappings[OpCode_LD_H_MEM_HL].destination =
		mappings[OpCode_LD_H_d8].destination = createGBByteValue(&(hardware->registers->H));

	mappings[OpCode_LD_L_A].destination =
		mappings[OpCode_LD_L_B].destination =
		mappings[OpCode_LD_L_C].destination =
		mappings[OpCode_LD_L_D].destination =
		mappings[OpCode_LD_L_E].destination =
		mappings[OpCode_LD_L_H].destination =
		mappings[OpCode_LD_L_L].destination =
		mappings[OpCode_LD_L_MEM_HL].destination =
		mappings[OpCode_LD_L_d8].destination = createGBByteValue(&(hardware->registers->L));

	mappings[OpCode_LD_SP_HL].destination =
		mappings[OpCode_LD_SP_d16].destination = createGBWordValue(&(hardware->registers->SP));

	mappings[OpCode_LD_MEM_HL_A].destination =
		mappings[OpCode_LD_MEM_HL_B].destination =
		mappings[OpCode_LD_MEM_HL_C].destination =
		mappings[OpCode_LD_MEM_HL_D].destination =
		mappings[OpCode_LD_MEM_HL_E].destination =
		mappings[OpCode_LD_MEM_HL_H].destination =
		mappings[OpCode_LD_MEM_HL_L].destination =
		mappings[OpCode_LD_MEM_HL_d8].destination =
		mappings[OpCode_LD_MEM_HLD_A].destination =
		mappings[OpCode_LD_MEM_HLI_A].destination = createGBBytePointer(&(hardware->computedValues->memoryHL));

	mappings[OpCode_LD_MEM_BC_A].destination = createGBBytePointer(&(hardware->computedValues->memoryBC));
	mappings[OpCode_LD_MEM_DE_A].destination = createGBBytePointer(&(hardware->computedValues->memoryDE));

	mappings[OpCode_LD_MEM_C_A].destination = createGBBytePointer(&(hardware->computedValues->highMemoryC));

	mappings[OpCode_LD_MEM_a16_A].destination = createGBBytePointer(&(hardware->computedValues->memoryImmediateWord));
	mappings[OpCode_LD_MEM_a16_SP].destination = createGBSplitBytePointer(&(hardware->computedValues->memoryImmediateWordPlusOne), &(hardware->computedValues->memoryImmediateWord));

	mappings[OpCode_LDH_MEM_a8_A].destination = createGBBytePointer(&(hardware->computedValues->highMemoryImmediateByte));

	mappings[OpCode_LD_BC_d16].destination = createGBSplitByteValue(&(hardware->registers->B), &(hardware->registers->C));
	mappings[OpCode_LD_DE_d16].destination = createGBSplitByteValue(&(hardware->registers->D), &(hardware->registers->E));

	mappings[OpCode_LD_HL_SP_PLUS_r8].destination =
		mappings[OpCode_LD_HL_d16].destination = createGBSplitByteValue(&(hardware->registers->H), &(hardware->registers->L));

	mappings[OpCode_POP_AF].destination = createGBSplitByteValue(&(hardware->registers->A), &(hardware->registers->F));
	mappings[OpCode_POP_BC].destination = createGBSplitByteValue(&(hardware->registers->B), &(hardware->registers->C));
	mappings[OpCode_POP_DE].destination = createGBSplitByteValue(&(hardware->registers->D), &(hardware->registers->E));
	mappings[OpCode_POP_HL].destination = createGBSplitByteValue(&(hardware->registers->H), &(hardware->registers->L));

	mappings[OpCode_PUSH_AF].destination =
		mappings[OpCode_PUSH_BC].destination =
		mappings[OpCode_PUSH_DE].destination =
		mappings[OpCode_PUSH_HL].destination = createGBSplitBytePointer(&(hardware->computedValues->stackMinusOneValue), &(hardware->computedValues->stackMinusTwoValue));
}

void populateLoadNextSPs(Hardware *hardware, InstructionMapping *mappings) {

	mappings[OpCode_POP_AF].nextSP =
		mappings[OpCode_POP_BC].nextSP =
		mappings[OpCode_POP_DE].nextSP =
		mappings[OpCode_POP_HL].nextSP = &hardware->computedValues->SPPlusTwo;

	mappings[OpCode_PUSH_AF].nextSP=
		mappings[OpCode_PUSH_BC].nextSP=
		mappings[OpCode_PUSH_DE].nextSP =
		mappings[OpCode_PUSH_HL].nextSP = &hardware->computedValues->SPMinusTwo;
	
}
