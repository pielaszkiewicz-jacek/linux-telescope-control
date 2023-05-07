#ifndef TLINSKEYBOARDEVENTHANDLER_H
#define TLINSKEYBOARDEVENTHANDLER_H

#include <tlinsSystemServiceClient.hpp>
#include <tlinskeyboard.h>
#include <memory>
#include <thread>

namespace tlinsAstroPilot
{

class tlinsKeyboardEventHandler
{
private:
	std :: unique_ptr<tlinsSystemServiceClient> eventsReader;
	void operator()( const tlinsSystemServiceClient :: Event &ev );

	void applayConfiguration();

	TlinsAstroBase :: tlinsKeyboard keyboardMapper;

public:
	tlinsKeyboardEventHandler( std ::shared_ptr<grpc ::Channel> &channel );
	tlinsKeyboardEventHandler() = delete;
	virtual ~tlinsKeyboardEventHandler();
};

};

#endif // TLINSKEYBOARDEVENTHANDLER_H
