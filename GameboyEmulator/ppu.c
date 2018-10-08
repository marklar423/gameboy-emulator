
#include "ppu.h"
#include "ram.h"
#include "cpu_interrupts.h"
#include "util.h"

PPUFlag getNextMode(PPUFlag prevMode, int currentLine);
int getNextLine(int currentLine);

void setLCDLine(Hardware *hardware, unsigned char line);
void setLCDMode(Hardware *hardware, PPUFlag mode);
void populateVisibleSprites(Hardware *hardware);
void drawLine(Hardware *hardware);
void drawBackgroundLine(Hardware *hardware, int y);
void drawWindow(Hardware *hardware, int x, int y);
void drawSprites(Hardware *hardware, int y);
void populatePaletteColors(PixelColor *colors, unsigned char palleteMapping);
unsigned char* getTileBytes(unsigned char *tileData, int tileRow, unsigned char tileNumber, bool useSignedTileNumber);
PixelColor getTilePixelColor(PixelColor *colors, unsigned char *tileRowPixels, int tileColumn);

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
		PPUFlag prevMode = hardware->videoData->lcdStatus & LCD_STAT_MODE_MASK;
		int currentLine = hardware->videoData->lcdYCoord;

		PPUFlag mode = getNextMode(prevMode, currentLine);
		setLCDMode(hardware, mode);
		
		switch (mode) {
			case LCD_STAT_MODE_OAM_SEARCH:
				hardware->ppuCyclesToWait = PPU_CYCLES_OAM_SEARCH;
				setLCDLine(hardware, getNextLine(currentLine));
				populateVisibleSprites(hardware);
				break;

			case LCD_STAT_MODE_PIXEL_TRANSFER:
				hardware->ppuCyclesToWait = PPU_CYCLES_PIXEL_TRANSFER;
				drawLine(hardware);
				break;
			
			case LCD_STAT_MODE_HBLANK:
				hardware->ppuCyclesToWait = PPU_CYCLES_HBLANK;
				break;
			
			case LCD_STAT_MODE_VBLANK:
				hardware->ppuCyclesToWait = PPU_CYCLES_LINE_TOTAL;
				setLCDLine(hardware, getNextLine(currentLine));
				break;
		}


		/*char buffer[70];
		sprintf_s(buffer, sizeof(buffer), "Tick, %d, Mode, %d, line, %d, waiting, %d\n", tick, mode, hardware->videoData->lcdYCoord, hardware->ppuCyclesToWait);
		printDebugLine(buffer);*/
	}
	else {
		hardware->ppuCyclesToWait--;
	}
}

PPUFlag getNextMode(PPUFlag prevMode, int currentLine) {

	switch (prevMode) {
		case LCD_STAT_MODE_OAM_SEARCH: 
			return LCD_STAT_MODE_PIXEL_TRANSFER;
		case LCD_STAT_MODE_PIXEL_TRANSFER: 
			return LCD_STAT_MODE_HBLANK;
		case LCD_STAT_MODE_HBLANK:
			return (currentLine < SCREEN_VISIBLE_LINES - 1) ? LCD_STAT_MODE_OAM_SEARCH : LCD_STAT_MODE_VBLANK;
		case LCD_STAT_MODE_VBLANK:
			return (currentLine < SCREEN_TOTAL_LINES - 1) ? LCD_STAT_MODE_VBLANK : LCD_STAT_MODE_OAM_SEARCH;
	}
}

int getNextLine(int currentLine) {
	return currentLine == SCREEN_TOTAL_LINES - 1 ? 0 : currentLine + 1;
}

void resetFrameStatus(Hardware *hardware) {
	hardware->ppuCyclesToWait = 1;
	hardware->videoData->lcdStatus = (hardware->videoData->lcdStatus & (~LCD_STAT_MODE_MASK)) | LCD_STAT_MODE_VBLANK;
	hardware->videoData->lcdYCoord = SCREEN_TOTAL_LINES - 1;
}

void clearFramePixels(Hardware *hardware) {
	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {
			hardware->videoData->framePixels[y][x] = PixelColor_White;
		}
	}
}

