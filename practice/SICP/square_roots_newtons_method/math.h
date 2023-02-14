#pragma once

#define abs(a) ((a < 0) ? (-a) : (a)) 
#define aprox(a, b, c) ((abs((a - b)) < c) ? (1) : (0))
#define average(x, y) ((x + y) / 2)
#define square(x) (x * x)

#define improve_guess(guess, x) (average(guess, (x / guess)))
// iterative preprocessor macros are not possible, unfortunately.
//#define sqrt_iter_float(guess, x) (aprox(square(guess), x, 1e-6f) ? (guess) : (sqrt_iter_float(improve_guess(guess, x)), x))

long double sqrt_iter(long double guess, long double x, long double precision)
{
	if aprox(square(guess), x, precision) return guess;
	sqrt_iter(improve_guess(guess, x), x, precision);
}

long double sqrt(long double x, long double precision) 
{
	return sqrt_iter(1.0, x, precision);
}
