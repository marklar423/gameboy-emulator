#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include "ram.h"
#include "util.h"
#include "cpu_interrupts.h"

static unsigned char TODO = 0;

unsigned char* getArrayAddress(unsigned char *array, int index, int arraySize);

unsigned char* getRamAddress(Hardware *hardware, int address) {
	if (address >= RAM_LOCATION_CART_FIXED && address <= RAM_LOCATION_CART_FIXED_END)
		return &hardware->rom->romBytes[address];

	if (address >= RAM_LOCATION_CART_SWITCHABLE && address <= RAM_LOCATION_CART_SWITCHABLE_END)
		//todo: implement memory bank switching
		return &hardware->rom->romBytes[address];

	else if (address >= RAM_LOCATION_VRAM_TILES_1 && address < RAM_LOCATION_VRAM_BG_MAP_1)
		return getArrayAddress (hardware->videoData->tileData, address - RAM_LOCATION_VRAM_TILES_1, VRAM_TOTAL_TILES_SIZE);

	else if (address >= RAM_LOCATION_VRAM_BG_MAP_1 && address < RAM_LOCATION_VRAM_BG_MAP_2)
		return getArrayAddress(hardware->videoData->bgMap1, address - RAM_LOCATION_VRAM_BG_MAP_1, VRAM_BG_MAP_1_SIZE);

	else if (address >= RAM_LOCATION_VRAM_BG_MAP_2 && address <= RAM_LOCATION_VRAM_END)
		return getArrayAddress(hardware->videoData->bgMap2, address - RAM_LOCATION_VRAM_BG_MAP_2, VRAM_BG_MAP_2_SIZE);

	else if (address >= RAM_LOCATION_OAM && address <= RAM_LOCATION_OAM_END)
		return getArrayAddress(hardware->videoData->oamTable, address - RAM_LOCATION_OAM, OAM_SIZE);

	else if (address >= RAM_LOCATION_WORK_RAM_FIXED && address <= RAM_LOCATION_WORK_RAM_FIXED_END)
		return getArrayAddress(hardware->workRam, address - RAM_LOCATION_WORK_RAM_FIXED, WORK_RAM_SIZE);

	else if (address >= RAM_LOCATION_WORK_RAM_SWITCHABLE && address <= RAM_LOCATION_WORK_RAM_SWITCHABLE_END)
		//todo: implement memory bank switching for CGB
		return getArrayAddress(hardware->workRam, address - RAM_LOCATION_WORK_RAM_FIXED, WORK_RAM_SIZE);
	
	else if (address >= RAM_LOCATION_MIRROR_WORK_RAM_FIXED && address <= RAM_LOCATION_MIRROR_WORK_RAM_FIXED_END)
		//echo ram fixed
		return getArrayAddress(hardware->workRam, address - RAM_LOCATION_MIRROR_WORK_RAM_FIXED, WORK_RAM_SIZE);

	else if (address >= RAM_LOCATION_MIRROR_WORK_RAM_SWITCHABLE && address <= RAM_LOCATION_MIRROR_WORK_RAM_SWITCHABLE_END)
		//echo ram switchable
		return getArrayAddress(hardware->workRam, address - RAM_LOCATION_MIRROR_WORK_RAM_FIXED, WORK_RAM_SIZE);

	else if (address >= RAM_LOCATION_HRAM && address <= RAM_LOCATION_HRAM_END)
		return getArrayAddress(hardware->highRam, address - RAM_LOCATION_HRAM, HRAM_SIZE);

	else if (address >= RAM_LOCATION_SOUND_WAVE_PATTERN && address <= RAM_LOCATION_SOUND_WAVE_PATTERN_END)
		return getArrayAddress(hardware->soundData->chan3_WaveData, address - RAM_LOCATION_SOUND_WAVE_PATTERN, SOUND_WAVE_PATTERN_SIZE);

	else if (address == RAM_LOCATION_JOYPAD_INPUT) return &hardware->ioData->joypadData;
	else if (address == RAM_LOCATION_SERIAL_TRANSFER_DATA) return &hardware->ioData->serialTransferData;
	else if (address == RAM_LOCATION_SERIAL_TRANSFER_CONTROL) return &hardware->ioData->serialTransferControl;
	else if (address == RAM_LOCATION_TIMER_DIVIDER) return &hardware->timerData->divider;
	else if (address == RAM_LOCATION_TIMER_COUNTER) return &hardware->timerData->counter;
	else if (address == RAM_LOCATION_TIMER_MODULO) return &hardware->timerData->modulo;
	else if (address == RAM_LOCATION_TIMER_CONTROL) return &hardware->timerData->control;
	else if (address == RAM_LOCATION_SOUND_CHANNEL_3_ONOFF) return &hardware->soundData->chan3_OnOff;
	else if (address == RAM_LOCATION_SOUND_CHANNEL_3_LENGTH) return &hardware->soundData->chan3_Length;
	else if (address == RAM_LOCATION_SOUND_CHANNEL_3_VOLUME) return &hardware->soundData->chan3_Volume;
	else if (address == RAM_LOCATION_SOUND_CHANNEL_3_FREQUENCY_LOW) return &hardware->soundData->chan3_FrequencyLow;
	else if (address == RAM_LOCATION_SOUND_CHANNEL_3_FREQUENCY_HIGH_SETTINGS) return &hardware->soundData->chan3_FrequencyHighSettings;
	else if (address == RAM_LOCATION_SOUND_ONOFF) return &hardware->soundData->soundOnOff;
	else if (address == RAM_LOCATION_LCD_CONTROL) return &hardware->videoData->lcdControl;
	else if (address == RAM_LOCATION_LCD_STATUS) return &hardware->videoData->lcdStatus;
	else if (address == RAM_LOCATION_SCROLL_Y) return &hardware->videoData->scrollY;
	else if (address == RAM_LOCATION_SCROLL_X) return &hardware->videoData->scrollX;
	else if (address == RAM_LOCATION_LCD_Y_COORD) return &hardware->videoData->lcdYCoord;
	else if (address == RAM_LOCATION_LCD_Y_COMPARE) return &hardware->videoData->lcdYCompare;
	else if (address == RAM_LOCATION_DMA_TRANSFER) return &hardware->videoData->dmaTransfer;
	else if (address == RAM_LOCATION_BG_PALETTE) return &hardware->videoData->bgPalette;
	else if (address == RAM_LOCATION_OBJ_PALETTE_0) return &hardware->videoData->objPalette0;
	else if (address == RAM_LOCATION_OBJ_PALETTE_1) return &hardware->videoData->objPalette1;
	else if (address == RAM_LOCATION_WINDOW_Y) return &hardware->videoData->windowY;
	else if (address == RAM_LOCATION_WINDOW_X) return &hardware->videoData->windowX;
	else if (address == RAM_LOCATION_INTERRUPT_FLAGS) return &hardware->registers->requestedInterrupts;
	else if (address == RAM_LOCATION_INTERRUPTS_ENABLE)  return &hardware->registers->enabledInterrupts;

	//todo:
	else if ((address >= RAM_LOCATION_SOUND_CHANNEL_1_Sweep_register && address <= RAM_LOCATION_SOUND_Selection_of_Sound_output_terminal) 
				|| (address >= RAM_LOCATION_UNUSABLE && RAM_LOCATION_UNUSABLE_END <= RAM_LOCATION_UNUSABLE_END))
		return &TODO;

	//assert(false && "Unknown RAM location");
	return NULL;
}

