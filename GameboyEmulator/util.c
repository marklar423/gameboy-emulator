#include "util.h"


void joinBytes(const unsigned char *leastSignificant, const unsigned char *mostSignificant, int *result) {
	int left = *mostSignificant << 8;
	int right = *leastSignificant;
	*result = left | right;
}


void splitBytes(const int *value, unsigned char *leastSignificant, unsigned char *mostSignificant) {	
	*leastSignificant = (unsigned char)*value;
	*mostSignificant = (unsigned char)(*value >> 8);
}