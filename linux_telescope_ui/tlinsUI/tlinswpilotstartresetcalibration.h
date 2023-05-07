#ifndef TLINSWPILOTSTARTRESETCALIBRATION_H
#define TLINSWPILOTSTARTRESETCALIBRATION_H

#include <QWidget>
#include <tlinspilotshortcutsdefinitioninterface.h>

namespace Ui {
class tlinsWPilotStartResetCalibration;
}

class tlinsWPilotStartResetCalibration
    : public QWidget,
      public TlinsAstroBase::tlinsPilotShortcutsDefinitionInterface {
    Q_OBJECT

public:
    virtual void setParameters(const QJsonObject& doc);
    virtual void getParameters(QJsonObject& doc);
    virtual QWidget* getWidget();
    virtual void reset();
    virtual TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode
    getValidMode();

    explicit tlinsWPilotStartResetCalibration(QWidget* parent = nullptr);
    ~tlinsWPilotStartResetCalibration();

private:
    Ui::tlinsWPilotStartResetCalibration* ui;
};

#endif // TLINSWPILOTSTARTRESETCALIBRATION_H
