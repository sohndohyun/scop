#include "control.h"

#include <math.h>

#include <GLFW/glfw3.h>
extern GLFWwindow* window;

#define PI 3.14159265f

t_mat4 g_viewMatrix;
t_mat4 g_projectionMatrix;

t_vec3 g_position;
float g_horizontalAngle;
float g_verticalAngle;
float g_initialFoV;
float g_speed;
float g_mouseSpeed;

void initControl(){
	g_position = vec3(0, 0, 5);
	g_horizontalAngle = PI;
	g_verticalAngle = 0;
	g_initialFoV = 45.0f;
	g_speed = 4.0f;
	g_mouseSpeed = 0.003f;
}

void computeMatricesFromInputs(float deltaTime){
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	glfwSetCursorPos(window, 1024/2, 768/2);
	g_horizontalAngle += g_mouseSpeed * (float)(1024/2 - xpos);
	g_verticalAngle += g_mouseSpeed * (float)(768/2 - ypos);
	t_vec3 direction = vec3( 
		cosf(g_verticalAngle) * sinf(g_horizontalAngle),
		sinf(g_verticalAngle),
		cosf(g_verticalAngle) * cosf(g_horizontalAngle));
	
	t_vec3 right = vec3(
		sinf(g_horizontalAngle - PI/2.f),
		0,
		cosf(g_horizontalAngle - PI/2.f));
	
	t_vec3 up = vec3_cross(right, direction);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		g_position = vec3_add(g_position, vec3_mult(direction, deltaTime * g_speed));
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		g_position = vec3_sub(g_position, vec3_mult(direction, deltaTime * g_speed));
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		g_position = vec3_add(g_position, vec3_mult(right, deltaTime * g_speed));
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		g_position = vec3_sub(g_position, vec3_mult(right, deltaTime * g_speed));

	float FoV = g_initialFoV;


	g_projectionMatrix = perspective(radian(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	g_viewMatrix = lookAt(g_position, vec3_add(g_position, direction), up);
}

t_mat4 getProjectionMatrix(){
	return g_projectionMatrix;
}

t_mat4 getViewMatrix(){
	return g_viewMatrix;
}