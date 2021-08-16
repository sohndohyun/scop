#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

static void errorCallback(int errorCode, const char *errorDescription);
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

int main()
{
	GLFWwindow *window;
	GLenum errorCode;
	double lastTime;
	double currentTime;
	int numOfFrames;
	int count;

	float position[] = {
		0.0f, 0.5f, 0.0f,  //vertex 1  위 중앙
		0.5f, -0.5f, 0.0f, //vertex 2  오른쪽 아래
		-0.5f, -0.5f, 0.0f //vertex 3  왼쪽 아래
	};

	glfwSetErrorCallback(errorCallback);

	if (!glfwInit())
	{
		fprintf(stderr, "Error: GLFW initialize failed\n");
		exit(EXIT_FAILURE);
	}

	// will use opengl 4.1
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	// core(using without deprecated function) vs compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// remove deprecated API
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// resize window available
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// anti-aliasing
	glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(800, 600, "OpenGL Example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, keyCallback);

	glewExperimental = GL_TRUE;
	errorCode = glewInit();
	if (GLEW_OK != errorCode)
	{
		fprintf(stderr, "Error: GLEW initialize failed-%s\n", glewGetErrorString(errorCode));
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	if (!GLEW_VERSION_4_1)
	{
		fprintf(stderr, "OpenGL 4.1 API is not available.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	printf("OpenGL version: %s\n", glGetString(GL_VERSION));
	printf("GLSL version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));

	// frame update control (1 <- 60 fps 0 <- infinite)
	glfwSwapInterval(1);

	lastTime = glfwGetTime();
	numOfFrames = 0;

	count = 0;

	// loop until alt+f4 or close
	while (!glfwWindowShouldClose(window))
	{
		currentTime = glfwGetTime();
		numOfFrames++;

		if (currentTime - lastTime >= 1.0)
		{
			printf("%f ms/frame %d fps \n", 1000.0 / (double)numOfFrames, numOfFrames);
			numOfFrames = 0;
			lastTime = currentTime;
		}

		if (count % 2)
			glClearColor(1, 0, 0, 0);
		else
			glClearColor(0, 0, 1, 0);

		glClear(GL_COLOR_BUFFER_BIT);
		count++;

		// update window
		glfwSwapBuffers(window);

		// catch event e.g.) keyboard, mouse input ...
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

static void errorCallback(int errorCode, const char *errorDescription)
{
	(void)errorCode;
	fprintf(stderr, "Error: %s\n", errorDescription);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}