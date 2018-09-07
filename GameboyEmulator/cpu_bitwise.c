

#include "cpu_bitwise.h"

static const bool FALSE_VAL = false;
static const bool TRUE_VAL = true;
static const unsigned char ZERO = 0;
static const unsigned char ONE = 1;
static const unsigned char TWO = 2;
static const unsigned char THREE = 3;
static const unsigned char FOUR = 4;
static const unsigned char FIVE = 5;
static const unsigned char SIX = 6;
static const unsigned char SEVEN = 7;

void populateBitwiseOperands1(Hardware *hardware, InstructionMapping *mappings);
void populateBitwiseOperands2Destinations(Hardware *hardware, InstructionMapping *mappings);
void populateBitwiseOperandsResults(Hardware *hardware, InstructionMapping *mappings);
void populateBitwiseOperandsFlags(Hardware *hardware, InstructionMapping *mappings);

void populateBitwiseInstructions(Hardware *hardware, InstructionMapping *mappings) {
	populateBitwiseOperands1(hardware, mappings);
	populateBitwiseOperands2Destinations(hardware, mappings);
	populateBitwiseOperandsResults(hardware, mappings);
	populateBitwiseOperandsFlags(hardware, mappings);
}

void populateBitwiseOperands1(Hardware *hardware, InstructionMapping *mappings) {
	/*
	OpCode_RLC_B
	OpCode_RLC_C
	OpCode_RLC_D
	OpCode_RLC_E
	OpCode_RLC_H
	OpCode_RLC_L
	OpCode_RLC_MEM_HL
	OpCode_RLC_A
	OpCode_RRC_B
	OpCode_RRC_C
	OpCode_RRC_D
	OpCode_RRC_E
	OpCode_RRC_H
	OpCode_RRC_L
	OpCode_RRC_MEM_HL
	OpCode_RRC_A
	OpCode_RL_B
	OpCode_RL_C
	OpCode_RL_D
	OpCode_RL_E
	OpCode_RL_H
	OpCode_RL_L
	OpCode_RL_MEM_HL
	OpCode_RL_A
	OpCode_RR_B
	OpCode_RR_C
	OpCode_RR_D
	OpCode_RR_E
	OpCode_RR_H
	OpCode_RR_L
	OpCode_RR_MEM_HL
	OpCode_RR_A
	OpCode_SLA_B
	OpCode_SLA_C
	OpCode_SLA_D
	OpCode_SLA_E
	OpCode_SLA_H
	OpCode_SLA_L
	OpCode_SLA_MEM_HL
	OpCode_SLA_A
	OpCode_SRA_B
	OpCode_SRA_C
	OpCode_SRA_D
	OpCode_SRA_E
	OpCode_SRA_H
	OpCode_SRA_L
	OpCode_SRA_MEM_HL
	OpCode_SRA_A
	OpCode_SRL_B
	OpCode_SRL_C
	OpCode_SRL_D
	OpCode_SRL_E
	OpCode_SRL_H
	OpCode_SRL_L
	OpCode_SRL_MEM_HL
	OpCode_SRL_A
	*/
		
	mappings[OpCode_BIT_0_B].operand1 =
		mappings[OpCode_BIT_0_C].operand1 =
		mappings[OpCode_BIT_0_D].operand1 =
		mappings[OpCode_BIT_0_E].operand1 =
		mappings[OpCode_BIT_0_H].operand1 =
		mappings[OpCode_BIT_0_L].operand1 =
		mappings[OpCode_BIT_0_MEM_HL].operand1 =
		mappings[OpCode_BIT_0_A].operand1 =
		mappings[OpCode_RES_0_B].operand1 =
		mappings[OpCode_RES_0_C].operand1 =
		mappings[OpCode_RES_0_D].operand1 =
		mappings[OpCode_RES_0_E].operand1 =
		mappings[OpCode_RES_0_H].operand1 =
		mappings[OpCode_RES_0_L].operand1 =
		mappings[OpCode_RES_0_MEM_HL].operand1 =
		mappings[OpCode_RES_0_A].operand1 =
		mappings[OpCode_SET_0_B].operand1 =
		mappings[OpCode_SET_0_C].operand1 =
		mappings[OpCode_SET_0_D].operand1 =
		mappings[OpCode_SET_0_E].operand1 =
		mappings[OpCode_SET_0_H].operand1 =
		mappings[OpCode_SET_0_L].operand1 =
		mappings[OpCode_SET_0_MEM_HL].operand1 =
		mappings[OpCode_SET_0_A].operand1 = createGBByteValue(&ZERO);

	mappings[OpCode_BIT_1_B].operand1 =
		mappings[OpCode_BIT_1_C].operand1 =
		mappings[OpCode_BIT_1_D].operand1 =
		mappings[OpCode_BIT_1_E].operand1 =
		mappings[OpCode_BIT_1_H].operand1 =
		mappings[OpCode_BIT_1_L].operand1 =
		mappings[OpCode_BIT_1_MEM_HL].operand1 =
		mappings[OpCode_BIT_1_A].operand1 =
		mappings[OpCode_RES_1_B].operand1 =
		mappings[OpCode_RES_1_C].operand1 =
		mappings[OpCode_RES_1_D].operand1 =
		mappings[OpCode_RES_1_E].operand1 =
		mappings[OpCode_RES_1_H].operand1 =
		mappings[OpCode_RES_1_L].operand1 =
		mappings[OpCode_RES_1_MEM_HL].operand1 =
		mappings[OpCode_RES_1_A].operand1 =
		mappings[OpCode_SET_1_B].operand1 =
		mappings[OpCode_SET_1_C].operand1 =
		mappings[OpCode_SET_1_D].operand1 =
		mappings[OpCode_SET_1_E].operand1 =
		mappings[OpCode_SET_1_H].operand1 =
		mappings[OpCode_SET_1_L].operand1 =
		mappings[OpCode_SET_1_MEM_HL].operand1 =
		mappings[OpCode_SET_1_A].operand1 = createGBByteValue(&ONE);

	mappings[OpCode_BIT_2_B].operand1 =
		mappings[OpCode_BIT_2_C].operand1 =
		mappings[OpCode_BIT_2_D].operand1 =
		mappings[OpCode_BIT_2_E].operand1 =
		mappings[OpCode_BIT_2_H].operand1 =
		mappings[OpCode_BIT_2_L].operand1 =
		mappings[OpCode_BIT_2_MEM_HL].operand1 =
		mappings[OpCode_BIT_2_A].operand1 =
		mappings[OpCode_RES_2_B].operand1 =
		mappings[OpCode_RES_2_C].operand1 =
		mappings[OpCode_RES_2_D].operand1 =
		mappings[OpCode_RES_2_E].operand1 =
		mappings[OpCode_RES_2_H].operand1 =
		mappings[OpCode_RES_2_L].operand1 =
		mappings[OpCode_RES_2_MEM_HL].operand1 =
		mappings[OpCode_RES_2_A].operand1 =
		mappings[OpCode_SET_2_B].operand1 =
		mappings[OpCode_SET_2_C].operand1 =
		mappings[OpCode_SET_2_D].operand1 =
		mappings[OpCode_SET_2_E].operand1 =
		mappings[OpCode_SET_2_H].operand1 =
		mappings[OpCode_SET_2_L].operand1 =
		mappings[OpCode_SET_2_MEM_HL].operand1 =
		mappings[OpCode_SET_2_A].operand1 = createGBByteValue(&TWO);

	mappings[OpCode_BIT_3_B].operand1 =
		mappings[OpCode_BIT_3_C].operand1 =
		mappings[OpCode_BIT_3_D].operand1 =
		mappings[OpCode_BIT_3_E].operand1 =
		mappings[OpCode_BIT_3_H].operand1 =
		mappings[OpCode_BIT_3_L].operand1 =
		mappings[OpCode_BIT_3_MEM_HL].operand1 =
		mappings[OpCode_BIT_3_A].operand1 =
		mappings[OpCode_RES_3_B].operand1 =
		mappings[OpCode_RES_3_C].operand1 =
		mappings[OpCode_RES_3_D].operand1 =
		mappings[OpCode_RES_3_E].operand1 =
		mappings[OpCode_RES_3_H].operand1 =
		mappings[OpCode_RES_3_L].operand1 =
		mappings[OpCode_RES_3_MEM_HL].operand1 =
		mappings[OpCode_RES_3_A].operand1 =
		mappings[OpCode_SET_3_B].operand1 =
		mappings[OpCode_SET_3_C].operand1 =
		mappings[OpCode_SET_3_D].operand1 =
		mappings[OpCode_SET_3_E].operand1 =
		mappings[OpCode_SET_3_H].operand1 =
		mappings[OpCode_SET_3_L].operand1 =
		mappings[OpCode_SET_3_MEM_HL].operand1 =
		mappings[OpCode_SET_3_A].operand1 = createGBByteValue(&THREE);

	mappings[OpCode_BIT_4_B].operand1 =
		mappings[OpCode_BIT_4_C].operand1 =
		mappings[OpCode_BIT_4_D].operand1 =
		mappings[OpCode_BIT_4_E].operand1 =
		mappings[OpCode_BIT_4_H].operand1 =
		mappings[OpCode_BIT_4_L].operand1 =
		mappings[OpCode_BIT_4_MEM_HL].operand1 =
		mappings[OpCode_BIT_4_A].operand1 =
		mappings[OpCode_RES_4_B].operand1 =
		mappings[OpCode_RES_4_C].operand1 =
		mappings[OpCode_RES_4_D].operand1 =
		mappings[OpCode_RES_4_E].operand1 =
		mappings[OpCode_RES_4_H].operand1 =
		mappings[OpCode_RES_4_L].operand1 =
		mappings[OpCode_RES_4_MEM_HL].operand1 =
		mappings[OpCode_RES_4_A].operand1 =
		mappings[OpCode_SET_4_B].operand1 =
		mappings[OpCode_SET_4_C].operand1 =
		mappings[OpCode_SET_4_D].operand1 =
		mappings[OpCode_SET_4_E].operand1 =
		mappings[OpCode_SET_4_H].operand1 =
		mappings[OpCode_SET_4_L].operand1 =
		mappings[OpCode_SET_4_MEM_HL].operand1 =
		mappings[OpCode_SET_4_A].operand1 = createGBByteValue(&FOUR);

	mappings[OpCode_BIT_5_B].operand1 =
		mappings[OpCode_BIT_5_C].operand1 =
		mappings[OpCode_BIT_5_D].operand1 =
		mappings[OpCode_BIT_5_E].operand1 =
		mappings[OpCode_BIT_5_H].operand1 =
		mappings[OpCode_BIT_5_L].operand1 =
		mappings[OpCode_BIT_5_MEM_HL].operand1 =
		mappings[OpCode_BIT_5_A].operand1 =
		mappings[OpCode_RES_5_B].operand1 =
		mappings[OpCode_RES_5_C].operand1 =
		mappings[OpCode_RES_5_D].operand1 =
		mappings[OpCode_RES_5_E].operand1 =
		mappings[OpCode_RES_5_H].operand1 =
		mappings[OpCode_RES_5_L].operand1 =
		mappings[OpCode_RES_5_MEM_HL].operand1 =
		mappings[OpCode_RES_5_A].operand1 =
		mappings[OpCode_SET_5_B].operand1 =
		mappings[OpCode_SET_5_C].operand1 =
		mappings[OpCode_SET_5_D].operand1 =
		mappings[OpCode_SET_5_E].operand1 =
		mappings[OpCode_SET_5_H].operand1 =
		mappings[OpCode_SET_5_L].operand1 =
		mappings[OpCode_SET_5_MEM_HL].operand1 =
		mappings[OpCode_SET_5_A].operand1 = createGBByteValue(&FIVE);

	mappings[OpCode_BIT_6_B].operand1 =
		mappings[OpCode_BIT_6_C].operand1 =
		mappings[OpCode_BIT_6_D].operand1 =
		mappings[OpCode_BIT_6_E].operand1 =
		mappings[OpCode_BIT_6_H].operand1 =
		mappings[OpCode_BIT_6_L].operand1 =
		mappings[OpCode_BIT_6_MEM_HL].operand1 =
		mappings[OpCode_BIT_6_A].operand1 =
		mappings[OpCode_RES_6_B].operand1 =
		mappings[OpCode_RES_6_C].operand1 =
		mappings[OpCode_RES_6_D].operand1 =
		mappings[OpCode_RES_6_E].operand1 =
		mappings[OpCode_RES_6_H].operand1 =
		mappings[OpCode_RES_6_L].operand1 =
		mappings[OpCode_RES_6_MEM_HL].operand1 =
		mappings[OpCode_RES_6_A].operand1 =
		mappings[OpCode_SET_6_B].operand1 =
		mappings[OpCode_SET_6_C].operand1 =
		mappings[OpCode_SET_6_D].operand1 =
		mappings[OpCode_SET_6_E].operand1 =
		mappings[OpCode_SET_6_H].operand1 =
		mappings[OpCode_SET_6_L].operand1 =
		mappings[OpCode_SET_6_MEM_HL].operand1 =
		mappings[OpCode_SET_6_A].operand1 = createGBByteValue(&SIX);

	mappings[OpCode_BIT_7_B].operand1 =
		mappings[OpCode_BIT_7_C].operand1 =
		mappings[OpCode_BIT_7_D].operand1 =
		mappings[OpCode_BIT_7_E].operand1 =
		mappings[OpCode_BIT_7_H].operand1 =
		mappings[OpCode_BIT_7_L].operand1 =
		mappings[OpCode_BIT_7_MEM_HL].operand1 =
		mappings[OpCode_BIT_7_A].operand1 =
		mappings[OpCode_RES_7_B].operand1 =
		mappings[OpCode_RES_7_C].operand1 =
		mappings[OpCode_RES_7_D].operand1 =
		mappings[OpCode_RES_7_E].operand1 =
		mappings[OpCode_RES_7_H].operand1 =
		mappings[OpCode_RES_7_L].operand1 =
		mappings[OpCode_RES_7_MEM_HL].operand1 =
		mappings[OpCode_RES_7_A].operand1 =
		mappings[OpCode_SET_7_B].operand1 =
		mappings[OpCode_SET_7_C].operand1 =
		mappings[OpCode_SET_7_D].operand1 =
		mappings[OpCode_SET_7_E].operand1 =
		mappings[OpCode_SET_7_H].operand1 =
		mappings[OpCode_SET_7_L].operand1 =
		mappings[OpCode_SET_7_MEM_HL].operand1 =
		mappings[OpCode_SET_7_A].operand1 = createGBByteValue(&SEVEN);

	mappings[OpCode_RLCA].operand1 =
		mappings[OpCode_RLA].operand1 =
		mappings[OpCode_RRCA].operand1 =
		mappings[OpCode_RRA].operand1 =
		mappings[OpCode_SWAP_A].operand1 = createGBByteValue(&hardware->registers->A);

	mappings[OpCode_SWAP_B].operand1 = createGBByteValue(&hardware->registers->B);
	mappings[OpCode_SWAP_C].operand1 = createGBByteValue(&hardware->registers->C);
	mappings[OpCode_SWAP_D].operand1 = createGBByteValue(&hardware->registers->D);
	mappings[OpCode_SWAP_E].operand1 = createGBByteValue(&hardware->registers->E);
	mappings[OpCode_SWAP_H].operand1 = createGBByteValue(&hardware->registers->H);
	mappings[OpCode_SWAP_L].operand1 = createGBByteValue(&hardware->registers->L);
	mappings[OpCode_SWAP_MEM_HL].operand1 = createGBBytePointer(&hardware->cachedValues->memoryHL);
}

