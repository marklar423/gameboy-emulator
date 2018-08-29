
#include "cpu_alu.h"
#include <stdbool.h>

static const bool FALSE_VAL = false;
static const bool TRUE_VAL = true;
static const unsigned char ONE = 1;



void populateALUInstructions(Hardware *hardware, InstructionMapping *mappings) {
	populateALUOperands1(hardware, mappings);
	populateALUOperands2(hardware, mappings);
	populateALUResults(hardware, mappings);
	populateALUDestinations(hardware, mappings);
	populateALUFlagResults(hardware, mappings);
}

void populateALUOperands1(Hardware *hardware, InstructionMapping *mappings) {
		mappings[OpCode_ADD_A_A].operand1 =
		mappings[OpCode_ADD_A_B].operand1 =
		mappings[OpCode_ADD_A_C].operand1 =
		mappings[OpCode_ADD_A_D].operand1 =
		mappings[OpCode_ADD_A_E].operand1 =
		mappings[OpCode_ADD_A_H].operand1 =
		mappings[OpCode_ADD_A_L].operand1 =
		mappings[OpCode_ADD_A_MEM_HL].operand1 =
		mappings[OpCode_ADD_A_d8].operand1 =
		mappings[OpCode_XOR_A].operand1 =
		mappings[OpCode_XOR_B].operand1 =
		mappings[OpCode_XOR_C].operand1 =
		mappings[OpCode_XOR_D].operand1 =
		mappings[OpCode_XOR_E].operand1 =
		mappings[OpCode_XOR_H].operand1 =
		mappings[OpCode_XOR_L].operand1 =
		mappings[OpCode_XOR_MEM_HL].operand1 =
		mappings[OpCode_XOR_d8].operand1 = createGBByteValue(&(hardware->registers->A));

		mappings[OpCode_ADC_A_A].operand1 =
			mappings[OpCode_ADC_A_B].operand1 =
			mappings[OpCode_ADC_A_C].operand1 =
			mappings[OpCode_ADC_A_D].operand1 =
			mappings[OpCode_ADC_A_E].operand1 =
			mappings[OpCode_ADC_A_H].operand1 =
			mappings[OpCode_ADC_A_L].operand1 =
			mappings[OpCode_ADC_A_MEM_HL].operand1 =
			mappings[OpCode_ADC_A_d8].operand1 = createGBByteValue(&(hardware->cachedValues->APlusCarry));

	mappings[OpCode_INC_A].operand1 =
		mappings[OpCode_DEC_A].operand1 = createGBByteValue(&(hardware->registers->A));
	mappings[OpCode_INC_B].operand1 =
		mappings[OpCode_DEC_B].operand1 = createGBByteValue(&(hardware->registers->B));
	mappings[OpCode_INC_BC].operand1 =
		mappings[OpCode_DEC_BC].operand1 = createGBWordValue(&(hardware->cachedValues->BC));
	mappings[OpCode_INC_C].operand1 =
		mappings[OpCode_DEC_C].operand1 = createGBByteValue(&(hardware->registers->C));
	mappings[OpCode_INC_D].operand1 =
		mappings[OpCode_DEC_D].operand1 = createGBByteValue(&(hardware->registers->D));
	mappings[OpCode_INC_DE].operand1 =
		mappings[OpCode_DEC_DE].operand1 = createGBWordValue(&(hardware->cachedValues->DE));
	mappings[OpCode_INC_E].operand1 =
		mappings[OpCode_DEC_E].operand1 = createGBByteValue(&(hardware->registers->E));
	mappings[OpCode_INC_H].operand1 =
		mappings[OpCode_DEC_H].operand1 = createGBByteValue(&(hardware->registers->H));

	mappings[OpCode_ADD_HL_BC].operand1 =
		mappings[OpCode_ADD_HL_DE].operand1 =
		mappings[OpCode_ADD_HL_HL].operand1 =
		mappings[OpCode_ADD_HL_SP].operand1 =
		mappings[OpCode_INC_HL].operand1 =
		mappings[OpCode_DEC_HL].operand1 = createGBWordValue(&(hardware->cachedValues->HL));

	mappings[OpCode_INC_L].operand1 =
		mappings[OpCode_DEC_L].operand1 = createGBByteValue(&(hardware->registers->L));
	mappings[OpCode_INC_MEM_HL].operand1 =
		mappings[OpCode_DEC_MEM_HL].operand1 = createGBBytePointer(&(hardware->cachedValues->memoryHL));
	
		mappings[OpCode_INC_SP].operand1 =
		mappings[OpCode_DEC_SP].operand1 = createGBWordValue(&(hardware->registers->SP));
		
		mappings[OpCode_ADD_SP_r8].operand1 = createGBWordValue(&(hardware->registers->SP));
}

