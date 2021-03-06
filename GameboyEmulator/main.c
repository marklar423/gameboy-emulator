

#include <windows.h>

#define GLFW_DLL
#include <GLFW/glfw3.h>


#include "constants.h"
#include "gui.h"
#include "gui_audio.h"
#include "config.h"
#include "game_rom.h"
#include "cpu.h"
#include "ppu.h"
#include "ram.h"
#include "timer.h"
#include "sound_controller.h"

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
				red = green = blue = 0.70f;
				break;
			case PixelColor_DarkGray:
				red = green = blue = 0.40f;
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
	//clearFramePixels(g_hardware);
	getInputState(g_hardware->inputState);
	setJoypadDataState(g_hardware);
	
	for (int i = 0; i < TARGET_TICKS_FRAME; i++) {		
		tickCPU(g_hardware, g_mappings);
		tickPPU(g_hardware, i);

		if (i % CYCLES_PER_TIMER_TICK == 0) tickTimer(g_hardware, CYCLES_PER_TIMER_TICK);

		if (i % CYCLES_PER_SOUND_TICK == 0) {
			AudioSample audioSample = tickSound(g_hardware);
			writeGUIAudioBuffer(audioSample.leftSample, audioSample.rightSample);
		}
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

	initGUIAudio(AUDIO_BUFFER_SIZE, AUDIO_SAMPLE_RATE);

	char title[40];
	title[0] = '\0';
	strcat_s(title, 40, gameRom->gameName);
	strcat_s(title, 40, " | Gameboy Emulator");

	createGUIWindow(title);
	setGUICallbacks(updateFrame, drawFrame);
	runMainLoop(TARGET_FPS);

	disposeGUIAudio();

	return 0;
}
