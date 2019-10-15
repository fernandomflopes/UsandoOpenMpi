make
clear

if [[ "$OSTYPE" == "linux-gnu" ]]; then
        mpirun -np 7 ./objects/prog.o;
elif [[ "$OSTYPE" == "darwin"* ]]; then
        mpirun --use-hwthread-cpus ./objects/prog.o
fi