unsigned char* getArrayAddress(unsigned char *array, int index, int arraySize) {
	assert(index >= 0 && index < arraySize);
	return &(array[index]);
}

void writeLocation(Hardware *hardware, unsigned char *location, unsigned char value) {
		
	PPUFlag lcdMode = (hardware->videoData->lcdStatus & LCD_STAT_MODE_MASK);

	if (location == &hardware->videoData->lcdStatus) {
		//bits 0-2 are read only
		*location = (value & 0xF8) | (*location & 0x7);
	}
	else if (location == &hardware->videoData->lcdYCoord) {
		//writing should reset?
		*location = 0;
	}
	else if (location >= hardware->rom->romBytes && location <= &hardware->rom->romBytes[hardware->rom->romLength - 1]) {
		//no writing allowed
		//todo: implement MBC switching
	}
	/*else if (location >= hardware->videoData->oamTable && location <= &hardware->videoData->oamTable[OAM_SIZE - 1]) {
		if (lcdMode != LCD_STAT_MODE_PIXEL_TRANSFER && lcdMode != LCD_STAT_MODE_OAM_SEARCH) {
			//can't write to OAM during pixel transfer and OAM search
			*location = value;
		}
	}
	else if (location >= hardware->videoData->tileData && location <= &hardware->videoData->tileData[VRAM_TOTAL_TILES_SIZE - 1]) {
		if (lcdMode != LCD_STAT_MODE_PIXEL_TRANSFER) {
			//can't write to tiles during pixel transfer
			*location = value;
		}
	}
	else if (location >= hardware->videoData->bgMap1 && location <= &hardware->videoData->bgMap1[VRAM_BG_MAP_1_SIZE - 1]) {
		if (lcdMode != LCD_STAT_MODE_PIXEL_TRANSFER) {
			//can't write to map during pixel transfer
			*location = value;
		}
	}
	else if (location >= hardware->videoData->bgMap2 && location <= &hardware->videoData->bgMap2[VRAM_BG_MAP_2_SIZE - 1]) {
		if (lcdMode != LCD_STAT_MODE_PIXEL_TRANSFER) {
			//can't write to map during pixel transfer
			*location = value;
		}
	}*/
	else if (location == &hardware->videoData->dmaTransfer) {
		*location = value;

		//start DMA transfer
		hardware->isOAMDMATriggered = true;
	}
	else if (location == &hardware->ioData->joypadData) {
		//only bits 4 & 5 can be written
		*location = (value & 0x30) | (*location & 0xCF);
		setJoypadDataState(hardware);
	}
	else if (location == &hardware->registers->F) {
		//bits 0-3 are always zero
		*location = (value & 0xF0);
	}
	else if (location == &hardware->timerData->divider) {
		//writing resets to zero
		*location = 0;
	}
	else if (location == &hardware->timerData->control) {
		//only bits 0-2 can be written
		*location = (value & 0x07) | (*location & 0xF8);
	}
	else {
		*location = value;
	}

}

