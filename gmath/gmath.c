#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <math.h>

#include "gmath.h"

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
opvec2f(vec2f *a, vec2f *b, vec2f *result, char op)
// Preform op on two vec
{
	switch(op)
	{
		case '+':
			result->x = (a->x + b->x);
			result->y = (a->y + b->y);
			break;
		case '-':
			result->x = (a->x - b->x);
			result->y = (a->y - b->y);
			break;
		case '*':
			result->x = (a->x * b->x);
			result->y = (a->y * b->y);
			break;
		case '/':
			result->x = (a->x / b->x);
			result->y = (a->y / b->y);
	}
}

void
scalar_op_vec2f(vec2f *a, float scalar, vec2f *result, char op)
// Preform op on vec using scalar
{
	switch (op)
	{
		case '+': 
			result->x = a->x + scalar;
			result->y = a->y + scalar;
			break;
		case '-':
			result->x = a->x - scalar;
			result->y = a->y - scalar;
			break;
		case '*':
			result->x = a->x * scalar;
			result->y = a->y * scalar;
			break;
		case '/':
			result->x = a->x / scalar;
			result->y = a->y / scalar;
	}
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
// Preform op on two vec
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
scalar_op_vec3f(vec3f *a, float scalar, vec3f *result, char op)
// Preform op on vec using scalar
{
	switch (op)
	{
		case '+': 
			result->x = a->x + scalar;
			result->y = a->y + scalar;
			result->z = a->z + scalar;
			break;
		case '-':
			result->x = a->x - scalar;
			result->y = a->y - scalar;
			result->z = a->z - scalar;
			break;
		case '*':
			result->x = a->x * scalar;
			result->y = a->y * scalar;
			result->z = a->z * scalar;
			break;
		case '/':
			result->x = a->x / scalar;
			result->y = a->y / scalar;
			result->z = a->z / scalar;
	}
}

void
rotatevec3f(vec3f *origin, vec3f *vec, float degrees, char axis)
// Rotate vec counter clockwise about the origin on axis
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
			fprintf(stderr, 
					"rotatevec3f ERROR: '%c' is an invalid axis value.\n", 
					axis);
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
multiplyvec3f3x3(vec3f *a, float3x3 *b, vec3f *result)
//Preform dot product a*b output vec3f
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
eyefloat2x2(float2x2 a)
{
	memset(a, 0, sizeof(float2x2));
	for (int i = 0; i < 2; i++)
		a[i][i] = 1;
}

void
eyefloat3x3(float3x3 a)
{
	memset(a, 0, sizeof(float3x3));
	for (int i = 0; i < 3; i++)
		a[i][i] = 1;
}

void
eyefloat4x4(float4x4 a)
{
	memset(a, 0, sizeof(float4x4));
	for (int i = 0; i < 4; i++)
		a[i][i] = 1;
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
opvec4f(vec4f *a, vec4f *b, vec4f *result, char op)
// Preform op on two vec
{
	switch(op)
	{
		case '+':
			result->x = (a->x + b->x);
			result->y = (a->y + b->y);
			result->z = (a->z + b->z);
			result->w = (a->w + b->w);
			break;
		case '-':
			result->x = (a->x - b->x);
			result->y = (a->y - b->y);
			result->z = (a->z - b->z);
			result->w = (a->w - b->w);
			break;
		case '*':
			result->x = (a->x * b->x);
			result->y = (a->y * b->y);
			result->z = (a->z * b->z);
			result->w = (a->w * b->w);
			break;
		case '/':
			result->x = (a->x / b->x);
			result->y = (a->y / b->y);
			result->z = (a->z / b->z);
			result->w = (a->w / b->w);
	}
}

void
scalar_op_vec4f(vec4f *a, float scalar, vec4f *result, char op)
// Preform op on vec using scalar
{
	switch (op)
	{
		case '+': 
			result->x = a->x + scalar;
			result->y = a->y + scalar;
			result->z = a->z + scalar;
			result->w = a->w + scalar;
			break;
		case '-':
			result->x = a->x - scalar;
			result->y = a->y - scalar;
			result->z = a->z - scalar;
			result->w = a->w - scalar;
			break;
		case '*':
			result->x = a->x * scalar;
			result->y = a->y * scalar;
			result->z = a->z * scalar;
			result->w = a->w * scalar;
			break;
		case '/':
			result->x = a->x / scalar;
			result->y = a->y / scalar;
			result->z = a->z / scalar;
			result->w = a->w / scalar;
	}
}
