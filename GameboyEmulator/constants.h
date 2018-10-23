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
	RAM_LOCATION_VRAM_TILES_1 = 0x8000,
	RAM_LOCATION_VRAM_TILES_2 = 0x8800,
	RAM_LOCATION_VRAM_TILES_3 = 0x9000,
	RAM_LOCATION_VRAM_BG_MAP_1 = 0x9800,
	RAM_LOCATION_VRAM_BG_MAP_2 = 0x9C00,
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
	RAM_LOCATION_TIMER_DIVIDER = 0xFF04,
	RAM_LOCATION_TIMER_COUNTER = 0xFF05,
	RAM_LOCATION_TIMER_MODULO = 0xFF06,
	RAM_LOCATION_TIMER_CONTROL = 0xFF07,
	RAM_LOCATION_SOUND_CHANNEL_1_FREQUENCY_SWEEP = 0xFF10, //NR10 - Channel 1 Frequency Sweep
	RAM_LOCATION_SOUND_CHANNEL_1_PATTERN_LENGTH = 0xFF11, //NR11 - Channel 1 Sound_Length/Wave pattern duty
	RAM_LOCATION_SOUND_CHANNEL_1_VOLUME_SWEEP = 0xFF12, //NR12 - Channel 1 Volume sweep
	RAM_LOCATION_SOUND_CHANNEL_1_FREQUENCY_LOW = 0xFF13, //NR13 - Channel 1 Frequency low
	RAM_LOCATION_SOUND_CHANNEL_1_FREQUENCY_HIGH_SETTINGS = 0xFF14, //NR14 - Channel 1 Frequency high + settings
	RAM_LOCATION_SOUND_CHANNEL_2_PATTERN_LENGTH = 0xFF16, //NR21 - Channel 2 Sound Length/Wave Pattern Duty
	RAM_LOCATION_SOUND_CHANNEL_2_VOLUME_SWEEP = 0xFF17, //NR22 - Channel 2 Volume sweep
	RAM_LOCATION_SOUND_CHANNEL_2_FREQUENCY_LOW = 0xFF18, //NR23 - Channel 2 Frequency low
	RAM_LOCATION_SOUND_CHANNEL_2_FREQUENCY_HIGH_SETTINGS = 0xFF19, //NR24 - Channel 2 Frequency high + settings
	RAM_LOCATION_SOUND_CHANNEL_3_ONOFF = 0xFF1A, //NR30 
	RAM_LOCATION_SOUND_CHANNEL_3_LENGTH = 0xFF1B, //NR31
	RAM_LOCATION_SOUND_CHANNEL_3_VOLUME = 0xFF1C, //NR32
	RAM_LOCATION_SOUND_CHANNEL_3_FREQUENCY_LOW  = 0xFF1D, //NR33
	RAM_LOCATION_SOUND_CHANNEL_3_FREQUENCY_HIGH_SETTINGS = 0xFF1E, //NR34
	RAM_LOCATION_SOUND_WAVE_PATTERN = 0xFF30,
	RAM_LOCATION_SOUND_WAVE_PATTERN_END = 0xFF3F,
	RAM_LOCATION_SOUND_CHANNEL_4_Sound_Length = 0xFF20, //NR41 - Channel 4 Sound_Length
	RAM_LOCATION_SOUND_CHANNEL_4_Volume_Envelope = 0xFF21, //NR42 - Channel 4 Volume_Envelope
	RAM_LOCATION_SOUND_CHANNEL_4_Polynomial_Counter = 0xFF22, //NR43 - Channel 4 Polynomial Counter
	RAM_LOCATION_SOUND_CHANNEL_4_Counter_consecutive_Inital = 0xFF23, //NR44 - Channel 4 Counter/consecutive, Inital
	RAM_LOCATION_SOUND_CHANNEL_control_ON_OFF_Volume = 0xFF24, //NR50 - Channel control / ON-OFF / Volume
	RAM_LOCATION_SOUND_Selection_of_Sound_output_terminal = 0xFF25, //NR51 - Selection of Sound output terminal
	RAM_LOCATION_SOUND_ONOFF = 0xFF26,
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
	INTERRUPT_FLAG_VBLANK = 1,
	INTERRUPT_FLAG_LCD_STAT = 2,
	INTERRUPT_FLAG_TIMER_OVERFLOW = 4,
	INTERRUPT_FLAG_SERIAL_TRANSFER = 8,
	INTERRUPT_FLAG_BUTTON_PRESS = 16
} InterruptFlag;

