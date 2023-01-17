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
	printf("Initial vec4f\nv = ");
	printvec4f(v);
	
	vec4f *b = newvec4f(1.0f, 2.0f, 3.0f, 0.0f);
	printf("\nb = ");
	printvec4f(b);
	
	transform(v, b);

	free(b);
	printf("transform(v, b)\nv = ");
	printvec4f(v);

	float c = 2.0f;	
	printf("\nscale(v, %f)\nv = ", c);
	scale(v, c);
	printvec4f(v);
	free(v);
}

int main()
{
	GMATH_Tests();
	return 0;
}
