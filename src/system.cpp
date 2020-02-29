#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"   // AMR


// #define DEBUG3of3  // when I unComment this line, everything freezes, DEBUG1of3 is in process.h, DEBUG2of3 is in process.cpp

using std::set;
using std::size_t;
using std::string;
using std::vector;




// TODO: Return the system's CPU
Processor& System::Cpu() { 
    return cpu_; 
}


// TODO: Return a container composed of the system's processes

vector<Process>& System::Processes() {
        
    vector<int> pidList = LinuxParser::Pids();

    this->processes_.clear();
    
    for (unsigned i=0; i<pidList.size();i++){  // SOMEWHAT WORKS with this but not for full pidList
    
    // for (auto i: pidList){
        Process Proc(pidList[i]);  
        processes_.push_back(Proc);
    }
    
    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    FOR THIS TO WORK, PROCESS CPU UTILIZATION SHOULD WORK FIRST
    // ======================================================
    //                      FIX THE FOLLOWING TO Sort the PIDS
    // ======================================================

    // std::sort(processes_.begin(), processes_.end());
    std::sort(processes_.begin(), processes_.end(),[](Process& p1, Process& p2){return (p2<p1);}); // FIX THIS

    
    return processes_;
}



// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime();  }