

#include "cpu_cycles.h"

void populateCPUCycleCounts(InstructionMapping *mappings) {
	OpCycleCount *twoCycle = createOpCycleCount(2, 2);

	mappings[OpCode_ADC_A_MEM_HL].cycleCount =
		mappings[OpCode_ADC_A_d8].cycleCount =
		mappings[OpCode_ADD_A_MEM_HL].cycleCount =
		mappings[OpCode_ADD_A_d8].cycleCount =
		mappings[OpCode_ADD_HL_BC].cycleCount =
		mappings[OpCode_ADD_HL_DE].cycleCount =
		mappings[OpCode_ADD_HL_HL].cycleCount =
		mappings[OpCode_AND_MEM_HL].cycleCount =
		mappings[OpCode_ADD_HL_SP].cycleCount =
		mappings[OpCode_AND_d8].cycleCount =
		mappings[OpCode_CP_MEM_HL].cycleCount =
		mappings[OpCode_CP_d8].cycleCount =
		mappings[OpCode_DEC_BC].cycleCount =
		mappings[OpCode_DEC_DE].cycleCount =
		mappings[OpCode_DEC_HL].cycleCount =
		mappings[OpCode_DEC_SP].cycleCount =
		mappings[OpCode_INC_BC].cycleCount =
		mappings[OpCode_INC_DE].cycleCount =
		mappings[OpCode_INC_HL].cycleCount =
		mappings[OpCode_INC_SP].cycleCount =
		mappings[OpCode_LD_MEM_BC_A].cycleCount =
		mappings[OpCode_LD_MEM_C_A].cycleCount =
		mappings[OpCode_LD_MEM_DE_A].cycleCount =
		mappings[OpCode_LD_MEM_HL_A].cycleCount =
		mappings[OpCode_LD_MEM_HL_B].cycleCount =
		mappings[OpCode_LD_MEM_HL_C].cycleCount =
		mappings[OpCode_LD_MEM_HL_D].cycleCount =
		mappings[OpCode_LD_MEM_HL_E].cycleCount =
		mappings[OpCode_LD_MEM_HL_H].cycleCount =
		mappings[OpCode_LD_MEM_HL_L].cycleCount =
		mappings[OpCode_LD_MEM_HLI_A].cycleCount =
		mappings[OpCode_LD_MEM_HLD_A].cycleCount =
		mappings[OpCode_LD_A_MEM_BC].cycleCount =
		mappings[OpCode_LD_A_MEM_C].cycleCount =
		mappings[OpCode_LD_A_MEM_DE].cycleCount =
		mappings[OpCode_LD_A_MEM_HL].cycleCount =
		mappings[OpCode_LD_A_MEM_HLI].cycleCount =
		mappings[OpCode_LD_A_MEM_HLD].cycleCount =
		mappings[OpCode_LD_A_d8].cycleCount =
		mappings[OpCode_SBC_A_MEM_HL].cycleCount =
		mappings[OpCode_SBC_A_d8].cycleCount =
		mappings[OpCode_SUB_MEM_HL].cycleCount =
		mappings[OpCode_SUB_d8].cycleCount =
		mappings[OpCode_XOR_MEM_HL].cycleCount =
		mappings[OpCode_XOR_d8].cycleCount =
		mappings[OpCode_LD_B_MEM_HL].cycleCount =
		mappings[OpCode_LD_B_d8].cycleCount =
		mappings[OpCode_LD_C_MEM_HL].cycleCount =
		mappings[OpCode_LD_C_d8].cycleCount =
		mappings[OpCode_LD_D_MEM_HL].cycleCount =
		mappings[OpCode_LD_D_d8].cycleCount =
		mappings[OpCode_LD_E_MEM_HL].cycleCount =
		mappings[OpCode_LD_E_d8].cycleCount =
		mappings[OpCode_LD_H_MEM_HL].cycleCount =
		mappings[OpCode_LD_H_d8].cycleCount =
		mappings[OpCode_LD_L_MEM_HL].cycleCount =
		mappings[OpCode_LD_L_d8].cycleCount =
		mappings[OpCode_LD_SP_HL].cycleCount =
		mappings[OpCode_OR_MEM_HL].cycleCount =
		mappings[OpCode_OR_d8].cycleCount = twoCycle;
	
	/*
	TODO: test this
	//set the basic 0xCB cycle counts
	for (int i = OPCODE_PREFIX_CB; i <= OPCODE_PREFIX_CB + 0xFF; i++) {
		mappings[i].cycleCount = twoCycle;
	}
	*/

	mappings[OpCode_DEC_MEM_HL].cycleCount =
		mappings[OpCode_INC_MEM_HL].cycleCount =
		mappings[OpCode_JR_r8].cycleCount =
		mappings[OpCode_LDH_MEM_a8_A].cycleCount =
		mappings[OpCode_LDH_A_MEM_a8].cycleCount =
		mappings[OpCode_LD_MEM_HL_d8].cycleCount =
		mappings[OpCode_POP_AF].cycleCount =
		mappings[OpCode_POP_BC].cycleCount =
		mappings[OpCode_POP_DE].cycleCount =
		mappings[OpCode_POP_HL].cycleCount =
		mappings[OpCode_LD_BC_d16].cycleCount =
		mappings[OpCode_LD_DE_d16].cycleCount =
		mappings[OpCode_LD_HL_SP_PLUS_r8].cycleCount =
		mappings[OpCode_LD_HL_d16].cycleCount =
		mappings[OpCode_LD_SP_d16].cycleCount = 
		mappings[OpCode_RLC_MEM_HL].cycleCount =
		mappings[OpCode_RRC_MEM_HL].cycleCount =
		mappings[OpCode_RL_MEM_HL].cycleCount =
		mappings[OpCode_RR_MEM_HL].cycleCount =
		mappings[OpCode_SLA_MEM_HL].cycleCount =
		mappings[OpCode_SRA_MEM_HL].cycleCount =
		mappings[OpCode_SWAP_MEM_HL].cycleCount =
		mappings[OpCode_SRL_MEM_HL].cycleCount =
		mappings[OpCode_BIT_0_MEM_HL].cycleCount =
		mappings[OpCode_BIT_1_MEM_HL].cycleCount =
		mappings[OpCode_BIT_2_MEM_HL].cycleCount =
		mappings[OpCode_BIT_3_MEM_HL].cycleCount =
		mappings[OpCode_BIT_4_MEM_HL].cycleCount =
		mappings[OpCode_BIT_5_MEM_HL].cycleCount =
		mappings[OpCode_BIT_6_MEM_HL].cycleCount =
		mappings[OpCode_BIT_7_MEM_HL].cycleCount =
		mappings[OpCode_RES_0_MEM_HL].cycleCount =
		mappings[OpCode_RES_1_MEM_HL].cycleCount =
		mappings[OpCode_RES_2_MEM_HL].cycleCount =
		mappings[OpCode_RES_3_MEM_HL].cycleCount =
		mappings[OpCode_RES_4_MEM_HL].cycleCount =
		mappings[OpCode_RES_5_MEM_HL].cycleCount =
		mappings[OpCode_RES_6_MEM_HL].cycleCount =
		mappings[OpCode_RES_7_MEM_HL].cycleCount =
		mappings[OpCode_SET_0_MEM_HL].cycleCount =
		mappings[OpCode_SET_1_MEM_HL].cycleCount =
		mappings[OpCode_SET_2_MEM_HL].cycleCount =
		mappings[OpCode_SET_3_MEM_HL].cycleCount =
		mappings[OpCode_SET_4_MEM_HL].cycleCount =
		mappings[OpCode_SET_5_MEM_HL].cycleCount =
		mappings[OpCode_SET_6_MEM_HL].cycleCount =
		mappings[OpCode_SET_7_MEM_HL].cycleCount = createOpCycleCount(3, 3);

	mappings[OpCode_ADD_SP_r8].cycleCount =
		mappings[OpCode_JP_a16].cycleCount =
		mappings[OpCode_LD_MEM_a16_A].cycleCount =
		mappings[OpCode_PUSH_AF].cycleCount =
		mappings[OpCode_PUSH_BC].cycleCount =
		mappings[OpCode_PUSH_DE].cycleCount =
		mappings[OpCode_PUSH_HL].cycleCount =
		mappings[OpCode_RST_00H].cycleCount =
		mappings[OpCode_RST_08H].cycleCount =
		mappings[OpCode_RST_10H].cycleCount =
		mappings[OpCode_RST_18H].cycleCount =
		mappings[OpCode_RST_20H].cycleCount =
		mappings[OpCode_RST_28H].cycleCount =
		mappings[OpCode_RST_30H].cycleCount =
		mappings[OpCode_RST_38H].cycleCount =
		mappings[OpCode_RET].cycleCount =
		mappings[OpCode_RETI].cycleCount =
		mappings[OpCode_LD_A_MEM_a16].cycleCount = createOpCycleCount(4, 4);


	mappings[OpCode_CALL_C_a16].cycleCount =
		mappings[OpCode_CALL_NC_a16].cycleCount =
		mappings[OpCode_CALL_NZ_a16].cycleCount =
		mappings[OpCode_CALL_Z_a16].cycleCount = createOpCycleCount(6, 3);

	mappings[OpCode_JP_C_a16].cycleCount =
		mappings[OpCode_JP_NC_a16].cycleCount =
		mappings[OpCode_JP_NZ_a16].cycleCount =
		mappings[OpCode_JP_Z_a16].cycleCount = createOpCycleCount(4, 3);

	mappings[OpCode_JR_C_r8].cycleCount =
		mappings[OpCode_JR_NC_r8].cycleCount =
		mappings[OpCode_JR_NZ_r8].cycleCount =
		mappings[OpCode_JR_Z_r8].cycleCount = createOpCycleCount(3, 2);

	mappings[OpCode_RET_C].cycleCount =
		mappings[OpCode_RET_NC].cycleCount =
		mappings[OpCode_RET_NZ].cycleCount =
		mappings[OpCode_RET_Z].cycleCount = createOpCycleCount(5, 2);

	mappings[OpCode_CALL_a16].cycleCount = createOpCycleCount(6, 6);
	mappings[OpCode_LD_MEM_a16_SP].cycleCount = createOpCycleCount(5, 5);
}