void populateALUOperands2(Hardware *hardware, InstructionMapping *mappings) {
	mappings[OpCode_ADC_A_A].operand2 =
		mappings[OpCode_ADD_A_A].operand2 =
		mappings[OpCode_XOR_A].operand2 = createGBByteValue(&(hardware->registers->A));

	mappings[OpCode_ADC_A_B].operand2 =
		mappings[OpCode_ADD_A_B].operand2 =
		mappings[OpCode_XOR_B].operand2 = createGBByteValue(&(hardware->registers->B));

	mappings[OpCode_ADC_A_C].operand2 =
		mappings[OpCode_ADD_A_C].operand2 =
		mappings[OpCode_XOR_C].operand2 = createGBByteValue(&(hardware->registers->C));

	mappings[OpCode_ADC_A_D].operand2 =
		mappings[OpCode_ADD_A_D].operand2 =
		mappings[OpCode_XOR_D].operand2 = createGBByteValue(&(hardware->registers->D));

	mappings[OpCode_ADC_A_E].operand2 =
		mappings[OpCode_ADD_A_E].operand2 =
		mappings[OpCode_XOR_E].operand2 = createGBByteValue(&(hardware->registers->E));

	mappings[OpCode_ADC_A_H].operand2 =
		mappings[OpCode_ADD_A_H].operand2 =
		mappings[OpCode_XOR_H].operand2 = createGBByteValue(&(hardware->registers->H));

	mappings[OpCode_ADC_A_L].operand2 =
		mappings[OpCode_ADD_A_L].operand2 =
		mappings[OpCode_XOR_L].operand2 = createGBByteValue(&(hardware->registers->L));

	mappings[OpCode_ADC_A_MEM_HL].operand2 =
		mappings[OpCode_ADD_A_MEM_HL].operand2 =
		mappings[OpCode_XOR_MEM_HL].operand2 = createGBBytePointer(&(hardware->cachedValues->memoryHL));

	mappings[OpCode_ADC_A_d8].operand2 =
		mappings[OpCode_ADD_A_d8].operand2 =
		mappings[OpCode_XOR_d8].operand2 = createGBByteValue(&(hardware->cachedValues->immediateByte));


	mappings[OpCode_ADD_HL_BC].operand2 = createGBWordValue(&(hardware->cachedValues->BC));
		mappings[OpCode_ADD_HL_DE].operand2 = createGBWordValue(&(hardware->cachedValues->DE));
		mappings[OpCode_ADD_HL_HL].operand2 = createGBWordValue(&(hardware->cachedValues->HL));
		mappings[OpCode_ADD_HL_SP].operand2 = createGBWordValue(&(hardware->registers->SP));

		mappings[OpCode_DEC_A].operand2 =
		mappings[OpCode_DEC_B].operand2 =
		mappings[OpCode_DEC_BC].operand2 =
		mappings[OpCode_DEC_C].operand2 =
		mappings[OpCode_DEC_D].operand2 =
		mappings[OpCode_DEC_DE].operand2 =
		mappings[OpCode_DEC_E].operand2 =
		mappings[OpCode_DEC_H].operand2 =
		mappings[OpCode_DEC_HL].operand2 =
		mappings[OpCode_DEC_L].operand2 =
		mappings[OpCode_DEC_MEM_HL].operand2 =
		mappings[OpCode_DEC_SP].operand2 =
		mappings[OpCode_INC_A].operand2 =
		mappings[OpCode_INC_B].operand2 =
		mappings[OpCode_INC_BC].operand2 =
		mappings[OpCode_INC_C].operand2 =
		mappings[OpCode_INC_D].operand2 =
		mappings[OpCode_INC_DE].operand2 =
		mappings[OpCode_INC_E].operand2 =
		mappings[OpCode_INC_H].operand2 =
		mappings[OpCode_INC_HL].operand2 =
		mappings[OpCode_INC_L].operand2 =
		mappings[OpCode_INC_MEM_HL].operand2 =
		mappings[OpCode_INC_SP].operand2 = createGBByteValue(&(ONE));


		mappings[OpCode_ADD_SP_r8].operand2 = createGBByteValueSigned(&(hardware->cachedValues->immediateByte));
}

