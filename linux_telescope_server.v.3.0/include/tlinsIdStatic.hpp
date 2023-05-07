#ifndef __tlinsIdStatic_hpp__
#define __tlinsIdStatic_hpp__

#include <tlinsId.hpp>

std::mutex    tlinsId::synch;
unsigned long tlinsId::id = 0;

#endif
