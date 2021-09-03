#include "texture.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

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