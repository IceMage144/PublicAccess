CC = gcc
CFLAGS = -I.
SFLAGS = -Wall -ansi -pedantic -O2
DEPS = buffer.h vectorfuncs.h auxfuncs.h tabelaSimbolo_VO.h tabelaSimbolo_LO.h linkedlistfuncs.h tabelaSimbolo_LD.h tabelaSimbolo_VD.h tabelaSimbolo_AB.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(SFLAGS)

tabelaSimbolo.o: tabelaSimbolo.c
	$(CC) -c -o $@ $< $(CFLAGS) $(SFLAGS) 

ep4: buffer.o vectorfuncs.o tabelaSimbolo_VO.o tabelaSimbolo.o auxfuncs.o tabelaSimbolo_LO.o linkedlistfuncs.o tabelaSimbolo_LD.o tabelaSimbolo_VD.o tabelaSimbolo_AB.o
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -f *.o *~