
#include <windows.h>

#define GLFW_DLL
#include <GLFW/glfw3.h>

#include "gui.h"
#include "util.h"

static guiCallback g_updateLoopCallback, g_drawFrameCallback;
static GLFWwindow *g_window;

void createGUIWindow() {
	/* Initialize the library */
	if (!glfwInit()) THROW_ERROR("ERROR INITIALIZING GLFW");

	/* Create a windowed mode window and its OpenGL context */
	g_window = glfwCreateWindow(480, 432, "Gameboy Emulator", NULL, NULL);
	if (!g_window)
	{
		glfwTerminate();
		THROW_ERROR("ERROR CREATING WINDOW");
	}

	glfwSetWindowPos(g_window, 100, 100);

	/* Make the window's context current */
	glfwMakeContextCurrent(g_window);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 480, 432);
	glOrtho(0.0, 160.0, 144.0, 0.0, 0.0, 1.0);	
	glMatrixMode(GL_MODELVIEW);

	//since we're polling for input, this ensures we don't miss input events
	glfwSetInputMode(g_window, GLFW_STICKY_KEYS, 1);
}

void setGUICallbacks(guiCallback updateLoopCallback, guiCallback drawFrameCallback) {
	g_updateLoopCallback = updateLoopCallback;
	g_drawFrameCallback = drawFrameCallback;
}

void runMainLoop(float targetFPS) {
	double limitFPS = 1.0f / targetFPS;

	double lastTime = glfwGetTime();
	double deltaTime = 0, nowTime = 0;

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(g_window))
	{
		//Measure time
		nowTime = glfwGetTime();
		deltaTime += (nowTime - lastTime) / limitFPS;
		lastTime = nowTime;

		//Only update at targetFPS frames
		while (deltaTime >= 1.0) {
			g_updateLoopCallback();
			deltaTime--;

			g_drawFrameCallback();

			//Swap front and back buffers
			glfwSwapBuffers(g_window);
		}


		//Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
}

void getInputState(InputState *inputState) {	
	inputState->isBPressed = (glfwGetKey(g_window, GLFW_KEY_Z) == GLFW_PRESS);
	inputState->isAPressed = (glfwGetKey(g_window, GLFW_KEY_X) == GLFW_PRESS);
	inputState->isStartPressed = (glfwGetKey(g_window, GLFW_KEY_ENTER) == GLFW_PRESS);
	inputState->isSelectPressed = (glfwGetKey(g_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS);
	inputState->isUpPressed = (glfwGetKey(g_window, GLFW_KEY_UP) == GLFW_PRESS);
	inputState->isDownPressed = (glfwGetKey(g_window, GLFW_KEY_DOWN) == GLFW_PRESS);
	inputState->isRightPressed = (glfwGetKey(g_window, GLFW_KEY_RIGHT) == GLFW_PRESS);
	inputState->isLeftPressed = (glfwGetKey(g_window, GLFW_KEY_LEFT) == GLFW_PRESS);
}