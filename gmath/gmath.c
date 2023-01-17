#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "gmath.h"

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

vec4f
*newvec4f(float x, float y, float z, float w)
// Initialize a new vec4f
{
	vec4f *new = malloc(sizeof(vec4f));
	new->x = x;
	new->y = y;
	new->z = z;
	new->w = w;
		
	return new;
}

void
transform(vec4f *left, vec4f *right)
// transform left by right
{
	left->x = left->x + right->x;
	left->y = left->y + right->y;
	left->z = left->z + right->z;
	left->w = left->w + right->w;
}

void
scale(vec4f *left, float right)
// scale left by right
{
	left->x = left->x * right;
	left->y = left->y * right;
	left->z = left->z * right;
	left->w = left->w * right;
}

void
printvec4f(vec4f *v)
{
	printf("{ %f, %f, %f, %f }\n", v->x, v->y, v->z, v->w);
}
