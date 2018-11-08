#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include "ram.h"
#include "util.h"
#include "cpu_interrupts.h"

static unsigned char TODO = 0xFF;

unsigned char * getSwitchableRom(Hardware *hardware, RamAddress *address);
unsigned char * getSwitchableCartRam(Hardware *hardware, RamAddress *address);

void writeRomAddress(Hardware *hardware, RamAddress *address, unsigned char value);
void writeVRAM(Hardware *hardware, RamAddress *address, unsigned char value);
void writeSound(Hardware *hardware, RamAddress *address, unsigned char value);
void writeJoypad(Hardware *hardware, RamAddress *address, unsigned char value);
void writeTimer(Hardware *hardware, RamAddress *address, unsigned char value);
void writeVideoSettings(Hardware *hardware, RamAddress *address, unsigned char value);

unsigned char* getArrayAddress(unsigned char *array, int index, int arraySize);

RamAddress* getRamAddress(Hardware *hardware, int address) {
	if (address >= RAM_LOCATION_ROM_FIXED && address <= RAM_LOCATION_ROM_FIXED_END)
		return createRamAddress(address, &hardware->rom->romBytes[address], NULL, writeRomAddress);

	else if (address >= RAM_LOCATION_ROM_SWITCHABLE && address <= RAM_LOCATION_ROM_SWITCHABLE_END)
		return createRamAddress(address, NULL, getSwitchableRom, writeRomAddress);

	else if (address >= RAM_LOCATION_VRAM_TILES_1 && address < RAM_LOCATION_VRAM_BG_MAP_1)
		return createRamAddress(address, getArrayAddress(hardware->videoData->tileData, address - RAM_LOCATION_VRAM_TILES_1, VRAM_TOTAL_TILES_SIZE),
			NULL, writeVRAM);

	else if (address >= RAM_LOCATION_VRAM_BG_MAP_1 && address < RAM_LOCATION_VRAM_BG_MAP_2) 
		return createRamAddress(address, getArrayAddress(hardware->videoData->bgMap1, address - RAM_LOCATION_VRAM_BG_MAP_1, VRAM_BG_MAP_1_SIZE),
			NULL, writeVRAM);
	
	else if (address >= RAM_LOCATION_VRAM_BG_MAP_2 && address <= RAM_LOCATION_VRAM_END) 
		return createRamAddress(address, getArrayAddress(hardware->videoData->bgMap2, address - RAM_LOCATION_VRAM_BG_MAP_2, VRAM_BG_MAP_2_SIZE),
			NULL, writeVRAM);
	
	else if (address >= RAM_LOCATION_OAM && address <= RAM_LOCATION_OAM_END)
		return createRamAddress(address, getArrayAddress(hardware->videoData->oamTable, address - RAM_LOCATION_OAM, OAM_SIZE),
			NULL, writeVRAM);

	else if ((address >= RAM_LOCATION_CART_RAM && address <= RAM_LOCATION_CART_RAM_END) && hardware->rom->hasExternalRam)
		return createRamAddress(address, NULL, getSwitchableCartRam, NULL);

	else if (address >= RAM_LOCATION_WORK_RAM_FIXED && address <= RAM_LOCATION_WORK_RAM_FIXED_END)
		return createRamAddress(address, getArrayAddress(hardware->workRam, address - RAM_LOCATION_WORK_RAM_FIXED, WORK_RAM_SIZE), NULL, NULL);

	else if (address >= RAM_LOCATION_WORK_RAM_SWITCHABLE && address <= RAM_LOCATION_WORK_RAM_SWITCHABLE_END)
		//todo: implement memory bank switching for CGB
		return createRamAddress(address, getArrayAddress(hardware->workRam, address - RAM_LOCATION_WORK_RAM_FIXED, WORK_RAM_SIZE), NULL, NULL);
	
	else if (address >= RAM_LOCATION_MIRROR_WORK_RAM_FIXED && address <= RAM_LOCATION_MIRROR_WORK_RAM_FIXED_END)
		//echo ram fixed
		return createRamAddress(address, getArrayAddress(hardware->workRam, address - RAM_LOCATION_MIRROR_WORK_RAM_FIXED, WORK_RAM_SIZE), NULL, NULL);

	else if (address >= RAM_LOCATION_MIRROR_WORK_RAM_SWITCHABLE && address <= RAM_LOCATION_MIRROR_WORK_RAM_SWITCHABLE_END)
		//echo ram switchable
		return createRamAddress(address, getArrayAddress(hardware->workRam, address - RAM_LOCATION_MIRROR_WORK_RAM_FIXED, WORK_RAM_SIZE), NULL, NULL);

	else if (address >= RAM_LOCATION_HRAM && address <= RAM_LOCATION_HRAM_END)
		return createRamAddress(address, getArrayAddress(hardware->highRam, address - RAM_LOCATION_HRAM, HRAM_SIZE), NULL, NULL);

	else if (address >= RAM_LOCATION_SOUND_WAVE_PATTERN && address <= RAM_LOCATION_SOUND_WAVE_PATTERN_END) 
		return createRamAddress(address, getArrayAddress(hardware->soundData->chan3_WaveData, address - RAM_LOCATION_SOUND_WAVE_PATTERN, SOUND_WAVE_PATTERN_BYTES),
			NULL, writeSound);
	
	else if (address == RAM_LOCATION_JOYPAD_INPUT) return createRamAddress(address, &hardware->ioData->joypadData, NULL, writeJoypad);
	else if (address == RAM_LOCATION_SERIAL_TRANSFER_DATA) return createRamAddress(address, &hardware->ioData->serialTransferData, NULL, NULL);
	else if (address == RAM_LOCATION_SERIAL_TRANSFER_CONTROL) return createRamAddress(address, &hardware->ioData->serialTransferControl, NULL, NULL);
	else if (address == RAM_LOCATION_TIMER_DIVIDER) return createRamAddress(address, &hardware->timerData->divider, NULL, writeTimer);
	else if (address == RAM_LOCATION_TIMER_COUNTER) return createRamAddress(address, &hardware->timerData->counter, NULL, writeTimer);
	else if (address == RAM_LOCATION_TIMER_MODULO) return createRamAddress(address, &hardware->timerData->modulo, NULL, writeTimer);
	else if (address == RAM_LOCATION_TIMER_CONTROL) return createRamAddress(address, &hardware->timerData->control, NULL, writeTimer);
	else if (address == RAM_LOCATION_SOUND_CHANNEL_1_FREQUENCY_SWEEP) return createRamAddress(address, &hardware->soundData->chan1_FrequencySweep, NULL, writeSound);
	else if (address == RAM_LOCATION_SOUND_CHANNEL_1_PATTERN_LENGTH) return createRamAddress(address, &hardware->soundData->chan1_PatternLength, NULL, writeSound);
	else if (address == RAM_LOCATION_SOUND_CHANNEL_1_VOLUME_SWEEP) return createRamAddress(address, &hardware->soundData->chan1_VolumeSweep, NULL, writeSound);
	else if (address == RAM_LOCATION_SOUND_CHANNEL_1_FREQUENCY_LOW) return createRamAddress(address, &hardware->soundData->chan1_FrequencyLow, NULL, writeSound);
	else if (address == RAM_LOCATION_SOUND_CHANNEL_1_FREQUENCY_HIGH_SETTINGS) return createRamAddress(address, &hardware->soundData->chan1_FrequencyHighSettings, NULL, writeSound);
	else if (address == RAM_LOCATION_SOUND_CHANNEL_2_PATTERN_LENGTH) return createRamAddress(address, &hardware->soundData->chan2_PatternLength, NULL, writeSound);
	else if (address == RAM_LOCATION_SOUND_CHANNEL_2_VOLUME_SWEEP) return createRamAddress(address, &hardware->soundData->chan2_VolumeSweep, NULL, writeSound);
	else if (address == RAM_LOCATION_SOUND_CHANNEL_2_FREQUENCY_LOW) return createRamAddress(address, &hardware->soundData->chan2_FrequencyLow, NULL, writeSound);
	else if (address == RAM_LOCATION_SOUND_CHANNEL_2_FREQUENCY_HIGH_SETTINGS) return createRamAddress(address, &hardware->soundData->chan2_FrequencyHighSettings, NULL, writeSound);
	else if (address == RAM_LOCATION_SOUND_CHANNEL_3_ONOFF) return createRamAddress(address, &hardware->soundData->chan3_OnOff, NULL, writeSound);
	else if (address == RAM_LOCATION_SOUND_CHANNEL_3_LENGTH) return createRamAddress(address, &hardware->soundData->chan3_Length, NULL, writeSound);
	else if (address == RAM_LOCATION_SOUND_CHANNEL_3_VOLUME) return createRamAddress(address, &hardware->soundData->chan3_Volume, NULL, writeSound);
	else if (address == RAM_LOCATION_SOUND_CHANNEL_3_FREQUENCY_LOW) return createRamAddress(address, &hardware->soundData->chan3_FrequencyLow, NULL, writeSound);
	else if (address == RAM_LOCATION_SOUND_CHANNEL_3_FREQUENCY_HIGH_SETTINGS) return createRamAddress(address, &hardware->soundData->chan3_FrequencyHighSettings, NULL, writeSound);
	else if (address == RAM_LOCATION_SOUND_CHANNEL_4_LENGTH) return createRamAddress(address, &hardware->soundData->chan4_length, NULL, writeSound);
	else if (address == RAM_LOCATION_SOUND_CHANNEL_4_VOLUME_SWEEP) return createRamAddress(address, &hardware->soundData->chan4_VolumeSweep, NULL, writeSound);
	else if (address == RAM_LOCATION_SOUND_CHANNEL_4_POLYNOMIAL_COUNTER) return createRamAddress(address, &hardware->soundData->chan4_polynomialCounter, NULL, writeSound);
	else if (address == RAM_LOCATION_SOUND_CHANNEL_4_SETTINGS) return createRamAddress(address, &hardware->soundData->chan4_settings, NULL, writeSound);
	else if (address == RAM_LOCATION_SOUND_MASTER_LR_VOLUME) return createRamAddress(address, &hardware->soundData->masterVolume, NULL, writeSound);
	else if (address == RAM_LOCATION_SOUND_CHANNEL_LR_ENABLE) return createRamAddress(address, &hardware->soundData->channelLeftRightEnable, NULL, writeSound);
	else if (address == RAM_LOCATION_SOUND_ENABLE) return createRamAddress(address, &hardware->soundData->soundEnable, NULL, writeSound);
	else if (address == RAM_LOCATION_LCD_CONTROL) return createRamAddress(address, &hardware->videoData->lcdControl, NULL, writeVideoSettings);
	else if (address == RAM_LOCATION_LCD_STATUS) return createRamAddress(address, &hardware->videoData->lcdStatus, NULL, writeVideoSettings);
	else if (address == RAM_LOCATION_SCROLL_Y) return createRamAddress(address, &hardware->videoData->scrollY, NULL, writeVideoSettings);
	else if (address == RAM_LOCATION_SCROLL_X) return createRamAddress(address, &hardware->videoData->scrollX, NULL, writeVideoSettings);
	else if (address == RAM_LOCATION_LCD_Y_COORD) return createRamAddress(address, &hardware->videoData->lcdYCoord, NULL, writeVideoSettings);
	else if (address == RAM_LOCATION_LCD_Y_COMPARE) return createRamAddress(address, &hardware->videoData->lcdYCompare, NULL, writeVideoSettings);
	else if (address == RAM_LOCATION_DMA_TRANSFER) return createRamAddress(address, &hardware->videoData->dmaTransfer, NULL, writeVideoSettings);
	else if (address == RAM_LOCATION_BG_PALETTE) return createRamAddress(address, &hardware->videoData->bgPalette, NULL, writeVideoSettings);
	else if (address == RAM_LOCATION_OBJ_PALETTE_0) return createRamAddress(address, &hardware->videoData->objPalette0, NULL, writeVideoSettings);
	else if (address == RAM_LOCATION_OBJ_PALETTE_1) return createRamAddress(address, &hardware->videoData->objPalette1, NULL, writeVideoSettings);
	else if (address == RAM_LOCATION_WINDOW_Y) return createRamAddress(address, &hardware->videoData->windowY, NULL, writeVideoSettings);
	else if (address == RAM_LOCATION_WINDOW_X) return createRamAddress(address, &hardware->videoData->windowX, NULL, writeVideoSettings);
	else if (address == RAM_LOCATION_INTERRUPT_FLAGS) return createRamAddress(address, &hardware->registers->requestedInterrupts, NULL, NULL);
	else if (address == RAM_LOCATION_INTERRUPTS_ENABLE)  return createRamAddress(address, &hardware->registers->enabledInterrupts, NULL, NULL);

	//todo:
	else if ((address >= RAM_LOCATION_SOUND_CHANNEL_1_FREQUENCY_SWEEP && address <= RAM_LOCATION_SOUND_CHANNEL_LR_ENABLE) 
				|| (address >= RAM_LOCATION_UNUSABLE && RAM_LOCATION_UNUSABLE_END <= RAM_LOCATION_UNUSABLE_END))
	return createRamAddress(address, &TODO, NULL, NULL);

	return createRamAddress(address, NULL, NULL, NULL);
}

