.PHONY=clean
.DELETE_ON_ERROR=
CC = gcc
CFLAGS = -I.
SFLAGS = -Wall -ansi -pedantic -O2

Hex: HexPlayer.o myvector.o auxfuncs.o PlayerFunctions.o
	$(CC) $^ -o $@ $(CFLAGS)

Hexdb: HexPlayer.o myvector.o auxfuncs.o PlayerFunctions.o
	$(CC) $^ -g $(CFLAGS)

%.o: %.c %.h
	$(CC) -c $< $(CFLAGS) $(SFLAGS)

HexPlayer.o: HexPlayer.c
	$(CC) -c $< $(CFLAGS) $(SFLAGS)

clean:
	rm -f *.o *~ *.gch Hex a.out
