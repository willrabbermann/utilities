#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <tgmath.h>
#include <string.h>

#include "gmath.h"

// Clamp target between min & max

int 
iclamp(int target, int min, int max)
{
	if (target > max) return max;
	else if (target < min) return min;
	else return target;
}

float
fclamp(float target, float min, float max)
{
	if (target > max) return max;
	else if (target < min) return min;
	else return target;
}

double
dclamp(double target, double min, double max)
{
	if (target > max) return max;
	else if (target < min) return min;
	else return target;
}

// 2 point float vector //

vec2f 
*newvec2f(float x, float y)
{
	vec2f *new = malloc(sizeof(vec2f));
	new->x = x;
	new->y = y;
		
	return new;
}

void
printvec2f(vec2f *v)
{
	printf("{ %f, %f }\n", v->x, v->y);
}

void
addvec2f(vec2f *src, vec2f *change)
{
	src->x = src->x + change->x;
	src->y = src->y + change->y;
}

void
scalevec2f(vec2f *src, float scalar)
{
	src->x = src->x * scalar;
	src->y = src->y * scalar;
}

void
rotatevec2f(vec2f *origin, vec2f *vec, float degrees)
// Rotate vec counter clockwise about the origin
{
	float angle = deg2rad(degrees);
	float x, y, x_rot, y_rot;
	x = vec->x - origin->x;
	y = vec->y - origin->y;
	x_rot = x * cos(angle) - y * sin(angle);
	y_rot = -x * sin(angle) + y * cos(angle);
	vec->x = (x_rot + origin->x);
	vec->y = (y_rot + origin->y);
}

// 3 point float vector //

vec3f 
*newvec3f(float x, float y, float z)
{
	vec3f *new = malloc(sizeof(vec3f));
	new->x = x;
	new->y = y;
	new->z = z;
		
	return new;
}

void
printvec3f(vec3f *v)
{
	printf("{ %f, %f, %f }\n", v->x, v->y, v->z);
}

void
opvec3f(vec3f *a, vec3f *b, vec3f *result, char op)
{
	switch(op)
	{
		case '+':
			result->x = (a->x + b->x);
			result->y = (a->y + b->y);
			result->z = (a->z + b->z);
			break;
		case '-':
			result->x = (a->x - b->x);
			result->y = (a->y - b->y);
			result->z = (a->z - b->z);
			break;
		case '*':
			result->x = (a->x * b->x);
			result->y = (a->y * b->y);
			result->z = (a->z * b->z);
			break;
		case '/':
			result->x = (a->x / b->x);
			result->y = (a->y / b->y);
			result->z = (a->z / b->z);
	}
}

void
addvec3f(vec3f *src, vec3f *change)
{
	src->x = src->x + change->x;
	src->y = src->y + change->y;
	src->z = src->z + change->z;
}

void
scalevec3f(vec3f *src, float scalar)
{
	src->x = src->x * scalar;
	src->y = src->y * scalar;
	src->z = src->z * scalar;
}

void
multiplyvec3f3x3(vec3f *a, float3x3 *b, vec3f *result)
{
	if (a == result)
	{
		vec3f *tmp = malloc(sizeof *tmp);
		tmp->x = a->x * (*b)[0][0] + a->y * (*b)[1][0] + a->z * (*b)[2][0];
		tmp->y = a->x * (*b)[0][1] + a->y * (*b)[1][1] + a->z * (*b)[2][1];
		tmp->z = a->x * (*b)[0][2] + a->y * (*b)[1][2] + a->z * (*b)[2][2];
		memcpy(result, tmp, sizeof *tmp);
		free(tmp);
	}
	else
	{
		result->x = a->x * (*b)[0][0] + a->y * (*b)[1][0] + a->z * (*b)[2][0];
		result->y = a->x * (*b)[0][1] + a->y * (*b)[1][1] + a->z * (*b)[2][1];
		result->z = a->x * (*b)[0][2] + a->y * (*b)[1][2] + a->z * (*b)[2][2];
	}
}

void
rotatevec3f(vec3f *origin, vec3f *vec, float degrees, char axis)
{
	float angle = deg2rad(degrees);
	float3x3 *rot_matrix = malloc(sizeof(*rot_matrix));
	switch(axis)
	{
		case 'x':
			memcpy(rot_matrix, &(float3x3){
					{ 1, 0, 0 },
					{ 0, -sin(angle), cos(angle) },
					{ 0, cos(angle), sin(angle) }},
					sizeof(float3x3));
			break;
		case 'y':
			memcpy(rot_matrix, &(float3x3){
					{ sin(angle), 0, cos(angle) },
					{ 0, 1, 0 },
					{ cos(angle), 0, -sin(angle) }},
					sizeof(float3x3));
			break;
		case 'z':
			memcpy(rot_matrix, &(float3x3){
					{ -sin(angle), cos(angle), 0 },
					{ cos(angle), sin(angle), 0 },
					{ 0, 0, 1 }},
					sizeof(float3x3));			
			break;
		default:
			fprintf(stderr, "rotatevec3f ERROR: '%c' is an invalid axis value.\n", axis);
			free(rot_matrix);
			return;
	}
	vec3f *offset_vec = malloc(sizeof *offset_vec); 
	opvec3f(vec, origin, offset_vec, '-');
	multiplyvec3f3x3(offset_vec, rot_matrix, offset_vec);
	opvec3f(offset_vec, origin, offset_vec, '+');
	memcpy(vec, offset_vec, sizeof(*offset_vec));
	free(offset_vec);
	free(rot_matrix);
}

void
eyefloat3x3(float3x3 a)
{
	memset(a, 0, sizeof(float3x3));
	a[0][0] = 1;
	a[1][1] = 1;
	a[2][2] = 1;
}

void 
printfloat3x3(float3x3 a)
{
	for (int b = 0; b < 3; b++)
	{
		for (int c = 0; c < 3; c++)
			printf("[%f]", a[b][c]);
		printf("\n");
	}
}

void
multiplyfloat3x3(float3x3 a, float3x3 b, float3x3 result)
{
	for (int c = 0; c < 3; c++)
		for (int d = 0; d < 3; d++)
			result[c][d] = a[c][d] * b[c][d];
}

void 
addfloat3x3(float3x3 a, float3x3 b, float3x3 result)
{
	for (int c = 0; c < 3; c++)
		for (int d = 0; d < 3; d++)
			result[c][d] = a[c][d] + b[c][d];
}

// 4 point float vector //

vec4f
*newvec4f(float x, float y, float z, float w)
{
	vec4f *new = malloc(sizeof(vec4f));
	new->x = x;
	new->y = y;
	new->z = z;
	new->w = w;
		
	return new;
}

void
printvec4f(vec4f *v)
{
	printf("{ %f, %f, %f, %f }\n", v->x, v->y, v->z, v->w);
}

void
addvec4f(vec4f *src, vec4f *change)
{
	src->x = src->x + change->x;
	src->y = src->y + change->y;
	src->z = src->z + change->z;
	src->w = src->w + change->w;
}

void
scalevec4f(vec4f *src, float scalar)
{
	src->x = src->x * scalar;
	src->y = src->y * scalar;
	src->z = src->z * scalar;
	src->w = src->w * scalar;
}
