#include "process.hpp"


Process::Process(const uint rank):rank(rank) {}

Master::Master(const uint rank, const uint size):Process(rank), size(size) {}

void Master::ReceiveIntFrom(const uint rank) {
    int data;
    MPI_Recv(&data, 
                    1, 
                    MPI_INT, 
                    rank, 
                    rank, 
                    MPI_COMM_WORLD,
                    MPI_STATUS_IGNORE);
}

void Master::SendTo(const uint rank, string data) {
    data += '\0';
    MPI_Send(data.c_str(), 
                    data.size(), 
                    MPI_CHAR, 
                    rank, 
                    this->rank, 
                    MPI_COMM_WORLD);   
}

void Master::ReadIndexFile(const string path) {
    ifstream cin(path); 
    string s;
    while(cin >> s)
        this->process_queue.push(s);    
}

void Master::SlaveProcess() {
    while(!this->process_queue.empty()) {
        for(int i = 0; i < this->size; i++){
            this->SendTo(i, this->process_queue.front());
            this->process_queue.pop();
        }
    }

    for(int i = 0; i < this->size; i++){
        string s = "EOF\0";
        this->SendTo(i, s);
    }
}


Slave::Slave(const uint rank): Process(rank)
{
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
    while(1) {    
        char data[50];
        MPI_Recv(&data, 
                    30, 
                    MPI_CHAR, 
                    MMPI::Globals::MASTER_RANK, 
                    0, 
                    MPI_COMM_WORLD,
                    MPI_STATUS_IGNORE);
    
        string path(data);
        if(data == "EOF") {
            return;
        }
        this->MakeProcess(path);
    }
}

long double Slave::CelsiusToFarenheit(long double c) {
    return (9 * c + 160) / 5;
}

void Slave::MakeProcess(const string path) {
    cout << "processando " << path << endl;
    
    string cinpath = MMPI::Globals::DIR_FILES_PATH + path;
    string outpath = MMPI::Globals::DIR_OUT_FILES_PATH + path;

    ifstream cin(cinpath);
    ofstream  mfile(outpath);

    long double st;
    while(cin >> st) {
        mfile << this->CelsiusToFarenheit(st);
        mfile << "\n";
    }
    cin.close();
}
