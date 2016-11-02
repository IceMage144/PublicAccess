CC = g++
CFLAGSF = -ISFML-2.4.0/include
CFLAGSS = -LSFML-2.4.0/lib
OBJS = Simulador_da_LFDGN.o

%.o: %.cpp
	$(CC) -c $< $(CFLAGSF)

plot: Simulador_da_LFDGN.o
	g++ Simulador_da_LFDGN.o -o plot $(CFLAGSS) -lsfml-graphics -lsfml-window -lsfml-system
	rm -f *.o

exec: plot
	export LD_LIBRARY_PATH=./SFML-2.4.0/lib && ./plot