void pushByteToStack(Hardware *hardware, unsigned char value) {
	hardware->registers->SP--;
	unsigned char* topOfStack = getRamAddress(hardware, hardware->registers->SP);
	*topOfStack = value;
}

void pushWordToStack(Hardware *hardware, int value) {
	unsigned char leastSignificant, mostSignificant;
	splitBytes(value, &leastSignificant, &mostSignificant);

	pushByteToStack(hardware, mostSignificant);
	pushByteToStack(hardware, leastSignificant);
}

unsigned char popByteFromStack(Hardware *hardware){
	unsigned char* topOfStack = getRamAddress(hardware, hardware->registers->SP);
	hardware->registers->SP++;
	return *topOfStack;
}

void setJoypadDataState(Hardware *hardware) {
	//zero means button pressed/selected, one means not pressed/selected		
	if ((hardware->ioData->joypadData & IO_FLAG_SELECT_BUTTON) == 0) {		
		SET_BIT_IF(!hardware->inputState->isAPressed, IO_FLAG_RIGHT_A_PRESSED, hardware->ioData->joypadData);
		SET_BIT_IF(!hardware->inputState->isBPressed, IO_FLAG_LEFT_B_PRESSED, hardware->ioData->joypadData);
		SET_BIT_IF(!hardware->inputState->isSelectPressed, IO_FLAG_UP_SELECT_PRESSED, hardware->ioData->joypadData);
		SET_BIT_IF(!hardware->inputState->isStartPressed, IO_FLAG_DOWN_START_PRESSED, hardware->ioData->joypadData);
	}
	else if ((hardware->ioData->joypadData & IO_FLAG_SELECT_DIRECTION) == 0) {
		SET_BIT_IF(!hardware->inputState->isRightPressed, IO_FLAG_RIGHT_A_PRESSED, hardware->ioData->joypadData);
		SET_BIT_IF(!hardware->inputState->isLeftPressed, IO_FLAG_LEFT_B_PRESSED, hardware->ioData->joypadData);
		SET_BIT_IF(!hardware->inputState->isUpPressed, IO_FLAG_UP_SELECT_PRESSED, hardware->ioData->joypadData);
		SET_BIT_IF(!hardware->inputState->isDownPressed, IO_FLAG_DOWN_START_PRESSED, hardware->ioData->joypadData);
	}
	else {
		hardware->ioData->joypadData |= 0x0F;
	}

	if ((hardware->ioData->joypadData & 0x0F) == 0) {
		setRequestedInterrupt(hardware, INTERRUPT_FLAG_BUTTON_PRESS, true);
	}
}

void populateRamAddresses(Hardware *hardware) {
	for (int i = 0; i < TOTAL_RAM_SIZE; i++) {
		hardware->ramAddresses[i] = getRamAddress(hardware, i);
	}
}