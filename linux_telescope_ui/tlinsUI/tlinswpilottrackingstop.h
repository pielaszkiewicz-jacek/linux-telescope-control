#ifndef TLINSWPILOTTRACKINGSTOP_H
#define TLINSWPILOTTRACKINGSTOP_H

#include <QWidget>
#include <tlinspilotshortcutsdefinitioninterface.h>

namespace Ui {
class tlinsWPilotTrackingStop;
}

class tlinsWPilotTrackingStop
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

    explicit tlinsWPilotTrackingStop(QWidget* parent = nullptr);
    ~tlinsWPilotTrackingStop();

private:
    Ui::tlinsWPilotTrackingStop* ui;
};

#endif // TLINSWPILOTTRACKINGSTOP_H
