#include <stdio.h>

#include "math.h"

int main()
{
	long double a = 3.141592653589793238462643383279502884197169399375;
	long double sqrt_a = sqrt(a, 1e-45f);
	printf("a\t\t=\t%.45Lf\n", a);
	printf("sqrt(a)\t\t=\t%.45Lf\n", sqrt_a);
	printf("square(sqrt(a))\t=\t%.45Lf\n", square(sqrt_a));
	printf("a\t\t=\t%.45Lf\n", a);
	return 0;
}
