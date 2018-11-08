
#include "cpu_alu.h"
#include <stdbool.h>

static const bool FALSE_VAL = false;
static const bool TRUE_VAL = true;
static const unsigned char ONE = 1;
static const unsigned char MAX_BYTE = 0xff;
static const unsigned char FLAGS_CY_VALUE = FLAGS_CY;



void populateALUInstructions(InstructionMappingList *mappings) {
	populateALUOperands1(mappings);
	populateALUOperands2(mappings);
	populateALUResults(mappings);
	populateALUDestinations(mappings);
	populateALUFlagResults(mappings);
}

void populateALUOperands1(InstructionMappingList *mappings) {
	mappings->mappings[OpCode_ADD_A_A].operand1 =
		mappings->mappings[OpCode_ADD_A_B].operand1 =
		mappings->mappings[OpCode_ADD_A_C].operand1 =
		mappings->mappings[OpCode_ADD_A_D].operand1 =
		mappings->mappings[OpCode_ADD_A_E].operand1 =
		mappings->mappings[OpCode_ADD_A_H].operand1 =
		mappings->mappings[OpCode_ADD_A_L].operand1 =
		mappings->mappings[OpCode_ADD_A_MEM_HL].operand1 =
		mappings->mappings[OpCode_ADD_A_d8].operand1 =
		mappings->mappings[OpCode_CP_A].operand1 =
		mappings->mappings[OpCode_CP_B].operand1 =
		mappings->mappings[OpCode_CP_C].operand1 =
		mappings->mappings[OpCode_CP_D].operand1 =
		mappings->mappings[OpCode_CP_E].operand1 =
		mappings->mappings[OpCode_CP_H].operand1 =
		mappings->mappings[OpCode_CP_L].operand1 =
		mappings->mappings[OpCode_CP_MEM_HL].operand1 =
		mappings->mappings[OpCode_CP_d8].operand1 =
		mappings->mappings[OpCode_CPL].operand1 =
		//mappings->mappings[OpCode_DAA].operand1 =
		mappings->mappings[OpCode_SUB_A].operand1 =
		mappings->mappings[OpCode_SUB_B].operand1 =
		mappings->mappings[OpCode_SUB_C].operand1 =
		mappings->mappings[OpCode_SUB_D].operand1 =
		mappings->mappings[OpCode_SUB_E].operand1 =
		mappings->mappings[OpCode_SUB_H].operand1 =
		mappings->mappings[OpCode_SUB_L].operand1 =
		mappings->mappings[OpCode_SUB_MEM_HL].operand1 =
		mappings->mappings[OpCode_SUB_d8].operand1 =
		mappings->mappings[OpCode_AND_A].operand1 =
		mappings->mappings[OpCode_AND_B].operand1 =
		mappings->mappings[OpCode_AND_C].operand1 =
		mappings->mappings[OpCode_AND_D].operand1 =
		mappings->mappings[OpCode_AND_E].operand1 =
		mappings->mappings[OpCode_AND_H].operand1 =
		mappings->mappings[OpCode_AND_L].operand1 =
		mappings->mappings[OpCode_AND_MEM_HL].operand1 =
		mappings->mappings[OpCode_AND_d8].operand1 =
		mappings->mappings[OpCode_OR_A].operand1 =
		mappings->mappings[OpCode_OR_B].operand1 =
		mappings->mappings[OpCode_OR_C].operand1 =
		mappings->mappings[OpCode_OR_D].operand1 =
		mappings->mappings[OpCode_OR_E].operand1 =
		mappings->mappings[OpCode_OR_H].operand1 =
		mappings->mappings[OpCode_OR_L].operand1 =
		mappings->mappings[OpCode_OR_MEM_HL].operand1 =
		mappings->mappings[OpCode_OR_d8].operand1 =
		mappings->mappings[OpCode_XOR_A].operand1 =
		mappings->mappings[OpCode_XOR_B].operand1 =
		mappings->mappings[OpCode_XOR_C].operand1 =
		mappings->mappings[OpCode_XOR_D].operand1 =
		mappings->mappings[OpCode_XOR_E].operand1 =
		mappings->mappings[OpCode_XOR_H].operand1 =
		mappings->mappings[OpCode_XOR_L].operand1 =
		mappings->mappings[OpCode_XOR_MEM_HL].operand1 =
		mappings->mappings[OpCode_XOR_d8].operand1 = 
		mappings->mappings[OpCode_ADC_A_A].operand1 =
		mappings->mappings[OpCode_ADC_A_B].operand1 =
		mappings->mappings[OpCode_ADC_A_C].operand1 =
		mappings->mappings[OpCode_ADC_A_D].operand1 =
		mappings->mappings[OpCode_ADC_A_E].operand1 =
		mappings->mappings[OpCode_ADC_A_H].operand1 =
		mappings->mappings[OpCode_ADC_A_L].operand1 =
		mappings->mappings[OpCode_ADC_A_MEM_HL].operand1 =
		mappings->mappings[OpCode_ADC_A_d8].operand1 = 
		mappings->mappings[OpCode_SBC_A_A].operand1 =
		mappings->mappings[OpCode_SBC_A_B].operand1 =
		mappings->mappings[OpCode_SBC_A_C].operand1 =
		mappings->mappings[OpCode_SBC_A_D].operand1 =
		mappings->mappings[OpCode_SBC_A_E].operand1 =
		mappings->mappings[OpCode_SBC_A_H].operand1 =
		mappings->mappings[OpCode_SBC_A_L].operand1 =
		mappings->mappings[OpCode_SBC_A_MEM_HL].operand1 =
		mappings->mappings[OpCode_SBC_A_d8].operand1 = createGBByteValue(&(hardware->registers->A));

	mappings->mappings[OpCode_INC_A].operand1 =
		mappings->mappings[OpCode_DEC_A].operand1 = createGBByteValue(&(hardware->registers->A));
	mappings->mappings[OpCode_INC_B].operand1 =
		mappings->mappings[OpCode_DEC_B].operand1 = createGBByteValue(&(hardware->registers->B));
	mappings->mappings[OpCode_INC_BC].operand1 =
		mappings->mappings[OpCode_DEC_BC].operand1 = createGBWordValue(&(hardware->computedValues->BC));
	mappings->mappings[OpCode_INC_C].operand1 =
		mappings->mappings[OpCode_DEC_C].operand1 = createGBByteValue(&(hardware->registers->C));
	mappings->mappings[OpCode_INC_D].operand1 =
		mappings->mappings[OpCode_DEC_D].operand1 = createGBByteValue(&(hardware->registers->D));
	mappings->mappings[OpCode_INC_DE].operand1 =
		mappings->mappings[OpCode_DEC_DE].operand1 = createGBWordValue(&(hardware->computedValues->DE));
	mappings->mappings[OpCode_INC_E].operand1 =
		mappings->mappings[OpCode_DEC_E].operand1 = createGBByteValue(&(hardware->registers->E));
	mappings->mappings[OpCode_INC_H].operand1 =
		mappings->mappings[OpCode_DEC_H].operand1 = createGBByteValue(&(hardware->registers->H));

	mappings->mappings[OpCode_ADD_HL_BC].operand1 =
		mappings->mappings[OpCode_ADD_HL_DE].operand1 =
		mappings->mappings[OpCode_ADD_HL_HL].operand1 =
		mappings->mappings[OpCode_ADD_HL_SP].operand1 =
		mappings->mappings[OpCode_INC_HL].operand1 =
		mappings->mappings[OpCode_DEC_HL].operand1 = createGBWordValue(&(hardware->computedValues->HL));

	mappings->mappings[OpCode_INC_L].operand1 =
		mappings->mappings[OpCode_DEC_L].operand1 = createGBByteValue(&(hardware->registers->L));
	mappings->mappings[OpCode_INC_MEM_HL].operand1 =
		mappings->mappings[OpCode_DEC_MEM_HL].operand1 = createGBBytePointer(&(hardware->computedValues->memoryHL));

	mappings->mappings[OpCode_INC_SP].operand1 =
		mappings->mappings[OpCode_DEC_SP].operand1 = createGBWordValue(&(hardware->registers->SP));

	mappings->mappings[OpCode_ADD_SP_r8].operand1 = createGBWordValue(&(hardware->registers->SP));

	mappings->mappings[OpCode_CCF].operand1 = createGBByteValue(&(hardware->registers->F));
}

