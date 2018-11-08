
#include "cpu_jump.h"

static const unsigned char ONE = 1;
static const int HEX_00 = 0x0, HEX_08 = 0x8, HEX_10 = 0x10, HEX_18 = 0x18, HEX_20 = 0x20, HEX_28 = 0x28, HEX_30 = 0x30, HEX_38 = 0x38;


void populateJumpInstructions(Hardware *hardware, InstructionMappingList *mappings) {
	populateJumpCalculations(hardware, mappings);
	populateJumpNextPC(hardware, mappings);
	populateJumpFlagConditions(hardware, mappings);
}

void populateJumpCalculations(Hardware *hardware, InstructionMappingList *mappings) {
	mappings->mappings[OpCode_CALL_C_a16].operand1 =
		mappings->mappings[OpCode_CALL_NC_a16].operand1 =
		mappings->mappings[OpCode_CALL_NZ_a16].operand1 =
		mappings->mappings[OpCode_CALL_Z_a16].operand1 =
		mappings->mappings[OpCode_CALL_a16].operand1 = 
		mappings->mappings[OpCode_RST_00H].operand1 =
		mappings->mappings[OpCode_RST_08H].operand1 =
		mappings->mappings[OpCode_RST_10H].operand1 =
		mappings->mappings[OpCode_RST_18H].operand1 =
		mappings->mappings[OpCode_RST_20H].operand1 =
		mappings->mappings[OpCode_RST_28H].operand1 =
		mappings->mappings[OpCode_RST_30H].operand1 =
		mappings->mappings[OpCode_RST_38H].operand1 = mappings->value_nextPCAddress;
	
	mappings->mappings[OpCode_CALL_C_a16].destination =
		mappings->mappings[OpCode_CALL_NC_a16].destination =
		mappings->mappings[OpCode_CALL_NZ_a16].destination =
		mappings->mappings[OpCode_CALL_Z_a16].destination =
		mappings->mappings[OpCode_CALL_a16].destination =
		mappings->mappings[OpCode_RST_00H].destination =
		mappings->mappings[OpCode_RST_08H].destination =
		mappings->mappings[OpCode_RST_10H].destination =
		mappings->mappings[OpCode_RST_18H].destination =
		mappings->mappings[OpCode_RST_20H].destination =
		mappings->mappings[OpCode_RST_28H].destination =
		mappings->mappings[OpCode_RST_30H].destination =
		mappings->mappings[OpCode_RST_38H].destination = mappings->value_split_stackMinusOne_stackMinusTwo;

	mappings->mappings[OpCode_CALL_C_a16].nextSP =
		mappings->mappings[OpCode_CALL_NC_a16].nextSP =
		mappings->mappings[OpCode_CALL_NZ_a16].nextSP =
		mappings->mappings[OpCode_CALL_Z_a16].nextSP =
		mappings->mappings[OpCode_CALL_a16].nextSP =
		mappings->mappings[OpCode_RST_00H].nextSP =
		mappings->mappings[OpCode_RST_08H].nextSP =
		mappings->mappings[OpCode_RST_10H].nextSP =
		mappings->mappings[OpCode_RST_18H].nextSP =
		mappings->mappings[OpCode_RST_20H].nextSP =
		mappings->mappings[OpCode_RST_28H].nextSP =
		mappings->mappings[OpCode_RST_30H].nextSP =
		mappings->mappings[OpCode_RST_38H].nextSP = &hardware->computedValues->SPMinusTwo;
	
	mappings->mappings[OpCode_RET].nextSP =
		mappings->mappings[OpCode_RETI].nextSP =
		mappings->mappings[OpCode_RET_C].nextSP =
		mappings->mappings[OpCode_RET_NC].nextSP =
		mappings->mappings[OpCode_RET_NZ].nextSP =
		mappings->mappings[OpCode_RET_Z].nextSP = &hardware->computedValues->SPPlusTwo;
}

