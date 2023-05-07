#ifndef TLINSWPILOTHORISINTALVERTICALSTEPS_H
#define TLINSWPILOTHORISINTALVERTICALSTEPS_H

#include <QWidget>
#include <tlinspilotshortcutsdefinitioninterface.h>

namespace Ui {
class tlinsWPilotHorisintalVerticalSteps;
}

class tlinsWPilotHorisintalVerticalSteps : public QWidget,
                                           public TlinsAstroBase::tlinsPilotShortcutsDefinitionInterface {
    Q_OBJECT

public:
    virtual void setParameters(const QJsonObject& doc);
    virtual void getParameters(QJsonObject& doc);
    virtual QWidget* getWidget();
    virtual void reset();
    virtual TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode getValidMode();

    explicit tlinsWPilotHorisintalVerticalSteps(QWidget* parent = nullptr);
    ~tlinsWPilotHorisintalVerticalSteps();

private:
    Ui::tlinsWPilotHorisintalVerticalSteps* ui;
};

#endif // TLINSWPILOTHORISINTALVERTICALSTEPS_H