void populateALUResults(Hardware *hardware, InstructionMapping *mappings) {
	mappings[OpCode_XOR_A].result =
		mappings[OpCode_XOR_B].result =
		mappings[OpCode_XOR_C].result =
		mappings[OpCode_XOR_D].result =
		mappings[OpCode_XOR_E].result =
		mappings[OpCode_XOR_H].result =
		mappings[OpCode_XOR_L].result =
		mappings[OpCode_XOR_MEM_HL].result =
		mappings[OpCode_XOR_d8].result = &(hardware->cachedResults->xor);

	mappings[OpCode_DEC_A].result =
		mappings[OpCode_DEC_B].result =
		mappings[OpCode_DEC_BC].result =
		mappings[OpCode_DEC_C].result =
		mappings[OpCode_DEC_D].result =
		mappings[OpCode_DEC_DE].result =
		mappings[OpCode_DEC_E].result =
		mappings[OpCode_DEC_H].result =
		mappings[OpCode_DEC_HL].result =
		mappings[OpCode_DEC_L].result =
		mappings[OpCode_DEC_MEM_HL].result =
		mappings[OpCode_DEC_SP].result = &(hardware->cachedResults->subtract);

	mappings[OpCode_ADC_A_A].result =
		mappings[OpCode_ADC_A_B].result =
		mappings[OpCode_ADC_A_C].result =
		mappings[OpCode_ADC_A_D].result =
		mappings[OpCode_ADC_A_E].result =
		mappings[OpCode_ADC_A_H].result =
		mappings[OpCode_ADC_A_L].result =
		mappings[OpCode_ADC_A_MEM_HL].result =
		mappings[OpCode_ADC_A_d8].result =
		mappings[OpCode_ADD_A_A].result =
		mappings[OpCode_ADD_A_B].result =
		mappings[OpCode_ADD_A_C].result =
		mappings[OpCode_ADD_A_D].result =
		mappings[OpCode_ADD_A_E].result =
		mappings[OpCode_ADD_A_H].result =
		mappings[OpCode_ADD_A_L].result =
		mappings[OpCode_ADD_A_MEM_HL].result =
		mappings[OpCode_ADD_A_d8].result =
		mappings[OpCode_ADD_HL_BC].result =
		mappings[OpCode_ADD_HL_DE].result =
		mappings[OpCode_ADD_HL_HL].result =
		mappings[OpCode_ADD_HL_SP].result =
		mappings[OpCode_ADD_SP_r8].result = 
		mappings[OpCode_INC_A].result =
		mappings[OpCode_INC_B].result =
		mappings[OpCode_INC_BC].result =
		mappings[OpCode_INC_C].result =
		mappings[OpCode_INC_D].result =
		mappings[OpCode_INC_DE].result =
		mappings[OpCode_INC_E].result =
		mappings[OpCode_INC_H].result =
		mappings[OpCode_INC_HL].result =
		mappings[OpCode_INC_L].result =
		mappings[OpCode_INC_MEM_HL].result =
		mappings[OpCode_INC_SP].result = &(hardware->cachedResults->add);
}

