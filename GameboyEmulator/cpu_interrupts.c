
#include "cpu_interrupts.h"
#include "cpu_ram.h"

void processInterrupts(Hardware *hardware) {
	if (hardware->registers->globalInterruptsEnabled) {
		unsigned char requestedEnabledInterrupt = (hardware->registers->requestedInterrupts & hardware->registers->enabledInterrupts);

		if (requestedEnabledInterrupt) {
			int interruptAddress = 0;

			unsigned char interruptToExecute = 0;

			if ((interruptToExecute = requestedEnabledInterrupt & INTERRUPT_FLAG_VBLANK) != 0) 
				interruptAddress = ROM_LOCATION_INTERRUPT_VBLANK;

			else if ((interruptToExecute = requestedEnabledInterrupt & INTERRUPT_FLAG_LCD_STAT) != 0) 
				interruptAddress = ROM_LOCATION_INTERRUPT_LCD_STAT;

			else if ((interruptToExecute = requestedEnabledInterrupt & INTERRUPT_FLAG_TIMER_OVERFLOW) != 0) 
				interruptAddress = ROM_LOCATION_INTERRUPT_TIMER_OVERFLOW;

			else if ((interruptToExecute = requestedEnabledInterrupt & INTERRUPT_FLAG_SERIAL_TRANSFER) != 0) 
				interruptAddress = ROM_LOCATION_INTERRUPT_SERIAL_TRANSFER;

			else if ((interruptToExecute = requestedEnabledInterrupt & INTERRUPT_FLAG_BUTTON_PRESS) != 0) 
				interruptAddress = ROM_LOCATION_INTERRUPT_BUTTON_PRESS;

			if (interruptAddress) {
				//clear flag of current interrupt
				hardware->registers->requestedInterrupts &= ~(interruptToExecute);

				//disable interrupts
				hardware->registers->globalInterruptsEnabled = false;

				//push current address to stack
				pushWordToStack(hardware, hardware->registers->PC);

				//jump to interrupt handler
				hardware->registers->PC = interruptAddress;
			}
		}
	}
}