void populateJumpNextPC(Hardware *hardware, InstructionMappingList *mappings) {
	mappings->mappings[OpCode_JP_MEM_HL].nextPC = &(hardware->computedValues->HL);

	mappings->mappings[OpCode_JP_C_a16].nextPC =
		mappings->mappings[OpCode_JP_NC_a16].nextPC =
		mappings->mappings[OpCode_JP_NZ_a16].nextPC =
		mappings->mappings[OpCode_JP_Z_a16].nextPC =
		mappings->mappings[OpCode_JP_a16].nextPC = 
		mappings->mappings[OpCode_CALL_C_a16].nextPC =
		mappings->mappings[OpCode_CALL_NC_a16].nextPC =
		mappings->mappings[OpCode_CALL_NZ_a16].nextPC =
		mappings->mappings[OpCode_CALL_Z_a16].nextPC =
		mappings->mappings[OpCode_CALL_a16].nextPC = &(hardware->computedValues->immediateWord);

	mappings->mappings[OpCode_JR_C_r8].nextPC =
		mappings->mappings[OpCode_JR_NC_r8].nextPC =
		mappings->mappings[OpCode_JR_NZ_r8].nextPC =
		mappings->mappings[OpCode_JR_Z_r8].nextPC =
		mappings->mappings[OpCode_JR_r8].nextPC = &(hardware->computedValues->NextPCAddressPlusImmediateByteSigned);

	mappings->mappings[OpCode_RET].nextPC =
		mappings->mappings[OpCode_RETI].nextPC =
		mappings->mappings[OpCode_RET_C].nextPC =
		mappings->mappings[OpCode_RET_NC].nextPC =
		mappings->mappings[OpCode_RET_NZ].nextPC =
		mappings->mappings[OpCode_RET_Z].nextPC = &hardware->computedValues->stackWordValue;

	mappings->mappings[OpCode_RST_00H].nextPC = &HEX_00;
	mappings->mappings[OpCode_RST_08H].nextPC = &HEX_08;
	mappings->mappings[OpCode_RST_10H].nextPC = &HEX_10;
	mappings->mappings[OpCode_RST_18H].nextPC = &HEX_18;
	mappings->mappings[OpCode_RST_20H].nextPC = &HEX_20;
	mappings->mappings[OpCode_RST_28H].nextPC = &HEX_28;
	mappings->mappings[OpCode_RST_30H].nextPC = &HEX_30;
	mappings->mappings[OpCode_RST_38H].nextPC = &HEX_38;
}

void populateJumpFlagConditions(Hardware *hardware, InstructionMappingList *mappings) {	
	mappings->mappings[OpCode_CALL_C_a16].flagCondition =
		mappings->mappings[OpCode_JP_C_a16].flagCondition =
		mappings->mappings[OpCode_JR_C_r8].flagCondition =
		mappings->mappings[OpCode_RET_C].flagCondition = createFlagCondition(FLAGS_CY, false);

	mappings->mappings[OpCode_CALL_NC_a16].flagCondition =
		mappings->mappings[OpCode_JR_NC_r8].flagCondition =
		mappings->mappings[OpCode_JP_NC_a16].flagCondition =
		mappings->mappings[OpCode_RET_NC].flagCondition = createFlagCondition(FLAGS_CY, true);

	mappings->mappings[OpCode_CALL_NZ_a16].flagCondition =
		mappings->mappings[OpCode_JR_NZ_r8].flagCondition =
		mappings->mappings[OpCode_JP_NZ_a16].flagCondition =
		mappings->mappings[OpCode_RET_NZ].flagCondition = createFlagCondition(FLAGS_Z, true);

	mappings->mappings[OpCode_CALL_Z_a16].flagCondition =
		mappings->mappings[OpCode_JR_Z_r8].flagCondition =
		mappings->mappings[OpCode_JP_Z_a16].flagCondition =
		mappings->mappings[OpCode_RET_Z].flagCondition = createFlagCondition(FLAGS_Z, false);
}

