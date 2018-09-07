#include <GL/glut.h>
#include <windows.h>

#include "constants.h"
#include "game_rom.h"
#include "cpu.h"
#include "ppu.h"

static int numFrames = 0;

static Hardware *hardware;
static InstructionMapping *mappings;

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	/*glBegin(GL_POLYGON);
	
	glColor3f(0.0f, 0.0f, 0.9f);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glEnd();*/

	GLfloat xStart = -1.0f, yStart = -1.0f;

	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {
			GLfloat red, green, blue;

			switch (hardware->videoData->framePixels[y][x]) {
			case PixelColor_White:
				red = green = blue = 1.0f;
				break;
			case PixelColor_LightGray:
				red = green = blue = 0.166f;
				break;
			case PixelColor_DarkGray:
				red = green = blue = 0.77f;
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

	//glFlush();
	glutSwapBuffers();

	/*char log[50];
	sprintf_s(log, 50, "Redisplay %d\n", ++count);
	OutputDebugString(log);*/
}

void timer(int value) {
	glutTimerFunc(TARGET_MILLSECONDS_PER_FRAME, timer, 0);
		
	clearFramePixels(hardware);

	for (int i = 0; i < TARGET_TICKS_FRAME; i++) {		
		tickCPU(hardware, mappings);
		tickPPU(hardware, i);
	}

	resetFrameStatus(hardware);
	
	glutPostRedisplay();
	numFrames++;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) 
{
	GameRom *gameRom = readGameRom(lpCmdLine);

	hardware = initCPU(gameRom, true);
	mappings = initInstructionMappings(hardware);

	int argc = 0;
	glutInit(&argc, NULL);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Gameboy Emulator");
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 500.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glutDisplayFunc(display);		
	glutTimerFunc(TARGET_MILLSECONDS_PER_FRAME, timer, 0);
	glutMainLoop();

	return 0;
}
