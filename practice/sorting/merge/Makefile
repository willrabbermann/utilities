CFLAGS=-fsanitize=address -Wall -Wextra -pedantic -O2
LDFLAGS=
SRC=merge.c
BIN=sort

all:
	cc $(CFLAGS) -o $(BIN) $(SRC) $(LDFLAGS)

debug:
	cc $(CFLAGS) -g -o $(BIN) $(SRC) $(LDFLAGS)
	gdb ./$(BIN)

clean:
	rm -f $(BIN)
