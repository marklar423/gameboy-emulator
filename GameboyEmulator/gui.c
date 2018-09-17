
#include "gui.h"
#include <GL/glut.h>

static guiCallback g_updateLoopCallback, g_drawFrameCallback;

void glutTimerCallback(int value) {
	glutTimerFunc(TARGET_MILLSECONDS_PER_FRAME, glutTimerCallback, 0);

	g_updateLoopCallback();

	glutPostRedisplay();
}

void glutRedisplayCallback() {
	g_drawFrameCallback();
	glutSwapBuffers();	
}

void createGUIWindow() {
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
}

void setGUICallbacks(guiCallback updateLoopCallback, guiCallback drawFrameCallback) {
	g_updateLoopCallback = updateLoopCallback;
	g_drawFrameCallback = drawFrameCallback;
}

void runMainLoop() {
	glutDisplayFunc(glutRedisplayCallback);
	glutTimerFunc(TARGET_MILLSECONDS_PER_FRAME, glutTimerCallback, 0);
	glutMainLoop();
}