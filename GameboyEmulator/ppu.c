
#include "ppu.h"
#include "ram.h"
#include "cpu_interrupts.h"


void setLCDLine(Hardware *hardware, unsigned char line);
void setLCDMode(Hardware *hardware, PPUFlag mode);
void populateVisibleSprites(Hardware *hardware);
void drawLine(Hardware *hardware);
void drawBackgroundLine(Hardware *hardware, int y);
void drawWindow(Hardware *hardware, int x, int y);
void drawSprites(Hardware *hardware, int x, int y);

int nextLine, nextMode;
bool started = false;

void tickPPU(Hardware *hardware, int tick) {
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
		int prevMode = hardware->videoData->lcdStatus & LCD_STAT_MODE_MASK;
		int currentLine = hardware->videoData->lcdYCoord;
		
		if (started) {
			assert(prevMode == nextMode);
			assert(currentLine == nextLine);
		}
		started = true;

		switch (prevMode) {
			case LCD_STAT_MODE_VBLANK:
				if (currentLine <  SCREEN_TOTAL_LINES - 1) {
					setLCDLine(hardware, ++currentLine);
					hardware->ppuCyclesToWait = PPU_CYCLES_LINE_TOTAL;
				}
				else {
					setLCDLine(hardware, 0);
					setLCDMode(hardware, LCD_STAT_MODE_OAM_SEARCH);
					populateVisibleSprites(hardware);
					hardware->ppuCyclesToWait = PPU_CYCLES_OAM_SEARCH;
				}
			break;

			case LCD_STAT_MODE_OAM_SEARCH:
				setLCDMode(hardware, LCD_STAT_MODE_PIXEL_TRANSFER);
				drawLine(hardware);
				hardware->ppuCyclesToWait = PPU_CYCLES_PIXEL_TRANSFER;
				break;

			case LCD_STAT_MODE_PIXEL_TRANSFER:
				setLCDMode(hardware, LCD_STAT_MODE_HBLANK);
				hardware->ppuCyclesToWait = PPU_CYCLES_HBLANK;
				break;

			case LCD_STAT_MODE_HBLANK:
				setLCDLine(hardware, ++currentLine);
				assert((tick % 114) == 0);
				assert((tick / 114) == currentLine);

				if (currentLine < SCREEN_VISIBLE_LINES) {
					setLCDMode(hardware, LCD_STAT_MODE_OAM_SEARCH);
					populateVisibleSprites(hardware);
					hardware->ppuCyclesToWait = PPU_CYCLES_OAM_SEARCH;
				}
				else {
					setLCDMode(hardware, LCD_STAT_MODE_VBLANK);
					hardware->ppuCyclesToWait = PPU_CYCLES_LINE_TOTAL;
				}
				break;
		}		
	}
	else {
		hardware->ppuCyclesToWait--;
	}
}

void resetFrameStatus(Hardware *hardware) {
	hardware->ppuCyclesToWait = 1;
	hardware->videoData->lcdStatus = (hardware->videoData->lcdStatus & (~LCD_STAT_MODE_MASK)) | LCD_STAT_MODE_VBLANK;
	hardware->videoData->lcdYCoord = SCREEN_TOTAL_LINES;
}

void clearFramePixels(Hardware *hardware) {
	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {
			hardware->videoData->framePixels[y][x] = PixelColor_White;
		}
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
	int currentLine = hardware->videoData->lcdYCoord;
	
	drawBackgroundLine(hardware, currentLine);

	for (int i = 0; i < SCREEN_WIDTH; i++) {
		drawWindow(hardware, i, currentLine);
		drawSprites(hardware, i, currentLine);
	}
}

