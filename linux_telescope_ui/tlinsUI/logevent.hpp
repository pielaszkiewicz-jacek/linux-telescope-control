#ifndef LOGEVENT_HPP
#define LOGEVENT_HPP

#include "tlinsuimainwindow.h"

extern tlinsUIMainWindow* getMainWindowInstance();

#define PRINT_LOG(s)                               \
    do {                                           \
        emit getMainWindowInstance()->logEvent(s); \
    } while (false)

#endif // LOGEVENT_HPP
