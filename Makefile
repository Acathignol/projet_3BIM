CC = g++
CFLAGS = -g -Wall -Wextra --std=c++11

all: main

main: main.o Image.o Pedest.o Building.o
	$(CC) $(CFLAGS) main.o Image.o Pedest.o Building.o -o main

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Image.o: Image.cpp Image.h
	$(CC) $(CFLAGS) -c Image.cpp

Pedest.o: Pedest.cpp Pedest.h
	$(CC) $(CFLAGS) -c Pedest.cpp

Building.o: Building.cpp Building.h
	$(CC) $(CFLAGS) -c Building.cpp

clean:
	rm *.o
 
