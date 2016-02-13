all : main

main: main.o 
	g++ -g main.o -o main -std=c++11
	
main.o: main.cpp 
	g++ -g -c main.cpp -o main.o -std=c++11

clean : 
	rm -f *.o
