#include "util.h"


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