void populateALUOperands2(InstructionMappingList *mappings) {
	mappings->mappings[OpCode_ADC_A_A].operand2 =
		mappings->mappings[OpCode_ADD_A_A].operand2 =
		mappings->mappings[OpCode_CP_A].operand2 =
		mappings->mappings[OpCode_SBC_A_A].operand2 =
		mappings->mappings[OpCode_SUB_A].operand2 =
		mappings->mappings[OpCode_AND_A].operand2 =
		mappings->mappings[OpCode_OR_A].operand2 =
		mappings->mappings[OpCode_XOR_A].operand2 = createGBByteValue(&(hardware->registers->A));

	mappings->mappings[OpCode_ADC_A_B].operand2 =
		mappings->mappings[OpCode_ADD_A_B].operand2 =
		mappings->mappings[OpCode_CP_B].operand2 =
		mappings->mappings[OpCode_SBC_A_B].operand2 =
		mappings->mappings[OpCode_SUB_B].operand2 =
		mappings->mappings[OpCode_AND_B].operand2 =
		mappings->mappings[OpCode_OR_B].operand2 =
		mappings->mappings[OpCode_XOR_B].operand2 = createGBByteValue(&(hardware->registers->B));

	mappings->mappings[OpCode_ADC_A_C].operand2 =
		mappings->mappings[OpCode_ADD_A_C].operand2 =
		mappings->mappings[OpCode_CP_C].operand2 =
		mappings->mappings[OpCode_SBC_A_C].operand2 =
		mappings->mappings[OpCode_SUB_C].operand2 =
		mappings->mappings[OpCode_AND_C].operand2 =
		mappings->mappings[OpCode_OR_C].operand2 =
		mappings->mappings[OpCode_XOR_C].operand2 = createGBByteValue(&(hardware->registers->C));

	mappings->mappings[OpCode_ADC_A_D].operand2 =
		mappings->mappings[OpCode_ADD_A_D].operand2 =
		mappings->mappings[OpCode_CP_D].operand2 =
		mappings->mappings[OpCode_SBC_A_D].operand2 =
		mappings->mappings[OpCode_SUB_D].operand2 =
		mappings->mappings[OpCode_AND_D].operand2 =
		mappings->mappings[OpCode_OR_D].operand2 =
		mappings->mappings[OpCode_XOR_D].operand2 = createGBByteValue(&(hardware->registers->D));

	mappings->mappings[OpCode_ADC_A_E].operand2 =
		mappings->mappings[OpCode_ADD_A_E].operand2 =
		mappings->mappings[OpCode_CP_E].operand2 =
		mappings->mappings[OpCode_SBC_A_E].operand2 =
		mappings->mappings[OpCode_SUB_E].operand2 =
		mappings->mappings[OpCode_AND_E].operand2 =
		mappings->mappings[OpCode_OR_E].operand2 =
		mappings->mappings[OpCode_XOR_E].operand2 = createGBByteValue(&(hardware->registers->E));

	mappings->mappings[OpCode_ADC_A_H].operand2 =
		mappings->mappings[OpCode_ADD_A_H].operand2 =
		mappings->mappings[OpCode_CP_H].operand2 =
		mappings->mappings[OpCode_SBC_A_H].operand2 =
		mappings->mappings[OpCode_SUB_H].operand2 =
		mappings->mappings[OpCode_AND_H].operand2 =
		mappings->mappings[OpCode_OR_H].operand2 =
		mappings->mappings[OpCode_XOR_H].operand2 = createGBByteValue(&(hardware->registers->H));

	mappings->mappings[OpCode_ADC_A_L].operand2 =
		mappings->mappings[OpCode_ADD_A_L].operand2 =
		mappings->mappings[OpCode_CP_L].operand2 =
		mappings->mappings[OpCode_SBC_A_L].operand2 =
		mappings->mappings[OpCode_SUB_L].operand2 =
		mappings->mappings[OpCode_AND_L].operand2 =
		mappings->mappings[OpCode_OR_L].operand2 =
		mappings->mappings[OpCode_XOR_L].operand2 = createGBByteValue(&(hardware->registers->L));

	mappings->mappings[OpCode_ADC_A_MEM_HL].operand2 =
		mappings->mappings[OpCode_ADD_A_MEM_HL].operand2 =
		mappings->mappings[OpCode_CP_MEM_HL].operand2 =
		mappings->mappings[OpCode_SBC_A_MEM_HL].operand2 =
		mappings->mappings[OpCode_SUB_MEM_HL].operand2 =
		mappings->mappings[OpCode_AND_MEM_HL].operand2 =
		mappings->mappings[OpCode_OR_MEM_HL].operand2 =
		mappings->mappings[OpCode_XOR_MEM_HL].operand2 = createGBBytePointer(&(hardware->computedValues->memoryHL));

	mappings->mappings[OpCode_ADC_A_d8].operand2 =
		mappings->mappings[OpCode_ADD_A_d8].operand2 =
		mappings->mappings[OpCode_CP_d8].operand2 =
		mappings->mappings[OpCode_SBC_A_d8].operand2 =
		mappings->mappings[OpCode_SUB_d8].operand2 =
		mappings->mappings[OpCode_AND_d8].operand2 =
		mappings->mappings[OpCode_OR_d8].operand2 =
		mappings->mappings[OpCode_XOR_d8].operand2 = createGBByteValue(&(hardware->computedValues->immediateByte));


	mappings->mappings[OpCode_ADD_HL_BC].operand2 = createGBWordValue(&(hardware->computedValues->BC));
	mappings->mappings[OpCode_ADD_HL_DE].operand2 = createGBWordValue(&(hardware->computedValues->DE));
	mappings->mappings[OpCode_ADD_HL_HL].operand2 = createGBWordValue(&(hardware->computedValues->HL));
	mappings->mappings[OpCode_ADD_HL_SP].operand2 = createGBWordValue(&(hardware->registers->SP));

	mappings->mappings[OpCode_DEC_A].operand2 =
		mappings->mappings[OpCode_DEC_B].operand2 =
		mappings->mappings[OpCode_DEC_BC].operand2 =
		mappings->mappings[OpCode_DEC_C].operand2 =
		mappings->mappings[OpCode_DEC_D].operand2 =
		mappings->mappings[OpCode_DEC_DE].operand2 =
		mappings->mappings[OpCode_DEC_E].operand2 =
		mappings->mappings[OpCode_DEC_H].operand2 =
		mappings->mappings[OpCode_DEC_HL].operand2 =
		mappings->mappings[OpCode_DEC_L].operand2 =
		mappings->mappings[OpCode_DEC_MEM_HL].operand2 =
		mappings->mappings[OpCode_DEC_SP].operand2 =
		mappings->mappings[OpCode_INC_A].operand2 =
		mappings->mappings[OpCode_INC_B].operand2 =
		mappings->mappings[OpCode_INC_BC].operand2 =
		mappings->mappings[OpCode_INC_C].operand2 =
		mappings->mappings[OpCode_INC_D].operand2 =
		mappings->mappings[OpCode_INC_DE].operand2 =
		mappings->mappings[OpCode_INC_E].operand2 =
		mappings->mappings[OpCode_INC_H].operand2 =
		mappings->mappings[OpCode_INC_HL].operand2 =
		mappings->mappings[OpCode_INC_L].operand2 =
		mappings->mappings[OpCode_INC_MEM_HL].operand2 =
		mappings->mappings[OpCode_INC_SP].operand2 = createGBByteValue(&(ONE));

	mappings->mappings[OpCode_ADD_SP_r8].operand2 = createGBByteValueSigned(&(hardware->computedValues->immediateByte));
	mappings->mappings[OpCode_CPL].operand2 = createGBByteValue(&(MAX_BYTE));

	mappings->mappings[OpCode_CCF].operand2 = createGBByteValue(&(FLAGS_CY_VALUE));
}

