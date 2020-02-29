#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/

// #define DEBUG1of3  // when I unComment this line, everything freezes, DEBUG2of3 is in process.cpp, DEBUG3of3 is in system.cpp

class Process {
 public:
  Process(int pid){
    pid_=pid;
     cpu_util = Process::CpuUtilization();
     } 
  int Pid();                               // TODO: See src/process.cpp

  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
  int pid_;  
  float cpu_util{0.0};
};

#endif