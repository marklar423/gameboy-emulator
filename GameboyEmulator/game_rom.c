
#include <stdio.h>
#include <windows.h>
#include "game_rom.h"


GameRom* readGameRom(const char* filePath) {
	FILE *filePtr;
	long fileLen;

	fopen_s(&filePtr, filePath, "rb");  // Open the file in binary mode
	fseek(filePtr, 0, SEEK_END);          // Jump to the end of the file
	fileLen = ftell(filePtr);             // Get the current byte offset in the file
	rewind(filePtr);                      // Jump back to the beginning of the file

	char *fileBytes = malloc((fileLen + 1) * sizeof(char)); // Enough memory for file + \0
	fread(fileBytes, fileLen, 1, filePtr); // Read in the entire file
	fclose(filePtr); // Close the file

	GameRom *rom = createGameRom(fileBytes, fileLen);
	rom->romBytesSwitchable = &rom->romBytes[RAM_LOCATION_ROM_SWITCHABLE];
	parseCartHeader(rom);

	return rom;
}

void parseCartHeader(GameRom *rom) {
	int n = 0;
	for (int i = ROM_LOCATION_GAME_NAME; i <= ROM_LOCATION_GAME_NAME_END; i++) {
		rom->gameName[n++] = rom->romBytes[i];
	}
	rom->gameName[n] = '\0';

	rom->cartType = rom->romBytes[ROM_LOCATION_CART_TYPE];
	rom->hasExternalRam = hasCartRam(rom);
	rom->hasExternalBattery = hasCartBattery(rom);
	populateCartHardware(rom);
}


void populateCartHardware(GameRom *rom) {
	switch (rom->cartType) {
		case CART_TYPE_ROM_ONLY:
		case CART_TYPE_ROM_RAM:
		case CART_TYPE_ROM_RAM_BATTERY:
			rom->cartRomOnly = calloc(1, sizeof(CartRomOnly));
			rom->ramSwitchable = &rom->cartRomOnly->ramBytes;
			break;
		case CART_TYPE_MBC1:
		case CART_TYPE_MBC1_RAM:
		case CART_TYPE_MBC1_RAM_BATTERY:
			rom->cartMBC1 = calloc(1, sizeof(CartMBC1));
			rom->ramSwitchable = &rom->cartMBC1->ramBytes;
			break;
		case CART_TYPE_MBC2:
		case CART_TYPE_MBC2_BATTERY:
		case CART_TYPE_MBC3:
		case CART_TYPE_MBC3_RAM:
		case CART_TYPE_MBC3_RAM_BATTERY:
		case CART_TYPE_MBC3_TIMER_BATTERY:
		case CART_TYPE_MBC3_TIMER_RAM_BATTERY:
		case CART_TYPE_MBC5:
		case CART_TYPE_MBC5_RAM:
		case CART_TYPE_MBC5_RAM_BATTERY:
		case CART_TYPE_MBC5_RUMBLE:
		case CART_TYPE_MBC5_RUMBLE_RAM:
		case CART_TYPE_MBC5_RUMBLE_RAM_BATTERY:
		case CART_TYPE_MBC6:
		case CART_TYPE_MBC7_SENSOR_RUMBLE_RAM_BATTERY:
		case CART_TYPE_MMM01:
		case CART_TYPE_MMM01_RAM:
		case CART_TYPE_MMM01_RAM_BATTERY:
		case CART_TYPE_POCKET_CAMERA:
		case CART_TYPE_BANDAI_TAMA5:
		case CART_TYPE_HuC1_RAM_BATTERY:
		case CART_TYPE_HuC3:
			break;
	}
}

bool hasCartRam(GameRom *rom) {
	switch (rom->cartType) {
	case CART_TYPE_ROM_RAM:
	case CART_TYPE_ROM_RAM_BATTERY:
	case CART_TYPE_MBC1_RAM:
	case CART_TYPE_MBC1_RAM_BATTERY:
	case CART_TYPE_MBC2_BATTERY:
	case CART_TYPE_MBC3_RAM:
	case CART_TYPE_MBC3_RAM_BATTERY:
	case CART_TYPE_MBC3_TIMER_RAM_BATTERY:
	case CART_TYPE_MBC5_RAM:
	case CART_TYPE_MBC5_RAM_BATTERY:
	case CART_TYPE_MBC5_RUMBLE_RAM:
	case CART_TYPE_MBC5_RUMBLE_RAM_BATTERY:
	case CART_TYPE_MBC7_SENSOR_RUMBLE_RAM_BATTERY:
	case CART_TYPE_MMM01_RAM:
	case CART_TYPE_MMM01_RAM_BATTERY:
	case CART_TYPE_HuC1_RAM_BATTERY:
		return true;
	}

	return false;
}

bool hasCartBattery(GameRom *rom) {
	switch (rom->cartType) {
	case CART_TYPE_ROM_RAM_BATTERY:
	case CART_TYPE_MBC1_RAM_BATTERY:
	case CART_TYPE_MBC2_BATTERY:
	case CART_TYPE_MBC3_RAM_BATTERY:
	case CART_TYPE_MBC3_TIMER_BATTERY:
	case CART_TYPE_MBC3_TIMER_RAM_BATTERY:
	case CART_TYPE_MBC5_RAM_BATTERY:
	case CART_TYPE_MBC5_RUMBLE_RAM_BATTERY:
	case CART_TYPE_MBC7_SENSOR_RUMBLE_RAM_BATTERY:
	case CART_TYPE_MMM01_RAM_BATTERY:
	case CART_TYPE_HuC1_RAM_BATTERY:
		return true;
	}

	return false;
}