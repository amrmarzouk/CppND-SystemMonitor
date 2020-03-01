#include <string>
#include <iostream>
// #include <ios>
#include <iomanip>
// #include <sstream>


#include "format.h"
#include "linux_parser.h"   

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) { 
    
    long int time=0;
    long int hour=0;
    long int min=0;
    long int sec=0;
    
    time=seconds;
    
	hour = time/SECINHOUR; // time/3600
	time = time%SECINHOUR; 
	min = time/SECINMIN;   // time/60
	time = time%SECINMIN;
	sec = time;

    // string MyStr = std::to_string (hour) +":"+std::to_string (min) +":"+ std::to_string (sec);

    std::ostringstream out;
    out << std::internal << std::setfill('0') << std::setw(2) << hour << ":" 
        << std::internal << std::setfill('0') << std::setw(2) << min  <<":"
        << std::internal << std::setfill('0') << std::setw(2) << sec;
    out << std::left << std::setfill(' ');

    return  out.str();
}