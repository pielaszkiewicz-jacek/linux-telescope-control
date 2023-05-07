#ifndef TLINSJOYSTICKEVENTHANDLER_H
#define TLINSJOYSTICKEVENTHANDLER_H

#include <tlinsSystemServiceClient.hpp>
#include <tlinsjoystick.h>

namespace tlinsAstroPilot
{

class tlinsJoystickEventHandler
{
private:
    std :: unique_ptr<tlinsSystemServiceClient> eventsReader;
    void operator()( const tlinsSystemServiceClient :: Event &ev );
    void applayConfiguration();

    TlinsAstroBase :: tlinsJoystick joystickMapper;

public:
    tlinsJoystickEventHandler( std ::shared_ptr<grpc ::Channel> &channel );
    tlinsJoystickEventHandler() = delete;
    virtual ~tlinsJoystickEventHandler();

};

};

#endif // TLINSJOYSTICKEVENTHANDLER_H
