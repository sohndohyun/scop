#pragma once

#include <GLFW/glfw3.h>

typedef struct s_env{
	GLfloat *vertex;
	GLfloat *uv;
	GLfloat *norm;
}t_env;

extern t_env g_env;
extern GLFWwindow *g_window;