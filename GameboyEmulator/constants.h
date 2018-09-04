#pragma once

typedef enum _RomLocation {
	ROM_LOCATION_INTERRUPT_VBLANK = 0x40,
	ROM_LOCATION_INTERRUPT_LCD_STAT = 0x48,
	ROM_LOCATION_INTERRUPT_TIMER_OVERFLOW = 0x50,
	ROM_LOCATION_INTERRUPT_SERIAL_TRANSFER = 0x58,
	ROM_LOCATION_INTERRUPT_BUTTON_PRESS = 0x60,
	ROM_LOCATION_EXEC_START = 0x100,
	ROM_LOCATION_LOGO = 0x104,
	ROM_LOCATION_LOGO_END = 0x133,
	ROM_LOCATION_GAME_NAME = 0x134,
	ROM_LOCATION_GAME_NAME_END = 0x142
} RomLocation;


typedef enum _RamLocation {
	RAM_LOCATION_CART_FIXED = 0x0,
	RAM_LOCATION_CART_FIXED_END = 0x3fff,
	RAM_LOCATION_CART_SWITCHABLE = 0x4000,
	RAM_LOCATION_CART_SWITCHABLE_END = 0x7fff,
	RAM_LOCATION_VRAM = 0x8000,
	RAM_LOCATION_VRAM_END = 0x9FFF,
	RAM_LOCATION_CART_RAM = 0xA000,
	RAM_LOCATION_CART_RAM_END = 0xBFFF,
	RAM_LOCATION_WORK_RAM_FIXED = 0xC000,
	RAM_LOCATION_WORK_RAM_FIXED_END = 0xCFFF,
	RAM_LOCATION_WORK_RAM_SWITCHABLE = 0xD000,
	RAM_LOCATION_WORK_RAM_SWITCHABLE_END = 0xDFFF,
	RAM_LOCATION_MIRROR_WORK_RAM_FIXED = 0xE000,
	RAM_LOCATION_MIRROR_WORK_RAM_FIXED_END = 0xEFFF,
	RAM_LOCATION_MIRROR_WORK_RAM_SWITCHABLE = 0xF000,
	RAM_LOCATION_MIRROR_WORK_RAM_SWITCHABLE_END = 0xFDFF,
	RAM_LOCATION_OAM = 0xFE00,
	RAM_LOCATION_OAM_END = 0xFE9F,
	RAM_LOCATION_UNUSABLE = 0xFEA0,
	RAM_LOCATION_UNUSABLE_END = 0xFEFF,
	RAM_LOCATION_JOYPAD_INPUT = 0xFF00,
	RAM_LOCATION_SERIAL_TRANSFER_DATA = 0xFF01,
	RAM_LOCATION_SERIAL_TRANSFER_CONTROL = 0xFF02,
	RAM_LOCATION_SOUND_CHANNEL_1_Sweep_register = 0xFF10, //NR10 - Channel 1 Sweep register
	RAM_LOCATION_SOUND_CHANNEL_1_Sound_length_Wave_pattern_duty = 0xFF11, //NR11 - Channel 1 Sound_Length/Wave pattern duty
	RAM_LOCATION_SOUND_CHANNEL_1_Volume_Envelope = 0xFF12, //NR12 - Channel 1 Volume_Envelope
	RAM_LOCATION_SOUND_CHANNEL_1_Frequency_lo = 0xFF13, //NR13 - Channel 1 Frequency_lo 
	RAM_LOCATION_SOUND_CHANNEL_1_Frequency_hi = 0xFF14, //NR14 - Channel 1 Frequency_hi
	RAM_LOCATION_SOUND_CHANNEL_2_Sound_Length_Wave_Pattern_Duty = 0xFF16, //NR21 - Channel 2 Sound_Length/Wave Pattern Duty
	RAM_LOCATION_SOUND_CHANNEL_2_Volume_Envelope = 0xFF17, //NR22 - Channel 2 Volume_Envelope
	RAM_LOCATION_SOUND_CHANNEL_2_Frequency_lo_data = 0xFF18, //NR23 - Channel 2 Frequency_lo data 
	RAM_LOCATION_SOUND_CHANNEL_2_Frequency_hi_data = 0xFF19, //NR24 - Channel 2 Frequency_hi data
	RAM_LOCATION_SOUND_CHANNEL_3_Sound_on_off = 0xFF1A, //NR30 - Channel 3 Sound on/off
	RAM_LOCATION_SOUND_CHANNEL_3_Sound_Length = 0xFF1B, //NR31 - Channel 3 Sound_Length
	RAM_LOCATION_SOUND_CHANNEL_3_Select_output_level = 0xFF1C, //NR32 - Channel 3 Select output level
	RAM_LOCATION_SOUND_CHANNEL_3_Frequency_lower_data  = 0xFF1D, //NR33 - Channel 3 Frequency's lower data
	RAM_LOCATION_SOUND_CHANNEL_3_Frequency_higher_data = 0xFF1E, //NR34 - Channel 3 Frequency's higher data
	RAM_LOCATION_SOUND_WAVE_PATTERN = 0xFF30,
	RAM_LOCATION_SOUND_WAVE_PATTERN_END = 0xFF3F,
	RAM_LOCATION_SOUND_CHANNEL_4_Sound_Length = 0xFF20, //NR41 - Channel 4 Sound_Length
	RAM_LOCATION_SOUND_CHANNEL_4_Volume_Envelope = 0xFF21, //NR42 - Channel 4 Volume_Envelope
	RAM_LOCATION_SOUND_CHANNEL_4_Polynomial_Counter = 0xFF22, //NR43 - Channel 4 Polynomial Counter
	RAM_LOCATION_SOUND_CHANNEL_4_Counter_consecutive_Inital = 0xFF23, //NR44 - Channel 4 Counter/consecutive, Inital
	RAM_LOCATION_SOUND_CHANNEL_control_ON_OFF_Volume = 0xFF24, //NR50 - Channel control / ON-OFF / Volume
	RAM_LOCATION_SOUND_Selection_of_Sound_output_terminal = 0xFF25, //NR51 - Selection of Sound output terminal
	RAM_LOCATION_SOUND_ON_OFF = 0xFF26,
	RAM_LOCATION_LCD_CONTROL = 0xFF40,
	RAM_LOCATION_LCD_STATUS = 0xFF41,
	RAM_LOCATION_SCROLL_Y = 0xFF42,
	RAM_LOCATION_SCROLL_X = 0xFF43,
	RAM_LOCATION_LCD_Y_COORD = 0xFF44,
	RAM_LOCATION_LCD_Y_COMPARE = 0xFF45,
	RAM_LOCATION_DMA_TRANSFER = 0xFF46,
	RAM_LOCATION_BG_PALETTE = 0xFF47,
	RAM_LOCATION_OBJ_PALETTE_0 = 0xFF48,
	RAM_LOCATION_OBJ_PALETTE_1 = 0xFF49,
	RAM_LOCATION_WINDOW_Y = 0xFF4A,
	RAM_LOCATION_WINDOW_X = 0xFF4B,
	RAM_LOCATION_INTERRUPT_FLAGS = 0xFF0F,
	RAM_LOCATION_IO_END = 0xFF7F,
	RAM_LOCATION_HRAM = 0xFF80,
	RAM_LOCATION_HRAM_END = 0xFFFE,
	RAM_LOCATION_INTERRUPTS_ENABLE = 0xFFFF,
	RAM_MAX = 0xffff
} RamLocation;


