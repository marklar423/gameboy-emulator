#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include "cpu_ram.h"
#include "util.h"

unsigned char* getRamAddress(Hardware *hardware, int address) {
	if (address >= RAM_LOCATION_CART_FIXED && address <= RAM_LOCATION_CART_FIXED_END) 
		return &hardware->rom->romBytes[address];

	else if (address >= RAM_LOCATION_WORK_RAM_FIXED && address <= RAM_LOCATION_WORK_RAM_SWITCHABLE_END) 
		return &hardware->workRam[address - RAM_LOCATION_WORK_RAM_FIXED];

	else if (address >= RAM_LOCATION_HRAM && address <= RAM_LOCATION_HRAM_END)
		return &hardware->highRam[address - RAM_LOCATION_HRAM];
	
	else if (address == RAM_LOCATION_JOYPAD_INPUT) return &hardware->ioData->joypadInput;
	else if (address == RAM_LOCATION_SERIAL_TRANSFER_DATA) return &hardware->ioData->serialTransferData;
	else if (address == RAM_LOCATION_SERIAL_TRANSFER_CONTROL) return &hardware->ioData->serialTransferControl;
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
	
	

	//assert(false && "Unknown RAM location");
	return NULL;
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