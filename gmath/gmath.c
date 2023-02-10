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

float
distancevec2f(vec2f a, vec2f b)
{
	return sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2));
}

void
printvec2f(vec2f v)
{
	printf("{ %f, %f }\n", v.x, v.y);
}

void
opvec2f(vec2f a, vec2f b, vec2f *result, char op)
// Preform op on two vec
{
	switch(op)
	{
		case '+':
			result->x = (a.x + b.x);
			result->y = (a.y + b.y);
			break;
		case '-':
			result->x = (a.x - b.x);
			result->y = (a.y - b.y);
			break;
		case '*':
			result->x = (a.x * b.x);
			result->y = (a.y * b.y);
			break;
		case '/':
			result->x = (a.x / b.x);
			result->y = (a.y / b.y);
	}
}

void
scalar_op_vec2f(vec2f a, float scalar, vec2f *result, char op, char axis)
// Preform op on vec using scalar on axis (default = all)
{
	switch (op)
	{
		case '+': 
			switch (axis)
			{
				case 'x':
					result->x = a.x + scalar;
					break;
				case 'y':
					result->y = a.y + scalar;
					break;
				default:
					result->x = a.x + scalar;
					result->y = a.y + scalar;
			}
			break;
		case '-':
			switch (axis)
			{
				case 'x':
					result->x = a.x - scalar;
					break;
				case 'y':
					result->y = a.y - scalar;
					break;
				default:
					result->x = a.x - scalar;
					result->y = a.y - scalar;
			}
			break;
		case '*':
			switch (axis)
			{
				case 'x':
					result->x = a.x * scalar;
					break;
				case 'y':
					result->y = a.y * scalar;
					break;
				default:
					result->x = a.x * scalar;
					result->y = a.y * scalar;
			}
			break;
		case '/':
			switch (axis)
			{
				case 'x':
					result->x = a.x / scalar;
					break;
				case 'y':
					result->y = a.y / scalar;
					break;
				default:
					result->x = a.x / scalar;
					result->y = a.y / scalar;
			}
	}
}

void
rotatevec2f(vec2f origin, vec2f *vec, float degrees)
// Rotate vec counter clockwise about the origin
{
	float angle = deg2rad(degrees);
	float x, y, x_rot, y_rot;
	x = vec->x - origin.x;
	y = vec->y - origin.y;
	x_rot = x * cos(angle) - y * sin(angle);
	y_rot = -x * sin(angle) + y * cos(angle);
	vec->x = (x_rot + origin.x);
	vec->y = (y_rot + origin.y);
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

float
distancevec3f(vec3f a, vec3f b)
{
	return sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2) 
			+ pow((b.z - a.z), 2));
}

void
printvec3f(vec3f v)
{
	printf("{ %f, %f, %f }\n", v.x, v.y, v.z);
}

void
opvec3f(vec3f a, vec3f b, vec3f *result, char op)
// Preform op on two vec
{
	switch(op)
	{
		case '+':
			result->x = (a.x + b.x);
			result->y = (a.y + b.y);
			result->z = (a.z + b.z);
			break;
		case '-':
			result->x = (a.x - b.x);
			result->y = (a.y - b.y);
			result->z = (a.z - b.z);
			break;
		case '*':
			result->x = (a.x * b.x);
			result->y = (a.y * b.y);
			result->z = (a.z * b.z);
			break;
		case '/':
			result->x = (a.x / b.x);
			result->y = (a.y / b.y);
			result->z = (a.z / b.z);
	}
}

