
#include "timer.h"
#include "cpu_interrupts.h"

int cyclesPerIncrement(TimerSpeed speed) {
	switch (speed) {
		case TIMER_SPEED_CYCLES_4:	return 4;
		case TIMER_SPEED_CYCLES_16: return 16;
		case TIMER_SPEED_CYCLES_64: return 64;
		case TIMER_SPEED_CYCLES_256: return 256;
	}
}

void tickTimer(Hardware *hardware, int tickCycles) {
	TimerData *timerData = hardware->timerData;

	//divider register
	timerData->dividerCycleAccumulator += tickCycles;

	if (timerData->dividerCycleAccumulator == cyclesPerIncrement(TIMER_DIVIDER_CYCLES)) {
		timerData->dividerCycleAccumulator = 0;
		timerData->divider++;
	}

	//timer register
	if ((timerData->control & TIMER_CONTROL_MASK_TIMER_ENABLE) != 0) {
		timerData->cycleAccumulator += tickCycles;

		TimerSpeed speed = timerData->control & TIMER_CONTROL_MASK_TIMER_SPEED;

		if (timerData->cycleAccumulator == cyclesPerIncrement(speed)) {
			timerData->cycleAccumulator = 0;
			timerData->counter++;

			if (timerData->counter == 0) {
				timerData->counter = timerData->modulo;
				setRequestedInterrupt(hardware, INTERRUPT_FLAG_TIMER_OVERFLOW, true);
			}
		}
	}

}