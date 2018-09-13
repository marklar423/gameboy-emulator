#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include "ram.h"
#include "util.h"

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

	else if (address >= RAM_LOCATION_HRAM && address <= RAM_LOCATION_HRAM_END)
		return getArrayAddress(hardware->highRam, address - RAM_LOCATION_HRAM, HRAM_SIZE);

	else if (address == RAM_LOCATION_JOYPAD_INPUT) return &hardware->ioData->joypadInput;
	else if (address == RAM_LOCATION_SERIAL_TRANSFER_DATA) return &hardware->ioData->serialTransferData;
	else if (address == RAM_LOCATION_SERIAL_TRANSFER_CONTROL) return &hardware->ioData->serialTransferControl;
	else if (address == RAM_LOCATION_SOUND_ON_OFF) return &hardware->soundData->soundOnOff;
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

void writeRamLocation(Hardware *hardware, unsigned char *location, unsigned char value) {
		
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
	else if (location >= hardware->videoData->oamTable && location <= &hardware->videoData->oamTable[OAM_SIZE - 1]) {
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
	}
	else if (location == &hardware->videoData->dmaTransfer) {
		//todo: start DMA transfer
		*location = value;
	}
	else if (location == &hardware->ioData->joypadInput) {
		//only bits 4-7 can be written (only 4 & 5 are used)
		*location = (value & 0xF0) | (*location & 0x0F);
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