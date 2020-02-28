randSelect: randSelect.o
	g++ randSelect.o -o randSelect -std=c++11

randSelect.o: randSelect.h
	g++ randSelect.cpp -o randSelect.o -std=c++11
