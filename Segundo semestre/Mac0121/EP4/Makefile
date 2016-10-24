CC = gcc
CFLAGS = -I.
SFLAGS = -Wall -ansi -pedantic -O2
DEPS = buffer.h vectorfuncs.h auxfuncs.h tabelaSimbolo_VO.h tabelaSimbolo_LO.h linkedlistfuncs.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(SFLAGS)

tabelaSimbolo.o: tabelaSimbolo.c
	$(CC) -c -o $@ $< $(CFLAGS) $(SFLAGS) 

ep4: buffer.o vectorfuncs.o tabelaSimbolo_VO.o tabelaSimbolo.o auxfuncs.o tabelaSimbolo_LO.o linkedlistfuncs.o
	$(CC) $^ -o $@ $(CFLAGS)
	rm -f *.o *~

dep4: buffer.c vectorfuncs.c tabelaSimbolo_VO.c tabelaSimbolo.c auxfuncs.c tabelaSimbolo_LO.c linkedlistfuncs.c
	cc -g $^ $(SFLAGS)

mep4:  buffer.c vectorfuncs.c tabelaSimbolo_VO.c tabelaSimbolo.c auxfuncs.c tabelaSimbolo_LO.c linkedlistfuncs.c
	cc -g $^ $(SFLAGS)