#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include "cpu_ram.h"
#include "util.h"

unsigned char* getRamAddress(Hardware *hardware, int address) {
	if (address >= RAM_LOCATION_CART_FIXED && address <= RAM_LOCATION_CART_FIXED_END) {
		return &hardware->rom->romBytes[address];
	}
	else if (address >= RAM_LOCATION_WORK_RAM_FIXED && address <= RAM_LOCATION_WORK_RAM_SWITCHABLE_END) {
		return &hardware->workRam[address - RAM_LOCATION_WORK_RAM_FIXED];
	}
	else if (address == RAM_LOCATION_INTERRUPT_FLAGS) {
		return &hardware->registers->requestedInterrupts;
	}
	else if (address == RAM_LOCATION_INTERRUPTS_ENABLE) {
		return &hardware->registers->enabledInterrupts;
	}

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