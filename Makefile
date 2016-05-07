CC = g++
CFLAGS = -g -Wall -Wextra --std=c++11

all: main

main: main.o ImagePPM.o Pedest.o Building.o
	$(CC) $(CFLAGS) main.o ImagePPM.o Pedest.o Building.o -lsfml-graphics -lsfml-window -lsfml-system -o main

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

ImagePPM.o: ImagePPM.cpp ImagePPM.h
	$(CC) $(CFLAGS) -c ImagePPM.cpp

Pedest.o: Pedest.cpp Pedest.h
	$(CC) $(CFLAGS) -c Pedest.cpp

Building.o: Building.cpp Building.h
	$(CC) $(CFLAGS) -c Building.cpp

clean:
	rm *.o
 
