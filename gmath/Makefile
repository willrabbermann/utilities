CFLAGS=-fsanitize=address -Wall -Wextra -pedantic -O2
LDFLAGS=-lm
SRC=gmath.c

all:
	cc $(CFLAGS) -o solution test-gmath.c $(SRC) $(LDFLAGS)

debug:
	cc $(CFLAGS) -g -o solution test-gmath.c $(SRC) $(LDFLAGS)
	gdb ./solution

clean:
	rm -f solution
