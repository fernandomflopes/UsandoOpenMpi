all: prog

prog: process.o
	mpic++ source/main.cpp objects/process.o -o objects/prog.o -std=c++17

process.o:
	mpic++ source/process.cpp -o objects/process.o -c -std=c++17

clean:
	rm objects/*.o
	rm files/output/*.*	
