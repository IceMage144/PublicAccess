CC = g++
CFLAGSF = -I../../SFML-2.4.0/include
CFLAGSS = -L../../SFML-2.4.0/lib
DEPS = physical_objects.h vectors.h

main.o: main.cpp
	$(CC) -c $< $(CFLAGSF)

%.o: %.cpp $(DEPS)
	$(CC) -c $< $(CFLAGSF)

teste2: main.o physical_objects.o vectors.o
	$(CC) $^ -o $@ $(CFLAGSS) -lsfml-graphics -lsfml-window -lsfml-system
	rm -f *.o

teste:
	g++ topper.cpp -o teste -I../../../SFML-2.4.0/include -L../../../SFML-2.4.0/lib -lsfml-graphics -lsfml-window -lsfml-system

exec: teste
	g++ topper.cpp -o teste -I../../../SFML-2.4.0/include -L../../../SFML-2.4.0/lib -lsfml-graphics -lsfml-window -lsfml-system
	export LD_LIBRARY_PATH=./../../SFML-2.4.0/lib && ./teste
