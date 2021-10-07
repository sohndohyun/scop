#include "loader.h"
#include "env.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

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

GLuint loadBmp(const char * imagePath){
	printf("Reading image %s\n", imagePath);

	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	unsigned int width, height;

	unsigned char * data;

	int fd = open(imagePath, O_RDONLY);
	if (fd < 0) {
		printf("%s could not be opened. Are you in the right directory?\n", imagePath);
		return 0;
	}

	if (read(fd, header, 54) != 54){
		close(fd);
		printf("Not a correct BMP file\n");
		return 0;
	}

	if (header[0] != 'B' || header[1] != 'M'){
		close(fd);
		printf("Not a correct BMP file\n");
		return 0;
	}

	if ( *(int*)&(header[0x1E]) != 0){
		close(fd);
		printf("Not a correct BMP file\n");
		return 0;
	}

	if ( *(int*)&(header[0x1C]) != 24){
		close(fd);
		printf("Not a correct BMP file\n");
		return 0;
	}

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	if (imageSize == 0)
		imageSize = width * height * 3;
	if (dataPos == 0)
		dataPos = 54;

	data = (unsigned char*)malloc(sizeof(unsigned char) * imageSize);
	if (read(fd, data, imageSize) != imageSize){
		close(fd);
		free(data);
		printf("Not a correct BMP file\n");
		return 0;
	}
	
	close(fd);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	free(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	return textureID;	
}

// v, vt, vn, f, l, mtllib, usemtl, o, g, s

static void readFace(char **token, int tokenCnt){
	for (int i = 0;i < tokenCnt;++i){
		char** temp = ft_split(token[i], '/');
	}
}

int loadObj(const char *path){
	printf("loading obj file %s... \n", path);

	int fd = open(path, O_RDONLY);
	if (fd < 0){
		printf("Impossible to open file %s! Are you in the right path?\n", path);
		return 0;
	}

	int vertexCount = 0;
	int faceCount = 0;
	int normalCount = 0;
	int texcoordCount = 0;

	char *line;
	while (ft_gnl(fd, &line) > 0){
		int at = strchr(line, ' ') - line;
		if (at == 2 && strncmp(line, "vt", at) == 0)
			++texcoordCount;
		else if (at == 2 && strncmp(line, "vn", at) == 0)
			++normalCount;
		else if (at == 1 && strncmp(line, "v", at) == 0)
			++vertexCount;
		else if (at == 1 && strncmp(line, "f", at) == 0)
			++faceCount;		
		free(line);
	}
	lseek(fd, 0, SEEK_SET);

	GLfloat* vertexArray = malloc(sizeof(GLfloat) * 4 * vertexCount);
	GLfloat* normalArray = malloc(sizeof(GLfloat) * 3 * normalCount);
	GLfloat* texcoordArray = malloc(sizeof(GLfloat) * 3 * texcoordCount);

	int vertexIndex = 0;
	int faceIndex = 0;
	int normalIndex = 0;
	int texcoordIndex = 0;

	char *line;
	while (ft_gnl(fd, &line) > 0){
		char **token = ft_split(line, ' ');
		int tokenCnt = ft_split_cnt(token);
		if (!token){
			if (strcmp(token[0], "vt") == 0){
				for (int i = 1;i < tokenCnt;++i)
					texcoordArray[3 * texcoordIndex + (i - 1)] = atof(token[i]);
				++texcoordIndex;
			}
			else if (strcmp(token[0], "vn") == 0){
				for (int i = 1;i < tokenCnt;++i)
					normalArray[3 * normalIndex + (i - 1)] = atof(token[i]);
				++normalIndex;
			}
			else if (strcmp(token[0], "v") == 0){
				for (int i = 1;i < tokenCnt;++i)
					vertexArray[4 * vertexIndex + (i - 1)] = atof(token[i]);
				++vertexIndex;
			}
			else if (strcmp(token[0], "f") == 0){
				readFace(token + 1, tokenCnt - 1);
				++faceIndex;
			}
			dsFreeStrArray(token);
		}		
		free(line);
	}

	free(vertexArray);
	free(normalArray);
	free(texcoordArray);

	close(fd);
	return 1;
}
