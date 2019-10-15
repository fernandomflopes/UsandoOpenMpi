#include <iostream>
#include <mpi.h>

using namespace std;

void run(const int*, const int *);

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
    if(*rank == 0) {
        cout << "i'm master";
    } else {
        cout << "i'm slave";
    }
    cout << endl;
}