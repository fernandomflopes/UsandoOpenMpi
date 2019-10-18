mkdir objects
make clean
make

if [[ "$OSTYPE" == "linux-gnu" ]]; then
        mpirun -np 2 ./objects/prog.o;
elif [[ "$OSTYPE" == "darwin"* ]]; then
        mpirun --use-hwthread-cpus ./objects/prog.o
fi
