
#include <stdio.h>
#include <windows.h>

#include "config.h"
#include "ini.h"

int iniFileCallback(void* user, const char* section, const char* name, const char* value) {
	Config *config = (Config *) user;

#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
	if (MATCH("rom", "path")) {
		int strSize = strlen(value) + 1;
		config->romPath = malloc(strSize);
		strcpy_s(config->romPath, strSize, value);
	}
	else {
		return 0;  /* unknown section/name, error */
	}
	return 1;
}

Config * readConfigFile(char *filePath) {
	Config *config = malloc(sizeof(Config));

	FILE *filePtr;
	long fileLen;

	fopen_s(&filePtr, filePath, "r");
	
	ini_parse_file(filePtr, iniFileCallback, config);

	fclose(filePtr);

	return config;
}