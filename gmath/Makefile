CC=gcc
CFLAGS=-Wall -lm -O2
NAME=gmath

ALL=$(CC) $(CFLAGS) -o $(NAME) main.c

all:
	$(ALL)

debug:
	$(ALL) -g

clean:
	rm -f $(NAME)
	rm -rf *.o
