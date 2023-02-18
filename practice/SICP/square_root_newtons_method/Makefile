CFLAGS=-fsanitize=address -Wall -Wextra -pedantic -O2
LDFLAGS=
SRC=test.c

all:
	cc $(CFLAGS) -o solution $(SRC) $(LDFLAGS)

debug:
	cc $(CFLAGS) -g -o solution $(SRC) $(LDFLAGS)
	gdb solution

clean:
	rm -f solution