typedef enum _PPUFlag {
	LCD_STAT_MODE_HBLANK = 0,
	LCD_STAT_MODE_VBLANK = 1,
	LCD_STAT_MODE_OAM_SEARCH = 2,
	LCD_STAT_MODE_PIXEL_TRANSFER = 3,

	LCD_STAT_MODE_MASK = 3,
	LCD_STAT_COMPARE_MASK = 4,
	LCD_STAT_HBLANK_INT_ENABLE_MASK = 8,
	LCD_STAT_VBLANK_INT_ENABLE_MASK = 16,
	LCD_STAT_OAM_INT_ENABLE_MASK = 32,
	LCD_STAT_COMPARE_INT_ENABLE_MASK = 64,
	

	PPU_FLAG_LCD_ENABLE = 128, //0 = Off, 1 = On
	PPU_FLAG_WINDOW_TILE_MAP_SELECT = 61, //0 = 9800 - 9BFF, 1 = 9C00 - 9FFF
	PPU_FLAG_WINDOW_ENABLE = 32, //0 = Off, 1 = On
	PPU_FLAG_BG_TILE_DATA_ADDRESS_MODE = 16, //0 = 8800 - 97FF, 1 = 8000 - 8FFF
	PPU_FLAG_BG_TILE_MAP_SELECT = 8, //0 = 9800 - 9BFF, 1 = 9C00 - 9FFF
	PPU_FLAG_OBJ_SIZE_MASK = 4, //0 = 8x8, 1 = 8x16
	PPU_FLAG_OBJ_ENABLE = 2, //0 = Off, 1 = On
	PPU_FLAG_BG_ENABLE = 1 //0 = Off, 1 = On
} PPUFlag;

typedef enum _SoundFlag {
	SOUND_MASK_PULSE_DUTY = 0xC0,
	SOUND_MASK_PULSE_VOLUME = 0xF0,
	SOUND_MASK_PULSE_VOLUME_SWEEP_INCREASE = 0x8,
	SOUND_MASK_CHAN3_VOLUME = 0x60,
	SOUND_MASK_FREQUENCY_HIGH_BITS = 0x7,
	SOUND_MASK_PULSE_VOLUME_SWEEP_STEP = 0x7,

	SOUND_FLAG_PULSE_DUTY_12_5 = 0x0,
	SOUND_FLAG_PULSE_DUTY_25 = 0x40,
	SOUND_FLAG_PULSE_DUTY_50 = 0x80,
	SOUND_FLAG_PULSE_DUTY_75 = 0xC0,

	SOUND_FLAG_CHAN3_VOLUME_MUTE = 0,
	SOUND_FLAG_CHAN3_VOLUME_FULL = 0x20,
	SOUND_FLAG_CHAN3_VOLUME_HALF = 0x40,
	SOUND_FLAG_CHAN3_VOLUME_QUARTER = 0x60,
} SoundFlag;

typedef enum _OAMIndex {
	OAM_INDEX_POS_Y = 0,
	OAM_INDEX_POS_X = 1,
	OAM_INDEX_TILE_NUM = 2,
	OAM_INDEX_FLAGS = 3,

	OAM_FLAG_PRIORITY = 128,
	OAM_FLAG_Y_FLIP = 64,
	OAM_FLAG_X_FLIP = 32,
	OAM_FLAG_PALETTE_NUM_MASK = 16
} OAMIndex;

typedef enum _PixelColor {
	PixelColor_White = 0,
	PixelColor_LightGray = 1,
	PixelColor_DarkGray = 2,
	PixelColor_Black = 3
} PixelColor;

typedef enum _IOFlag {
	IO_FLAG_SELECT_BUTTON = 32, //0 = Select
	IO_FLAG_SELECT_DIRECTION = 16, //0 = Select
	IO_FLAG_DOWN_START_PRESSED = 8,  //0 = Pressed
	IO_FLAG_UP_SELECT_PRESSED = 4, //0 = Pressed
	IO_FLAG_LEFT_B_PRESSED = 2, //0 = Pressed
	IO_FLAG_RIGHT_A_PRESSED = 1 //0 = Pressed
} IOFlag;

