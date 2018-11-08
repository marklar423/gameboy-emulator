#pragma once

#include "constants.h"
#include "objects.h"


GameRom* readGameRom(const char* filePath);

void parseCartHeader(GameRom *rom);

bool hasCartRam(GameRom *rom);

bool hasCartBattery(GameRom *rom);

void populateCartHardware(GameRom *rom);