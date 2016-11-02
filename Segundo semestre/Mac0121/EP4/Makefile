CC = gcc
CFLAGS = -I.
SFLAGS = -Wall -ansi -pedantic -O2
DEPS = buffer.h vectorfuncs.h auxfuncs.h tabelaSimbolo_VO.h tabelaSimbolo_LO.h linkedlistfuncs.h tabelaSimbolo_LD.h tabelaSimbolo_VD.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(SFLAGS)

tabelaSimbolo.o: tabelaSimbolo.c
	$(CC) -c -o $@ $< $(CFLAGS) $(SFLAGS) 

ep4: buffer.o vectorfuncs.o tabelaSimbolo_VO.o tabelaSimbolo.o auxfuncs.o tabelaSimbolo_LO.o linkedlistfuncs.o tabelaSimbolo_LD.o tabelaSimbolo_VD.o
	$(CC) $^ -o $@ $(CFLAGS)

dep4: buffer.c vectorfuncs.c tabelaSimbolo_VO.c tabelaSimbolo.c auxfuncs.c tabelaSimbolo_LO.c linkedlistfuncs.c tabelaSimbolo_LD.c tabelaSimbolo_VD.c
	$(CC) -g $^ $(SFLAGS)

mep4:  buffer.c vectorfuncs.c tabelaSimbolo_VO.c tabelaSimbolo.c auxfuncs.c tabelaSimbolo_LO.c linkedlistfuncs.c tabelaSimbolo_LD.c tabelaSimbolo_VD.c
	$(CC) -g $^ $(SFLAGS)

clean:
	rm -f *.o *~