QT -= gui
QT += sql
QT += core

CONFIG += c++14 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#HEADERS +=
#	tlinsjoystickeventhandler.h \
#	tlinskeyboardeventhandler.h \
#	tlinspilotsystemlistener.h \
#	tlinspluginhorisintalvertical.h \
#	tlinspluginhorisintalverticalsteps.h \
#	tlinsplugintrackingstart.h \
#	tlinsplugintrackingstop.h \
#	tlinspluginutilsmoverequest.h \
#	tlinsshortcutsmanager.h \
#	tlinsrcevenethandler.h \
#	tlinspluginsstate.h \
#	tlinsdceventhandler.h \
#	tlinspluginresetcalibration.h \
#	tlinspluginsetreferenceobject.h \
#	tlinspluginclosecalibration.h \
#	tlinspluginradcincrement.h \
#	tlinspluginhorisontalverticaldelta.h \
#	tlinspluginhorisontalverticalspeeddelta.h \
#	tlinspluginradcdelta.h \
#	tlinspluginradcspeeddelta.h

SOURCES += \
		main.cpp
#	tlinsjoystickeventhandler.cpp \
#	tlinskeyboardeventhandler.cpp \
#	tlinspilotsystemlistener.cpp \
#	tlinspluginhorisintalvertical.cpp \
#	tlinspluginhorisintalverticalsteps.cpp \
#	tlinsplugintrackingstart.cpp \
#	tlinsplugintrackingstop.cpp \
#	tlinspluginutilsmoverequest.cpp \
#	tlinsshortcutsmanager.cpp \
#	tlinsrcevenethandler.cpp \
#	tlinspluginsstate.cpp \
#	tlinsdceventhandler.cpp \
#	tlinspluginresetcalibration.cpp \
#	tlinspluginsetreferenceobject.cpp \
#	tlinspluginclosecalibration.cpp \
#	tlinspluginradcincrement.cpp \
#	tlinspluginhorisontalverticaldelta.cpp \
#	tlinspluginhorisontalverticalspeeddelta.cpp \
#	tlinspluginradcdelta.cpp \
#	tlinspluginradcspeeddelta.cpp

INCLUDEPATH += $$PWD/../external/release/include \
			   $$PWD/../current/math/astro/include/ \
               $$PWD/../current/client/include/ \
               $$PWD/../current/include/parameters/ \
               $$PWD/../current/include/ \
               $$PWD/../current/include/sdevice/ \
               $$PWD/../current/system_service/client/include \
			   $$PWD/../current/system_service/include \
               $$PWD/../current/generated/ \
               $$PWD/../build-linux_telescope_ui_lib-Debug \
			   $$PWD/../current_pilot_lib \
			   $$PWD/../linux_telescope_ui_lib \
               $$PWD/../linux_telescope_ui_lib/sofa/include \
               /usr/local/include \
               $$PWD/../current/x86


unix|win32: LIBS += -L$$PWD/../external/release/lib
unix|win32: LIBS += -L$$PWD/../external/release/lib64
unix|win32: LIBS += -L$$PWD/../build-linux_telescope_ui_lib-Debug/
unix|win32: LIBS += -L$$PWD/../build-linux_telescope_pilot_lib-Debug/
unix|win32: LIBS += -L$$PWD/../current/x86/
unix|win32: LIBS += -Wl,--whole-archive -llinux_telescope_pilot_lib -Wl,--no-whole-archive
unix|win32: LIBS += -ltlins_system_service_client
unix|win32: LIBS += -llinux_telescope_ui_lib
unix|win32: LIBS += -ltlins_loger
unix|win32: LIBS += -ltlins_client
unix|win32: LIBS += -ltlins_rpc
unix|win32: LIBS += -lprotobuf
unix|win32: LIBS += -lgrpc++
unix|win32: LIBS += -lgrpc