typedef enum _CPUResultFlag {
	FLAGS_Z = 128,
	FLAGS_N = 64,
	FLAGS_H = 32,
	FLAGS_CY = 16
} CPUResultFlag;

typedef enum _InterruptFlag {
	INTERRUPT_FLAG_VBLANK = 0,
	INTERRUPT_FLAG_LCD_STAT = 2,
	INTERRUPT_FLAG_TIMER_OVERFLOW = 4,
	INTERRUPT_FLAG_SERIAL_TRANSFER = 8,
	INTERRUPT_FLAG_BUTTON_PRESS = 16
} InterruptFlag;

typedef enum _PPUFlag {
	PPU_FLAG_MODE_HBLANK = 0,
	PPU_FLAG_MODE_VBLANK = 1,
	PPU_FLAG_MODE_OAM_SEARCH = 2,
	PPU_FLAG_MODE_PIXEL_TRANSFER = 3,
	PPU_FLAG_MODE_MASK = 3,

	PPU_FLAG_LCD_ENABLE = 128, //0 = Off, 1 = On
	PPU_FLAG_WINDOW_TILE_MAP_SELECT = 61, //0 = 9800 - 9BFF, 1 = 9C00 - 9FFF
	PPU_FLAG_WINDOW_ENABLE = 32, //0 = Off, 1 = On
	PPU_FLAG_BG_TILE_ADDRESS_MODE = 16, //0 = 8800 - 97FF, 1 = 8000 - 8FFF
	PPU_FLAG_BG_TILE_MAP_SELECT = 8, //0 = 9800 - 9BFF, 1 = 9C00 - 9FFF
	PPU_FLAG_OBJ_SIZE_MASK = 4, //0 = 8x8, 1 = 8x16
	PPU_FLAG_OBJ_ENABLE = 2, //0 = Off, 1 = On
	PPU_FLAG_BG_ENABLE = 1 //0 = Off, 1 = On
} PPUFlag;

