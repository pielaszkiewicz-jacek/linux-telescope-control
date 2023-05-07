#ifndef TLINSPILOTSHORTCUTSDEFINITIONINTERFACE_H
#define TLINSPILOTSHORTCUTSDEFINITIONINTERFACE_H

#include "tlinspilotshortcutsdefinitionvalidmode.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QWidget>

namespace TlinsAstroBase {

class tlinsPilotShortcutsDefinitionInterface {
public:
    //	enum class validMode
    //	{
    //		DEVICE	= 1,
    //		ASTRO   = 2,
    //		BOTH    = 3
    //	};
public:
    virtual void setParameters(const QJsonObject& doc) = 0;
    virtual void getParameters(QJsonObject& doc) = 0;
    virtual QWidget* getWidget() = 0;
    virtual void reset() = 0;
    virtual TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode getValidMode() = 0;
    virtual ~tlinsPilotShortcutsDefinitionInterface();
};

}

#endif // TLINSPILOTSHORTCUTSDEFINITIONINTERFACE_H