unsigned char* getArrayAddress(unsigned char *array, int index, int arraySize) {
	assert(index >= 0 && index < arraySize);
	return &(array[index]);
}

unsigned char * getSwitchableRom(Hardware *hardware, RamAddress *address) {
	//todo: implement memory bank switching
	return getArrayAddress(hardware->rom->romBytesSwitchable, address->address - RAM_LOCATION_ROM_SWITCHABLE, SWITCHABLE_CART_ROM_ADDRESS_SIZE);
}

unsigned char * getSwitchableCartRam(Hardware *hardware, RamAddress *address) {
	return getArrayAddress(hardware->rom->ramSwitchable, address - RAM_LOCATION_CART_RAM_END, SWITCHABLE_CART_RAM_ADDRESS_SIZE);
}

void writeRomAddress(Hardware *hardware, RamAddress *address, unsigned char value) {
	//todo: implement bank switching
}

void writeVRAM(Hardware *hardware, RamAddress *address, unsigned char value) {

	PPUFlag lcdMode = (hardware->videoData->lcdStatus & LCD_STAT_MODE_MASK);
	
	/*if (location >= hardware->videoData->oamTable && location <= &hardware->videoData->oamTable[OAM_SIZE - 1]) {
		if (lcdMode != LCD_STAT_MODE_PIXEL_TRANSFER && lcdMode != LCD_STAT_MODE_OAM_SEARCH) {
			//can't write to OAM during pixel transfer and OAM search
			(*getRamAddressPointer(hardware, address)) = value;
		}
	}
	else if (location >= hardware->videoData->tileData && location <= &hardware->videoData->tileData[VRAM_TOTAL_TILES_SIZE - 1]) {
		if (lcdMode != LCD_STAT_MODE_PIXEL_TRANSFER) {
			//can't write to tiles during pixel transfer
			(*getRamAddressPointer(hardware, address)) = value;
		}
	}
	else if (location >= hardware->videoData->bgMap1 && location <= &hardware->videoData->bgMap1[VRAM_BG_MAP_1_SIZE - 1]) {
		if (lcdMode != LCD_STAT_MODE_PIXEL_TRANSFER) {
			//can't write to map during pixel transfer
			(*getRamAddressPointer(hardware, address)) = value;
		}
	}
	else if (location >= hardware->videoData->bgMap2 && location <= &hardware->videoData->bgMap2[VRAM_BG_MAP_2_SIZE - 1]) {
		if (lcdMode != LCD_STAT_MODE_PIXEL_TRANSFER) {
			//can't write to map during pixel transfer
			(*getRamAddressPointer(hardware, address)) = value;
		}
	}
	else {*/
		(*getRamAddressPointer(hardware, address)) = value;
	//}
}

