#pragma once

#include <GL/glew.h>
#include <dsgm.h>
#include <libft.h>

GLuint loadShader(const char *vertexFilePath, const char *fragmentFilePath);
GLuint loadBmp(const char * imagePath);
int loadObj(const char *path);