CC = gcc
CFLAGS = -I.
SFLAGS = -Wall -pedantic -ansi -O2
DEPS = myvector.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(SFLAGS)

tresReversao.o: tresReversao.c
	$(CC) -c -o $@ $< $(CFLAGS) $(SFLAGS)

ep3: tresReversao.o myvector.o
	$(CC) $^ -o $@ $(CFLAGS)
	rm -f *.o *~