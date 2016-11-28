.PHONY=clean
.DELETE_ON_ERROR=
CC = gcc
CFLAGS = -I.
SFLAGS = -Wall -ansi -pedantic -O2

ep5: hex.o auxfuncs.o BoardFuncs.o PathFinding.o
	$(CC) $^ -o $@ $(CFLAGS)

%.o: %.c %.h
	$(CC) -c $< $(CFLAGS) $(SFLAGS)

hex.o: hex.c
	$(CC) -c $< $(CFLAGS) $(SFLAGS)

clean:
	rm -f *.o *~ *.gch ep5 a.out