void populateALUDestinations(Hardware *hardware, InstructionMapping *mappings) {
	mappings[OpCode_ADC_A_A].destination =
		mappings[OpCode_ADC_A_B].destination =
		mappings[OpCode_ADC_A_C].destination =
		mappings[OpCode_ADC_A_D].destination =
		mappings[OpCode_ADC_A_E].destination =
		mappings[OpCode_ADC_A_H].destination =
		mappings[OpCode_ADC_A_L].destination =
		mappings[OpCode_ADC_A_MEM_HL].destination =
		mappings[OpCode_ADC_A_d8].destination =
		mappings[OpCode_ADD_A_A].destination =
		mappings[OpCode_ADD_A_B].destination =
		mappings[OpCode_ADD_A_C].destination =
		mappings[OpCode_ADD_A_D].destination =
		mappings[OpCode_ADD_A_E].destination =
		mappings[OpCode_ADD_A_H].destination =
		mappings[OpCode_ADD_A_L].destination =
		mappings[OpCode_ADD_A_MEM_HL].destination =
		mappings[OpCode_ADD_A_d8].destination =
		mappings[OpCode_XOR_A].destination =
		mappings[OpCode_XOR_B].destination =
		mappings[OpCode_XOR_C].destination =
		mappings[OpCode_XOR_D].destination =
		mappings[OpCode_XOR_E].destination =
		mappings[OpCode_XOR_H].destination =
		mappings[OpCode_XOR_L].destination =
		mappings[OpCode_XOR_MEM_HL].destination =
		mappings[OpCode_XOR_d8].destination = createGBByteValue(&(hardware->registers->A));


	mappings[OpCode_INC_A].destination =
		mappings[OpCode_DEC_A].destination = createGBByteValue(&(hardware->registers->A));
	mappings[OpCode_INC_B].destination =
		mappings[OpCode_DEC_B].destination = createGBByteValue(&(hardware->registers->B));
	mappings[OpCode_INC_BC].destination =
		mappings[OpCode_DEC_BC].destination = createGBSplitByteValue(&(hardware->registers->B), &(hardware->registers->C));
	mappings[OpCode_INC_C].destination =
		mappings[OpCode_DEC_C].destination = createGBByteValue(&(hardware->registers->C));
	mappings[OpCode_INC_D].destination =
		mappings[OpCode_DEC_D].destination = createGBByteValue(&(hardware->registers->D));
	mappings[OpCode_INC_DE].destination =
		mappings[OpCode_DEC_DE].destination = createGBSplitByteValue(&(hardware->registers->D), &(hardware->registers->E));
	mappings[OpCode_INC_E].destination =
		mappings[OpCode_DEC_E].destination = createGBByteValue(&(hardware->registers->E));
	mappings[OpCode_INC_H].destination =
		mappings[OpCode_DEC_H].destination = createGBByteValue(&(hardware->registers->H));


	mappings[OpCode_ADD_HL_BC].destination =
		mappings[OpCode_ADD_HL_DE].destination =
		mappings[OpCode_ADD_HL_HL].destination =
		mappings[OpCode_ADD_HL_SP].destination =
		mappings[OpCode_INC_HL].destination =
		mappings[OpCode_DEC_HL].destination = createGBSplitByteValue(&(hardware->registers->H), &(hardware->registers->L));

	mappings[OpCode_INC_L].destination =
		mappings[OpCode_DEC_L].destination = createGBByteValue(&(hardware->registers->L));
	mappings[OpCode_INC_MEM_HL].destination =
		mappings[OpCode_DEC_MEM_HL].destination = createGBBytePointer(&(hardware->cachedValues->memoryHL));


	mappings[OpCode_ADD_SP_r8].destination =
		mappings[OpCode_INC_SP].destination =
		mappings[OpCode_DEC_SP].destination = createGBWordValue(&(hardware->registers->SP));
}