void populateBitwiseOperands2Destinations(Hardware *hardware, InstructionMapping *mappings) {
	mappings[OpCode_BIT_0_A].operand2 =
		mappings[OpCode_BIT_1_A].operand2 =
		mappings[OpCode_BIT_2_A].operand2 =
		mappings[OpCode_BIT_3_A].operand2 =
		mappings[OpCode_BIT_4_A].operand2 =
		mappings[OpCode_BIT_5_A].operand2 =
		mappings[OpCode_BIT_6_A].operand2 =
		mappings[OpCode_BIT_7_A].operand2 =
		mappings[OpCode_RLCA].destination =
		mappings[OpCode_RLA].destination =
		mappings[OpCode_RRCA].destination =
		mappings[OpCode_RRA].destination =
		mappings[OpCode_RES_0_A].destination =
		mappings[OpCode_RES_0_A].operand2 =
		mappings[OpCode_RES_1_A].destination =
		mappings[OpCode_RES_1_A].operand2 =
		mappings[OpCode_RES_2_A].destination =
		mappings[OpCode_RES_2_A].operand2 =
		mappings[OpCode_RES_3_A].destination =
		mappings[OpCode_RES_3_A].operand2 =
		mappings[OpCode_RES_4_A].destination =
		mappings[OpCode_RES_4_A].operand2 =
		mappings[OpCode_RES_5_A].destination =
		mappings[OpCode_RES_5_A].operand2 =
		mappings[OpCode_RES_6_A].destination =
		mappings[OpCode_RES_6_A].operand2 =
		mappings[OpCode_RES_7_A].destination =
		mappings[OpCode_RES_7_A].operand2 =
		mappings[OpCode_SET_0_A].destination =
		mappings[OpCode_SET_0_A].operand2 =
		mappings[OpCode_SET_1_A].destination =
		mappings[OpCode_SET_1_A].operand2 =
		mappings[OpCode_SET_2_A].destination =
		mappings[OpCode_SET_2_A].operand2 =
		mappings[OpCode_SET_3_A].destination =
		mappings[OpCode_SET_3_A].operand2 =
		mappings[OpCode_SET_4_A].destination =
		mappings[OpCode_SET_4_A].operand2 =
		mappings[OpCode_SET_5_A].destination =
		mappings[OpCode_SET_5_A].operand2 =
		mappings[OpCode_SET_6_A].destination =
		mappings[OpCode_SET_6_A].operand2 =
		mappings[OpCode_SET_7_A].destination =
		mappings[OpCode_SET_7_A].operand2 = createGBByteValue(&hardware->registers->A);

		mappings[OpCode_BIT_0_B].operand2 =
		mappings[OpCode_BIT_1_B].operand2 =
		mappings[OpCode_BIT_2_B].operand2 =
		mappings[OpCode_BIT_3_B].operand2 =
		mappings[OpCode_BIT_4_B].operand2 =
		mappings[OpCode_BIT_5_B].operand2 =
		mappings[OpCode_BIT_6_B].operand2 =
		mappings[OpCode_BIT_7_B].operand2 =
		mappings[OpCode_RES_0_B].destination =
		mappings[OpCode_RES_0_B].operand2 =
		mappings[OpCode_RES_1_B].destination =
		mappings[OpCode_RES_1_B].operand2 =
		mappings[OpCode_RES_2_B].destination =
		mappings[OpCode_RES_2_B].operand2 =
		mappings[OpCode_RES_3_B].destination =
		mappings[OpCode_RES_3_B].operand2 =
		mappings[OpCode_RES_4_B].destination =
		mappings[OpCode_RES_4_B].operand2 =
		mappings[OpCode_RES_5_B].destination =
		mappings[OpCode_RES_5_B].operand2 =
		mappings[OpCode_RES_6_B].destination =
		mappings[OpCode_RES_6_B].operand2 =
		mappings[OpCode_RES_7_B].destination =
		mappings[OpCode_RES_7_B].operand2 =
		mappings[OpCode_SET_0_B].destination =
		mappings[OpCode_SET_0_B].operand2 =
		mappings[OpCode_SET_1_B].destination =
		mappings[OpCode_SET_1_B].operand2 =
		mappings[OpCode_SET_2_B].destination =
		mappings[OpCode_SET_2_B].operand2 =
		mappings[OpCode_SET_3_B].destination =
		mappings[OpCode_SET_3_B].operand2 =
		mappings[OpCode_SET_4_B].destination =
		mappings[OpCode_SET_4_B].operand2 =
		mappings[OpCode_SET_5_B].destination =
		mappings[OpCode_SET_5_B].operand2 =
		mappings[OpCode_SET_6_B].destination =
		mappings[OpCode_SET_6_B].operand2 =
		mappings[OpCode_SET_7_B].destination =
		mappings[OpCode_SET_7_B].operand2 = createGBByteValue(&hardware->registers->B);

		mappings[OpCode_BIT_0_C].operand2 =
		mappings[OpCode_BIT_1_C].operand2 =
		mappings[OpCode_BIT_2_C].operand2 =
		mappings[OpCode_BIT_3_C].operand2 =
		mappings[OpCode_BIT_4_C].operand2 =
		mappings[OpCode_BIT_5_C].operand2 =
		mappings[OpCode_BIT_6_C].operand2 =
		mappings[OpCode_BIT_7_C].operand2 =
		mappings[OpCode_RES_0_C].destination =
		mappings[OpCode_RES_0_C].operand2 =
		mappings[OpCode_RES_1_C].destination =
		mappings[OpCode_RES_1_C].operand2 =
		mappings[OpCode_RES_2_C].destination =
		mappings[OpCode_RES_2_C].operand2 =
		mappings[OpCode_RES_3_C].destination =
		mappings[OpCode_RES_3_C].operand2 =
		mappings[OpCode_RES_4_C].destination =
		mappings[OpCode_RES_4_C].operand2 =
		mappings[OpCode_RES_5_C].destination =
		mappings[OpCode_RES_5_C].operand2 =
		mappings[OpCode_RES_6_C].destination =
		mappings[OpCode_RES_6_C].operand2 =
		mappings[OpCode_RES_7_C].destination =
		mappings[OpCode_RES_7_C].operand2 =
		mappings[OpCode_SET_0_C].destination =
		mappings[OpCode_SET_0_C].operand2 =
		mappings[OpCode_SET_1_C].destination =
		mappings[OpCode_SET_1_C].operand2 =
		mappings[OpCode_SET_2_C].destination =
		mappings[OpCode_SET_2_C].operand2 =
		mappings[OpCode_SET_3_C].destination =
		mappings[OpCode_SET_3_C].operand2 =
		mappings[OpCode_SET_4_C].destination =
		mappings[OpCode_SET_4_C].operand2 =
		mappings[OpCode_SET_5_C].destination =
		mappings[OpCode_SET_5_C].operand2 =
		mappings[OpCode_SET_6_C].destination =
		mappings[OpCode_SET_6_C].operand2 =
		mappings[OpCode_SET_7_C].destination =
		mappings[OpCode_SET_7_C].operand2 = createGBByteValue(&hardware->registers->C);

		mappings[OpCode_BIT_0_D].operand2 =
		mappings[OpCode_BIT_1_D].operand2 =
		mappings[OpCode_BIT_2_D].operand2 =
		mappings[OpCode_BIT_3_D].operand2 =
		mappings[OpCode_BIT_4_D].operand2 =
		mappings[OpCode_BIT_5_D].operand2 =
		mappings[OpCode_BIT_6_D].operand2 =
		mappings[OpCode_BIT_7_D].operand2 =
		mappings[OpCode_RES_0_D].destination =
		mappings[OpCode_RES_0_D].operand2 =
		mappings[OpCode_RES_1_D].destination =
		mappings[OpCode_RES_1_D].operand2 =
		mappings[OpCode_RES_2_D].destination =
		mappings[OpCode_RES_2_D].operand2 =
		mappings[OpCode_RES_3_D].destination =
		mappings[OpCode_RES_3_D].operand2 =
		mappings[OpCode_RES_4_D].destination =
		mappings[OpCode_RES_4_D].operand2 =
		mappings[OpCode_RES_5_D].destination =
		mappings[OpCode_RES_5_D].operand2 =
		mappings[OpCode_RES_6_D].destination =
		mappings[OpCode_RES_6_D].operand2 =
		mappings[OpCode_RES_7_D].destination =
		mappings[OpCode_RES_7_D].operand2 =
		mappings[OpCode_SET_0_D].destination =
		mappings[OpCode_SET_0_D].operand2 =
		mappings[OpCode_SET_1_D].destination =
		mappings[OpCode_SET_1_D].operand2 =
		mappings[OpCode_SET_2_D].destination =
		mappings[OpCode_SET_2_D].operand2 =
		mappings[OpCode_SET_3_D].destination =
		mappings[OpCode_SET_3_D].operand2 =
		mappings[OpCode_SET_4_D].destination =
		mappings[OpCode_SET_4_D].operand2 =
		mappings[OpCode_SET_5_D].destination =
		mappings[OpCode_SET_5_D].operand2 =
		mappings[OpCode_SET_6_D].destination =
		mappings[OpCode_SET_6_D].operand2 =
		mappings[OpCode_SET_7_D].destination =
		mappings[OpCode_SET_7_D].operand2 = createGBByteValue(&hardware->registers->D);

		mappings[OpCode_BIT_0_E].operand2 =
		mappings[OpCode_BIT_1_E].operand2 =
		mappings[OpCode_BIT_2_E].operand2 =
		mappings[OpCode_BIT_3_E].operand2 =
		mappings[OpCode_BIT_4_E].operand2 =
		mappings[OpCode_BIT_5_E].operand2 =
		mappings[OpCode_BIT_6_E].operand2 =
		mappings[OpCode_BIT_7_E].operand2 =
		mappings[OpCode_RES_0_E].destination =
		mappings[OpCode_RES_0_E].operand2 =
		mappings[OpCode_RES_1_E].destination =
		mappings[OpCode_RES_1_E].operand2 =
		mappings[OpCode_RES_2_E].destination =
		mappings[OpCode_RES_2_E].operand2 =
		mappings[OpCode_RES_3_E].destination =
		mappings[OpCode_RES_3_E].operand2 =
		mappings[OpCode_RES_4_E].destination =
		mappings[OpCode_RES_4_E].operand2 =
		mappings[OpCode_RES_5_E].destination =
		mappings[OpCode_RES_5_E].operand2 =
		mappings[OpCode_RES_6_E].destination =
		mappings[OpCode_RES_6_E].operand2 =
		mappings[OpCode_RES_7_E].destination =
		mappings[OpCode_RES_7_E].operand2 =
		mappings[OpCode_SET_0_E].destination =
		mappings[OpCode_SET_0_E].operand2 =
		mappings[OpCode_SET_1_E].destination =
		mappings[OpCode_SET_1_E].operand2 =
		mappings[OpCode_SET_2_E].destination =
		mappings[OpCode_SET_2_E].operand2 =
		mappings[OpCode_SET_3_E].destination =
		mappings[OpCode_SET_3_E].operand2 =
		mappings[OpCode_SET_4_E].destination =
		mappings[OpCode_SET_4_E].operand2 =
		mappings[OpCode_SET_5_E].destination =
		mappings[OpCode_SET_5_E].operand2 =
		mappings[OpCode_SET_6_E].destination =
		mappings[OpCode_SET_6_E].operand2 =
		mappings[OpCode_SET_7_E].destination =
		mappings[OpCode_SET_7_E].operand2 = createGBByteValue(&hardware->registers->E);

		mappings[OpCode_BIT_0_H].operand2 =
		mappings[OpCode_BIT_1_H].operand2 =
		mappings[OpCode_BIT_2_H].operand2 =
		mappings[OpCode_BIT_3_H].operand2 =
		mappings[OpCode_BIT_4_H].operand2 =
		mappings[OpCode_BIT_5_H].operand2 =
		mappings[OpCode_BIT_6_H].operand2 =
		mappings[OpCode_BIT_7_H].operand2 =
		mappings[OpCode_RES_0_H].destination =
		mappings[OpCode_RES_0_H].operand2 =
		mappings[OpCode_RES_1_H].destination =
		mappings[OpCode_RES_1_H].operand2 =
		mappings[OpCode_RES_2_H].destination =
		mappings[OpCode_RES_2_H].operand2 =
		mappings[OpCode_RES_3_H].destination =
		mappings[OpCode_RES_3_H].operand2 =
		mappings[OpCode_RES_4_H].destination =
		mappings[OpCode_RES_4_H].operand2 =
		mappings[OpCode_RES_5_H].destination =
		mappings[OpCode_RES_5_H].operand2 =
		mappings[OpCode_RES_6_H].destination =
		mappings[OpCode_RES_6_H].operand2 =
		mappings[OpCode_RES_7_H].destination =
		mappings[OpCode_RES_7_H].operand2 =
		mappings[OpCode_SET_0_H].destination =
		mappings[OpCode_SET_0_H].operand2 =
		mappings[OpCode_SET_1_H].destination =
		mappings[OpCode_SET_1_H].operand2 =
		mappings[OpCode_SET_2_H].destination =
		mappings[OpCode_SET_2_H].operand2 =
		mappings[OpCode_SET_3_H].destination =
		mappings[OpCode_SET_3_H].operand2 =
		mappings[OpCode_SET_4_H].destination =
		mappings[OpCode_SET_4_H].operand2 =
		mappings[OpCode_SET_5_H].destination =
		mappings[OpCode_SET_5_H].operand2 =
		mappings[OpCode_SET_6_H].destination =
		mappings[OpCode_SET_6_H].operand2 =
		mappings[OpCode_SET_7_H].destination =
		mappings[OpCode_SET_7_H].operand2 = createGBByteValue(&hardware->registers->H);

		mappings[OpCode_BIT_0_L].operand2 =
		mappings[OpCode_BIT_1_L].operand2 =
		mappings[OpCode_BIT_2_L].operand2 =
		mappings[OpCode_BIT_3_L].operand2 =
		mappings[OpCode_BIT_4_L].operand2 =
		mappings[OpCode_BIT_5_L].operand2 =
		mappings[OpCode_BIT_6_L].operand2 =
		mappings[OpCode_BIT_7_L].operand2 =
		mappings[OpCode_RES_0_L].destination =
		mappings[OpCode_RES_0_L].operand2 =
		mappings[OpCode_RES_1_L].destination =
		mappings[OpCode_RES_1_L].operand2 =
		mappings[OpCode_RES_2_L].destination =
		mappings[OpCode_RES_2_L].operand2 =
		mappings[OpCode_RES_3_L].destination =
		mappings[OpCode_RES_3_L].operand2 =
		mappings[OpCode_RES_4_L].destination =
		mappings[OpCode_RES_4_L].operand2 =
		mappings[OpCode_RES_5_L].destination =
		mappings[OpCode_RES_5_L].operand2 =
		mappings[OpCode_RES_6_L].destination =
		mappings[OpCode_RES_6_L].operand2 =
		mappings[OpCode_RES_7_L].destination =
		mappings[OpCode_RES_7_L].operand2 =
		mappings[OpCode_SET_0_L].destination =
		mappings[OpCode_SET_0_L].operand2 =
		mappings[OpCode_SET_1_L].destination =
		mappings[OpCode_SET_1_L].operand2 =
		mappings[OpCode_SET_2_L].destination =
		mappings[OpCode_SET_2_L].operand2 =
		mappings[OpCode_SET_3_L].destination =
		mappings[OpCode_SET_3_L].operand2 =
		mappings[OpCode_SET_4_L].destination =
		mappings[OpCode_SET_4_L].operand2 =
		mappings[OpCode_SET_5_L].destination =
		mappings[OpCode_SET_5_L].operand2 =
		mappings[OpCode_SET_6_L].destination =
		mappings[OpCode_SET_6_L].operand2 =
		mappings[OpCode_SET_7_L].destination =
		mappings[OpCode_SET_7_L].operand2 = createGBByteValue(&hardware->registers->L);

		mappings[OpCode_BIT_0_MEM_HL].operand2 =
		mappings[OpCode_BIT_1_MEM_HL].operand2 =
		mappings[OpCode_BIT_2_MEM_HL].operand2 =
		mappings[OpCode_BIT_3_MEM_HL].operand2 =
		mappings[OpCode_BIT_4_MEM_HL].operand2 =
		mappings[OpCode_BIT_5_MEM_HL].operand2 =
		mappings[OpCode_BIT_6_MEM_HL].operand2 =
		mappings[OpCode_BIT_7_MEM_HL].operand2 =
		mappings[OpCode_RES_0_MEM_HL].destination =
		mappings[OpCode_RES_0_MEM_HL].operand2 =
		mappings[OpCode_RES_1_MEM_HL].destination =
		mappings[OpCode_RES_1_MEM_HL].operand2 =
		mappings[OpCode_RES_2_MEM_HL].destination =
		mappings[OpCode_RES_2_MEM_HL].operand2 =
		mappings[OpCode_RES_3_MEM_HL].destination =
		mappings[OpCode_RES_3_MEM_HL].operand2 =
		mappings[OpCode_RES_4_MEM_HL].destination =
		mappings[OpCode_RES_4_MEM_HL].operand2 =
		mappings[OpCode_RES_5_MEM_HL].destination =
		mappings[OpCode_RES_5_MEM_HL].operand2 =
		mappings[OpCode_RES_6_MEM_HL].destination =
		mappings[OpCode_RES_6_MEM_HL].operand2 =
		mappings[OpCode_RES_7_MEM_HL].destination =
		mappings[OpCode_RES_7_MEM_HL].operand2 =
		mappings[OpCode_SET_0_MEM_HL].destination =
		mappings[OpCode_SET_0_MEM_HL].operand2 =
		mappings[OpCode_SET_1_MEM_HL].destination =
		mappings[OpCode_SET_1_MEM_HL].operand2 =
		mappings[OpCode_SET_2_MEM_HL].destination =
		mappings[OpCode_SET_2_MEM_HL].operand2 =
		mappings[OpCode_SET_3_MEM_HL].destination =
		mappings[OpCode_SET_3_MEM_HL].operand2 =
		mappings[OpCode_SET_4_MEM_HL].destination =
		mappings[OpCode_SET_4_MEM_HL].operand2 =
		mappings[OpCode_SET_5_MEM_HL].destination =
		mappings[OpCode_SET_5_MEM_HL].operand2 =
		mappings[OpCode_SET_6_MEM_HL].destination =
		mappings[OpCode_SET_6_MEM_HL].operand2 =
		mappings[OpCode_SET_7_MEM_HL].destination =
		mappings[OpCode_SET_7_MEM_HL].operand2 = createGBBytePointer(&hardware->cachedValues->memoryHL);

		mappings[OpCode_SWAP_A].destination = createGBByteValue(&hardware->registers->A);
		mappings[OpCode_SWAP_B].destination = createGBByteValue(&hardware->registers->B);
		mappings[OpCode_SWAP_C].destination = createGBByteValue(&hardware->registers->C);
		mappings[OpCode_SWAP_D].destination = createGBByteValue(&hardware->registers->D);
		mappings[OpCode_SWAP_E].destination = createGBByteValue(&hardware->registers->E);
		mappings[OpCode_SWAP_H].destination = createGBByteValue(&hardware->registers->H);
		mappings[OpCode_SWAP_L].destination = createGBByteValue(&hardware->registers->L);
		mappings[OpCode_SWAP_MEM_HL].destination = createGBBytePointer(&hardware->cachedValues->memoryHL);
}