void writeSound(Hardware *hardware, RamAddress *address, unsigned char value) {
	if (address->address == RAM_LOCATION_SOUND_CHANNEL_1_PATTERN_LENGTH|| address->address == RAM_LOCATION_SOUND_CHANNEL_1_FREQUENCY_HIGH_SETTINGS) {
		(*getRamAddressPointer(hardware, address)) = value;
		hardware->soundData->chan1_currentTick = 1;
	}
	else if (address->address == RAM_LOCATION_SOUND_CHANNEL_2_PATTERN_LENGTH || address->address == RAM_LOCATION_SOUND_CHANNEL_2_FREQUENCY_HIGH_SETTINGS) {
		(*getRamAddressPointer(hardware, address)) = value;
		hardware->soundData->chan2_currentTick = 1;
	}
	else if ((address->address >= RAM_LOCATION_SOUND_WAVE_PATTERN && address->address <= RAM_LOCATION_SOUND_WAVE_PATTERN_END)
		|| address->address == RAM_LOCATION_SOUND_CHANNEL_3_LENGTH || address->address == RAM_LOCATION_SOUND_CHANNEL_3_FREQUENCY_HIGH_SETTINGS) {
		(*getRamAddressPointer(hardware, address)) = value;
		hardware->soundData->chan3_currentTick = 1;
	}
	else if (address->address == RAM_LOCATION_SOUND_CHANNEL_4_LENGTH || address->address == RAM_LOCATION_SOUND_CHANNEL_4_SETTINGS) {
		(*getRamAddressPointer(hardware, address)) = value;
		hardware->soundData->chan4_currentTick = 1;
	}
	else {
		(*getRamAddressPointer(hardware, address)) = value;
	}
}

