#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
    float PrevUserJeffies_=0;
    float UserJeffies_=0;

    float PrevNiceJeffies_=0;
    float NiceJeffies_=0;

    float PrevSystemJeffies_=0;
    float SystemJeffies_=0;

    float PrevIdleJeffies_=0; 
    float IdleJeffies_=0; 

    float PrevIowaitJeffies_=0;
    float IowaitJeffies_=0;

    float PrevIrqJeffies_=0;
    float IrqJeffies_=0;

    float PrevSoftirqJeffies_=0;
    float SoftirqJeffies_=0;

    float PrevStealJeffies_=0;
    float StealJeffies_=0;
    
    float PrevGuestJeffies_=0;
    float GuestJeffies_=0;

    float PrevNonIdleJeffies_=0;
    float NonIdleJeffies_=0;

    float PrevTotalJeffies_=0;
    float TotalJeffies_=0;

    float TotalDiffJeffies_=0;
    float IdleDiffJeffies_=0;


};

#endif