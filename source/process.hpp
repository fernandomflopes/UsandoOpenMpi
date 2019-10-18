#ifndef _PROCESS_HPP_
#define _PROCESS_HPP_

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
    
    virtual void MakeProcess(const string path) = 0;
    
    //long double CelsiusToFarenheit(long double c);
private:
    const uint master_rank = MMPI::Globals::MASTER_RANK;
};

class SlaveCelsiusCalculator: public Slave {
public:
	SlaveCelsiusCalculator(const int rank);
	virtual void MakeProcess(const string path);	
    long double CelsiusToFarenheit(long double c);
};

#endif
