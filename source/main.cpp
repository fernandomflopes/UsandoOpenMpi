#include <iostream>
#include <vector>
#include <mpi.h>

#include "process.hpp"

using namespace std;

void run(const int*, const int*);

int main(int argc, char **argv) {
    int rank, size;
    
    MPI_Init(&argc, &argv);
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    run(&rank, &size);

    MPI_Finalize();

    return 0;
}

void run(const int* rank, const int* size) {
    if(*rank == MMPI::Globals::MASTER_RANK) {
        Master master(*rank, *size);
        master.ReadIndexFile("files/indexfile.txt");
        master.SlaveProcess();
    }
    else {
        Slave slave(*rank);
        slave.ReceiveFromMaster();
    }
    cout << endl;
}