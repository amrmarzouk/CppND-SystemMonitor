#ifndef FORMAT_H
#define FORMAT_H


#define SECINHOUR 3600
#define SECINMIN  60


#include <string>

namespace Format {
    std::string ElapsedTime(long times);  // TODO: See src/format.cpp
};                                    // namespace Format

#endif