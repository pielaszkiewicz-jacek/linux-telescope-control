QT -= gui
QT += sql
QT += core

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
	tlinspilot.cpp \
	tlinsjoystickeventhandler.cpp \
	tlinskeyboardeventhandler.cpp \
	tlinspilotsystemlistener.cpp \
	tlinspluginhorisintalvertical.cpp \
	tlinspluginhorisintalverticalkeys.cpp \
	tlinspluginhorisintalverticalsteps.cpp \
	tlinsplugintrackingstart.cpp \
	tlinsplugintrackingstop.cpp \
	tlinspluginutilsmoverequest.cpp \
	tlinsshortcutsmanager.cpp \
	tlinsrcevenethandler.cpp \
	tlinspluginsstate.cpp \
	tlinsdceventhandler.cpp \
	tlinspluginresetcalibration.cpp \
	tlinspluginsetreferenceobject.cpp \
	tlinspluginclosecalibration.cpp \
	tlinspluginradcincrement.cpp \
	tlinspluginhorisontalverticaldelta.cpp \
	tlinspluginhorisontalverticalspeeddelta.cpp \
	tlinspluginradcdelta.cpp \
	tlinspluginradcspeeddelta.cpp


HEADERS += \
	tlinspilot.h \
	tlinsjoystickeventhandler.h \
	tlinskeyboardeventhandler.h \
	tlinspilotsystemlistener.h \
	tlinspluginhorisintalvertical.h \
	tlinspluginhorisintalverticalkeys.h \
	tlinspluginhorisintalverticalsteps.h \
	tlinsplugintrackingstart.h \
	tlinsplugintrackingstop.h \
	tlinspluginutilsmoverequest.h \
	tlinsshortcutsmanager.h \
	tlinsrcevenethandler.h \
	tlinspluginsstate.h \
	tlinsdceventhandler.h \
	tlinspluginresetcalibration.h \
	tlinspluginsetreferenceobject.h \
	tlinspluginclosecalibration.h \
	tlinspluginradcincrement.h \
	tlinspluginhorisontalverticaldelta.h \
	tlinspluginhorisontalverticalspeeddelta.h \
	tlinspluginradcdelta.h \
	tlinspluginradcspeeddelta.h

INCLUDEPATH += $$PWD/../external/release.x86/include \
			   $$PWD/../current/math/astro/include/ \
			   $$PWD/../current/client/include/ \
			   $$PWD/../current/include/parameters/ \
			   $$PWD/../current/include/ \
			   $$PWD/../current/include/sdevice/ \
			   $$PWD/../current/system_service/client/include \
			   $$PWD/../current/system_service/include \
			   $$PWD/../current/generated/ \
			   $$PWD/../build-linux_telescope_ui_lib-Debug \
			   $$PWD/../linux_telescope_ui_lib \
			   $$PWD/../linux_telescope_ui_lib/sofa/include \
			   $$PWD/../external/eigen-3.4.0 \
			   /usr/local/include \
			   $$PWD/../current/x86


# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
