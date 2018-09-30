
#include "cpu_jump.h"

static const unsigned char ONE = 1;
static const int HEX_00 = 0x0, HEX_08 = 0x8, HEX_10 = 0x10, HEX_18 = 0x18, HEX_20 = 0x20, HEX_28 = 0x28, HEX_30 = 0x30, HEX_38 = 0x38;


void populateJumpInstructions(Hardware *hardware, InstructionMapping *mappings) {
	populateJumpCalculations(hardware, mappings);
	populateJumpNextPC(hardware, mappings);
	populateJumpFlagConditions(hardware, mappings);
}

void populateJumpCalculations(Hardware *hardware, InstructionMapping *mappings) {
	mappings[OpCode_CALL_C_a16].operand1 =
		mappings[OpCode_CALL_NC_a16].operand1 =
		mappings[OpCode_CALL_NZ_a16].operand1 =
		mappings[OpCode_CALL_Z_a16].operand1 =
		mappings[OpCode_CALL_a16].operand1 = 
		mappings[OpCode_RST_00H].operand1 =
		mappings[OpCode_RST_08H].operand1 =
		mappings[OpCode_RST_10H].operand1 =
		mappings[OpCode_RST_18H].operand1 =
		mappings[OpCode_RST_20H].operand1 =
		mappings[OpCode_RST_28H].operand1 =
		mappings[OpCode_RST_30H].operand1 =
		mappings[OpCode_RST_38H].operand1 = createGBWordValue(&(hardware->computedValues->NextPCAddress));
	
	mappings[OpCode_CALL_C_a16].destination =
		mappings[OpCode_CALL_NC_a16].destination =
		mappings[OpCode_CALL_NZ_a16].destination =
		mappings[OpCode_CALL_Z_a16].destination =
		mappings[OpCode_CALL_a16].destination =
		mappings[OpCode_RST_00H].destination =
		mappings[OpCode_RST_08H].destination =
		mappings[OpCode_RST_10H].destination =
		mappings[OpCode_RST_18H].destination =
		mappings[OpCode_RST_20H].destination =
		mappings[OpCode_RST_28H].destination =
		mappings[OpCode_RST_30H].destination =
		mappings[OpCode_RST_38H].destination = createGBSplitBytePointer(&(hardware->computedValues->stackMinusOneValue), &(hardware->computedValues->stackMinusTwoValue));

	mappings[OpCode_CALL_C_a16].nextSP =
		mappings[OpCode_CALL_NC_a16].nextSP =
		mappings[OpCode_CALL_NZ_a16].nextSP =
		mappings[OpCode_CALL_Z_a16].nextSP =
		mappings[OpCode_CALL_a16].nextSP =
		mappings[OpCode_RST_00H].nextSP =
		mappings[OpCode_RST_08H].nextSP =
		mappings[OpCode_RST_10H].nextSP =
		mappings[OpCode_RST_18H].nextSP =
		mappings[OpCode_RST_20H].nextSP =
		mappings[OpCode_RST_28H].nextSP =
		mappings[OpCode_RST_30H].nextSP =
		mappings[OpCode_RST_38H].nextSP = &hardware->computedValues->SPMinusTwo;
	
	mappings[OpCode_RET].nextSP =
		mappings[OpCode_RETI].nextSP =
		mappings[OpCode_RET_C].nextSP =
		mappings[OpCode_RET_NC].nextSP =
		mappings[OpCode_RET_NZ].nextSP =
		mappings[OpCode_RET_Z].nextSP = &hardware->computedValues->SPPlusTwo;
}

void populateJumpNextPC(Hardware *hardware, InstructionMapping *mappings) {
	mappings[OpCode_JP_MEM_HL].nextPC = &(hardware->computedValues->HL);

	mappings[OpCode_JP_C_a16].nextPC =
		mappings[OpCode_JP_NC_a16].nextPC =
		mappings[OpCode_JP_NZ_a16].nextPC =
		mappings[OpCode_JP_Z_a16].nextPC =
		mappings[OpCode_JP_a16].nextPC = 
		mappings[OpCode_CALL_C_a16].nextPC =
		mappings[OpCode_CALL_NC_a16].nextPC =
		mappings[OpCode_CALL_NZ_a16].nextPC =
		mappings[OpCode_CALL_Z_a16].nextPC =
		mappings[OpCode_CALL_a16].nextPC = &(hardware->computedValues->immediateWord);

	mappings[OpCode_JR_C_r8].nextPC =
		mappings[OpCode_JR_NC_r8].nextPC =
		mappings[OpCode_JR_NZ_r8].nextPC =
		mappings[OpCode_JR_Z_r8].nextPC =
		mappings[OpCode_JR_r8].nextPC = &(hardware->computedValues->NextPCAddressPlusImmediateByteSigned);

	mappings[OpCode_RET].nextPC =
		mappings[OpCode_RETI].nextPC =
		mappings[OpCode_RET_C].nextPC =
		mappings[OpCode_RET_NC].nextPC =
		mappings[OpCode_RET_NZ].nextPC =
		mappings[OpCode_RET_Z].nextPC = &hardware->computedValues->stackWordValue;

	mappings[OpCode_RST_00H].nextPC = &HEX_00;
	mappings[OpCode_RST_08H].nextPC = &HEX_08;
	mappings[OpCode_RST_10H].nextPC = &HEX_10;
	mappings[OpCode_RST_18H].nextPC = &HEX_18;
	mappings[OpCode_RST_20H].nextPC = &HEX_20;
	mappings[OpCode_RST_28H].nextPC = &HEX_28;
	mappings[OpCode_RST_30H].nextPC = &HEX_30;
	mappings[OpCode_RST_38H].nextPC = &HEX_38;
}

void populateJumpFlagConditions(Hardware *hardware, InstructionMapping *mappings) {	
	mappings[OpCode_CALL_C_a16].flagCondition =
		mappings[OpCode_JP_C_a16].flagCondition =
		mappings[OpCode_JR_C_r8].flagCondition =
		mappings[OpCode_RET_C].flagCondition = createFlagCondition(FLAGS_CY, false);

	mappings[OpCode_CALL_NC_a16].flagCondition =
		mappings[OpCode_JR_NC_r8].flagCondition =
		mappings[OpCode_JP_NC_a16].flagCondition =
		mappings[OpCode_RET_NC].flagCondition = createFlagCondition(FLAGS_CY, true);

	mappings[OpCode_CALL_NZ_a16].flagCondition =
		mappings[OpCode_JR_NZ_r8].flagCondition =
		mappings[OpCode_JP_NZ_a16].flagCondition =
		mappings[OpCode_RET_NZ].flagCondition = createFlagCondition(FLAGS_Z, true);

	mappings[OpCode_CALL_Z_a16].flagCondition =
		mappings[OpCode_JR_Z_r8].flagCondition =
		mappings[OpCode_JP_Z_a16].flagCondition =
		mappings[OpCode_RET_Z].flagCondition = createFlagCondition(FLAGS_Z, false);
}