void populateCPUOpSizes(InstructionMapping *mappings) {
	mappings[OpCode_ADC_A_d8].sizeBytes = 2;
	mappings[OpCode_ADD_A_d8].sizeBytes = 2;
	mappings[OpCode_ADD_SP_r8].sizeBytes = 2;
	mappings[OpCode_AND_d8].sizeBytes = 2;
	mappings[OpCode_CALL_C_a16].sizeBytes = 3;
	mappings[OpCode_CALL_NC_a16].sizeBytes = 3;
	mappings[OpCode_CALL_NZ_a16].sizeBytes = 3;
	mappings[OpCode_CALL_Z_a16].sizeBytes = 3;
	mappings[OpCode_CALL_a16].sizeBytes = 3;
	mappings[OpCode_CP_d8].sizeBytes = 2;
	mappings[OpCode_JP_C_a16].sizeBytes = 3;
	mappings[OpCode_JP_NC_a16].sizeBytes = 3;
	mappings[OpCode_JP_NZ_a16].sizeBytes = 3;
	mappings[OpCode_JP_Z_a16].sizeBytes = 3;
	mappings[OpCode_JP_a16].sizeBytes = 3;
	mappings[OpCode_JR_C_r8].sizeBytes = 2;
	mappings[OpCode_JR_NC_r8].sizeBytes = 2;
	mappings[OpCode_JR_NZ_r8].sizeBytes = 2;
	mappings[OpCode_JR_Z_r8].sizeBytes = 2;
	mappings[OpCode_JR_r8].sizeBytes = 2;
	mappings[OpCode_LDH_A_MEM_a8].sizeBytes = 2;
	mappings[OpCode_LDH_MEM_a8_A].sizeBytes = 2;
	//mappings[OpCode_LD_A_MEM_C].sizeBytes = 2;
	mappings[OpCode_LD_A_MEM_a16].sizeBytes = 3;
	mappings[OpCode_LD_A_d8].sizeBytes = 2;
	mappings[OpCode_LD_B_d8].sizeBytes = 2;
	mappings[OpCode_LD_C_d8].sizeBytes = 2;
	mappings[OpCode_LD_DE_d16].sizeBytes = 3;
	mappings[OpCode_LD_D_d8].sizeBytes = 2;
	mappings[OpCode_LD_E_d8].sizeBytes = 2;
	mappings[OpCode_LD_HL_SP_PLUS_r8].sizeBytes = 2;
	mappings[OpCode_LD_HL_d16].sizeBytes = 3;
	mappings[OpCode_LD_H_d8].sizeBytes = 2;
	mappings[OpCode_LD_L_d8].sizeBytes = 2;
	//mappings[OpCode_LD_MEM_C_A].sizeBytes = 2;
	mappings[OpCode_LD_MEM_HL_d8].sizeBytes = 2;
	mappings[OpCode_LD_MEM_a16_A].sizeBytes = 3;
	mappings[OpCode_LD_MEM_a16_SP].sizeBytes = 3;
	mappings[OpCode_LD_SP_d16].sizeBytes = 3;
	mappings[OpCode_OR_d8].sizeBytes = 2;
	mappings[OpCode_SBC_A_d8].sizeBytes = 2;
	mappings[OpCode_SUB_d8].sizeBytes = 2;
	mappings[OpCode_XOR_d8].sizeBytes = 2;
	mappings[OpCode_LD_BC_d16].sizeBytes = 3;

	mappings[OpCode_STOP].sizeBytes = 2;
}