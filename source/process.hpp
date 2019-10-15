#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <iostream>
#include <mpi.h>

using namespace std;

namespace MMPI {
    namespace Globals {
        const int MASTER_RANK = 0;
    };
};

class Process {
public:
    Process(const uint rank);
private:

protected:
    const uint rank;
};

class Master: public Process {
public:
    Master(const uint rank);
    void ReceiveIntBy(const uint rank);
};

class Slave: public Process {
public:
    Slave(const uint rank);
    void SendToMaster(int);
private:
    const uint master_rank = MMPI::Globals::MASTER_RANK;
    
};

#endif