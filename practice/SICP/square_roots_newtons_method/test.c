#include <stdio.h>

#include "math.h"

int main()
{
	long double a = 3.141592653589793238462643383279502884197169399375;
	printf("a = %.45Lf\n", a);
	printf("sqrt(a) = %.45Lf\n", sqrt(a, 1e-45f));
	return 0;
}