void
scalar_op_vec3f(vec3f a, float scalar, vec3f *result, char op, char axis)
// Preform op on vec using scalar on axis (default = all)
{
	switch (op)
	{
		case '+': 
			switch (axis)
			{
				case 'x':
					result->x = a.x + scalar;
					break;
				case 'y':
					result->y = a.y + scalar;
					break;
				case 'z':
					result->z = a.z + scalar;
					break;
				default:
					result->x = a.x + scalar;
					result->y = a.y + scalar;
					result->z = a.z + scalar;
			}
			break;
		case '-':
			switch (axis)
			{
				case 'x':
					result->x = a.x - scalar;
					break;
				case 'y':
					result->y = a.y - scalar;
					break;
				case 'z':
					result->z = a.z - scalar;
					break;
				default:
					result->x = a.x - scalar;
					result->y = a.y - scalar;
					result->z = a.z - scalar;
			}
			break;
		case '*':
			switch (axis)
			{
				case 'x':
					result->x = a.x * scalar;
					break;
				case 'y':
					result->y = a.y * scalar;
					break;
				case 'z':
					result->z = a.z * scalar;
					break;
				default:
					result->x = a.x * scalar;
					result->y = a.y * scalar;
					result->z = a.z * scalar;
			}
			break;
		case '/':
			switch (axis)
			{
				case 'x':
					result->x = a.x / scalar;
					break;
				case 'y':
					result->y = a.y / scalar;
					break;
				case 'z':
					result->z = a.z / scalar;
					break;
				default:
					result->x = a.x / scalar;
					result->y = a.y / scalar;
					result->z = a.z / scalar;
			}
	}
}

