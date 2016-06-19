CC = g++
CFLAGS = -g -Wall -Wextra --std=c++11

all: escape

escape: obj/main.o obj/Pedest.o obj/Building.o
	$(CC) $(CFLAGS) obj/main.o obj/Pedest.o obj/Building.o -lsfml-graphics -lsfml-window -lsfml-system -o escape

obj/main.o: src/main.cpp
	$(CC) $(CFLAGS) -c src/main.cpp -o obj/main.o

obj/Pedest.o: src/Pedest.cpp src/Pedest.h
	$(CC) $(CFLAGS) -c src/Pedest.cpp -o obj/Pedest.o

obj/Building.o: src/Building.cpp src/Building.h
	$(CC) $(CFLAGS) -c src/Building.cpp -o obj/Building.o

clean:
	rm obj/*.o
 
