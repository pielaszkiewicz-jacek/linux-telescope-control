#ifndef TLINSWPILOTCLOSEVELOCITYMEASURMENT_H
#define TLINSWPILOTCLOSEVELOCITYMEASURMENT_H

#include <QWidget>
#include <tlinspilotshortcutsdefinitioninterface.h>

namespace Ui {
class tlinsWPilotCloseVelocityMeasurment;
}

class tlinsWPilotCloseVelocityMeasurment : public QWidget,
                                           public TlinsAstroBase::tlinsPilotShortcutsDefinitionInterface {
    Q_OBJECT

public:
    virtual void setParameters(const QJsonObject& doc);
    virtual void getParameters(QJsonObject& doc);
    virtual QWidget* getWidget();
    virtual void reset();
    virtual TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode getValidMode();

    explicit tlinsWPilotCloseVelocityMeasurment(QWidget* parent = nullptr);
    ~tlinsWPilotCloseVelocityMeasurment();

private:
    Ui::tlinsWPilotCloseVelocityMeasurment* ui;
};

#endif // TLINSWPILOTCLOSEVELOCITYMEASURMENT_H