void drawBackgroundLine(Hardware *hardware, int y) {
	//is BG enabled?
	if ((hardware->videoData->lcdControl & PPU_FLAG_BG_ENABLE) == PPU_FLAG_BG_ENABLE) {

		//map the pallete colors
		PixelColor palleteColors[4];
		palleteColors[0] = hardware->videoData->bgPalette & 3;
		palleteColors[1] = (hardware->videoData->bgPalette & 12) >> 2;
		palleteColors[2] = (hardware->videoData->bgPalette & 48) >> 4;
		palleteColors[3] = (hardware->videoData->bgPalette & 192) >> 6;

		//get the right tile map
		unsigned char* bgTileMap;

		if ((hardware->videoData->lcdControl & PPU_FLAG_BG_TILE_MAP_SELECT) == PPU_FLAG_BG_TILE_MAP_SELECT) {
			bgTileMap = hardware->videoData->bgMap2;
		}
		else {
			bgTileMap = hardware->videoData->bgMap1;
		}

		//get the relevant map cell row
		int mapY, mapX = -1;
		mapY = (hardware->videoData->scrollY + y) / TILE_SIZE;

		if (mapY >= BG_MAP_TILES_HEIGHT) 
			mapY = 0;

		unsigned char tileNumber;

		//get the row of pixels in the tile to draw
		int tilePixelsRowNumber;
		tilePixelsRowNumber = (hardware->videoData->scrollY + y) - (mapY * TILE_SIZE);

		unsigned char *tileRowPixels;

		for (int x = 0; x < SCREEN_WIDTH; x++) {
			int targetMapX = (hardware->videoData->scrollX + x) / TILE_SIZE;
				
			if (mapX != targetMapX) {
				//map cell changed, so get the new tile number
				mapX = targetMapX;

				if (mapX >= BG_MAP_TILES_WIDTH)
					mapX = 0;

				tileNumber = bgTileMap[(mapY * BG_MAP_TILES_WIDTH) + mapX];
				
				//which address mode are we in?
				int baseTileAddress = 0, tileAddress;

				if ((hardware->videoData->lcdControl & PPU_FLAG_BG_TILE_DATA_ADDRESS_MODE) == PPU_FLAG_BG_TILE_DATA_ADDRESS_MODE) {
					tileAddress = tileNumber * BYTES_PER_TILE;
				}
				else {
					baseTileAddress = VRAM_TILES_1_SIZE + VRAM_TILES_2_SIZE;
					char tileNumberSigned = tileNumber;
					tileAddress = tileNumberSigned * BYTES_PER_TILE;
				}

				tileRowPixels = (hardware->videoData->tileData + tileAddress + (tilePixelsRowNumber * 2));
			}

			//get the column of the pixel in the tile to draw
			int tilePixelColumnNumber = (hardware->videoData->scrollX + x) - (mapX * TILE_SIZE);
			
			unsigned char pixelPalleteColor = 0;
			unsigned char tilePixelColumnMask = 128 >> tilePixelColumnNumber;

			if ((tileRowPixels[0] & tilePixelColumnMask) == tilePixelColumnMask) pixelPalleteColor |= 1;
			if ((tileRowPixels[1] & tilePixelColumnMask) == tilePixelColumnMask) pixelPalleteColor |= 2;

			hardware->videoData->framePixels[y][x] = palleteColors[pixelPalleteColor];
		}
	}
}

void drawWindow(Hardware *hardware, int x, int y) {
	//is window enabled?
	if ((hardware->videoData->lcdControl & PPU_FLAG_WINDOW_ENABLE) == PPU_FLAG_WINDOW_ENABLE) {

	}
}

void drawSprites(Hardware *hardware, int x, int y) {
	//are sprites enabled?
	if ((hardware->videoData->lcdControl & PPU_FLAG_OBJ_ENABLE) == PPU_FLAG_OBJ_ENABLE) {

	}
}

void setLCDMode(Hardware *hardware, PPUFlag mode) {
	nextMode = mode;

	unsigned char currentMode = hardware->videoData->lcdStatus;
	PPUFlag prevMode = currentMode & LCD_STAT_MODE_MASK;

	if (prevMode != mode) {
		hardware->videoData->lcdStatus = (hardware->videoData->lcdStatus & (~LCD_STAT_MODE_MASK)) | mode;

		//handle mode change interrupt and V blank interrupt
		PPUFlag intEnabledMask;
		bool requestInterrupt = false;
		
		switch (mode) {
		case LCD_STAT_MODE_HBLANK:
			requestInterrupt = true;
			intEnabledMask = LCD_STAT_HBLANK_INT_ENABLE_MASK;
			break;
		case LCD_STAT_MODE_VBLANK:
			requestInterrupt = true;
			intEnabledMask = LCD_STAT_VBLANK_INT_ENABLE_MASK;
			setRequestedInterrupt(hardware, INTERRUPT_FLAG_VBLANK, true);
			break;
		case LCD_STAT_MODE_OAM_SEARCH:
			requestInterrupt = true;
			intEnabledMask = LCD_STAT_OAM_INT_ENABLE_MASK;
			break;
		}

		if (requestInterrupt && (hardware->videoData->lcdStatus & intEnabledMask) == intEnabledMask) {
			setRequestedInterrupt(hardware, INTERRUPT_FLAG_LCD_STAT, true);
		}
	}
}

void setLCDLine(Hardware *hardware, unsigned char line) {
	nextLine = line;
	hardware->videoData->lcdYCoord = line;

	if (line == hardware->videoData->lcdYCompare) {
		hardware->videoData->lcdStatus |= LCD_STAT_COMPARE_MASK;

		//handle LCD Y interrupt
		if ((hardware->videoData->lcdStatus & LCD_STAT_COMPARE_INT_ENABLE_MASK) == LCD_STAT_COMPARE_INT_ENABLE_MASK) {
			setRequestedInterrupt(hardware, INTERRUPT_FLAG_LCD_STAT, true);
		}
	}
	else {
		hardware->videoData->lcdStatus &=  ~LCD_STAT_COMPARE_MASK;
	}

}