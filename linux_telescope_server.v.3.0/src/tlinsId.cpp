#include <tlinsBacktrace.hpp>
#include <tlinsId.hpp>

#include <stdio.h>

unsigned long tlinsId::getId()
{
	std::unique_lock<std::mutex> lock(tlinsId::synch);
	return tlinsId::id++;
}
std::string tlinsId::getIdStr()
{
	char idStr[256];
	sprintf(idStr, "%ld", tlinsId::getId());
	return std::string(idStr);
}
