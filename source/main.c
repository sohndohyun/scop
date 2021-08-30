#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "shader.h"
#include "dsgm.h"

int main(){
	GLFWwindow *window;
	GLuint vertexArrayID;
	GLuint vertexBuffer;
	GLuint programID;
	GLuint matrixID;

	t_mat4 projection = perspective(radian(45.0f), 1600.f / 900.0f, 0.1f, 100.0f);
	t_mat4 view = lookAt(vec3(4.0f, 3.0f, 3.0f), vec3(0.f,0.f,0.f), vec3(0.f,1.f,0.f));
	t_mat4 model = scale(0.5f, 0.5f, 0.5f);
	t_mat4 MVP = mat4_mult(projection, mat4_mult(view, model));

	static const GLfloat g_vertex_buffer_data[] = { 
		0.0f,1.0f, 0.0f,
    	1.0f,-1.0f, 0.0f,
    	-1.0f, -1.0f, 0.0f,
	};

//	MVP = view;
	matlog(MVP);

	if (!glfwInit()){
		fprintf(stderr, "GLFW initialize failed\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); //anti-ali
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1600, 900, "scop", NULL, NULL);
	if (!window){
		fprintf(stderr, "GLFW window open failed\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); 
	
	// init glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK){
		fprintf(stderr, "Failed to intialize glew\n");
		glfwTerminate();
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	programID = loadShader("vertexShader.glsl", "fragmentShader.glsl");

	matrixID = glGetUniformLocation(programID, "MVP");


	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	do {
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);

		glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP.v[0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}	while (glfwWindowShouldClose(window) == 0 && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);
	
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &vertexArrayID);
	
	glfwTerminate();
	return 0;
}