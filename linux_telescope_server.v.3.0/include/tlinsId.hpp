#ifndef __tlinsId_hpp__
#define __tlinsId_hpp__

#include <mutex>
#include <string>

class tlinsId {
  private:
	static std::mutex    synch;
	static unsigned long id;

  public:
	static unsigned long getId();
	static std::string   getIdStr();
};

#endif
