#pragma once

#include "constants.h"
#include "objects.h"


GameRom* readGameRom(const char* filePath);
void parseCartHeader(GameRom *rom);