void
rotatevec3f(vec3f origin, vec3f *vec, float degrees, char axis)
// Rotate vec counter clockwise about the origin on axis
{
	float angle = deg2rad(degrees);
	float3x3 *rot_matrix = malloc(sizeof(*rot_matrix));
	switch(axis)
	{
		case 'x':
			memcpy(rot_matrix, &(float3x3){
					{ 1,			0,			0 },
					{ 0,   cos(angle), -sin(angle)},
					{ 0,   sin(angle),	cos(angle)}},
					sizeof(float3x3));
			break;
		case 'y':
			memcpy(rot_matrix, &(float3x3){
					{ cos(angle),	0, sin(angle) },
					{ 0,			1,			0 },
					{ -sin(angle),	0, cos(angle) }},
					sizeof(float3x3));
			break;
		case 'z':
			memcpy(rot_matrix, &(float3x3){
					{  cos(angle), -sin(angle), 0 },
					{  sin(angle),	cos(angle), 0 },
					{  0,			0,			1 }},
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
	opvec3f(*vec, origin, offset_vec, '-');
	dotproduct_3x3_vec3f(*rot_matrix, offset_vec, offset_vec);
	opvec3f(*offset_vec, origin, offset_vec, '+');
	memcpy(vec, offset_vec, sizeof(*offset_vec));
	free(offset_vec);
	free(rot_matrix);
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

float
distancevec4f(vec4f a, vec4f b)
{
	return sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2) 
			+ pow((b.z - a.z), 2) + pow((b.w - a.w), 2));
}

void
printvec4f(vec4f v)
{
	printf("{ %f, %f, %f, %f }\n", v.x, v.y, v.z, v.w);
}

void
opvec4f(vec4f a, vec4f b, vec4f *result, char op)
// Preform op on two vec
{
	switch(op)
	{
		case '+':
			result->x = (a.x + b.x);
			result->y = (a.y + b.y);
			result->z = (a.z + b.z);
			result->w = (a.w + b.w);
			break;
		case '-':
			result->x = (a.x - b.x);
			result->y = (a.y - b.y);
			result->z = (a.z - b.z);
			result->w = (a.w - b.w);
			break;
		case '*':
			result->x = (a.x * b.x);
			result->y = (a.y * b.y);
			result->z = (a.z * b.z);
			result->w = (a.w * b.w);
			break;
		case '/':
			result->x = (a.x / b.x);
			result->y = (a.y / b.y);
			result->z = (a.z / b.z);
			result->w = (a.w / b.w);
	}
}

void
scalar_op_vec4f(vec4f a, float scalar, vec4f *result, char op, char axis)
// Preform op on vec using scalar on axis (default = all)
{
	switch (op)
	{
		case '+': 
			switch (axis)
			{
				case 'x':
					result->x = a.x + scalar;
					break;
				case 'y':
					result->y = a.y + scalar;
					break;
				case 'z':
					result->z = a.z + scalar;
					break;
				case 'w':
					result->w = a.w + scalar;
					break;
				default:
					result->x = a.x + scalar;
					result->y = a.y + scalar;
					result->z = a.z + scalar;
					result->w = a.w + scalar;
			}
			break;
		case '-':
			switch (axis)
			{
				case 'x':
					result->x = a.x - scalar;
					break;
				case 'y':
					result->y = a.y - scalar;
					break;
				case 'z':
					result->z = a.z - scalar;
					break;
				case 'w':
					result->w = a.w - scalar;
					break;
				default:
					result->x = a.x - scalar;
					result->y = a.y - scalar;
					result->z = a.z - scalar;
					result->w = a.w - scalar;
			}
			break;
		case '*':
			switch (axis)
			{
				case 'x':
					result->x = a.x * scalar;
					break;
				case 'y':
					result->y = a.y * scalar;
					break;
				case 'z':
					result->z = a.z * scalar;
					break;
				case 'w':
					result->w = a.w * scalar;
					break;
				default:
					result->x = a.x * scalar;
					result->y = a.y * scalar;
					result->z = a.z * scalar;
					result->w = a.w * scalar;
			}
			break;
		case '/':
			switch (axis)
			{
				case 'x':
					result->x = a.x / scalar;
					break;
				case 'y':
					result->y = a.y / scalar;
					break;
				case 'z':
					result->z = a.z / scalar;
					break;
				case 'w':
					result->w = a.w / scalar;
					break;
				default:
					result->x = a.x / scalar;
					result->y = a.y / scalar;
					result->z = a.z / scalar;
					result->w = a.w / scalar;
			}
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
printfloat2x2(float2x2 a)
{
	for (int b = 0; b < 2; b++)
	{
		for (int c = 0; c < 2; c++)
			printf("[%f]", a[b][c]);
		printf("\n");
	}
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
printfloat4x4(float4x4 a)
{
	for (int b = 0; b < 4; b++)
	{
		for (int c = 0; c < 4; c++)
			printf("[%f]", a[b][c]);
		printf("\n");
	}
}

void
opfloat3x3(float3x3 a, float3x3 b, float3x3 result, char op)
// Preform a op b
{
	for (int c = 0; c < 3; c++)
		for (int d = 0; d < 3; d++)
			switch (op)
			{
				case '+':
					result[c][d] = a[c][d] + b[c][d];
					break;
				case '-':
					result[c][d] = a[c][d] - b[c][d];
					break;
				case '*':
					result[c][d] = a[c][d] * b[c][d];
					break;
				case '/':
					result[c][d] = a[c][d] / b[c][d];
			}
}

void dotproduct_2x2_vec2f(float2x2 a, vec2f *b, vec2f *result)
// Preform dot product a*b output vec2f
// vec2f 'b' is treated as a column matrix
{
	if (b == result)
	{
		vec2f *tmp = malloc(sizeof *tmp);
		tmp->x = a[0][0] * b->x + a[0][1] * b->y;
		tmp->y = a[1][0] * b->x + a[1][1] * b->y;
		memcpy(result, tmp, sizeof *tmp);
		free(tmp);
	}
	else
	{
		result->x = a[0][0] * b->x + a[0][1] * b->y;
		result->y = a[1][0] * b->x + a[1][1] * b->y;
	}

}

void
dotproduct_3x3_vec3f(float3x3 a, vec3f *b, vec3f *result)
// Preform dot product a*b output vec3f
// vec3f 'b' is treated as a column matrix
{
	if (b == result)
	{
		vec3f *tmp = malloc(sizeof *tmp);
		tmp->x = a[0][0] * b->x + a[0][1] * b->y + a[0][2] * b->z;
		tmp->y = a[1][0] * b->x + a[1][1] * b->y + a[1][2] * b->z;
		tmp->z = a[2][0] * b->x + a[2][1] * b->y + a[2][2] * b->z;
		memcpy(result, tmp, sizeof *tmp);
		free(tmp);
	}
	else
	{
		result->x = a[0][0] * b->x + a[0][1] * b->y + a[0][2] * b->z;
		result->y = a[1][0] * b->x + a[1][1] * b->y + a[1][2] * b->z;
		result->z = a[2][0] * b->x + a[2][1] * b->y + a[2][2] * b->z;
	}
}

void
dotproduct_4x4_vec4f(float4x4 a, vec4f *b, vec4f *result)
// Preform dot product a*b output vec4f
// vec4f 'b' is treated as a column matrix
{
	if (b == result)
	{
		vec4f *tmp = malloc(sizeof *tmp);
		tmp->x = a[0][0] * b->x + a[0][1] * b->y + a[0][2] * b->z + a[0][3] * b->w;
		tmp->y = a[1][0] * b->x + a[1][1] * b->y + a[1][2] * b->z + a[1][3] * b->w;
		tmp->z = a[2][0] * b->x + a[2][1] * b->y + a[2][2] * b->z + a[2][3] * b->w;
		tmp->w = a[3][0] * b->x + a[3][1] * b->y + a[3][2] * b->z + a[3][3] * b->w;
		memcpy(result, tmp, sizeof *tmp);
		free(tmp);
	}
	else
	{
		result->x = a[0][0] * b->x + a[0][1] * b->y + a[0][2] * b->z + a[0][3] * b->w;
		result->y = a[1][0] * b->x + a[1][1] * b->y + a[1][2] * b->z + a[1][3] * b->w;
		result->z = a[2][0] * b->x + a[2][1] * b->y + a[2][2] * b->z + a[2][3] * b->w;
		result->w = a[3][0] * b->x + a[3][1] * b->y + a[3][2] * b->z + a[3][3] * b->w;
	}
}

void 
calc_global_g_object(g_object *obj) 
{
	vert3f rotated_pos;
	rotated_pos.x = obj->rot.w * obj->localpos.x + obj->rot.y * obj->localpos.z 
		- obj->rot.z * obj->localpos.y;
	rotated_pos.y = obj->rot.w * obj->localpos.y + obj->rot.z * obj->localpos.x 
		- obj->rot.x * obj->localpos.z;
	rotated_pos.z = obj->rot.w * obj->localpos.z + obj->rot.x * obj->localpos.y 
		- obj->rot.y * obj->localpos.x;
	float tmp_x = -obj->rot.x * obj->localpos.x - obj->rot.y * obj->localpos.y 
		- obj->rot.z * obj->localpos.z;
	rotated_pos.x += tmp_x * obj->rot.x;
	rotated_pos.y += tmp_x * obj->rot.y;
	rotated_pos.z += tmp_x * obj->rot.z;

	obj->globalpos = rotated_pos;
}

void 
set_quaternion_g_object(g_object *obj, float degree, float x, float y, float z)
{
	float angle = deg2rad(fmod(degree, 360.0f));
	float length = sqrt(x*x + y*y + z*z);
	float sA = sin(angle);
	float cA = cos(angle);
	memcpy(&obj->rot, 
		&(quaternion)
		{ x * sA / length, y * sA / length, z * sA / length, cA },
		sizeof(quaternion)); 
	float norm = sqrt(pow(obj->rot.x, 2) + pow(obj->rot.y, 2) 
			+ pow(obj->rot.z, 2) + pow(obj->rot.w, 2));
	obj->rot.x /= norm;
	obj->rot.y /= norm;
	obj->rot.z /= norm;
	obj->rot.w /= norm;
	calc_global_g_object(obj);
}

