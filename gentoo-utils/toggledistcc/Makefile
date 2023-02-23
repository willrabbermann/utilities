CFLAGS=-Wall -fsanitize=address --pedantic -O2
LDFLAGS=
SRC=toggledistcc.c
BIN=toggledistcc

all:
	cc $(CFLAGS) -o $(BIN) $(SRC) $(LDFLAGS)

debug:
	cc $(CFLAGS) -g -o $(BIN) $(SRC) $(LDFLAGS)
	gdb $(BIN)

clean:
	rm -f $(BIN)

install:
	test -f $(BIN) || make all
	cp -v $(BIN) /usr/local/sbin/
