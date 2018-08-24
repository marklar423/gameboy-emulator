
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
	populateGameName(rom);

	return rom;
}

void populateGameName(GameRom *rom) {
	int n = 0;
	for (int i = ROM_LOCATION_GAME_NAME; i <= ROM_LOCATION_GAME_NAME_END; i++) {
		rom->gameName[n++] = rom->romBytes[i];
	}
	rom->gameName[n] = '\0';
}