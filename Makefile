all: main

main: main.o Image.o Pedest.o Building.o Point.o
	g++ -g -Wall -o main main.o Image.o Pedest.o Building.o Point.o --std=c++11

main.o: main.cpp
	g++ -c -g -Wall -o main.o main.cpp --std=c++11

Image.o: Image.cpp Image.h
	g++ -c -g -Wall -o Image.o Image.cpp --std=c++11

Pedest.o: Pedest.cpp Pedest.h
	g++ -c -g -Wall -o Pedest.o Pedest.cpp --std=c++11

Building.o: Building.cpp Building.h
	g++ -c -g -Wall -o Building.o Building.cpp --std=c++11

Point.o: Point.cpp Point.h
	g++ -c -g -Wall -o Point.o Point.cpp --std=c++11

clean:
	rm *.o