void populateBitwiseOperandsResults(Hardware *hardware, InstructionMapping *mappings) {
	mappings[OpCode_BIT_0_B].result =
		mappings[OpCode_BIT_0_C].result =
		mappings[OpCode_BIT_0_D].result =
		mappings[OpCode_BIT_0_E].result =
		mappings[OpCode_BIT_0_H].result =
		mappings[OpCode_BIT_0_L].result =
		mappings[OpCode_BIT_0_MEM_HL].result =
		mappings[OpCode_BIT_0_A].result =
		mappings[OpCode_BIT_1_B].result =
		mappings[OpCode_BIT_1_C].result =
		mappings[OpCode_BIT_1_D].result =
		mappings[OpCode_BIT_1_E].result =
		mappings[OpCode_BIT_1_H].result =
		mappings[OpCode_BIT_1_L].result =
		mappings[OpCode_BIT_1_MEM_HL].result =
		mappings[OpCode_BIT_1_A].result =
		mappings[OpCode_BIT_2_B].result =
		mappings[OpCode_BIT_2_C].result =
		mappings[OpCode_BIT_2_D].result =
		mappings[OpCode_BIT_2_E].result =
		mappings[OpCode_BIT_2_H].result =
		mappings[OpCode_BIT_2_L].result =
		mappings[OpCode_BIT_2_MEM_HL].result =
		mappings[OpCode_BIT_2_A].result =
		mappings[OpCode_BIT_3_B].result =
		mappings[OpCode_BIT_3_C].result =
		mappings[OpCode_BIT_3_D].result =
		mappings[OpCode_BIT_3_E].result =
		mappings[OpCode_BIT_3_H].result =
		mappings[OpCode_BIT_3_L].result =
		mappings[OpCode_BIT_3_MEM_HL].result =
		mappings[OpCode_BIT_3_A].result =
		mappings[OpCode_BIT_4_B].result =
		mappings[OpCode_BIT_4_C].result =
		mappings[OpCode_BIT_4_D].result =
		mappings[OpCode_BIT_4_E].result =
		mappings[OpCode_BIT_4_H].result =
		mappings[OpCode_BIT_4_L].result =
		mappings[OpCode_BIT_4_MEM_HL].result =
		mappings[OpCode_BIT_4_A].result =
		mappings[OpCode_BIT_5_B].result =
		mappings[OpCode_BIT_5_C].result =
		mappings[OpCode_BIT_5_D].result =
		mappings[OpCode_BIT_5_E].result =
		mappings[OpCode_BIT_5_H].result =
		mappings[OpCode_BIT_5_L].result =
		mappings[OpCode_BIT_5_MEM_HL].result =
		mappings[OpCode_BIT_5_A].result =
		mappings[OpCode_BIT_6_B].result =
		mappings[OpCode_BIT_6_C].result =
		mappings[OpCode_BIT_6_D].result =
		mappings[OpCode_BIT_6_E].result =
		mappings[OpCode_BIT_6_H].result =
		mappings[OpCode_BIT_6_L].result =
		mappings[OpCode_BIT_6_MEM_HL].result =
		mappings[OpCode_BIT_6_A].result =
		mappings[OpCode_BIT_7_B].result =
		mappings[OpCode_BIT_7_C].result =
		mappings[OpCode_BIT_7_D].result =
		mappings[OpCode_BIT_7_E].result =
		mappings[OpCode_BIT_7_H].result =
		mappings[OpCode_BIT_7_L].result =
		mappings[OpCode_BIT_7_MEM_HL].result =
		mappings[OpCode_BIT_7_A].result = &hardware->cachedResults->getBit;

	mappings[OpCode_RES_0_B].result =
		mappings[OpCode_RES_0_C].result =
		mappings[OpCode_RES_0_D].result =
		mappings[OpCode_RES_0_E].result =
		mappings[OpCode_RES_0_H].result =
		mappings[OpCode_RES_0_L].result =
		mappings[OpCode_RES_0_MEM_HL].result =
		mappings[OpCode_RES_0_A].result =
		mappings[OpCode_RES_1_B].result =
		mappings[OpCode_RES_1_C].result =
		mappings[OpCode_RES_1_D].result =
		mappings[OpCode_RES_1_E].result =
		mappings[OpCode_RES_1_H].result =
		mappings[OpCode_RES_1_L].result =
		mappings[OpCode_RES_1_MEM_HL].result =
		mappings[OpCode_RES_1_A].result =
		mappings[OpCode_RES_2_B].result =
		mappings[OpCode_RES_2_C].result =
		mappings[OpCode_RES_2_D].result =
		mappings[OpCode_RES_2_E].result =
		mappings[OpCode_RES_2_H].result =
		mappings[OpCode_RES_2_L].result =
		mappings[OpCode_RES_2_MEM_HL].result =
		mappings[OpCode_RES_2_A].result =
		mappings[OpCode_RES_3_B].result =
		mappings[OpCode_RES_3_C].result =
		mappings[OpCode_RES_3_D].result =
		mappings[OpCode_RES_3_E].result =
		mappings[OpCode_RES_3_H].result =
		mappings[OpCode_RES_3_L].result =
		mappings[OpCode_RES_3_MEM_HL].result =
		mappings[OpCode_RES_3_A].result =
		mappings[OpCode_RES_4_B].result =
		mappings[OpCode_RES_4_C].result =
		mappings[OpCode_RES_4_D].result =
		mappings[OpCode_RES_4_E].result =
		mappings[OpCode_RES_4_H].result =
		mappings[OpCode_RES_4_L].result =
		mappings[OpCode_RES_4_MEM_HL].result =
		mappings[OpCode_RES_4_A].result =
		mappings[OpCode_RES_5_B].result =
		mappings[OpCode_RES_5_C].result =
		mappings[OpCode_RES_5_D].result =
		mappings[OpCode_RES_5_E].result =
		mappings[OpCode_RES_5_H].result =
		mappings[OpCode_RES_5_L].result =
		mappings[OpCode_RES_5_MEM_HL].result =
		mappings[OpCode_RES_5_A].result =
		mappings[OpCode_RES_6_B].result =
		mappings[OpCode_RES_6_C].result =
		mappings[OpCode_RES_6_D].result =
		mappings[OpCode_RES_6_E].result =
		mappings[OpCode_RES_6_H].result =
		mappings[OpCode_RES_6_L].result =
		mappings[OpCode_RES_6_MEM_HL].result =
		mappings[OpCode_RES_6_A].result =
		mappings[OpCode_RES_7_B].result =
		mappings[OpCode_RES_7_C].result =
		mappings[OpCode_RES_7_D].result =
		mappings[OpCode_RES_7_E].result =
		mappings[OpCode_RES_7_H].result =
		mappings[OpCode_RES_7_L].result =
		mappings[OpCode_RES_7_MEM_HL].result =
		mappings[OpCode_RES_7_A].result = &hardware->cachedResults->resetBit;

	mappings[OpCode_SET_0_B].result =
		mappings[OpCode_SET_0_C].result =
		mappings[OpCode_SET_0_D].result =
		mappings[OpCode_SET_0_E].result =
		mappings[OpCode_SET_0_H].result =
		mappings[OpCode_SET_0_L].result =
		mappings[OpCode_SET_0_MEM_HL].result =
		mappings[OpCode_SET_0_A].result =
		mappings[OpCode_SET_1_B].result =
		mappings[OpCode_SET_1_C].result =
		mappings[OpCode_SET_1_D].result =
		mappings[OpCode_SET_1_E].result =
		mappings[OpCode_SET_1_H].result =
		mappings[OpCode_SET_1_L].result =
		mappings[OpCode_SET_1_MEM_HL].result =
		mappings[OpCode_SET_1_A].result =
		mappings[OpCode_SET_2_B].result =
		mappings[OpCode_SET_2_C].result =
		mappings[OpCode_SET_2_D].result =
		mappings[OpCode_SET_2_E].result =
		mappings[OpCode_SET_2_H].result =
		mappings[OpCode_SET_2_L].result =
		mappings[OpCode_SET_2_MEM_HL].result =
		mappings[OpCode_SET_2_A].result =
		mappings[OpCode_SET_3_B].result =
		mappings[OpCode_SET_3_C].result =
		mappings[OpCode_SET_3_D].result =
		mappings[OpCode_SET_3_E].result =
		mappings[OpCode_SET_3_H].result =
		mappings[OpCode_SET_3_L].result =
		mappings[OpCode_SET_3_MEM_HL].result =
		mappings[OpCode_SET_3_A].result =
		mappings[OpCode_SET_4_B].result =
		mappings[OpCode_SET_4_C].result =
		mappings[OpCode_SET_4_D].result =
		mappings[OpCode_SET_4_E].result =
		mappings[OpCode_SET_4_H].result =
		mappings[OpCode_SET_4_L].result =
		mappings[OpCode_SET_4_MEM_HL].result =
		mappings[OpCode_SET_4_A].result =
		mappings[OpCode_SET_5_B].result =
		mappings[OpCode_SET_5_C].result =
		mappings[OpCode_SET_5_D].result =
		mappings[OpCode_SET_5_E].result =
		mappings[OpCode_SET_5_H].result =
		mappings[OpCode_SET_5_L].result =
		mappings[OpCode_SET_5_MEM_HL].result =
		mappings[OpCode_SET_5_A].result =
		mappings[OpCode_SET_6_B].result =
		mappings[OpCode_SET_6_C].result =
		mappings[OpCode_SET_6_D].result =
		mappings[OpCode_SET_6_E].result =
		mappings[OpCode_SET_6_H].result =
		mappings[OpCode_SET_6_L].result =
		mappings[OpCode_SET_6_MEM_HL].result =
		mappings[OpCode_SET_6_A].result =
		mappings[OpCode_SET_7_B].result =
		mappings[OpCode_SET_7_C].result =
		mappings[OpCode_SET_7_D].result =
		mappings[OpCode_SET_7_E].result =
		mappings[OpCode_SET_7_H].result =
		mappings[OpCode_SET_7_L].result =
		mappings[OpCode_SET_7_MEM_HL].result =
		mappings[OpCode_SET_7_A].result == &hardware->cachedResults->setBit;


	mappings[OpCode_SWAP_A].result =
		mappings[OpCode_SWAP_B].result =
		mappings[OpCode_SWAP_C].result =
		mappings[OpCode_SWAP_D].result =
		mappings[OpCode_SWAP_E].result =
		mappings[OpCode_SWAP_H].result =
		mappings[OpCode_SWAP_L].result =
		mappings[OpCode_SWAP_MEM_HL].result = &hardware->cachedResults->swapNibbles;

	mappings[OpCode_RLCA].result = &hardware->cachedResults->rotateRight;
	mappings[OpCode_RLA].result = &hardware->cachedResults->rotateLeftCarry;
	mappings[OpCode_RRCA].result = &hardware->cachedResults->rotateRight;
	mappings[OpCode_RRA].result = &hardware->cachedResults->rotateRightCarry;
}

