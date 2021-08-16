#include "dsUtils.h"

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

#define BUFSIZE 1024

char* dsStrJoin(const char* s1, const char* s2){
	char* result;
	int	s1_len;
	int	s2_len;

	if (!s1 && !s2)
		return (NULL);
	if (s1 && !s2)
		return strdup(s1);
	if (!s1 && s2)
		return strdup(s2);
	s1_len = strlen(s1);
	s2_len = strlen(s2);
	if (!(result = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (0);
	memcpy(result, s1, s1_len);
	memcpy(result + s1_len, s2, s2_len);
	result[s1_len + s2_len] = 0;
	return (result);
}

char* dsStrClearJoin(char** s1, const char* s2){
	char* temp = dsStrJoin(*s1, s2);
	free(*s1);
	*s1 = temp;
	return temp;
}

char* dsReadFile(const char* filePath){
	int fd = open(filePath,  O_CREAT);
	char buf[BUFSIZE + 1];
	char* ret = NULL;
	int rdrt;
	if (fd == -1){
		printf("%s\n", strerror(errno));
		return NULL;
	}
	while ((rdrt = read(fd, buf, BUFSIZE)) > 0){
		buf[rdrt] = 0;
		printf("%s\n", buf);
		dsStrClearJoin(&ret, buf);
	}
	close(fd);
	return ret;
}