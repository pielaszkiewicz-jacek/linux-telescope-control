#include "tlinsjoystickeventhandler.h"
#include "tlinskeyboardeventhandler.h"
#include <QCoreApplication>
#include <QtDebug>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>
#include <grpc/grpc.h>
#include <tlinsBacktrace.hpp>
#include <tlinsconfiguration.h>
#include <tlinsconnection.h>
#include <tlinspilot.h>
#include <tlinsserverstatusinfo.h>

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    tlinsAstroPilot::tlinsPilot pilot { TLINS_CONNECTION_DEFAULT };

    return a.exec();
}
