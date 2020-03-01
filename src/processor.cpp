#include <iostream>
#include <string>
#include <vector>

#include <unistd.h> //<<<<<<<<<<<<<<<<<<<<<<

#include "processor.h"
#include "linux_parser.h"


using std::stof;
using std::string;
using std::to_string;
using std::vector;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    vector<string> CPUStates = LinuxParser::CpuUtilization();

    float UserJeffies_=std::stof(CPUStates[LinuxParser::CPUStates::kUser_]);
    float NiceJeffies_=std::stof(CPUStates[LinuxParser::CPUStates::kNice_]);
    float SystemJeffies_=std::stof(CPUStates[LinuxParser::CPUStates::kSystem_]);

    float IdleJeffies_=std::stof(CPUStates[LinuxParser::CPUStates::kIdle_]);
    float IowaitJeffies_=std::stof(CPUStates[LinuxParser::CPUStates::kIOwait_]);
    float IrqJeffies_=std::stof(CPUStates[LinuxParser::CPUStates::kIRQ_]);
    float SoftirqJeffies_=std::stof(CPUStates[LinuxParser::CPUStates::kSoftIRQ_]);
    float StealJeffies_=std::stof(CPUStates[LinuxParser::CPUStates::kSteal_]);
    // float GuestJeffies_=std::stof(CPUStates[LinuxParser::CPUStates::kGuest_]); // Not Used
    
    float PrevUserJeffies_{0},
          PrevNiceJeffies_{0},
          PrevSystemJeffies_{0},
          PrevIdleJeffies_{0},
          PrevIowaitJeffies_{0},
          PrevIrqJeffies_{0},
          PrevSoftirqJeffies_{0},
          PrevStealJeffies_{0},
        //   PrevGuestJeffies_{0},   // Not Used
          NonIdleJeffies_{0}, PrevNonIdleJeffies_{0},
          TotalJeffies_{0}, PrevTotalJeffies_{0},
          TotalDiffJeffies_{0}, 
          IdleDiffJeffies_ {0};


    // PrevIdle = previdle + previowait
    PrevIdleJeffies_= PrevIdleJeffies_ + PrevIowaitJeffies_;

    // Idle = idle + iowait
    IdleJeffies_=IdleJeffies_ +IowaitJeffies_;

    // PrevNonIdle     = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal
    PrevNonIdleJeffies_= PrevUserJeffies_ + 
                        PrevNiceJeffies_ + 
                        PrevSystemJeffies_+ 
                        PrevIrqJeffies_ + 
                        PrevSoftirqJeffies_ + 
                        PrevStealJeffies_;

    // NonIdle = user + nice + system + irq + softirq + steal
    NonIdleJeffies_ = UserJeffies_ + 
                    NiceJeffies_ + 
                    SystemJeffies_ + 
                    IrqJeffies_ + 
                    SoftirqJeffies_ + 
                    StealJeffies_;

    // PrevTotal = PrevIdle + PrevNonIdle
    PrevTotalJeffies_ = PrevIdleJeffies_ + PrevNonIdleJeffies_ ;

    // Total = Idle + NonIdle
    TotalJeffies_ = IdleJeffies_ + NonIdleJeffies_;

    // # differentiate: actual value minus the previous one
    // totald = Total - PrevTotal
    TotalDiffJeffies_ = TotalJeffies_ - PrevTotalJeffies_;

    // idled = Idle - PrevIdle
    IdleDiffJeffies_ = IdleJeffies_ - PrevIdleJeffies_;

    PrevUserJeffies_= UserJeffies_;
    PrevNiceJeffies_= NiceJeffies_;
    PrevSystemJeffies_= SystemJeffies_;
    PrevIdleJeffies_= IdleJeffies_; 
    PrevIowaitJeffies_= IowaitJeffies_;
    PrevIrqJeffies_= IrqJeffies_;
    PrevSoftirqJeffies_= SoftirqJeffies_;
    PrevStealJeffies_= StealJeffies_;
    // PrevGuestJeffies_= GuestJeffies_;   // Not Used
    PrevNonIdleJeffies_= NonIdleJeffies_;
    PrevTotalJeffies_=  TotalJeffies_;

    // CPU_Percentage = (totald - idled)/totald
    return ((TotalDiffJeffies_-IdleDiffJeffies_)/TotalDiffJeffies_);     
}