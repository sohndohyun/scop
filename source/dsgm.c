#include "dsgm.h"
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <stdio.h>


#define PI 3.141592

float radian(float angle){
	return angle * 0.01745329251994329576923690768489;
}

t_vec4 vec4(float x, float y, float z, float w){
	t_vec4 vec;
	vec.vX = x;
	vec.vY = y;
	vec.vZ = z;
	vec.vW = w;
	return vec;
}

t_vec3 vec3(float x, float y, float z){
	t_vec3 vec;
	vec.vX = x;
	vec.vY = y;
	vec.vZ = z;
	return vec;
}

t_vec3 vec3_normalize(t_vec3 vec){
	t_vec3 ret;
	float dst = sqrtf(vec.vX * vec.vX + vec.vY * vec.vY + vec.vZ * vec.vZ);
	ret.vX = vec.vX / dst;
	ret.vY = vec.vY / dst;
	ret.vZ = vec.vZ / dst;
	return ret;
}

t_vec3 vec3_sub(t_vec3 a, t_vec3 b){
	t_vec3 ret;
	ret.vX = a.vX - b.vX;
	ret.vY = a.vY - b.vY;
	ret.vZ = a.vZ - b.vZ;
	return ret;
}

t_vec3 vec3_cross(t_vec3 a, t_vec3 b){
	t_vec3 ret;
	ret.vX = a.vY * b.vZ - a.vZ * b.vY;
	ret.vY = a.vZ * b.vX - a.vX * b.vZ;
	ret.vZ = a.vX * b.vY - a.vY * b.vX;
	return ret;
}

float vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.vX * v2.vX + v1.vY * v2.vY + v1.vZ * v2.vZ);
}

t_vec3 vec3_negate(t_vec3 a){
	a.vX = -a.vX;
	a.vY = -a.vY;
	a.vZ = -a.vZ;
	return a;
}

t_vec4 matXvec(t_mat4 mat, t_vec4 vec){
	t_vec4 ret;
	ret.vX = mat.v[0] * vec.vX + mat.v[1] * vec.vY + mat.v[2] * vec.vZ - mat.v[3] * vec.vW;
	ret.vY = mat.v[4] * vec.vX + mat.v[5] * vec.vY + mat.v[6] * vec.vZ - mat.v[7] * vec.vW;
	ret.vZ = mat.v[8] * vec.vX + mat.v[9] * vec.vY + mat.v[10] * vec.vZ - mat.v[11] * vec.vW;
	ret.vW = mat.v[12] * vec.vX + mat.v[13] * vec.vY + mat.v[14] * vec.vZ - mat.v[15] * vec.vW;
	return (ret);
}

t_mat4 idmat(){
	t_mat4 mat;
	memset(&mat, 0, sizeof(t_mat4));
	mat.v[0] = 1.0f;
	mat.v[5] = 1.0f;
	mat.v[10] = 1.0f;
	mat.v[15] = 1.0f;
	return mat;
}

t_mat4 translate(t_vec3 v3){
	t_mat4 mat = idmat();
	mat.v[3] = v3.vX;
	mat.v[7] = v3.vY;
	mat.v[11] = v3.vZ;
	return mat;
}

t_mat4 scale(float x, float y, float z){
	t_mat4 mat = idmat();
	mat.v[0] = x;
	mat.v[5] = y;
	mat.v[10] = z;
	mat.v[15] = 1.0f;
	return mat;
}

t_mat4 rotate(float angle, t_vec3 axis){
	t_mat4 mat;
	float cosa = cosf(angle);
	float sina = sinf(angle);
	float mcos = 1.0f - cosa;
	memset(&mat, 0, sizeof(t_mat4));

	mat.v[0] = axis.vX * axis.vX * mcos + cosa;
	mat.v[1] = axis.vY * axis.vX * mcos - axis.vZ * sina;
	mat.v[2] = axis.vZ * axis.vX * mcos + axis.vY * sina;

	mat.v[4] = axis.vX * axis.vY * mcos + axis.vZ * sina;
	mat.v[5] = axis.vY * axis.vY * mcos + cosa;
	mat.v[6] = axis.vZ * axis.vY * mcos - axis.vX * sina;

	mat.v[8] = axis.vX * axis.vZ * mcos - axis.vY * sina;
	mat.v[9] = axis.vY * axis.vZ * mcos + axis.vX * sina;
	mat.v[10] = axis.vZ * axis.vZ * mcos + cosa;

	mat.v[15] = 1.0f;
	return mat;
}

