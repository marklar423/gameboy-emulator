

#include <windows.h>

#define GLFW_DLL
#include <GLFW/glfw3.h>


#include "constants.h"
#include "gui.h"
#include "config.h"
#include "game_rom.h"
#include "cpu.h"
#include "ppu.h"
#include "ram.h"

static int numFrames = 0;

static Hardware *g_hardware;
static InstructionMapping *g_mappings;
static Config *g_config;

void drawFrame() {
	glClear(GL_COLOR_BUFFER_BIT);	
	glPointSize(4.0f);

	GLfloat xStart = -1.0f, yStart = -1.0f;

	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {
			GLfloat red, green, blue;

			switch (g_hardware->videoData->framePixels[y][x]) {
			case PixelColor_White:
				red = green = blue = 1.0f;
				break;
			case PixelColor_LightGray:
				red = green = blue = 0.75f;
				break;
			case PixelColor_DarkGray:
				red = green = blue = 0.50f;
				break;
			case PixelColor_Black:
				red = green = blue = 0.0f;
				break;
			}

			glBegin(GL_POINTS);
			glColor3f(red, green, blue);						
			glVertex2i(x, y);
			glEnd();
		}
	}
}


void updateFrame() {		
	clearFramePixels(g_hardware);
	getInputState(g_hardware->inputState);
	setJoypadDataState(g_hardware);
	
	for (int i = 0; i < TARGET_TICKS_FRAME; i++) {		
		tickCPU(g_hardware, g_mappings);
		tickPPU(g_hardware, i);
	}

	//resetFrameStatus(hardware);
	
	numFrames++;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) 
{
	g_config = readConfigFile("config.ini");
	GameRom *gameRom = readGameRom(g_config->romPath);

	g_hardware = initCPU(gameRom, true);
	g_mappings = initInstructionMappings(g_hardware);

	createGUIWindow();
	setGUICallbacks(updateFrame, drawFrame);
	runMainLoop(TARGET_FPS);

	return 0;
}
