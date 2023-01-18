#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
transformvec2f(vec2f *src, vec2f *change)
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
transformvec3f(vec3f *src, vec3f *change)
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
transformvec4f(vec4f *src, vec4f *change)
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
