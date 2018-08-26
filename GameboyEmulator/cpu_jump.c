
#include "cpu_jump.h"


void populateJumpInstructions(Hardware *hardware, InstructionMapping *mappings) {
	populateJumpNextPC(hardware, mappings);
	populateJumpFlagConditions(hardware, mappings);
	populateJumpOpSizes(hardware, mappings);
}

void populateJumpNextPC(Hardware *hardware, InstructionMapping *mappings) {
	mappings[OpCode_JP_MEM_HL].nextPC = &(hardware->cachedValues->HL);

	mappings[OpCode_JP_C_a16].nextPC =
		mappings[OpCode_JP_NC_a16].nextPC =
		mappings[OpCode_JP_NZ_a16].nextPC =
		mappings[OpCode_JP_Z_a16].nextPC =
		mappings[OpCode_JP_a16].nextPC = &(hardware->cachedValues->immediateWord);

	mappings[OpCode_JR_C_r8].nextPC =
		mappings[OpCode_JR_NC_r8].nextPC =
		mappings[OpCode_JR_NZ_r8].nextPC =
		mappings[OpCode_JR_Z_r8].nextPC =
		mappings[OpCode_JR_r8].nextPC = &(hardware->cachedValues->NextPCAddressPlusImmediateByteSigned);

	/*OpCode_CALL_C_a16 = 0xdc,
		OpCode_CALL_NC_a16 = 0xd4,
		OpCode_CALL_NZ_a16 = 0xc4,
		OpCode_CALL_Z_a16 = 0xcc,
		OpCode_CALL_a16 = 0xcd,

		OpCode_RET = 0xc9,
		OpCode_RETI = 0xd9,
		OpCode_RET_C = 0xd8,
		OpCode_RET_NC = 0xd0,
		OpCode_RET_NZ = 0xc0,
		OpCode_RET_Z = 0xc8,

		OpCode_RST_00H = 0xc7,
		OpCode_RST_08H = 0xcf,
		OpCode_RST_10H = 0xd7,
		OpCode_RST_18H = 0xdf,
		OpCode_RST_20H = 0xe7,
		OpCode_RST_28H = 0xef,
		OpCode_RST_30H = 0xf7,
		OpCode_RST_38H = 0xff,*/

}

void populateJumpFlagConditions(Hardware *hardware, InstructionMapping *mappings) {
	mappings[OpCode_JP_C_a16].flagCondition =
		mappings[OpCode_JR_C_r8].flagCondition = createFlagCondition(FLAGS_CY, false);

	mappings[OpCode_JR_NC_r8].flagCondition =
		mappings[OpCode_JP_NC_a16].flagCondition = createFlagCondition(FLAGS_CY, true);

	mappings[OpCode_JR_NZ_r8].flagCondition =
		mappings[OpCode_JP_NZ_a16].flagCondition = createFlagCondition(FLAGS_Z, true);

	mappings[OpCode_JR_Z_r8].flagCondition =
		mappings[OpCode_JP_Z_a16].flagCondition = createFlagCondition(FLAGS_Z, false);
}


void populateJumpOpSizes(Hardware *hardware, InstructionMapping *mappings) {
	mappings[OpCode_JP_C_a16].sizeBytes =
		mappings[OpCode_JP_NC_a16].sizeBytes =
		mappings[OpCode_JP_NZ_a16].sizeBytes =
		mappings[OpCode_JP_Z_a16].sizeBytes =
		mappings[OpCode_JP_a16].sizeBytes = 3;

	mappings[OpCode_JR_C_r8].sizeBytes =
		mappings[OpCode_JR_NC_r8].sizeBytes =
		mappings[OpCode_JR_NZ_r8].sizeBytes =
		mappings[OpCode_JR_Z_r8].sizeBytes =
		mappings[OpCode_JR_r8].sizeBytes = 2;
}