
#include "ppu.h"
#include "ram.h"


void setLCDLine(Hardware *hardware, unsigned char line);
void setLCDMode(Hardware *hardware, PPUFlag mode);
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
		int prevMode = hardware->videoData->lcdStatus & PPU_FLAG_MODE_MASK;
		int currentLine = hardware->videoData->lcdYCoord;

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
	int currentLine = hardware->videoData->lcdYCoord;
	int numVisible = 0, numSprites = RAM_LOCATION_OAM_END - RAM_LOCATION_OAM + 1;
	
	for (int i = 0; i < numSprites && numVisible < VISIBLE_SPRITES_PER_LINE; i++) {
		int yPos = hardware->videoData->oamTable[i + OAM_INDEX_POS_Y];
		int xPos = hardware->videoData->oamTable[i + OAM_INDEX_POS_X];

		//todo: handle double height sprites
		if (xPos > 0 && xPos < SCREEN_WIDTH + TILE_SIZE) {
			if (currentLine < (yPos - TILE_SIZE) && currentLine >= yPos - (TILE_SIZE * 2)) {
				hardware->videoData->lineVisibleSprites[numVisible++] = &(hardware->videoData->oamTable[i]);
			}			
		}
	}

	for (int i = numVisible; i < VISIBLE_SPRITES_PER_LINE; i++) {
		hardware->videoData->lineVisibleSprites[i] = NULL;
	}
}

void drawLine(Hardware *hardware) {

}

void setLCDMode(Hardware *hardware, PPUFlag mode) {
	unsigned char currentMode = hardware->videoData->lcdStatus;
	int prevMode = currentMode & PPU_FLAG_MODE_MASK;

	if (prevMode != mode) {
		hardware->videoData->lcdStatus = (hardware->videoData->lcdStatus & (~PPU_FLAG_MODE_MASK)) | mode;
		//todo: handle mode change interrupt and V blank interrupt
	}
}

void setLCDLine(Hardware *hardware, unsigned char line) {
	hardware->videoData->lcdYCoord = line;
	//todo: handle LCD Y interrupt
}