typedef enum _TimerFlag {
	TIMER_CONTROL_MASK_TIMER_ENABLE = 4,
	TIMER_CONTROL_MASK_TIMER_SPEED = 3
} TimerFlag;

typedef enum _TimerSpeed {	
	TIMER_SPEED_CYCLES_256 = 0, //CPU Clock / 1024 (4096 Hz)
	TIMER_SPEED_CYCLES_4 = 1,  //CPU Clock / 16   (262144 Hz)
	TIMER_SPEED_CYCLES_16 = 2, //CPU Clock / 64   (65536 Hz)
	TIMER_SPEED_CYCLES_64 = 3, //CPU Clock / 256  (16384 Hz)
} TimerSpeed;

#define VRAM_TOTAL_SIZE 0x2000
#define VRAM_TOTAL_TILES_SIZE 0x1800
#define VRAM_TILES_1_SIZE 0x800
#define VRAM_TILES_2_SIZE 0x800
#define VRAM_TILES_3_SIZE 0x800
#define VRAM_BG_MAP_1_SIZE 0x400
#define VRAM_BG_MAP_2_SIZE 0x400
#define BYTES_PER_TILE 16
#define OAM_SIZE 0xA0

#define WORK_RAM_SIZE 0x2000
#define HRAM_SIZE 0x7F
#define TOTAL_RAM_SIZE 0x10000

#define PPU_CYCLES_OAM_SEARCH 20
#define PPU_CYCLES_PIXEL_TRANSFER 43
#define PPU_CYCLES_HBLANK 51
#define PPU_CYCLES_LINE_TOTAL 114

#define SOUND_WAVE_PATTERN_BYTES 16
#define SOUND_WAVE_PATTERNS 32
#define CYCLES_PER_SOUND_TICK 21
#define AUDIO_SAMPLE_RATE 49932
#define SOUND_SAMPLES_PER_VOLUME_STEP 780
#define AUDIO_BUFFER_SIZE 96000

#define TIMER_DIVIDER_CYCLES TIMER_SPEED_CYCLES_64
#define CYCLES_PER_TIMER_TICK 4

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

 - OAM transfer takes 160(?) clocks @ 4 MHz (40 ticks @ 1 MHz)
*/

#define TARGET_FPS 59.7275f
#define TARGET_MILLSECONDS_PER_FRAME 16.75f
#define TARGET_TICKS_FRAME 17556
#define SCREEN_VISIBLE_LINES 144
#define VBLANK_LINES 10
#define SCREEN_TOTAL_LINES 154
#define TOTAL_SPRITES 40
#define BYTES_PER_SPRITE 4
#define VISIBLE_SPRITES_PER_LINE 10
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144
#define TILE_SIZE 8
#define SCREEN_TILES_WIDTH 20
#define SCREEN_TILES_HEIGHT 18
#define BG_MAP_TILES_WIDTH 32
#define BG_MAP_TILES_HEIGHT 32

