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
	vec2f *f = newvec2f(5.0f, 3.3f);
	vec2f *g = newvec2f(1.5f, 0.0f);
	printf("\nf = ");
	printvec2f(f);
	printf("g = ");
	printvec2f(g);
	printf("opvec2f(f, g, f, '-')\nf = ");
	opvec2f(f, g, f, '-');
	printvec2f(f);
	free(g);
	
	float h = 3.333f;
	printf("scalar_op_vec2f(f, %f, f, '/')\nf = ", h);
	scalar_op_vec2f(f, h, f, '/');
	printvec2f(f);
	free(f);

	vec3f *a = newvec3f(1.0f, 2.5f, 0.0f);
	vec3f *d = newvec3f(1.0f, 2.0f, 1.0f);
	printf("\na = ");
	printvec3f(a);
	printf("d = ");
	printvec3f(d);
	printf("opvec3f(a, d, a, '*')\na = ");
	opvec3f(a, d, a, '*');
	printvec3f(a);
	free(d);
	
	float e = 0.5f;
	printf("scalar_op_vec3f(a, %f, a, '*')\na = ", e);
	scalar_op_vec3f(a, e, a, '*');
	printvec3f(a);
	free(a);

	vec4f *v = newvec4f(0.0f, 1.5f, 1.0f, 1.0f);
	vec4f *b = newvec4f(1.0f, 2.0f, 3.0f, 0.0f);
	printf("\nv = ");
	printvec4f(v);
	printf("b = ");
	printvec4f(b);
	printf("opvec4f(v, b, v, '+')\nv = ");
	opvec4f(v, b, v, '+');
	printvec4f(v);
	free(b);

	float c = 2.0f;
	printf("scalar_op_vec4f(v, %f, v, '*')\nv = ", c);
	scalar_op_vec4f(v, c, v, '*');
	printvec4f(v);
	free(v);
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
		printf("Dot product error when multiplying (float3x3)g by (vec3f)v4\n");
	free(v4);
	free(g);

	vec2f *v1 = newvec2f(0.0f, 2.5f);
	vec2f *v2 = newvec2f(6.2f, 9.5f);
	printf("\nv1 = ");
	printvec2f(v1);
	printf("v2 = ");
	printvec2f(v2);
	float vec2fdist = distancevec2f(v1, v2); 
	printf("distancevec2f(v1, v2) = %f\n", vec2fdist);
	if ((float)9.3509357820488 != vec2fdist)
			printf("distancevec2f error\n");
	free(v1);
	free(v2);

	vec3f *v5 = newvec3f(0.0f, 2.5f, 0.0f);
	vec3f *v6 = newvec3f(6.2f, 9.5f, -5.0f);
	printf("\nv5 = ");
	printvec3f(v5);
	printf("v6 = ");
	printvec3f(v6);
	float vec3fdist = distancevec3f(v5, v6); 
	printf("distancevec3f(v5, v6) = %f\n", vec3fdist);
	if ((float)10.603772913449 != vec3fdist)
			printf("distancevec3f error\n");
	free(v5);
	free(v6);

	vec4f *v7 = newvec4f(0.0f, 2.5f, 2.0f, 1.0f);
	vec4f *v8 = newvec4f(6.2f, 9.5f, 0.0f, -1.0f);
	printf("\nv7 = ");
	printvec4f(v7);
	printf("v8 = ");
	printvec4f(v8);
	float vec4fdist = distancevec4f(v7, v8); 
	printf("distancevec4f(v7, v8) = %f\n", vec4fdist);
	if ((float)9.7693397934558 != vec4fdist)
			printf("distancevec4f error\n");
	free(v7);
	free(v8);
}

void
Macros_Test()
{
	printf("\nMacro tests\n");
	printf("\nclamp(1, 50.1234567, 100) = ");
	printf("%f\n", clamp(0, 50.1234567, 100));

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
