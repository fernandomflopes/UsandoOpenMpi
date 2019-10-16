#include "process.hpp"


Process::Process(const uint rank):rank(rank) {}

Master::Master(const uint rank):Process(rank) {
    cout << "i`m master " << "id:" << rank; 
}

void Master::ReceiveIntFrom(const uint rank) {
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

void Master::SendTo(const uint rank, const int data) {
    MPI_Send(&data, 
                    1, 
                    MPI_INT, 
                    rank, 
                    this->rank, 
                    MPI_COMM_WORLD);   
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

void Slave::ReceiveFromMaster() {
    int data;
    MPI_Recv(&data, 
                    1, 
                    MPI_INT, 
                    MMPI::Globals::MASTER_RANK, 
                    0, 
                    MPI_COMM_WORLD,
                    MPI_STATUS_IGNORE);
    cout << data << " RECEBIDO DO MESTRE" << endl;
}