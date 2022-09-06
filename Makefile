main: main.o
	g++ main.o -o main

main.o: main.cpp multiset.h
	g++ -c main.cpp -o main.o

.PHONY:

clean:
	rm -f main main.o