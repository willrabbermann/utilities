#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gmath.h"

void
GMATH_Tests()
{
	printf("sizeof(int) = %ld bytes\n", sizeof(int));
	printf("sizeof(float) = %ld bytes\n", sizeof(float));
	printf("sizeof(float*) = %ld bytes\n", sizeof(float*));
	printf("sizeof(double) = %ld bytes\n", sizeof(double));
	printf("sizeof(void *) = %ld bytes\n", sizeof(void *));
	printf("sizeof(float3x3) = %ld bytes\n", sizeof(float3x3)); 

	// vec4f transform
	vec4f *v = newvec4f(0.0f, 1.5f, 1.0f, 1.0f);
	printf("\nv = ");
	printvec4f(v);
	vec4f *b = newvec4f(1.0f, 2.0f, 3.0f, 0.0f);
	printf("b = ");
	printvec4f(b);
	addvec4f(v, b);
	printf("\ntransformvec4f(v, b)\nv = ");
	printvec4f(v);
	free(b);

	// vec4f scale
	float *c = malloc(sizeof(float));
	*c = 2.0f;
	printf("\nscalevec4f(v, %f)\nv = ", *c);
	scalevec4f(v, *c);
	printvec4f(v);
	free(v);
	free(c);

	// vec2f rotation
	vec2f *v2 = newvec2f(3.0f, 2.0f);
	vec2f *o = newvec2f(3.0f, 0.0f);
	printf("\nv2 = ");
	printvec2f(v2);
	printf("o = ");
	printvec2f(o);
	printf("\nrotatevec2f(o, v2, 90.0f)\n");
	rotatevec2f(o, v2, 90.0f);
	printf("v2 = ");
	printvec2f(v2);
	free(v2);
	free(o);

	// vec3f rotation
	vec3f *v3 = newvec3f(1.0f, 1.5f, 2.0f);
	vec3f *o2 = newvec3f(1.0f, 0.0f, 0.0f);
	printf("\nv3 = ");
	printvec3f(v3);
	printf("o2 = ");
	printvec3f(o2);
	rotatevec3f(o2, v3, 90.0f, 'x');
	printf("\nrotatevec3f(o2, v3, 90.0f, 'x')\n");
	printvec3f(v3);
	free(v3);
	free(o2);

	// Matrix operations
	printf("\ng = \n");
	float3x3 *g = calloc(1, sizeof *g);
	memcpy(g, &(float3x3){
		{ 1, 2, 3 },
		{ 0, 0, 0 },
		{ 1, 2, 3 }
	}, sizeof *g);
	printfloat3x3(*g);

	vec3f *v4 = newvec3f(1.0f, 2.0f, 1.0f);
	printf("\nv4 = ");
	printvec3f(v4);
	printf("\nmutliplyvec3f3x3(v4, g, v4)\n");
	multiplyvec3f3x3(v4, g, v4);
	printf("v4 = ");
	printvec3f(v4);
	free(v4);
	free(g);
}

int 
main()
{
	GMATH_Tests();
	return 0;
}
