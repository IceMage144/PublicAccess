CC = gcc
DEPS = polygons.h pgmdrawer.h

%.o: %.cpp $(DEPS)
	$(CC) -o -c $<

master.o: master.cpp
	$(CC) -o -c $<

test: polygon.o master.o pgmdrawer.o
	$(CC) $^ -o $@