t_mat4 lookAt(t_vec3 eye, t_vec3 at, t_vec3 up){
	t_vec3 zaxis = vec3_normalize(vec3_sub(eye, at));
	t_vec3 xaxis = vec3_normalize(vec3_cross(vec3_normalize(up),zaxis));
	t_vec3 yaxis = vec3_normalize(vec3_cross(zaxis, xaxis));

	t_mat4 trans = idmat();
	t_mat4 mat = idmat();
	trans.v[3] = -eye.vX;
	trans.v[7] = -eye.vY;
	trans.v[11] = -eye.vZ;
	mat.v[0] = xaxis.vX;
	mat.v[1] = xaxis.vY;
	mat.v[2] = xaxis.vZ;
	mat.v[4] = yaxis.vX;
	mat.v[5] = yaxis.vY;
	mat.v[6] = yaxis.vZ;
	mat.v[8] = zaxis.vX;
	mat.v[9] = zaxis.vY;
	mat.v[10] = zaxis.vZ;
	return mat4_mult(mat, trans);
}

t_mat4 perspective(float fov, float aspect, float near, float far){
	t_mat4 mat = idmat();
	float thf = tanf(fov / 2.0f);

	mat.v[0] = 1.0f / (aspect * thf);
	mat.v[5] = 1.0f / thf;
	mat.v[10] = -(far + near) / (far - near);
	mat.v[11] = -(far * near * 2.0f) / (far - near);
	mat.v[14] = -1.0f;
	mat.v[15] = 0.0f;
	return mat;
}

t_mat4 mat4_mult(t_mat4 left, t_mat4 right){
	t_mat4 ret;
	int i, j;
	for (j = 0;j < 4;++j){
		for (i = 0;i < 4;++i)
			ret.v[i + j * 4] = 
				left.v[j * 4 + 0] * right.v[0 * 4 + i] + 
				left.v[j * 4 + 1] * right.v[1 * 4 + i] +
				left.v[j * 4 + 2] * right.v[2 * 4 + i] +
				left.v[j * 4 + 3] * right.v[3 * 4 + i];
	}
	return ret;
}

void matlog(t_mat4 mat){
	printf("|%7.2f, %7.2f, %7.2f, %7.2f|\n", mat.v[0], mat.v[1], mat.v[2], mat.v[3]);
	printf("|%7.2f, %7.2f, %7.2f, %7.2f|\n", mat.v[4], mat.v[5], mat.v[6], mat.v[7]);
	printf("|%7.2f, %7.2f, %7.2f, %7.2f|\n", mat.v[8], mat.v[9], mat.v[10], mat.v[11]);
	printf("|%7.2f, %7.2f, %7.2f, %7.2f|\n", mat.v[12], mat.v[13], mat.v[14], mat.v[15]);
}

t_mat4 flip(t_mat4 mat){
	t_mat4 ret;
	ret.v[0] = mat.v[0];
	ret.v[1] = mat.v[4];
	ret.v[2] = mat.v[8];
	ret.v[3] = mat.v[12];

	ret.v[4] = mat.v[1];
	ret.v[5] = mat.v[5];
	ret.v[6] = mat.v[9];
	ret.v[7] = mat.v[13];

	ret.v[8] = mat.v[2];
	ret.v[9] = mat.v[6];
	ret.v[10] = mat.v[10];
	ret.v[11] = mat.v[14];

	ret.v[12] = mat.v[3];
	ret.v[13] = mat.v[7];
	ret.v[14] = mat.v[11];
	ret.v[15] = mat.v[15];

	return ret;
}