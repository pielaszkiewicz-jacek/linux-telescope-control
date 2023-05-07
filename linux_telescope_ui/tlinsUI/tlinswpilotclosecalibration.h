#ifndef TLINSWPILOTCLOSECALIBRATION_H
#define TLINSWPILOTCLOSECALIBRATION_H

#include <QWidget>
#include <tlinspilotshortcutsdefinitioninterface.h>

namespace Ui {
class tlinsWPilotCloseCalibration;
}

class tlinsWPilotCloseCalibration : public QWidget,
                                    public TlinsAstroBase::tlinsPilotShortcutsDefinitionInterface {
    Q_OBJECT

public:
    virtual void setParameters(const QJsonObject& doc);
    virtual void getParameters(QJsonObject& doc);
    virtual QWidget* getWidget();
    virtual void reset();
    virtual TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode getValidMode();

    explicit tlinsWPilotCloseCalibration(QWidget* parent = nullptr);
    ~tlinsWPilotCloseCalibration();

private:
    Ui::tlinsWPilotCloseCalibration* ui;
};

#endif // TLINSWPILOTCLOSECALIBRATION_H
