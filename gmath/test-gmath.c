#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <tgmath.h>

#include "gmath.h"

void
Vector_Scaling_Test()
{
	printf("Vector transformation/scaling tests\n");
	vec4f *v = newvec4f(0.0f, 1.5f, 1.0f, 1.0f);
	printf("\nv = ");
	printvec4f(v);
	vec4f *b = newvec4f(1.0f, 2.0f, 3.0f, 0.0f);
	printf("b = ");
	printvec4f(b);
	printf("opvec4f(v, b, v, '+')\nv = ");
	opvec4f(v, b, v, '+');
	printvec4f(v);
	free(b);

	float *c = malloc(sizeof(float));
	*c = 2.0f;
	printf("scalar_op_vec4f(v, %f, v, '*')\nv = ", *c);
	scalar_op_vec4f(v, *c, v, '*');
	printvec4f(v);
	free(v);
	free(c);
}

void
Vec2f_Rotation_Test()
{
	printf("\nVec2f rotation tests\n");
	vec2f *v2 = newvec2f(3.0f, 2.0f);
	vec2f *o = newvec2f(3.0f, 0.0f);
	printf("\nv2 = ");
	printvec2f(v2);
	printf("o = ");
	printvec2f(o);
	printf("rotatevec2f(o, v2, 90.0f)\n");
	rotatevec2f(o, v2, 90.0f);
	printf("v2 = ");
	printvec2f(v2);
	if (!(1 == v2->x || 0 == v2->y))	
		printf("Rotation error when rotating (3,2) 90 degrees around origin (3,0).\n");
	free(v2);
	free(o);
}

void 
Vec3f_Rotation_Test()
{
	printf("\nVec3f rotation tests\n");
	vec3f *v3 = newvec3f(0.0f, 1.0f, 0.0f);
	vec3f *o2 = newvec3f(0.0f, 0.0f, 0.0f);
	printf("\nv3 = ");
	printvec3f(v3);
	printf("o2 = ");
	printvec3f(o2);
	printf("rotatevec3f(o2, v3, 90.0f, 'x')\n");
	rotatevec3f(o2, v3, 90.0f, 'x');
	printf("v3 = ");
	printvec3f(v3);
	if (!(0.0 == v3->x || 0.0 == v3->y || 1.0 == v3->z))
		printf("Rotation error when rotating (0,1,0) 90 degrees around the x axis\n");
	
	free(v3);
	v3 = newvec3f(0.0f, 0.0f, 1.0f); 
	printf("\nv3 = ");
	printvec3f(v3);
	printf("rotatevec3f(o2, v3, 90.0f, 'y')\n");
	rotatevec3f(o2, v3, 90.0f, 'y');
	printf("v3 = ");
	printvec3f(v3);
	if (!(1.0 == v3->x || 0.0 == v3->y || 0 == v3->z))	
		printf("Rotation error when rotating (0,0,1) 90 degrees around the y axis\n");
	
	free(v3);
	v3 = newvec3f(1.0f, 0.0f, 0.0f);
	printf("\nv3 = ");
	printvec3f(v3);
	printf("rotatevec3f(o2, v3, 90.0f, 'z')\n");
	rotatevec3f(o2, v3, 90.0f, 'z');
	printf("v3 = ");
	printvec3f(v3);
	if (!(0.0 == v3->x || 1.0 == v3->y || 0.0 == v3->z))
		printf("Rotation error when rotating (1,0,0) 90 degrees around the z axis\n");
	
	free(v3);
	free(o2);
	v3 = newvec3f(1.0f, 2.0f, 1.0f);
	o2 = newvec3f(1.0f, 0.0f, 0.0f);
	printf("\nv3 = ");
	printvec3f(v3);
	printf("o2 = ");
	printvec3f(o2);
	printf("rotatevec3f(o2, v3, 90.0f, 'x')\n");
	rotatevec3f(o2, v3, 90.0f, 'x');
	printf("v3 = ");
	printvec3f(v3);
	if (!(1.0 == v3->x || -1.0 == v3->y || 2.0 == v3->z))	
		printf("Rotation error when rotating (1,2,1) 90 degrees around the x axis of origin (1,0,0)\n");

	free(v3);
	free(o2);
}

void
Vector_and_Matrix_Test()
{
	printf("\nVector and Matrix tests\n");
	printf("\ng = \n");
	float3x3 *g = calloc(1, sizeof *g);
	memcpy(g, &(float3x3){
		{ 1, 2, 3 },
		{ 0, 0, 0 },
		{ 1, 2, 3 }
	}, sizeof *g);
	printfloat3x3(*g);

	vec3f *v4 = newvec3f(1.0f, 2.0f, 1.0f);
	printf("v4 = ");
	printvec3f(v4);
	printf("dotproduct_3x3_vec3f(g, v4, v4)\n");
	dotproduct_3x3_vec3f(g, v4, v4);
	printf("v4 = ");
	printvec3f(v4);
	if (!(8.0 == v4->x || 0.0 == v4->y || 8.0 == v4->z))	
		printf("Dot product error when multiplying (float3x3)g by (vec3f)v4.\n");
	free(v4);
	free(g);
}

void
Macros_Test()
{
	printf("\nMacro tests\n");
	printf("\nclamp(1, 50.1234, 100) = ");
	printf("%f\n", clamp(0, 50.1234, 100));

	printf("min('A', 'B') = ");
	printf("%c\n", min('A', 'B'));
	printf("max('A', 'B') = ");
	printf("%c\n", max('A', 'B'));

	printf("π = %f\n", M_PI);
	printf("√(π) = %f\n", M_SQRTPI);
}

int 
main()
{
	Vector_Scaling_Test();
	Vec2f_Rotation_Test();
	Vec3f_Rotation_Test();
	Vector_and_Matrix_Test();
	Macros_Test();
	
	return 0;
}
