CC = g++
CFLAGS = -I.
OBJS = Dados.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

dados: Dados.o
	g++ Dados.o -o plot -lsfml-graphics -lsfml-window -lsfml-system
	rm -f *.o