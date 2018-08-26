
#include "cpu_interrupts.h"


void processInterrupts(Hardware *hardware) {
	if (hardware->registers->globalInterruptsEnabled) {
		unsigned char requestedEnabledInterrupt = (hardware->registers->requestedInterrupts & hardware->registers->enabledInterrupts);

		if (requestedEnabledInterrupt) {
			int interruptAddress = 0;

			if (requestedEnabledInterrupt & INTERRUPT_FLAG_VBLANK) interruptAddress = ROM_LOCATION_INTERRUPT_VBLANK;
			else if (requestedEnabledInterrupt & INTERRUPT_FLAG_LCD_STAT) interruptAddress = ROM_LOCATION_INTERRUPT_LCD_STAT;
			else if (requestedEnabledInterrupt & INTERRUPT_FLAG_TIMER_OVERFLOW) interruptAddress = ROM_LOCATION_INTERRUPT_TIMER_OVERFLOW;
			else if (requestedEnabledInterrupt & INTERRUPT_FLAG_SERIAL_TRANSFER) interruptAddress = ROM_LOCATION_INTERRUPT_SERIAL_TRANSFER;
			else if (requestedEnabledInterrupt & INTERRUPT_FLAG_BUTTON_PRESS) interruptAddress = ROM_LOCATION_INTERRUPT_BUTTON_PRESS;

			if (interruptAddress) {
				//push current address to stack
				hardware->registers->SP--;
				unsigned char* topOfStack = getRamAddress(hardware, hardware->registers->SP);
				*topOfStack = hardware->registers->PC;

				//disable interrupts
				hardware->registers->globalInterruptsEnabled = false;

				//jump to interrupt handler
				hardware->registers->PC = interruptAddress;
			}
		}
	}
}