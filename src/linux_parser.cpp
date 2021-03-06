#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include <iostream> 

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}


//========================================================
// NOTE: THIS FUNCTION WAS NOT WORKING PROPERLY 
//       I added version to the end of the kernel
//========================================================

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, ver;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel >> ver;
  }
  return ver; 
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }

  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization 
float LinuxParser::MemoryUtilization() { 
  std::string FilePath = kProcDirectory+kMeminfoFilename;
  float MemTotal = stof (FindLineInStream (FilePath, "MemTotal:"));
  float MemFree = stof (FindLineInStream (FilePath, "MemFree:"));

  return (((MemTotal-MemFree)/MemTotal));    // teet return Mem Utilization
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string line;
  string UpTimeSec;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> UpTimeSec;
  }
  return (std::stol(UpTimeSec)); 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  return ActiveJiffies() + IdleJiffies(); 
}

// TODO: Read and return the number of active jiffies for a PID
long LinuxParser::ActiveJiffies(int pid) { 
  std::ifstream stream(LinuxParser::kProcDirectory +
                       to_string(pid) + 
                       LinuxParser::kStatFilename);  // /proc/[PID]/stat
  string value;    
  long utime; // #14 utime - CPU time spent in user code, measured in clock ticks
  long stime; // #15 stime - CPU time spent in kernel code, measured in clock ticks
  long cutime; // #16 cutime - Waited-for children's CPU time spent in user code (in clock ticks)
  long cstime; // #17 cstime - Waited-for children's CPU time spent in kernel code (in clock ticks)

  if (stream.is_open()) { 
    for(int i=1;i<23;i++){
        std::getline(stream, value,' ');  
        switch(i){
          case 14: utime=stol(value);  break;
          case 15: stime=stol(value); break;
          case 16: cutime=stol(value); break;
          case 17: cstime=stol(value); break;
          default: break;
        }
    }
  }  
  long int totalTime = utime + stime;
  totalTime += cutime + cstime;

  return totalTime;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  long  UserJeffies_{0},
        NiceJeffies{0},
        SystemJeffies_{0},
        IdleJeffies_ {0},
        IowaitJeffies{0},
        IrqJeffies_{0},
        SoftirqJeffies_{0},
        StealJeffies_{0};

  std::string line;
  std::string DeleteMe;

  std::ifstream fstream(LinuxParser::kProcDirectory +
                           LinuxParser::kStatFilename);

  std::getline(fstream, line);
  std::istringstream linestream(line);
  linestream >>  DeleteMe>> 
                 UserJeffies_ >> 
                 NiceJeffies>>
                 SystemJeffies_>>
                 IdleJeffies_>>
                 IowaitJeffies>>
                 IrqJeffies_>>
                 SoftirqJeffies_>>
                 StealJeffies_;
                 
  return (UserJeffies_+
          NiceJeffies+
          SystemJeffies_+
          IdleJeffies_+
          IowaitJeffies+
          IrqJeffies_+
          SoftirqJeffies_+
          StealJeffies_);   
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {   
  
  long  IdleJeffies_ {0}, IowaitJeffies{0};
  std::string line;
  std::string DeleteMe;
  std::ifstream fstream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
  std::getline(fstream, line);
  std::istringstream linestream(line);
  linestream >>  DeleteMe >> 
                 DeleteMe >> 
                 DeleteMe  >> 
                 DeleteMe  >> 
                 IdleJeffies_>>
                 IowaitJeffies;

  return (IdleJeffies_+
          IowaitJeffies);
}

// TODO: Read and return Aggregate CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
 
  std::string FilePath = LinuxParser::kProcDirectory+LinuxParser::kStatFilename;
  std::ifstream stream(FilePath);
  std::string line;
  std::string title;
  vector<string> MyCPUStates{};

  if (stream.is_open()){
    std::getline(stream, line);
    std::istringstream linestream(line);

    std::string UserJefs,
                NiceJefs,
                SystemJefs,
                IdleJefs, 
                IOwaitJefs,
                IRQJefs,
                SoftIRQJefs,
                StealJefs,
                GuestJefs;

    linestream >> title 
               >> UserJefs
               >> NiceJefs
               >> SystemJefs
               >> IdleJefs
               >> IOwaitJefs
               >> IRQJefs
               >> SoftIRQJefs
               >> StealJefs
               >> GuestJefs;

    // I am not sure how to combine the following commands with the prev chunk
    MyCPUStates.push_back(UserJefs);
    MyCPUStates.push_back(NiceJefs);
    MyCPUStates.push_back(SystemJefs);
    MyCPUStates.push_back(IdleJefs);
    MyCPUStates.push_back(IOwaitJefs);
    MyCPUStates.push_back(IRQJefs);
    MyCPUStates.push_back(SoftIRQJefs);
    MyCPUStates.push_back(StealJefs);
    MyCPUStates.push_back(GuestJefs);
  }
  stream.close();

  return MyCPUStates;
}


// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  std::string FilePath = kProcDirectory+kStatFilename;
  string MyStr = FindLineInStream (FilePath, "processes");
  return (stoi(MyStr)); // return Number of Total  Processes
}

//  Helper function to find a string in the file stream and returns the corresponding value
// e.g. return the number of processes after procs_running in /procs/stat
string LinuxParser::FindLineInStream (string FilePath, string StringToBeFound){
  
  std::ifstream stream(FilePath);
  string line;
  string title;
  string ExtractedString;

   if (stream.is_open()) {
    while (std::getline(stream, line)) {
      // search for the StringToBeFound line in the stream
      if (line.find(StringToBeFound) != string::npos){ 
        std::istringstream linestream(line);
        linestream >> title >> ExtractedString;
      }
    }
  }
  stream.close(); // Close the input file stream
  return ExtractedString;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {   
  std::string FilePath = kProcDirectory+kStatFilename;
  string MyStr = FindLineInStream (FilePath, "procs_running");
  return (stoi(MyStr)); // return Number of Running Processes
}


// CPU Utilization for a specific process
float LinuxParser::CpuUtilization(int pid) {
  long upTime = LinuxParser::UpTime(); // System Uptime
  long totalTime = LinuxParser::ActiveJiffies(pid); // Process total time
  long startTime = LinuxParser::UpTime(pid); // Process Uptime
  long seconds = upTime - (startTime / sysconf(_SC_CLK_TCK));
    
  return ((float)(totalTime / sysconf(_SC_CLK_TCK))) / (float)seconds;
}



// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  
  std::string FilePath = kProcDirectory + to_string(pid) + kCmdlineFilename;
  std::ifstream filestream(FilePath);
  
  string str;
  if (filestream.is_open()) {
    filestream >> str;
  }
  filestream.close();
  return str;
}

// TODO: Read and return the memory used by a process
string LinuxParser::Ram(int pid) { 
  std::string FilePath = kProcDirectory+to_string(pid)+kStatusFilename;
  string MyStr = FindLineInStream (FilePath, "VmSize:");
  long VmSize = stol(MyStr)/1000;
  return (to_string(VmSize)); // return Process VmSize in MB
}

// TODO: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) { 
  std::string FilePath = kProcDirectory+to_string(pid)+kStatusFilename;
  string Uid = FindLineInStream (FilePath, "Uid:");
  return Uid; 
}

// TODO: Read and return the user associated with a process
string LinuxParser::User(int pid) { 
  std::ifstream stream(kPasswordPath);
  string line;
  string userID;
  string uid;
  if (stream.is_open()) { 
    while (std::getline(stream, line)) { 
        std::istringstream linestream(line);
        std::getline(linestream, userID,':');
        std::getline(linestream, uid,':');
        std::getline(linestream, uid,':');
        if(LinuxParser::Uid(pid)==uid){
           // found the Uid, exit loop and return the userID
           return userID;
        }
      }
    }
   return "Not FOUND"; // Didn't find the Uid
}

// TODO: Read and return the uptime of a process
long LinuxParser::UpTime(int pid) { 
  // http://man7.org/linux/man-pages/man5/proc.5.html
  // Process uptime is number 22 in /proc/[PID]/stat
  std::string FilePath = kProcDirectory+to_string(pid)+kStatFilename;
  std::ifstream stream(FilePath);

  long proc_uptime = 0;
  if (stream.is_open()) {
    string str{""};
    for (unsigned i = 0; i < 22; i++){
      stream >> str;
    }
    stream.close();
    proc_uptime = std::stol(str);
  }
  return proc_uptime/sysconf(_SC_CLK_TCK);   
}