void populateBitwiseOperandsFlags(Hardware *hardware, InstructionMapping *mappings) {
	mappings[OpCode_BIT_0_B].flagResult =
		mappings[OpCode_BIT_0_C].flagResult =
		mappings[OpCode_BIT_0_D].flagResult =
		mappings[OpCode_BIT_0_E].flagResult =
		mappings[OpCode_BIT_0_H].flagResult =
		mappings[OpCode_BIT_0_L].flagResult =
		mappings[OpCode_BIT_0_MEM_HL].flagResult =
		mappings[OpCode_BIT_0_A].flagResult =
		mappings[OpCode_BIT_1_B].flagResult =
		mappings[OpCode_BIT_1_C].flagResult =
		mappings[OpCode_BIT_1_D].flagResult =
		mappings[OpCode_BIT_1_E].flagResult =
		mappings[OpCode_BIT_1_H].flagResult =
		mappings[OpCode_BIT_1_L].flagResult =
		mappings[OpCode_BIT_1_MEM_HL].flagResult =
		mappings[OpCode_BIT_1_A].flagResult =
		mappings[OpCode_BIT_2_B].flagResult =
		mappings[OpCode_BIT_2_C].flagResult =
		mappings[OpCode_BIT_2_D].flagResult =
		mappings[OpCode_BIT_2_E].flagResult =
		mappings[OpCode_BIT_2_H].flagResult =
		mappings[OpCode_BIT_2_L].flagResult =
		mappings[OpCode_BIT_2_MEM_HL].flagResult =
		mappings[OpCode_BIT_2_A].flagResult =
		mappings[OpCode_BIT_3_B].flagResult =
		mappings[OpCode_BIT_3_C].flagResult =
		mappings[OpCode_BIT_3_D].flagResult =
		mappings[OpCode_BIT_3_E].flagResult =
		mappings[OpCode_BIT_3_H].flagResult =
		mappings[OpCode_BIT_3_L].flagResult =
		mappings[OpCode_BIT_3_MEM_HL].flagResult =
		mappings[OpCode_BIT_3_A].flagResult =
		mappings[OpCode_BIT_4_B].flagResult =
		mappings[OpCode_BIT_4_C].flagResult =
		mappings[OpCode_BIT_4_D].flagResult =
		mappings[OpCode_BIT_4_E].flagResult =
		mappings[OpCode_BIT_4_H].flagResult =
		mappings[OpCode_BIT_4_L].flagResult =
		mappings[OpCode_BIT_4_MEM_HL].flagResult =
		mappings[OpCode_BIT_4_A].flagResult =
		mappings[OpCode_BIT_5_B].flagResult =
		mappings[OpCode_BIT_5_C].flagResult =
		mappings[OpCode_BIT_5_D].flagResult =
		mappings[OpCode_BIT_5_E].flagResult =
		mappings[OpCode_BIT_5_H].flagResult =
		mappings[OpCode_BIT_5_L].flagResult =
		mappings[OpCode_BIT_5_MEM_HL].flagResult =
		mappings[OpCode_BIT_5_A].flagResult =
		mappings[OpCode_BIT_6_B].flagResult =
		mappings[OpCode_BIT_6_C].flagResult =
		mappings[OpCode_BIT_6_D].flagResult =
		mappings[OpCode_BIT_6_E].flagResult =
		mappings[OpCode_BIT_6_H].flagResult =
		mappings[OpCode_BIT_6_L].flagResult =
		mappings[OpCode_BIT_6_MEM_HL].flagResult =
		mappings[OpCode_BIT_6_A].flagResult =
		mappings[OpCode_BIT_7_B].flagResult =
		mappings[OpCode_BIT_7_C].flagResult =
		mappings[OpCode_BIT_7_D].flagResult =
		mappings[OpCode_BIT_7_E].flagResult =
		mappings[OpCode_BIT_7_H].flagResult =
		mappings[OpCode_BIT_7_L].flagResult =
		mappings[OpCode_BIT_7_MEM_HL].flagResult =
		mappings[OpCode_BIT_7_A].flagResult = createFlagResult(&hardware->resultInfo->isZero, &FALSE_VAL, &TRUE_VAL, NULL);


	mappings[OpCode_SWAP_A].flagResult =
		mappings[OpCode_SWAP_B].flagResult =
		mappings[OpCode_SWAP_C].flagResult =
		mappings[OpCode_SWAP_D].flagResult =
		mappings[OpCode_SWAP_E].flagResult =
		mappings[OpCode_SWAP_H].flagResult =
		mappings[OpCode_SWAP_L].flagResult =
		mappings[OpCode_SWAP_MEM_HL].flagResult = createFlagResult(&hardware->resultInfo->isZero, &FALSE_VAL, &FALSE_VAL, &FALSE_VAL);
	
	mappings[OpCode_RLCA].flagResult =
		mappings[OpCode_RLA].flagResult = createFlagResult(&FALSE_VAL, &FALSE_VAL, &FALSE_VAL, &hardware->resultInfo->isOperand1Bit7Set);

	mappings[OpCode_RRCA].flagResult =
		mappings[OpCode_RRA].flagResult = createFlagResult(&FALSE_VAL, &FALSE_VAL, &FALSE_VAL, &hardware->resultInfo->isOperand1Bit0Set);
}