void populateALUFlagResults(Hardware *hardware, InstructionMapping *mappings) {
	mappings[OpCode_XOR_A].flagResult =
		mappings[OpCode_XOR_B].flagResult =
		mappings[OpCode_XOR_C].flagResult =
		mappings[OpCode_XOR_D].flagResult =
		mappings[OpCode_XOR_E].flagResult =
		mappings[OpCode_XOR_H].flagResult =
		mappings[OpCode_XOR_L].flagResult =
		mappings[OpCode_XOR_MEM_HL].flagResult =
		mappings[OpCode_XOR_d8].flagResult = createFlagResult(&(hardware->resultInfo->isZero), &FALSE_VAL, &FALSE_VAL, &FALSE_VAL);

	mappings[OpCode_DEC_A].flagResult =
		mappings[OpCode_DEC_B].flagResult =
		mappings[OpCode_DEC_C].flagResult =
		mappings[OpCode_DEC_D].flagResult =
		mappings[OpCode_DEC_E].flagResult =
		mappings[OpCode_DEC_H].flagResult =
		mappings[OpCode_DEC_L].flagResult =
		mappings[OpCode_DEC_BC].flagResult =
		mappings[OpCode_DEC_DE].flagResult =
		mappings[OpCode_DEC_HL].flagResult =
		mappings[OpCode_DEC_SP].flagResult =
		mappings[OpCode_DEC_MEM_HL].flagResult = createFlagResult(&(hardware->resultInfo->isZero), &TRUE_VAL, &(hardware->resultInfo->isSubHalfBorrow), NULL);


	mappings[OpCode_INC_A].flagResult =
		mappings[OpCode_INC_B].flagResult =
		mappings[OpCode_INC_BC].flagResult =
		mappings[OpCode_INC_C].flagResult =
		mappings[OpCode_INC_D].flagResult =
		mappings[OpCode_INC_DE].flagResult =
		mappings[OpCode_INC_E].flagResult =
		mappings[OpCode_INC_H].flagResult =
		mappings[OpCode_INC_HL].flagResult =
		mappings[OpCode_INC_L].flagResult =
		mappings[OpCode_INC_MEM_HL].flagResult =
		mappings[OpCode_INC_SP].flagResult = createFlagResult(&(hardware->resultInfo->isZero), &FALSE_VAL, &(hardware->resultInfo->isAddHalfCarry), NULL);

	mappings[OpCode_ADC_A_A].flagResult =
		mappings[OpCode_ADC_A_B].flagResult =
		mappings[OpCode_ADC_A_C].flagResult =
		mappings[OpCode_ADC_A_D].flagResult =
		mappings[OpCode_ADC_A_E].flagResult =
		mappings[OpCode_ADC_A_H].flagResult =
		mappings[OpCode_ADC_A_L].flagResult =
		mappings[OpCode_ADC_A_MEM_HL].flagResult =
		mappings[OpCode_ADC_A_d8].flagResult =
		mappings[OpCode_ADD_A_A].flagResult =
		mappings[OpCode_ADD_A_B].flagResult =
		mappings[OpCode_ADD_A_C].flagResult =
		mappings[OpCode_ADD_A_D].flagResult =
		mappings[OpCode_ADD_A_E].flagResult =
		mappings[OpCode_ADD_A_H].flagResult =
		mappings[OpCode_ADD_A_L].flagResult =
		mappings[OpCode_ADD_A_MEM_HL].flagResult =
		mappings[OpCode_ADD_A_d8].flagResult = createFlagResult(&(hardware->resultInfo->isZero), &FALSE_VAL, &(hardware->resultInfo->isAddHalfCarry), &(hardware->resultInfo->isAddCarry));

		mappings[OpCode_ADD_HL_BC].flagResult =
		mappings[OpCode_ADD_HL_DE].flagResult =
		mappings[OpCode_ADD_HL_HL].flagResult =
		mappings[OpCode_ADD_HL_SP].flagResult = createFlagResult(NULL, &FALSE_VAL, &(hardware->resultInfo->isAddHalfCarry16), &(hardware->resultInfo->isAddCarry16));

		mappings[OpCode_ADD_SP_r8].flagResult = createFlagResult(&FALSE_VAL, &FALSE_VAL, &(hardware->resultInfo->isAddHalfCarry16), &(hardware->resultInfo->isAddCarry16));
}
