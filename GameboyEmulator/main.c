#include <GL/glut.h>
#include <windows.h>
#include <stdio.h>

#include "constants.h"
#include "cpu.h"

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

void idle() {
	tickCpu(hardware, mappings);
}

GameRom* readBytes(const char* filePath) {
	FILE *filePtr;
	long fileLen;

	fopen_s(&filePtr, filePath, "rb");  // Open the file in binary mode
	fseek(filePtr, 0, SEEK_END);          // Jump to the end of the file
	fileLen = ftell(filePtr);             // Get the current byte offset in the file
	rewind(filePtr);                      // Jump back to the beginning of the file

	char *fileBytes = malloc((fileLen + 1) * sizeof(char)); // Enough memory for file + \0
	fread(fileBytes, fileLen, 1, filePtr); // Read in the entire file
	fclose(filePtr); // Close the file

	GameRom *rom = malloc(sizeof(GameRom));
	rom->romBytes = fileBytes;
	rom->romLength = fileLen;

	return rom;
}

void populateGameName(GameRom *rom) {
	int n = 0;
	for (int i = ROM_LOCATION_GAME_NAME; i <= ROM_LOCATION_GAME_NAME_END; i++) {
		rom->gameName[n++] = rom->romBytes[i];
	}
	rom->gameName[n] = '\0';
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) 
{
	GameRom *gameRom = readBytes(lpCmdLine);
	populateGameName(gameRom);
	hardware = initCpu(gameRom, true);
	mappings = initMappings(hardware);

	int argc = 0;
	glutInit(&argc, NULL);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Gameboy Emulator");
	
	glutDisplayFunc(display);		
	glutIdleFunc(idle);
	glutMainLoop();

	return 0;
}