void populateALUResults(InstructionMappingList *mappings) {
	mappings->mappings[OpCode_DEC_A].result =
		mappings->mappings[OpCode_DEC_B].result =
		mappings->mappings[OpCode_DEC_BC].result =
		mappings->mappings[OpCode_DEC_C].result =
		mappings->mappings[OpCode_DEC_D].result =
		mappings->mappings[OpCode_DEC_DE].result =
		mappings->mappings[OpCode_DEC_E].result =
		mappings->mappings[OpCode_DEC_H].result =
		mappings->mappings[OpCode_DEC_HL].result =
		mappings->mappings[OpCode_DEC_L].result =
		mappings->mappings[OpCode_DEC_MEM_HL].result =
		mappings->mappings[OpCode_DEC_SP].result = &(hardware->operationResults->subtract);

		mappings->mappings[OpCode_ADD_A_A].result =
		mappings->mappings[OpCode_ADD_A_B].result =
		mappings->mappings[OpCode_ADD_A_C].result =
		mappings->mappings[OpCode_ADD_A_D].result =
		mappings->mappings[OpCode_ADD_A_E].result =
		mappings->mappings[OpCode_ADD_A_H].result =
		mappings->mappings[OpCode_ADD_A_L].result =
		mappings->mappings[OpCode_ADD_A_MEM_HL].result =
		mappings->mappings[OpCode_ADD_A_d8].result =
		mappings->mappings[OpCode_ADD_HL_BC].result =
		mappings->mappings[OpCode_ADD_HL_DE].result =
		mappings->mappings[OpCode_ADD_HL_HL].result =
		mappings->mappings[OpCode_ADD_HL_SP].result =
		mappings->mappings[OpCode_ADD_SP_r8].result =
		mappings->mappings[OpCode_INC_A].result =
		mappings->mappings[OpCode_INC_B].result =
		mappings->mappings[OpCode_INC_BC].result =
		mappings->mappings[OpCode_INC_C].result =
		mappings->mappings[OpCode_INC_D].result =
		mappings->mappings[OpCode_INC_DE].result =
		mappings->mappings[OpCode_INC_E].result =
		mappings->mappings[OpCode_INC_H].result =
		mappings->mappings[OpCode_INC_HL].result =
		mappings->mappings[OpCode_INC_L].result =
		mappings->mappings[OpCode_INC_MEM_HL].result =
		mappings->mappings[OpCode_INC_SP].result = &(hardware->operationResults->add);


		mappings->mappings[OpCode_ADC_A_A].result =
			mappings->mappings[OpCode_ADC_A_B].result =
			mappings->mappings[OpCode_ADC_A_C].result =
			mappings->mappings[OpCode_ADC_A_D].result =
			mappings->mappings[OpCode_ADC_A_E].result =
			mappings->mappings[OpCode_ADC_A_H].result =
			mappings->mappings[OpCode_ADC_A_L].result =
			mappings->mappings[OpCode_ADC_A_MEM_HL].result =
			mappings->mappings[OpCode_ADC_A_d8].result = &(hardware->operationResults->addWithCarry);

	mappings->mappings[OpCode_CP_A].result =
		mappings->mappings[OpCode_CP_B].result =
		mappings->mappings[OpCode_CP_C].result =
		mappings->mappings[OpCode_CP_D].result =
		mappings->mappings[OpCode_CP_E].result =
		mappings->mappings[OpCode_CP_H].result =
		mappings->mappings[OpCode_CP_L].result =
		mappings->mappings[OpCode_CP_MEM_HL].result =
		mappings->mappings[OpCode_CP_d8].result =
		mappings->mappings[OpCode_SUB_A].result =
		mappings->mappings[OpCode_SUB_B].result =
		mappings->mappings[OpCode_SUB_C].result =
		mappings->mappings[OpCode_SUB_D].result =
		mappings->mappings[OpCode_SUB_E].result =
		mappings->mappings[OpCode_SUB_H].result =
		mappings->mappings[OpCode_SUB_L].result =
		mappings->mappings[OpCode_SUB_MEM_HL].result =
		mappings->mappings[OpCode_SUB_d8].result = &(hardware->operationResults->subtract);

	mappings->mappings[OpCode_SBC_A_A].result =
		mappings->mappings[OpCode_SBC_A_B].result =
		mappings->mappings[OpCode_SBC_A_C].result =
		mappings->mappings[OpCode_SBC_A_D].result =
		mappings->mappings[OpCode_SBC_A_E].result =
		mappings->mappings[OpCode_SBC_A_H].result =
		mappings->mappings[OpCode_SBC_A_L].result =
		mappings->mappings[OpCode_SBC_A_MEM_HL].result =
		mappings->mappings[OpCode_SBC_A_d8].result = &(hardware->operationResults->subtractWithCarry);

	mappings->mappings[OpCode_AND_A].result =
		mappings->mappings[OpCode_AND_B].result =
		mappings->mappings[OpCode_AND_C].result =
		mappings->mappings[OpCode_AND_D].result =
		mappings->mappings[OpCode_AND_E].result =
		mappings->mappings[OpCode_AND_H].result =
		mappings->mappings[OpCode_AND_L].result =
		mappings->mappings[OpCode_AND_MEM_HL].result =
		mappings->mappings[OpCode_AND_d8].result =
		mappings->mappings[OpCode_CCF].result = &(hardware->operationResults->and);

	
	mappings->mappings[OpCode_OR_A].result =
		mappings->mappings[OpCode_OR_B].result =
		mappings->mappings[OpCode_OR_C].result =
		mappings->mappings[OpCode_OR_D].result =
		mappings->mappings[OpCode_OR_E].result =
		mappings->mappings[OpCode_OR_H].result =
		mappings->mappings[OpCode_OR_L].result =
		mappings->mappings[OpCode_OR_MEM_HL].result =
		mappings->mappings[OpCode_OR_d8].result = &(hardware->operationResults-> or);

	mappings->mappings[OpCode_XOR_A].result =
		mappings->mappings[OpCode_XOR_B].result =
		mappings->mappings[OpCode_XOR_C].result =
		mappings->mappings[OpCode_XOR_D].result =
		mappings->mappings[OpCode_XOR_E].result =
		mappings->mappings[OpCode_XOR_H].result =
		mappings->mappings[OpCode_XOR_L].result =
		mappings->mappings[OpCode_XOR_MEM_HL].result =
		mappings->mappings[OpCode_XOR_d8].result =
		mappings->mappings[OpCode_CPL].result = &(hardware->operationResults->xor);
}