typedef enum _PPUCycles {
	PPU_CYCLES_OAM_SEARCH = 20,
	PPU_CYCLES_PIXEL_TRANSFER = 43,
	PPU_CYCLES_HBLANK = 51,
	PPU_CYCLES_LINE_TOTAL = 114
} PPUCycles;

typedef enum _OAMIndex {
	OAM_INDEX_POS_Y = 0,
	OAM_INDEX_POS_X = 1,
	OAM_INDEX_TILE_NUM = 2,
	OAM_INDEX_FLAGS = 3
} OAMIndex;

#define NUM_OPCODES 512
#define VRAM_SIZE 0x2000
#define OAM_SIZE 0xA0
#define WORK_RAM_SIZE 0x1000
#define HRAM_SIZE 0x7F

/*
 Some notes:
 - Target clock speed = 1,048,576 Hz

 - Each CPU tick processes 1 cycle @ 1.048 MHz (or 4 cycles of original CPU)

 - For PPU, each line of pixels takes:
	- 20 clocks OAM search
	- 43 clocks drawing pixels
	- 51 clocks idle for h-blank
 - So each line of pixels total takes 114 clocks
 - There are 144 "drawing" lines, and 10 additional idle lines for v-blank

 - So total clocks per gameboy frame = 114 x (144 + 10) = 17,556 clocks per gameboy frame
*/

#define TARGET_FPS 59.7f
#define TARGET_MILLSECONDS_PER_FRAME 16.75f
#define TARGET_TICKS_FRAME 17556
#define SCREEN_VISIBLE_LINES 144
#define VBLANK_LINES 10
#define SCREEN_TOTAL_LINES 154
#define VISIBLE_SPRITES_PER_LINE 10
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144
#define TILE_SIZE 8

