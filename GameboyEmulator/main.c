#include <GL/glut.h>
#include <windows.h>

#include "constants.h"
#include "game_rom.h"
#include "cpu.h"
#include "ppu.h"

static int count = 0;

static Hardware *hardware;
static OperandMappings *mappings;

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	
	glColor3f(0.0f, 0.0f, 0.9f);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glEnd();
	glFlush();

	char log[50];
	sprintf_s(log, 50, "Redisplay %d\n", ++count);
	OutputDebugString(log);
}

void timer(int value) {
	glutTimerFunc(TARGET_MILLSECONDS_PER_FRAME, timer, 0);
	
	for (int i = 0; i <= TARGET_TICKS_FRAME; i++) {
		tickCPU(hardware, mappings);
		tickPPU(hardware, mappings);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) 
{
	GameRom *gameRom = readGameRom(lpCmdLine);

	hardware = initCPU(gameRom, true);
	mappings = initMappings(hardware);

	int argc = 0;
	glutInit(&argc, NULL);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Gameboy Emulator");
	
	glutDisplayFunc(display);		
	glutTimerFunc(TARGET_MILLSECONDS_PER_FRAME, timer, 0);
	glutMainLoop();

	return 0;
}
