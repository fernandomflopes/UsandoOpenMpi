#include "process.hpp"


Process::Process(const uint rank):rank(rank) {}

Master::Master(const uint rank):Process(rank) {
    cout << "i`m master " << "id:" << rank; 
}

void Master::ReceiveIntBy(const uint rank) {
    int data;
    MPI_Recv(&data, 
                    1, 
                    MPI_INT, 
                    rank, 
                    rank, 
                    MPI_COMM_WORLD,
                    MPI_STATUS_IGNORE);
                    
    cout << "Mestre recebeu: " << data << " de:" << rank;
}

Slave::Slave(const uint rank):Process(rank) {
    cout << "i`m slave " << "id: " << rank; 
}

void Slave::SendToMaster(int data) {
     MPI_Send(&data, 
                    1, 
                    MPI_INT, 
                    MMPI::Globals::MASTER_RANK, 
                    this->rank, 
                    MPI_COMM_WORLD);
    
}
