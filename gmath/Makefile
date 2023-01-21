CFLAGS=-fsanitize=address -Wall -Wextra -O2 -pedantic
LDFLAGS=-lm
SRC=gmath.c

all:
	cc $(CFLAGS) -o test-gmath test-gmath.c $(SRC) $(LDFLAGS)

debug:
	cc $(CFLAGS) -g -o test-gmath test-gmath.c $(SRC) $(LDFLAGS)
	gdb ./test-gmath

clean:
	rm -f test-gmath
