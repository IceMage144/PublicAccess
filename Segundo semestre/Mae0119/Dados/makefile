CC = g++
CFLAGSF = -ISFML-2.4.0/include
CFLAGSS = -LSFML-2.4.0/lib
OBJS = Dados.o

%.o: %.cpp
	$(CC) -c $< $(CFLAGSF)

dados: Dados.o
	g++ Dados.o -o plot $(CFLAGSS) -lsfml-graphics -lsfml-window -lsfml-system
	rm -f *.o

exec: plot
	export LD_LIBRARY_PATH=./SFML-2.4.0/lib && ./plot