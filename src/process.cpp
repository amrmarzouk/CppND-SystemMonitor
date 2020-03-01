#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// Constructor
 Process::Process(int pid){
    Process::pid_=pid;
    Process::proc_cpuutil_ = Process::CpuUtilization();
  } 

// TODO: Return this process's ID
int Process::Pid() { 
        return pid_; 
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
  return LinuxParser::CpuUtilization(pid_);     
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_);} 

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

string Process::User() { 
   return LinuxParser::User(pid_);
}
    
// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
    return LinuxParser::UpTime(pid_); // divide by sysconf(_SC_CLK_TCK) to get seconds    
}

// TODO: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const { 
    return proc_cpuutil_>a.proc_cpuutil_; 
}