void writeJoypad(Hardware *hardware, RamAddress *address, unsigned char value) {
	 if (address->address == RAM_LOCATION_JOYPAD_INPUT) {
		//only bits 4 & 5 can be written
		unsigned char currentValue = getRamAddressValue(hardware, address);
		(*getRamAddressPointer(hardware, address)) = (value & 0x30) | (currentValue & 0xCF);
		setJoypadDataState(hardware);
	}
	else {
		(*getRamAddressPointer(hardware, address)) = value;
	}
}

void writeTimer(Hardware *hardware, RamAddress *address, unsigned char value) {
	if (address == RAM_LOCATION_TIMER_DIVIDER) {
		//writing resets to zero
		(*getRamAddressPointer(hardware, address)) = 0;
	}
	else if (address == RAM_LOCATION_TIMER_CONTROL) {
		//only bits 0-2 can be written
		unsigned char currentValue = getRamAddressValue(hardware, address);
		(*getRamAddressPointer(hardware, address)) = (value & 0x07) | (currentValue & 0xF8);
	}
	else {
		(*getRamAddressPointer(hardware, address)) = value;
	}
}

void writeVideoSettings(Hardware *hardware, RamAddress *address, unsigned char value) {
	if (address == RAM_LOCATION_LCD_STATUS) {
		//bits 0-2 are read 
		unsigned char currentValue = getRamAddressValue(hardware, address);
		(*getRamAddressPointer(hardware, address)) = (value & 0xF8) | (currentValue & 0x7);
	}
	else if (address == RAM_LOCATION_LCD_Y_COORD) {
		//writing should reset?
		(*getRamAddressPointer(hardware, address)) = 0;
	}
	else if (address == RAM_LOCATION_DMA_TRANSFER) {
		(*getRamAddressPointer(hardware, address)) = value;

		//start DMA transfer
		hardware->isOAMDMATriggered = true;
	}	
	else {
		(*getRamAddressPointer(hardware, address)) = value;
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