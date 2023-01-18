#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <tgmath.h>

#include "gmath.h"

void
GMATH_Tests()
{
	printf("sizeof(int) = %ld bytes\n", sizeof(int)); 		// 4 bytes
	printf("sizeof(float) = %ld bytes\n", sizeof(float)); 	// 4 bytes
	printf("sizeof(double) = %ld bytes\n", sizeof(double));	// 8 bytes
	printf("sizeof(void *) = %ld bytes\n", sizeof(void *));	// 8 bytes

	vec4f *v = newvec4f(0.0f, 1.5f, 1.0f, 1.0f);
	printf("\nv = ");
	printvec4f(v);
	
	vec4f *b = newvec4f(1.0f, 2.0f, 3.0f, 0.0f);
	printf("b = ");
	printvec4f(b);
	
	transformvec4f(v, b);

	free(b);
	printf("\ntransformvec4f(v, b)\nv = ");
	printvec4f(v);

	float c = 2.0f;	
	printf("\nscalevec4f(v, %f)\nv = ", c);
	scalevec4f(v, c);
	printvec4f(v);
	free(v);

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
}

int 
main()
{
	GMATH_Tests();
	return 0;
}