#define NUM_OPCODES 512
#define OPCODE_PREFIX_CB 0x0100

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
	OpCode_PREFIX_CB = 0xCB,
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

	/***** Prefixed OpCodes *****/
	/* The "real" prefix is 0xCB00, but for the enum values we use 0x0100 to save memory */
	OpCode_RLC_B = 0x0100,
	OpCode_RLC_C = 0x0101,
	OpCode_RLC_D = 0x0102,
	OpCode_RLC_E = 0x0103,
	OpCode_RLC_H = 0x0104,
	OpCode_RLC_L = 0x0105,
	OpCode_RLC_MEM_HL = 0x0106,
	OpCode_RLC_A = 0x0107,
	OpCode_RRC_B = 0x0108,
	OpCode_RRC_C = 0x0109,
	OpCode_RRC_D = 0x010a,
	OpCode_RRC_E = 0x010b,
	OpCode_RRC_H = 0x010c,
	OpCode_RRC_L = 0x010d,
	OpCode_RRC_MEM_HL = 0x010e,
	OpCode_RRC_A = 0x010f,
	OpCode_RL_B = 0x0110,
	OpCode_RL_C = 0x0111,
	OpCode_RL_D = 0x0112,
	OpCode_RL_E = 0x0113,
	OpCode_RL_H = 0x0114,
	OpCode_RL_L = 0x0115,
	OpCode_RL_MEM_HL = 0x0116,
	OpCode_RL_A = 0x0117,
	OpCode_RR_B = 0x0118,
	OpCode_RR_C = 0x0119,
	OpCode_RR_D = 0x011a,
	OpCode_RR_E = 0x011b,
	OpCode_RR_H = 0x011c,
	OpCode_RR_L = 0x011d,
	OpCode_RR_MEM_HL = 0x011e,
	OpCode_RR_A = 0x011f,
	OpCode_SLA_B = 0x0120,
	OpCode_SLA_C = 0x0121,
	OpCode_SLA_D = 0x0122,
	OpCode_SLA_E = 0x0123,
	OpCode_SLA_H = 0x0124,
	OpCode_SLA_L = 0x0125,
	OpCode_SLA_MEM_HL = 0x0126,
	OpCode_SLA_A = 0x0127,
	OpCode_SRA_B = 0x0128,
	OpCode_SRA_C = 0x0129,
	OpCode_SRA_D = 0x012a,
	OpCode_SRA_E = 0x012b,
	OpCode_SRA_H = 0x012c,
	OpCode_SRA_L = 0x012d,
	OpCode_SRA_MEM_HL = 0x012e,
	OpCode_SRA_A = 0x012f,
	OpCode_SWAP_B = 0x0130,
	OpCode_SWAP_C = 0x0131,
	OpCode_SWAP_D = 0x0132,
	OpCode_SWAP_E = 0x0133,
	OpCode_SWAP_H = 0x0134,
	OpCode_SWAP_L = 0x0135,
	OpCode_SWAP_MEM_HL = 0x0136,
	OpCode_SWAP_A = 0x0137,
	OpCode_SRL_B = 0x0138,
	OpCode_SRL_C = 0x0139,
	OpCode_SRL_D = 0x013a,
	OpCode_SRL_E = 0x013b,
	OpCode_SRL_H = 0x013c,
	OpCode_SRL_L = 0x013d,
	OpCode_SRL_MEM_HL = 0x013e,
	OpCode_SRL_A = 0x013f,
	OpCode_BIT_0_B = 0x0140,
	OpCode_BIT_0_C = 0x0141,
	OpCode_BIT_0_D = 0x0142,
	OpCode_BIT_0_E = 0x0143,
	OpCode_BIT_0_H = 0x0144,
	OpCode_BIT_0_L = 0x0145,
	OpCode_BIT_0_MEM_HL = 0x0146,
	OpCode_BIT_0_A = 0x0147,
	OpCode_BIT_1_B = 0x0148,
	OpCode_BIT_1_C = 0x0149,
	OpCode_BIT_1_D = 0x014a,
	OpCode_BIT_1_E = 0x014b,
	OpCode_BIT_1_H = 0x014c,
	OpCode_BIT_1_L = 0x014d,
	OpCode_BIT_1_MEM_HL = 0x014e,
	OpCode_BIT_1_A = 0x014f,
	OpCode_BIT_2_B = 0x0150,
	OpCode_BIT_2_C = 0x0151,
	OpCode_BIT_2_D = 0x0152,
	OpCode_BIT_2_E = 0x0153,
	OpCode_BIT_2_H = 0x0154,
	OpCode_BIT_2_L = 0x0155,
	OpCode_BIT_2_MEM_HL = 0x0156,
	OpCode_BIT_2_A = 0x0157,
	OpCode_BIT_3_B = 0x0158,
	OpCode_BIT_3_C = 0x0159,
	OpCode_BIT_3_D = 0x015a,
	OpCode_BIT_3_E = 0x015b,
	OpCode_BIT_3_H = 0x015c,
	OpCode_BIT_3_L = 0x015d,
	OpCode_BIT_3_MEM_HL = 0x015e,
	OpCode_BIT_3_A = 0x015f,
	OpCode_BIT_4_B = 0x0160,
	OpCode_BIT_4_C = 0x0161,
	OpCode_BIT_4_D = 0x0162,
	OpCode_BIT_4_E = 0x0163,
	OpCode_BIT_4_H = 0x0164,
	OpCode_BIT_4_L = 0x0165,
	OpCode_BIT_4_MEM_HL = 0x0166,
	OpCode_BIT_4_A = 0x0167,
	OpCode_BIT_5_B = 0x0168,
	OpCode_BIT_5_C = 0x0169,
	OpCode_BIT_5_D = 0x016a,
	OpCode_BIT_5_E = 0x016b,
	OpCode_BIT_5_H = 0x016c,
	OpCode_BIT_5_L = 0x016d,
	OpCode_BIT_5_MEM_HL = 0x016e,
	OpCode_BIT_5_A = 0x016f,
	OpCode_BIT_6_B = 0x0170,
	OpCode_BIT_6_C = 0x0171,
	OpCode_BIT_6_D = 0x0172,
	OpCode_BIT_6_E = 0x0173,
	OpCode_BIT_6_H = 0x0174,
	OpCode_BIT_6_L = 0x0175,
	OpCode_BIT_6_MEM_HL = 0x0176,
	OpCode_BIT_6_A = 0x0177,
	OpCode_BIT_7_B = 0x0178,
	OpCode_BIT_7_C = 0x0179,
	OpCode_BIT_7_D = 0x017a,
	OpCode_BIT_7_E = 0x017b,
	OpCode_BIT_7_H = 0x017c,
	OpCode_BIT_7_L = 0x017d,
	OpCode_BIT_7_MEM_HL = 0x017e,
	OpCode_BIT_7_A = 0x017f,
	OpCode_RES_0_B = 0x0180,
	OpCode_RES_0_C = 0x0181,
	OpCode_RES_0_D = 0x0182,
	OpCode_RES_0_E = 0x0183,
	OpCode_RES_0_H = 0x0184,
	OpCode_RES_0_L = 0x0185,
	OpCode_RES_0_MEM_HL = 0x0186,
	OpCode_RES_0_A = 0x0187,
	OpCode_RES_1_B = 0x0188,
	OpCode_RES_1_C = 0x0189,
	OpCode_RES_1_D = 0x018a,
	OpCode_RES_1_E = 0x018b,
	OpCode_RES_1_H = 0x018c,
	OpCode_RES_1_L = 0x018d,
	OpCode_RES_1_MEM_HL = 0x018e,
	OpCode_RES_1_A = 0x018f,
	OpCode_RES_2_B = 0x0190,
	OpCode_RES_2_C = 0x0191,
	OpCode_RES_2_D = 0x0192,
	OpCode_RES_2_E = 0x0193,
	OpCode_RES_2_H = 0x0194,
	OpCode_RES_2_L = 0x0195,
	OpCode_RES_2_MEM_HL = 0x0196,
	OpCode_RES_2_A = 0x0197,
	OpCode_RES_3_B = 0x0198,
	OpCode_RES_3_C = 0x0199,
	OpCode_RES_3_D = 0x019a,
	OpCode_RES_3_E = 0x019b,
	OpCode_RES_3_H = 0x019c,
	OpCode_RES_3_L = 0x019d,
	OpCode_RES_3_MEM_HL = 0x019e,
	OpCode_RES_3_A = 0x019f,
	OpCode_RES_4_B = 0x01a0,
	OpCode_RES_4_C = 0x01a1,
	OpCode_RES_4_D = 0x01a2,
	OpCode_RES_4_E = 0x01a3,
	OpCode_RES_4_H = 0x01a4,
	OpCode_RES_4_L = 0x01a5,
	OpCode_RES_4_MEM_HL = 0x01a6,
	OpCode_RES_4_A = 0x01a7,
	OpCode_RES_5_B = 0x01a8,
	OpCode_RES_5_C = 0x01a9,
	OpCode_RES_5_D = 0x01aa,
	OpCode_RES_5_E = 0x01ab,
	OpCode_RES_5_H = 0x01ac,
	OpCode_RES_5_L = 0x01ad,
	OpCode_RES_5_MEM_HL = 0x01ae,
	OpCode_RES_5_A = 0x01af,
	OpCode_RES_6_B = 0x01b0,
	OpCode_RES_6_C = 0x01b1,
	OpCode_RES_6_D = 0x01b2,
	OpCode_RES_6_E = 0x01b3,
	OpCode_RES_6_H = 0x01b4,
	OpCode_RES_6_L = 0x01b5,
	OpCode_RES_6_MEM_HL = 0x01b6,
	OpCode_RES_6_A = 0x01b7,
	OpCode_RES_7_B = 0x01b8,
	OpCode_RES_7_C = 0x01b9,
	OpCode_RES_7_D = 0x01ba,
	OpCode_RES_7_E = 0x01bb,
	OpCode_RES_7_H = 0x01bc,
	OpCode_RES_7_L = 0x01bd,
	OpCode_RES_7_MEM_HL = 0x01be,
	OpCode_RES_7_A = 0x01bf,
	OpCode_SET_0_B = 0x01c0,
	OpCode_SET_0_C = 0x01c1,
	OpCode_SET_0_D = 0x01c2,
	OpCode_SET_0_E = 0x01c3,
	OpCode_SET_0_H = 0x01c4,
	OpCode_SET_0_L = 0x01c5,
	OpCode_SET_0_MEM_HL = 0x01c6,
	OpCode_SET_0_A = 0x01c7,
	OpCode_SET_1_B = 0x01c8,
	OpCode_SET_1_C = 0x01c9,
	OpCode_SET_1_D = 0x01ca,
	OpCode_SET_1_E = 0x01cb,
	OpCode_SET_1_H = 0x01cc,
	OpCode_SET_1_L = 0x01cd,
	OpCode_SET_1_MEM_HL = 0x01ce,
	OpCode_SET_1_A = 0x01cf,
	OpCode_SET_2_B = 0x01d0,
	OpCode_SET_2_C = 0x01d1,
	OpCode_SET_2_D = 0x01d2,
	OpCode_SET_2_E = 0x01d3,
	OpCode_SET_2_H = 0x01d4,
	OpCode_SET_2_L = 0x01d5,
	OpCode_SET_2_MEM_HL = 0x01d6,
	OpCode_SET_2_A = 0x01d7,
	OpCode_SET_3_B = 0x01d8,
	OpCode_SET_3_C = 0x01d9,
	OpCode_SET_3_D = 0x01da,
	OpCode_SET_3_E = 0x01db,
	OpCode_SET_3_H = 0x01dc,
	OpCode_SET_3_L = 0x01dd,
	OpCode_SET_3_MEM_HL = 0x01de,
	OpCode_SET_3_A = 0x01df,
	OpCode_SET_4_B = 0x01e0,
	OpCode_SET_4_C = 0x01e1,
	OpCode_SET_4_D = 0x01e2,
	OpCode_SET_4_E = 0x01e3,
	OpCode_SET_4_H = 0x01e4,
	OpCode_SET_4_L = 0x01e5,
	OpCode_SET_4_MEM_HL = 0x01e6,
	OpCode_SET_4_A = 0x01e7,
	OpCode_SET_5_B = 0x01e8,
	OpCode_SET_5_C = 0x01e9,
	OpCode_SET_5_D = 0x01ea,
	OpCode_SET_5_E = 0x01eb,
	OpCode_SET_5_H = 0x01ec,
	OpCode_SET_5_L = 0x01ed,
	OpCode_SET_5_MEM_HL = 0x01ee,
	OpCode_SET_5_A = 0x01ef,
	OpCode_SET_6_B = 0x01f0,
	OpCode_SET_6_C = 0x01f1,
	OpCode_SET_6_D = 0x01f2,
	OpCode_SET_6_E = 0x01f3,
	OpCode_SET_6_H = 0x01f4,
	OpCode_SET_6_L = 0x01f5,
	OpCode_SET_6_MEM_HL = 0x01f6,
	OpCode_SET_6_A = 0x01f7,
	OpCode_SET_7_B = 0x01f8,
	OpCode_SET_7_C = 0x01f9,
	OpCode_SET_7_D = 0x01fa,
	OpCode_SET_7_E = 0x01fb,
	OpCode_SET_7_H = 0x01fc,
	OpCode_SET_7_L = 0x01fd,
	OpCode_SET_7_MEM_HL = 0x01fe,
	OpCode_SET_7_A = 0x01ff,
} OpCode;


