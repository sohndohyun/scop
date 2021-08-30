#pragma once

#define vX v[0]
#define vY v[1]
#define vZ v[2]
#define vW v[3]

typedef struct s_vec4{
	float v[4];
}t_vec4;

typedef struct s_vec3{
	float v[3];
}t_vec3;

typedef struct s_mat4{
	float v[16];
}t_mat4;

float radian(float angle);
t_vec4 vec4(float x, float y, float z, float w);
t_vec3 vec3(float x, float y, float z);
t_vec3 vec3_normalize(t_vec3 vec);
t_vec3 vec3_sub(t_vec3 a, t_vec3 b);
t_vec3 vec3_cross(t_vec3 a, t_vec3 b);
float vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3 vec3_negate(t_vec3 a);
t_vec4 matXvec(t_mat4 mat, t_vec4 vec);
t_mat4 translate(t_vec3 v3);
t_mat4 idmat();
t_mat4 scale(float x, float y, float z);
t_mat4 rotate(float angle, t_vec3 axis);
t_mat4 lookAt(t_vec3 eye, t_vec3 at, t_vec3 up);
t_mat4 perspective(float fov, float aspect, float near_plane, float far_plane);
t_mat4 mat4_mult(t_mat4 left, t_mat4 right);
void matlog(t_mat4 mat);