void populateVisibleSprites(Hardware *hardware) {
	int numVisible = 0;
	int currentLine = hardware->videoData->lcdYCoord;
	
	for (int i = 0; i < TOTAL_SPRITES && numVisible < VISIBLE_SPRITES_PER_LINE; i++) {
		int spriteStartIndex = i * BYTES_PER_SPRITE;
		int yPos = hardware->videoData->oamTable[spriteStartIndex + OAM_INDEX_POS_Y];
		int xPos = hardware->videoData->oamTable[spriteStartIndex + OAM_INDEX_POS_X];

		//todo: handle double height sprites
		if (xPos > 0 && xPos < SCREEN_WIDTH + TILE_SIZE) {
			if (currentLine < (yPos - TILE_SIZE) && currentLine >= yPos - (TILE_SIZE * 2)) {
				hardware->videoData->lineVisibleSprites[numVisible++] = &(hardware->videoData->oamTable[spriteStartIndex]);
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
	drawSprites(hardware, currentLine);

	for (int i = 0; i < SCREEN_WIDTH; i++) {
		drawWindow(hardware, i, currentLine);
	}
}

void drawBackgroundLine(Hardware *hardware, int y) {
	//is BG enabled?
	if ((hardware->videoData->lcdControl & PPU_FLAG_BG_ENABLE) != 0) {

		//map the pallete colors
		PixelColor paletteColors[4];
		populatePaletteColors(&paletteColors, hardware->videoData->bgPalette);

		//get the right tile map
		unsigned char* bgTileMap;

		if ((hardware->videoData->lcdControl & PPU_FLAG_BG_TILE_MAP_SELECT) != 0) {
			bgTileMap = hardware->videoData->bgMap2;
		}
		else {
			bgTileMap = hardware->videoData->bgMap1;
		}

		//get the relevant map cell row
		int mapY, mapX = -1;
		mapY = (hardware->videoData->scrollY + y) / TILE_SIZE;

		//get the row of pixels in the tile to draw
		int tilePixelsRowNumber;
		tilePixelsRowNumber = (hardware->videoData->scrollY + y) - (mapY * TILE_SIZE);

		if (mapY >= BG_MAP_TILES_HEIGHT) 
			mapY -= BG_MAP_TILES_HEIGHT;

		unsigned char tileNumber;


		unsigned char *tileRowPixels = NULL;

		for (int x = 0; x < SCREEN_WIDTH; x++) {
			int targetMapX = (hardware->videoData->scrollX + x) / TILE_SIZE;

			if (targetMapX >= BG_MAP_TILES_WIDTH)
				targetMapX -= BG_MAP_TILES_WIDTH;

			if (mapX != targetMapX) {
				//map cell changed, so get the new tile number
				mapX = targetMapX;
				
				tileNumber = bgTileMap[(mapY * BG_MAP_TILES_WIDTH) + mapX];
				
				bool useSignedTileNumber = (hardware->videoData->lcdControl & PPU_FLAG_BG_TILE_DATA_ADDRESS_MODE) != PPU_FLAG_BG_TILE_DATA_ADDRESS_MODE;
				tileRowPixels = getTileBytes(hardware->videoData->tileData, tilePixelsRowNumber, tileNumber, useSignedTileNumber);
			}

			//get the column of the pixel in the tile to draw
			int tilePixelColumnNumber = (hardware->videoData->scrollX + x) - (mapX * TILE_SIZE);
			
			hardware->videoData->framePixels[y][x] = getTilePixelColor(paletteColors, tileRowPixels, tilePixelColumnNumber);
		}
	}
}

void drawWindow(Hardware *hardware, int x, int y) {
	//is window enabled?
	if ((hardware->videoData->lcdControl & PPU_FLAG_WINDOW_ENABLE) != 0) {

	}
}

void drawSprites(Hardware *hardware, int y) {
	//are sprites enabled?
	if ((hardware->videoData->lcdControl & PPU_FLAG_OBJ_ENABLE) != 0) {

		for (int i = 0; i < VISIBLE_SPRITES_PER_LINE && hardware->videoData->lineVisibleSprites[i] != NULL; i++) {
			unsigned char *sprite = hardware->videoData->lineVisibleSprites[i];

			int yPos = sprite[OAM_INDEX_POS_Y];
			int xPos = sprite[OAM_INDEX_POS_X];
			unsigned char tileNumber = sprite[OAM_INDEX_TILE_NUM];
			unsigned char flags = sprite[OAM_INDEX_FLAGS];

			bool isXFlipped = (flags & OAM_FLAG_X_FLIP) != 0;
			bool isYFlipped = (flags & OAM_FLAG_Y_FLIP) != 0;
			
			PixelColor paletteColors[4];
			unsigned char paletteData = (flags & OAM_FLAG_PALETTE_NUM_MASK) != 0 ?
											hardware->videoData->objPalette1 : hardware->videoData->objPalette0;
			populatePaletteColors(&paletteColors, paletteData);

			int tileRow = y - (yPos - (TILE_SIZE * 2));
			if (isYFlipped) tileRow = (TILE_SIZE - 1) - tileRow;

			unsigned char* tileRowPixels = getTileBytes(hardware->videoData->tileData, tileRow, tileNumber, false);

			int startX = xPos - TILE_SIZE;
			startX = startX < 0 ? 0 : startX;

			int endX = xPos < SCREEN_WIDTH ? xPos : SCREEN_WIDTH;

			for (int x = startX; x < endX; x++) {
				int tileCol = x - (xPos - TILE_SIZE);
				if (isXFlipped) tileCol = (TILE_SIZE - 1) - tileCol;

				PixelColor finalColor = getTilePixelColor(paletteColors, tileRowPixels, tileCol);
				
				//color zero is considered transparent and not rendered
				if (finalColor != paletteColors[0]) {
					hardware->videoData->framePixels[y][x] = finalColor;
				}
			}
		}
	}
}

void populatePaletteColors(PixelColor *colors, unsigned char paletteMapping) {
	colors[0] = paletteMapping & 3;
	colors[1] = (paletteMapping & 12) >> 2;
	colors[2] = (paletteMapping & 48) >> 4;
	colors[3] = (paletteMapping & 192) >> 6;
}

PixelColor getTilePixelColor(PixelColor *colors, unsigned char *tileRowPixels, int tileColumn) {
	unsigned char pixelPaletteColor = 0;
	unsigned char tilePixelColumnMask = 128 >> tileColumn;

	if ((tileRowPixels[0] & tilePixelColumnMask) == tilePixelColumnMask) pixelPaletteColor |= 1;
	if ((tileRowPixels[1] & tilePixelColumnMask) == tilePixelColumnMask) pixelPaletteColor |= 2;
	return colors[pixelPaletteColor];
}

unsigned char* getTileBytes(unsigned char *tileData, int tileRow, unsigned char tileNumber, bool useSignedTileNumber) {
	//which address mode are we in?
	int baseTileAddress = 0, tileAddress;

	if (useSignedTileNumber) {
		baseTileAddress = VRAM_TILES_1_SIZE + VRAM_TILES_2_SIZE;
		char tileNumberSigned = tileNumber;
		tileAddress = tileNumberSigned * BYTES_PER_TILE;		
	}
	else {
		tileAddress = tileNumber * BYTES_PER_TILE;
	}

	unsigned char *tileRowPixels = (tileData + tileAddress + (tileRow * 2));
	return tileRowPixels;
}

void setLCDMode(Hardware *hardware, PPUFlag mode) {
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
	hardware->videoData->lcdYCoord = line;

	if (line == hardware->videoData->lcdYCompare) {
		hardware->videoData->lcdStatus |= LCD_STAT_COMPARE_MASK;

		//handle LCD Y interrupt
		if ((hardware->videoData->lcdStatus & LCD_STAT_COMPARE_INT_ENABLE_MASK) == LCD_STAT_COMPARE_INT_ENABLE_MASK) {
			setRequestedInterrupt(hardware, INTERRUPT_FLAG_LCD_STAT, true);
		}
	}
	else {
		hardware->videoData->lcdStatus &= (~LCD_STAT_COMPARE_MASK);
	}

}