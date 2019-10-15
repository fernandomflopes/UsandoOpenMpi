all: prog

prog:
	mpic++ source/main.cpp -o objects/prog.o

clean:
	rm objects/*.o