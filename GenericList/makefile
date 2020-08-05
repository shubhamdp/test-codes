all:
		clear
		g++ Node.h
		g++ List.h
		g++ Node.cpp -o Node.o -c
		g++ List.cpp -o List.o -c
		g++ test.cpp -o test Node.o List.o
		./test