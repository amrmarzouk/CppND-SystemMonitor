#include <iostream>
#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    std::string FilePath = LinuxParser::kProcDirectory+LinuxParser::kStatFilename;
    std::ifstream stream(FilePath);
    std::string line;
    std::string title;
    
    

    if (stream.is_open()) {
            std::getline(stream, line);
            std::istringstream linestream(line);
            linestream >> title >> UserJeffies_
                                >> NiceJeffies_
                                >> SystemJeffies_
                                >> IdleJeffies_
                                >> IowaitJeffies_
                                >> IrqJeffies_
                                >> SoftirqJeffies_
                                >> StealJeffies_
                                >> GuestJeffies_;
    }
    // std::cout << "system_time:" << system_time << "\r\n";

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
    PrevGuestJeffies_= GuestJeffies_;
    PrevNonIdleJeffies_= NonIdleJeffies_;
    PrevTotalJeffies_=  TotalJeffies_;


    // CPU_Percentage = (totald - idled)/totald
    return ((TotalDiffJeffies_-IdleDiffJeffies_)/TotalDiffJeffies_); 
        
}