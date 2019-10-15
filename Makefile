all: prog

prog: process.o
	mpic++ source/main.cpp objects/process.o -o objects/prog.o

process.o:
	mpic++ source/process.cpp -o objects/process.o -c

clean:
	rm objects/*.o