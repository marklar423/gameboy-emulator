
#include "ppu.h"
#include "ram.h"


void setLCDLine(Hardware *hardware, unsigned char line);
void populateVisibleSprites(Hardware *hardware);
void drawLine(Hardware *hardware);


void tickPPU(Hardware *hardware) {
	/*	
	 - For PPU, each line of pixels takes:
		- 20 clocks OAM search
		- 43 clocks drawing pixels
		- 51 clocks idle for h-blank
	 - So each line of pixels total takes 114 clocks
	 - There are 144 "drawing" lines, and 10 additional idle lines for v-blank

	 - So total clocks per gameboy frame = 114 x (144 + 10) = 17,556 clocks per gameboy frame
	 */

	if (hardware->ppuCyclesToWait <= 1) {
		int prevMode = *(getRamAddress(hardware, RAM_LOCATION_LCD_STATUS)) & PPU_FLAG_MODE_MASK;
		int currentLine = *(getRamAddress(hardware, RAM_LOCATION_LCD_Y_COORD));

		switch (prevMode) {
			case PPU_FLAG_MODE_VBLANK:
				if (currentLine <  SCREEN_TOTAL_LINES - 1) {
					setLCDLine(hardware, currentLine + 1);
					hardware->ppuCyclesToWait = PPU_CYCLES_LINE_TOTAL;
				}
				else {
					setLCDLine(hardware, 0);
					setLCDMode(hardware, PPU_FLAG_MODE_OAM_SEARCH);
					populateVisibleSprites(hardware);
					hardware->ppuCyclesToWait = PPU_CYCLES_OAM_SEARCH;
				}
			break;

			case PPU_FLAG_MODE_OAM_SEARCH:
				setLCDMode(hardware, PPU_FLAG_MODE_PIXEL_TRANSFER);
				drawLine(hardware);
				hardware->ppuCyclesToWait = PPU_CYCLES_PIXEL_TRANSFER;
				break;

			case PPU_FLAG_MODE_PIXEL_TRANSFER:
				setLCDMode(hardware, PPU_FLAG_MODE_HBLANK);
				hardware->ppuCyclesToWait = PPU_CYCLES_HBLANK;
				break;

			case PPU_FLAG_MODE_HBLANK:
				setLCDLine(hardware, currentLine + 1);

				if (currentLine < SCREEN_VISIBLE_LINES - 1) {
					setLCDMode(hardware, PPU_FLAG_MODE_OAM_SEARCH);
					populateVisibleSprites(hardware);
					hardware->ppuCyclesToWait = PPU_CYCLES_OAM_SEARCH;
				}
				else {
					setLCDMode(hardware, PPU_FLAG_MODE_VBLANK);
					hardware->ppuCyclesToWait = PPU_CYCLES_LINE_TOTAL;
				}
				break;
		}		
	}
	else {
		hardware->ppuCyclesToWait--;
	}
}

void populateVisibleSprites(Hardware *hardware) {

}

void drawLine(Hardware *hardware) {

}

void setLCDMode(Hardware *hardware, PPUFlag mode) {
	unsigned char *currentMode = getRamAddress(hardware, RAM_LOCATION_LCD_STATUS);
	int prevMode = (*currentMode) & PPU_FLAG_MODE_MASK;

	if (prevMode != mode) {
		//todo: handle mode change interrupt and V blank interrupt
	}
}

void setLCDLine(Hardware *hardware, unsigned char line) {
	*(getRamAddress(hardware, RAM_LOCATION_LCD_Y_COORD)) = line;
	//todo: handle LCD Y interrupt
}