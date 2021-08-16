#include "shader.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "dsUtils.h"

GLuint loadShader(const char *vertexFilePath, const char *fragmentFilePath){
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	char* vertexShaderCode;
	char* fragmentShaderCode;

	const char* vertexSourcePointer;
	const char* fragmentSourcePointer;

	GLint result = GL_FALSE;
	int infoLogLength;
	char *log;

	GLuint programID;

	vertexShaderCode = dsReadFile(vertexFilePath);
	if (!vertexShaderCode) {
		fprintf(stderr, "Cannot read file %s. Are you using correct directory?\n", vertexFilePath);
		return 0;
	}
	fragmentShaderCode = dsReadFile(fragmentFilePath);
	if (!fragmentShaderCode) {
		fprintf(stderr, "Cannot read file %s. Are you using correct directory?\n", fragmentFilePath);
		free(vertexShaderCode);
		return 0;
	}

	printf("Compiling shader: %s\n", vertexFilePath);
	vertexSourcePointer = vertexShaderCode;
	glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
	glCompileShader(vertexShaderID);

	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0){
		log = malloc(sizeof(char) * (infoLogLength + 1));
		log[infoLogLength] = 0;
		glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, log);
		fprintf(stderr, "%s\n", log);
		free(log);
	}

	printf("Compiling shader: %s\n", fragmentFilePath);
	fragmentSourcePointer = fragmentShaderCode;
	glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
	glCompileShader(fragmentShaderID);

	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0){
		log = malloc(sizeof(char) * (infoLogLength + 1));
		log[infoLogLength] = 0;
		glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, log);
		fprintf(stderr, "%s\n", log);
		free(log);
	}

	printf("Linking program\n");
	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0){
		log = malloc(sizeof(char) * (infoLogLength + 1));
		log[infoLogLength] = 0;
		glGetProgramInfoLog(programID, infoLogLength, NULL, log);
		fprintf(stderr, "%s\n", log);
		free(log);
	}

	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	free(vertexShaderCode);
	free(fragmentShaderCode);
	return programID;
}