CC = g++
CFLAGS = -g -Wall -Wextra --std=c++11

all: main

main: main.o Pedest.o Building.o Zone.o
	$(CC) $(CFLAGS) main.o Pedest.o Building.o Zone.o -lsfml-graphics -lsfml-window -lsfml-system -o main

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Pedest.o: Pedest.cpp Pedest.h
	$(CC) $(CFLAGS) -c Pedest.cpp

Building.o: Building.cpp Building.h
	$(CC) $(CFLAGS) -c Building.cpp

Zone.o: Zone.cpp Zone.h
	$(CC) $(CFLAGS) -c Zone.cpp

clean:
	rm *.o
 