void populateALUDestinations(InstructionMappingList *mappings) {
	mappings->mappings[OpCode_ADC_A_A].destination =
		mappings->mappings[OpCode_ADC_A_B].destination =
		mappings->mappings[OpCode_ADC_A_C].destination =
		mappings->mappings[OpCode_ADC_A_D].destination =
		mappings->mappings[OpCode_ADC_A_E].destination =
		mappings->mappings[OpCode_ADC_A_H].destination =
		mappings->mappings[OpCode_ADC_A_L].destination =
		mappings->mappings[OpCode_ADC_A_MEM_HL].destination =
		mappings->mappings[OpCode_ADC_A_d8].destination =
		mappings->mappings[OpCode_ADD_A_A].destination =
		mappings->mappings[OpCode_ADD_A_B].destination =
		mappings->mappings[OpCode_ADD_A_C].destination =
		mappings->mappings[OpCode_ADD_A_D].destination =
		mappings->mappings[OpCode_ADD_A_E].destination =
		mappings->mappings[OpCode_ADD_A_H].destination =
		mappings->mappings[OpCode_ADD_A_L].destination =
		mappings->mappings[OpCode_ADD_A_MEM_HL].destination =
		mappings->mappings[OpCode_ADD_A_d8].destination =
		mappings->mappings[OpCode_CPL].destination =
		//mappings->mappings[OpCode_DAA].destination =
		mappings->mappings[OpCode_SBC_A_A].destination =
		mappings->mappings[OpCode_SBC_A_B].destination =
		mappings->mappings[OpCode_SBC_A_C].destination =
		mappings->mappings[OpCode_SBC_A_D].destination =
		mappings->mappings[OpCode_SBC_A_E].destination =
		mappings->mappings[OpCode_SBC_A_H].destination =
		mappings->mappings[OpCode_SBC_A_L].destination =
		mappings->mappings[OpCode_SBC_A_MEM_HL].destination =
		mappings->mappings[OpCode_SBC_A_d8].destination =
		mappings->mappings[OpCode_SUB_A].destination =
		mappings->mappings[OpCode_SUB_B].destination =
		mappings->mappings[OpCode_SUB_C].destination =
		mappings->mappings[OpCode_SUB_D].destination =
		mappings->mappings[OpCode_SUB_E].destination =
		mappings->mappings[OpCode_SUB_H].destination =
		mappings->mappings[OpCode_SUB_L].destination =
		mappings->mappings[OpCode_SUB_MEM_HL].destination =
		mappings->mappings[OpCode_SUB_d8].destination =
		mappings->mappings[OpCode_AND_A].destination =
		mappings->mappings[OpCode_AND_B].destination =
		mappings->mappings[OpCode_AND_C].destination =
		mappings->mappings[OpCode_AND_D].destination =
		mappings->mappings[OpCode_AND_E].destination =
		mappings->mappings[OpCode_AND_H].destination =
		mappings->mappings[OpCode_AND_L].destination =
		mappings->mappings[OpCode_AND_MEM_HL].destination =
		mappings->mappings[OpCode_AND_d8].destination =
		mappings->mappings[OpCode_OR_A].destination =
		mappings->mappings[OpCode_OR_B].destination =
		mappings->mappings[OpCode_OR_C].destination =
		mappings->mappings[OpCode_OR_D].destination =
		mappings->mappings[OpCode_OR_E].destination =
		mappings->mappings[OpCode_OR_H].destination =
		mappings->mappings[OpCode_OR_L].destination =
		mappings->mappings[OpCode_OR_MEM_HL].destination =
		mappings->mappings[OpCode_OR_d8].destination =
		mappings->mappings[OpCode_XOR_A].destination =
		mappings->mappings[OpCode_XOR_B].destination =
		mappings->mappings[OpCode_XOR_C].destination =
		mappings->mappings[OpCode_XOR_D].destination =
		mappings->mappings[OpCode_XOR_E].destination =
		mappings->mappings[OpCode_XOR_H].destination =
		mappings->mappings[OpCode_XOR_L].destination =
		mappings->mappings[OpCode_XOR_MEM_HL].destination =
		mappings->mappings[OpCode_XOR_d8].destination = createGBByteValue(&(hardware->registers->A));


	mappings->mappings[OpCode_INC_A].destination =
		mappings->mappings[OpCode_DEC_A].destination = createGBByteValue(&(hardware->registers->A));
	mappings->mappings[OpCode_INC_B].destination =
		mappings->mappings[OpCode_DEC_B].destination = createGBByteValue(&(hardware->registers->B));
	mappings->mappings[OpCode_INC_BC].destination =
		mappings->mappings[OpCode_DEC_BC].destination = createGBSplitByteValue(&(hardware->registers->B), &(hardware->registers->C));
	mappings->mappings[OpCode_INC_C].destination =
		mappings->mappings[OpCode_DEC_C].destination = createGBByteValue(&(hardware->registers->C));
	mappings->mappings[OpCode_INC_D].destination =
		mappings->mappings[OpCode_DEC_D].destination = createGBByteValue(&(hardware->registers->D));
	mappings->mappings[OpCode_INC_DE].destination =
		mappings->mappings[OpCode_DEC_DE].destination = createGBSplitByteValue(&(hardware->registers->D), &(hardware->registers->E));
	mappings->mappings[OpCode_INC_E].destination =
		mappings->mappings[OpCode_DEC_E].destination = createGBByteValue(&(hardware->registers->E));
	mappings->mappings[OpCode_INC_H].destination =
		mappings->mappings[OpCode_DEC_H].destination = createGBByteValue(&(hardware->registers->H));


	mappings->mappings[OpCode_ADD_HL_BC].destination =
		mappings->mappings[OpCode_ADD_HL_DE].destination =
		mappings->mappings[OpCode_ADD_HL_HL].destination =
		mappings->mappings[OpCode_ADD_HL_SP].destination =
		mappings->mappings[OpCode_INC_HL].destination =
		mappings->mappings[OpCode_DEC_HL].destination = createGBSplitByteValue(&(hardware->registers->H), &(hardware->registers->L));

	mappings->mappings[OpCode_INC_L].destination =
		mappings->mappings[OpCode_DEC_L].destination = createGBByteValue(&(hardware->registers->L));
	mappings->mappings[OpCode_INC_MEM_HL].destination =
		mappings->mappings[OpCode_DEC_MEM_HL].destination = createGBBytePointer(&(hardware->computedValues->memoryHL));


	mappings->mappings[OpCode_ADD_SP_r8].destination =
		mappings->mappings[OpCode_INC_SP].destination =
		mappings->mappings[OpCode_DEC_SP].destination = createGBWordValue(&(hardware->registers->SP));
}

