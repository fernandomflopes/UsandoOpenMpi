#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <iostream>
#include <fstream>
#include <queue>
#include <cstring>
#include <mpi.h>

using namespace std;

namespace MMPI {
    namespace Globals {
        const int MASTER_RANK = 0;
        const string DIR_FILES_PATH = "files/";
        const string DIR_OUT_FILES_PATH = "files/output/";
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
    Master(const uint rank, const uint size);
    void ReceiveIntFrom(const uint rank);
    void SendTo(const uint rank, string data);
    void ReadIndexFile(const string path);
    void SlaveProcess();
private:
    const uint size;
    queue<string> process_queue;
};

class Slave: public Process {
public:
    Slave(const uint rank);
    void SendToMaster(int);
    void ReceiveFromMaster();
    void MakeProcess(const string path);
    long double celsiusToFarenheit(long double c);
private:
    const uint master_rank = MMPI::Globals::MASTER_RANK;
    
};

#endif