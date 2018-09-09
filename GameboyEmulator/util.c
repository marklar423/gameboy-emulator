#include "util.h"
#include <stdio.h>
#include <windows.h>


int joinBytes(const unsigned char leastSignificant, const unsigned char mostSignificant) {
	int left = mostSignificant << 8;
	int right = leastSignificant;

	int result = left | right;
	return result;
}


void splitBytes(const int value, unsigned char *leastSignificant, unsigned char *mostSignificant) {	
	*leastSignificant = (unsigned char)value;
	*mostSignificant = (unsigned char)(value >> 8);
}

FILE *debugFile = NULL;

void printDebugLine(char *line) {
	if (debugFile == NULL) fopen_s(&debugFile, "debug.txt", "w");

	if (debugFile == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}

	fprintf(debugFile, line);
	fflush(debugFile);
}