void populateALUFlagResults(InstructionMappingList *mappings) {
	mappings->mappings[OpCode_AND_A].flagResult =
		mappings->mappings[OpCode_AND_B].flagResult =
		mappings->mappings[OpCode_AND_C].flagResult =
		mappings->mappings[OpCode_AND_D].flagResult =
		mappings->mappings[OpCode_AND_E].flagResult =
		mappings->mappings[OpCode_AND_H].flagResult =
		mappings->mappings[OpCode_AND_L].flagResult =
		mappings->mappings[OpCode_AND_MEM_HL].flagResult =
		mappings->mappings[OpCode_AND_d8].flagResult = createFlagResult(&(hardware->resultInfo->isZero), &FALSE_VAL, &TRUE_VAL, &FALSE_VAL);

	mappings->mappings[OpCode_OR_A].flagResult =
		mappings->mappings[OpCode_OR_B].flagResult =
		mappings->mappings[OpCode_OR_C].flagResult =
		mappings->mappings[OpCode_OR_D].flagResult =
		mappings->mappings[OpCode_OR_E].flagResult =
		mappings->mappings[OpCode_OR_H].flagResult =
		mappings->mappings[OpCode_OR_L].flagResult =
		mappings->mappings[OpCode_OR_MEM_HL].flagResult =
		mappings->mappings[OpCode_OR_d8].flagResult =
		mappings->mappings[OpCode_XOR_A].flagResult =
		mappings->mappings[OpCode_XOR_B].flagResult =
		mappings->mappings[OpCode_XOR_C].flagResult =
		mappings->mappings[OpCode_XOR_D].flagResult =
		mappings->mappings[OpCode_XOR_E].flagResult =
		mappings->mappings[OpCode_XOR_H].flagResult =
		mappings->mappings[OpCode_XOR_L].flagResult =
		mappings->mappings[OpCode_XOR_MEM_HL].flagResult =
		mappings->mappings[OpCode_XOR_d8].flagResult = createFlagResult(&(hardware->resultInfo->isZero), &FALSE_VAL, &FALSE_VAL, &FALSE_VAL);

	mappings->mappings[OpCode_DEC_A].flagResult =
		mappings->mappings[OpCode_DEC_B].flagResult =
		mappings->mappings[OpCode_DEC_C].flagResult =
		mappings->mappings[OpCode_DEC_D].flagResult =
		mappings->mappings[OpCode_DEC_E].flagResult =
		mappings->mappings[OpCode_DEC_H].flagResult =
		mappings->mappings[OpCode_DEC_L].flagResult =
		mappings->mappings[OpCode_DEC_MEM_HL].flagResult = createFlagResult(&(hardware->resultInfo->isZero), &TRUE_VAL, &(hardware->resultInfo->isSubHalfBorrow), NULL);


	mappings->mappings[OpCode_INC_A].flagResult =
		mappings->mappings[OpCode_INC_B].flagResult =
		mappings->mappings[OpCode_INC_C].flagResult =
		mappings->mappings[OpCode_INC_D].flagResult =
		mappings->mappings[OpCode_INC_E].flagResult =
		mappings->mappings[OpCode_INC_H].flagResult =
		mappings->mappings[OpCode_INC_L].flagResult =
		mappings->mappings[OpCode_INC_MEM_HL].flagResult = createFlagResult(&(hardware->resultInfo->isZero), &FALSE_VAL, &(hardware->resultInfo->isAddHalfCarry), NULL);
	
	mappings->mappings[OpCode_INC_BC].flagResult =
		mappings->mappings[OpCode_INC_DE].flagResult =
		mappings->mappings[OpCode_INC_HL].flagResult =
		mappings->mappings[OpCode_INC_SP].flagResult =
		mappings->mappings[OpCode_DEC_BC].flagResult =
		mappings->mappings[OpCode_DEC_DE].flagResult =
		mappings->mappings[OpCode_DEC_HL].flagResult =
		mappings->mappings[OpCode_DEC_SP].flagResult = NULL; //no flags affected

	mappings->mappings[OpCode_ADC_A_A].flagResult =
		mappings->mappings[OpCode_ADC_A_B].flagResult =
		mappings->mappings[OpCode_ADC_A_C].flagResult =
		mappings->mappings[OpCode_ADC_A_D].flagResult =
		mappings->mappings[OpCode_ADC_A_E].flagResult =
		mappings->mappings[OpCode_ADC_A_H].flagResult =
		mappings->mappings[OpCode_ADC_A_L].flagResult =
		mappings->mappings[OpCode_ADC_A_MEM_HL].flagResult =
		mappings->mappings[OpCode_ADC_A_d8].flagResult =
		mappings->mappings[OpCode_ADD_A_A].flagResult =
		mappings->mappings[OpCode_ADD_A_B].flagResult =
		mappings->mappings[OpCode_ADD_A_C].flagResult =
		mappings->mappings[OpCode_ADD_A_D].flagResult =
		mappings->mappings[OpCode_ADD_A_E].flagResult =
		mappings->mappings[OpCode_ADD_A_H].flagResult =
		mappings->mappings[OpCode_ADD_A_L].flagResult =
		mappings->mappings[OpCode_ADD_A_MEM_HL].flagResult =
		mappings->mappings[OpCode_ADD_A_d8].flagResult = createFlagResult(&(hardware->resultInfo->isZero), &FALSE_VAL, &(hardware->resultInfo->isAddHalfCarry), &(hardware->resultInfo->isAddCarry));

	mappings->mappings[OpCode_ADD_HL_BC].flagResult =
		mappings->mappings[OpCode_ADD_HL_DE].flagResult =
		mappings->mappings[OpCode_ADD_HL_HL].flagResult =
		mappings->mappings[OpCode_ADD_HL_SP].flagResult = createFlagResult(NULL, &FALSE_VAL, &(hardware->resultInfo->isAddHalfCarry16), &(hardware->resultInfo->isAddCarry16));

	mappings->mappings[OpCode_ADD_SP_r8].flagResult = createFlagResult(&FALSE_VAL, &FALSE_VAL, &(hardware->resultInfo->isAddHalfCarry16), &(hardware->resultInfo->isAddCarry16));

	mappings->mappings[OpCode_CP_A].flagResult =
		mappings->mappings[OpCode_CP_B].flagResult =
		mappings->mappings[OpCode_CP_C].flagResult =
		mappings->mappings[OpCode_CP_D].flagResult =
		mappings->mappings[OpCode_CP_E].flagResult =
		mappings->mappings[OpCode_CP_H].flagResult =
		mappings->mappings[OpCode_CP_L].flagResult =
		mappings->mappings[OpCode_CP_MEM_HL].flagResult =
		mappings->mappings[OpCode_CP_d8].flagResult =
		mappings->mappings[OpCode_SBC_A_A].flagResult =
		mappings->mappings[OpCode_SBC_A_B].flagResult =
		mappings->mappings[OpCode_SBC_A_C].flagResult =
		mappings->mappings[OpCode_SBC_A_D].flagResult =
		mappings->mappings[OpCode_SBC_A_E].flagResult =
		mappings->mappings[OpCode_SBC_A_H].flagResult =
		mappings->mappings[OpCode_SBC_A_L].flagResult =
		mappings->mappings[OpCode_SBC_A_MEM_HL].flagResult =
		mappings->mappings[OpCode_SBC_A_d8].flagResult =
		mappings->mappings[OpCode_SUB_A].flagResult =
		mappings->mappings[OpCode_SUB_B].flagResult =
		mappings->mappings[OpCode_SUB_C].flagResult =
		mappings->mappings[OpCode_SUB_D].flagResult =
		mappings->mappings[OpCode_SUB_E].flagResult =
		mappings->mappings[OpCode_SUB_H].flagResult =
		mappings->mappings[OpCode_SUB_L].flagResult =
		mappings->mappings[OpCode_SUB_MEM_HL].flagResult =
		mappings->mappings[OpCode_SUB_d8].flagResult = createFlagResult(&(hardware->resultInfo->isZero), &TRUE_VAL, &(hardware->resultInfo->isSubHalfBorrow), &(hardware->resultInfo->isSubBorrow));


	//mappings->mappings[OpCode_DAA].flagResult = createFlagResult(&(hardware->resultInfo->isZero), NULL, &FALSE_VAL, ?? );
	mappings->mappings[OpCode_CPL].flagResult = createFlagResult(NULL, &TRUE_VAL, &TRUE_VAL, NULL);

	mappings->mappings[OpCode_SCF].flagResult = createFlagResult(NULL, &FALSE_VAL, &FALSE_VAL, &TRUE_VAL);
	mappings->mappings[OpCode_CCF].flagResult = createFlagResult(NULL, &FALSE_VAL, &FALSE_VAL, &(hardware->resultInfo->isZero));
}
