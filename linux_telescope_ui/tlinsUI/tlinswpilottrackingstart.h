#ifndef TLINSWPILOTTRACKINGSTART_H
#define TLINSWPILOTTRACKINGSTART_H

#include <QWidget>
#include <tlinspilotshortcutsdefinitioninterface.h>

namespace Ui {
class tlinsWPilotTrackingStart;
}

class tlinsWPilotTrackingStart
    : public QWidget,
      public TlinsAstroBase::tlinsPilotShortcutsDefinitionInterface {
    Q_OBJECT

public:
    virtual void setParameters(const QJsonObject& doc);
    virtual void getParameters(QJsonObject& doc);
    virtual QWidget* getWidget();
    virtual void reset();
    virtual TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode
    getValidMode()
    {
        return TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode::BOTH;
    }

    explicit tlinsWPilotTrackingStart(QWidget* parent = nullptr);
    ~tlinsWPilotTrackingStart();

private:
    Ui::tlinsWPilotTrackingStart* ui;
};

#endif // TLINSWPILOTTRACKINGSTART_H
