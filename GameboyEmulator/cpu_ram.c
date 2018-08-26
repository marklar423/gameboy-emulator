#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include "cpu_ram.h"

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

	//assert(false && "Unknown RAM location");
	return NULL;
}
