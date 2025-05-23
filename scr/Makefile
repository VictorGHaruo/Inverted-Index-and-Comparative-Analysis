all: run

run: main
	./main

main: data.o main.o
	g++ main.o data.o -o main

main.o: main.cpp
	g++ -c main.cpp

data.o: data.cpp data.h
	g++ -c data.cpp

clean:
	rm -rf *.o main
