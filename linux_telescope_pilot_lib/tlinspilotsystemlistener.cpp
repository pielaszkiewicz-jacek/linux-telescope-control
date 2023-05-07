#include "tlinspilotsystemlistener.h"

namespace tlinsAstroPilot
{

tlinsPilotSystemListener::tlinsPilotSystemListener()
{
	std ::shared_ptr<grpc ::Channel> channel;
	tlinsKeyboardEventHandler lisener( channel );
}

};