typedef enum _OpCode {
	OpCode_ADC_A_A = 0x8f,
	OpCode_ADC_A_B = 0x88,
	OpCode_ADC_A_C = 0x89,
	OpCode_ADC_A_D = 0x8a,
	OpCode_ADC_A_E = 0x8b,
	OpCode_ADC_A_H = 0x8c,
	OpCode_ADC_A_L = 0x8d,
	OpCode_ADC_A_MEM_HL = 0x8e,
	OpCode_ADC_A_d8 = 0xce,
	OpCode_ADD_A_A = 0x87,
	OpCode_ADD_A_B = 0x80,
	OpCode_ADD_A_C = 0x81,
	OpCode_ADD_A_D = 0x82,
	OpCode_ADD_A_E = 0x83,
	OpCode_ADD_A_H = 0x84,
	OpCode_ADD_A_L = 0x85,
	OpCode_ADD_A_MEM_HL = 0x86,
	OpCode_ADD_A_d8 = 0xc6,
	OpCode_ADD_HL_BC = 0x9,
	OpCode_ADD_HL_DE = 0x19,
	OpCode_ADD_HL_HL = 0x29,
	OpCode_ADD_HL_SP = 0x39,
	OpCode_ADD_SP_r8 = 0xe8,
	OpCode_AND_A = 0xa7,
	OpCode_AND_B = 0xa0,
	OpCode_AND_C = 0xa1,
	OpCode_AND_D = 0xa2,
	OpCode_AND_E = 0xa3,
	OpCode_AND_H = 0xa4,
	OpCode_AND_L = 0xa5,
	OpCode_AND_MEM_HL = 0xa6,
	OpCode_AND_d8 = 0xe6,
	OpCode_CALL_C_a16 = 0xdc,
	OpCode_CALL_NC_a16 = 0xd4,
	OpCode_CALL_NZ_a16 = 0xc4,
	OpCode_CALL_Z_a16 = 0xcc,
	OpCode_CALL_a16 = 0xcd,
	OpCode_CCF = 0x3f,
	OpCode_CPL = 0x2f,
	OpCode_CP_A = 0xbf,
	OpCode_CP_B = 0xb8,
	OpCode_CP_C = 0xb9,
	OpCode_CP_D = 0xba,
	OpCode_CP_E = 0xbb,
	OpCode_CP_H = 0xbc,
	OpCode_CP_L = 0xbd,
	OpCode_CP_MEM_HL = 0xbe,
	OpCode_CP_d8 = 0xfe,
	OpCode_DAA = 0x27,
	OpCode_DEC_A = 0x3d,
	OpCode_DEC_B = 0x5,
	OpCode_DEC_BC = 0xb,
	OpCode_DEC_C = 0xd,
	OpCode_DEC_D = 0x15,
	OpCode_DEC_DE = 0x1b,
	OpCode_DEC_E = 0x1d,
	OpCode_DEC_H = 0x25,
	OpCode_DEC_HL = 0x2b,
	OpCode_DEC_L = 0x2d,
	OpCode_DEC_MEM_HL = 0x35,
	OpCode_DEC_SP = 0x3b,
	OpCode_DI = 0xf3,
	OpCode_EI = 0xfb,
	OpCode_HALT = 0x76,
	OpCode_INC_A = 0x3c,
	OpCode_INC_B = 0x4,
	OpCode_INC_BC = 0x3,
	OpCode_INC_C = 0xc,
	OpCode_INC_D = 0x14,
	OpCode_INC_DE = 0x13,
	OpCode_INC_E = 0x1c,
	OpCode_INC_H = 0x24,
	OpCode_INC_HL = 0x23,
	OpCode_INC_L = 0x2c,
	OpCode_INC_MEM_HL = 0x34,
	OpCode_INC_SP = 0x33,
	OpCode_JP_C_a16 = 0xda,
	OpCode_JP_MEM_HL = 0xe9,
	OpCode_JP_NC_a16 = 0xd2,
	OpCode_JP_NZ_a16 = 0xc2,
	OpCode_JP_Z_a16 = 0xca,
	OpCode_JP_a16 = 0xc3,
	OpCode_JR_C_r8 = 0x38,
	OpCode_JR_NC_r8 = 0x30,
	OpCode_JR_NZ_r8 = 0x20,
	OpCode_JR_Z_r8 = 0x28,
	OpCode_JR_r8 = 0x18,
	OpCode_LDH_A_MEM_a8 = 0xf0,
	OpCode_LDH_MEM_a8_A = 0xe0,
	OpCode_LD_A_A = 0x7f,
	OpCode_LD_A_B = 0x78,
	OpCode_LD_A_C = 0x79,
	OpCode_LD_A_D = 0x7a,
	OpCode_LD_A_E = 0x7b,
	OpCode_LD_A_H = 0x7c,
	OpCode_LD_A_L = 0x7d,
	OpCode_LD_A_MEM_BC = 0xa,
	OpCode_LD_A_MEM_C = 0xf2,
	OpCode_LD_A_MEM_DE = 0x1a,
	OpCode_LD_A_MEM_HL = 0x7e,
	OpCode_LD_A_MEM_HLD = 0x3a,
	OpCode_LD_A_MEM_HLI = 0x2a,
	OpCode_LD_A_MEM_a16 = 0xfa,
	OpCode_LD_A_d8 = 0x3e,
	OpCode_LD_BC_d16 = 0x1,
	OpCode_LD_B_A = 0x47,
	OpCode_LD_B_B = 0x40,
	OpCode_LD_B_C = 0x41,
	OpCode_LD_B_D = 0x42,
	OpCode_LD_B_E = 0x43,
	OpCode_LD_B_H = 0x44,
	OpCode_LD_B_L = 0x45,
	OpCode_LD_B_MEM_HL = 0x46,
	OpCode_LD_B_d8 = 0x6,
	OpCode_LD_C_A = 0x4f,
	OpCode_LD_C_B = 0x48,
	OpCode_LD_C_C = 0x49,
	OpCode_LD_C_D = 0x4a,
	OpCode_LD_C_E = 0x4b,
	OpCode_LD_C_H = 0x4c,
	OpCode_LD_C_L = 0x4d,
	OpCode_LD_C_MEM_HL = 0x4e,
	OpCode_LD_C_d8 = 0xe,
	OpCode_LD_DE_d16 = 0x11,
	OpCode_LD_D_A = 0x57,
	OpCode_LD_D_B = 0x50,
	OpCode_LD_D_C = 0x51,
	OpCode_LD_D_D = 0x52,
	OpCode_LD_D_E = 0x53,
	OpCode_LD_D_H = 0x54,
	OpCode_LD_D_L = 0x55,
	OpCode_LD_D_MEM_HL = 0x56,
	OpCode_LD_D_d8 = 0x16,
	OpCode_LD_E_A = 0x5f,
	OpCode_LD_E_B = 0x58,
	OpCode_LD_E_C = 0x59,
	OpCode_LD_E_D = 0x5a,
	OpCode_LD_E_E = 0x5b,
	OpCode_LD_E_H = 0x5c,
	OpCode_LD_E_L = 0x5d,
	OpCode_LD_E_MEM_HL = 0x5e,
	OpCode_LD_E_d8 = 0x1e,
	OpCode_LD_HL_SP_PLUS_r8 = 0xf8,
	OpCode_LD_HL_d16 = 0x21,
	OpCode_LD_H_A = 0x67,
	OpCode_LD_H_B = 0x60,
	OpCode_LD_H_C = 0x61,
	OpCode_LD_H_D = 0x62,
	OpCode_LD_H_E = 0x63,
	OpCode_LD_H_H = 0x64,
	OpCode_LD_H_L = 0x65,
	OpCode_LD_H_MEM_HL = 0x66,
	OpCode_LD_H_d8 = 0x26,
	OpCode_LD_L_A = 0x6f,
	OpCode_LD_L_B = 0x68,
	OpCode_LD_L_C = 0x69,
	OpCode_LD_L_D = 0x6a,
	OpCode_LD_L_E = 0x6b,
	OpCode_LD_L_H = 0x6c,
	OpCode_LD_L_L = 0x6d,
	OpCode_LD_L_MEM_HL = 0x6e,
	OpCode_LD_L_d8 = 0x2e,
	OpCode_LD_MEM_BC_A = 0x2,
	OpCode_LD_MEM_C_A = 0xe2,
	OpCode_LD_MEM_DE_A = 0x12,
	OpCode_LD_MEM_HLD_A = 0x32,
	OpCode_LD_MEM_HLI_A = 0x22,
	OpCode_LD_MEM_HL_A = 0x77,
	OpCode_LD_MEM_HL_B = 0x70,
	OpCode_LD_MEM_HL_C = 0x71,
	OpCode_LD_MEM_HL_D = 0x72,
	OpCode_LD_MEM_HL_E = 0x73,
	OpCode_LD_MEM_HL_H = 0x74,
	OpCode_LD_MEM_HL_L = 0x75,
	OpCode_LD_MEM_HL_d8 = 0x36,
	OpCode_LD_MEM_a16_A = 0xeA,
	OpCode_LD_MEM_a16_SP = 0x8,
	OpCode_LD_SP_HL = 0xf9,
	OpCode_LD_SP_d16 = 0x31,
	OpCode_NOP = 0x0,
	OpCode_OR_A = 0xb7,
	OpCode_OR_B = 0xb0,
	OpCode_OR_C = 0xb1,
	OpCode_OR_D = 0xb2,
	OpCode_OR_E = 0xb3,
	OpCode_OR_H = 0xb4,
	OpCode_OR_L = 0xb5,
	OpCode_OR_MEM_HL = 0xb6,
	OpCode_OR_d8 = 0xf6,
	OpCode_POP_AF = 0xf1,
	OpCode_POP_BC = 0xc1,
	OpCode_POP_DE = 0xd1,
	OpCode_POP_HL = 0xe1,
	OpCode_PREFIX_CB = 0xcb,
	OpCode_PUSH_AF = 0xf5,
	OpCode_PUSH_BC = 0xc5,
	OpCode_PUSH_DE = 0xd5,
	OpCode_PUSH_HL = 0xe5,
	OpCode_RET = 0xc9,
	OpCode_RETI = 0xd9,
	OpCode_RET_C = 0xd8,
	OpCode_RET_NC = 0xd0,
	OpCode_RET_NZ = 0xc0,
	OpCode_RET_Z = 0xc8,
	OpCode_RLA = 0x17,
	OpCode_RLCA = 0x7,
	OpCode_RRA = 0x1f,
	OpCode_RRCA = 0xf,
	OpCode_RST_00H = 0xc7,
	OpCode_RST_08H = 0xcf,
	OpCode_RST_10H = 0xd7,
	OpCode_RST_18H = 0xdf,
	OpCode_RST_20H = 0xe7,
	OpCode_RST_28H = 0xef,
	OpCode_RST_30H = 0xf7,
	OpCode_RST_38H = 0xff,
	OpCode_SBC_A_A = 0x9f,
	OpCode_SBC_A_B = 0x98,
	OpCode_SBC_A_C = 0x99,
	OpCode_SBC_A_D = 0x9a,
	OpCode_SBC_A_E = 0x9b,
	OpCode_SBC_A_H = 0x9c,
	OpCode_SBC_A_L = 0x9d,
	OpCode_SBC_A_MEM_HL = 0x9e,
	OpCode_SBC_A_d8 = 0xde,
	OpCode_SCF = 0x37,
	OpCode_STOP = 0x10,
	OpCode_SUB_A = 0x97,
	OpCode_SUB_B = 0x90,
	OpCode_SUB_C = 0x91,
	OpCode_SUB_D = 0x92,
	OpCode_SUB_E = 0x93,
	OpCode_SUB_H = 0x94,
	OpCode_SUB_L = 0x95,
	OpCode_SUB_MEM_HL = 0x96,
	OpCode_SUB_d8 = 0xd6,
	OpCode_XOR_A = 0xaf,
	OpCode_XOR_B = 0xa8,
	OpCode_XOR_C = 0xa9,
	OpCode_XOR_D = 0xaa,
	OpCode_XOR_E = 0xab,
	OpCode_XOR_H = 0xac,
	OpCode_XOR_L = 0xad,
	OpCode_XOR_MEM_HL = 0xae,
	OpCode_XOR_d8 = 0xee,
} OpCode;


typedef enum _OpCodePrefixed {

} OpCodePrefixed;