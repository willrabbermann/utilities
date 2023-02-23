CFLAGS=-Wall -fsanitize=address --pedantic -O2
INCLUDE=-I .
SRC=toggledhcp.c
BIN=toggledhcp

all:
	cc $(CFLAGS) -o $(BIN) $(SRC) $(INCLUDE)

debug:
	cc $(CFLAGS) -g -o $(BIN) $(SRC) $(INCLUDE)
	gdb $(BIN)

clean:
	rm -f $(BIN)
	
install:
	test -f $(BIN) || make all
	cp -v $(BIN) /usr/local/sbin/
