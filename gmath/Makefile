CFLAGS=-fsanitize=address -Wall -Wextra -pedantic -O2
LDFLAGS=-lm
SRC=gmath.c

all:
	cc $(CFLAGS) -o test-gmath test-gmath.c $(SRC) $(LDFLAGS)

debug:
	cc $(CFLAGS) -g -o test-gmath test-gmath.c $(SRC) $(LDFLAGS)

clean:
	rm -f test-gmath
