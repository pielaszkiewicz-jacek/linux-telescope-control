#ifndef TLINSPILOT_H
#define TLINSPILOT_H

#include "tlinskeyboardeventhandler.h"
#include "tlinsjoystickeventhandler.h"

#include <memory>
#include <string>

namespace tlinsAstroPilot
{

class tlinsPilot
{
private:
    std::string connectionName;
    std::unique_ptr<tlinsKeyboardEventHandler> lisenerKeyboard;
    std::unique_ptr<tlinsJoystickEventHandler> lisenerJoystick;
    std ::shared_ptr<grpc ::Channel> systemServiceChannel;

    void connectMoveAndAstroService();
    void connectService();

public:
    tlinsPilot(const std::string &connectionName_);
	virtual ~tlinsPilot();
};

};

#endif // TLINSPILOT_H
