#ifndef TLINSWPILOTSETVELOCITYMEASURMENT_H
#define TLINSWPILOTSETVELOCITYMEASURMENT_H

#include <QWidget>
#include <tlinspilotshortcutsdefinitioninterface.h>

namespace Ui {
class tlinsWPilotSetVelocityMeasurment;
}

class tlinsWPilotSetVelocityMeasurment : public QWidget,
                                         public TlinsAstroBase::tlinsPilotShortcutsDefinitionInterface {
    Q_OBJECT

public:
    virtual void setParameters(const QJsonObject& doc);
    virtual void getParameters(QJsonObject& doc);
    virtual QWidget* getWidget();
    virtual void reset();
    virtual TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode getValidMode();

    explicit tlinsWPilotSetVelocityMeasurment(QWidget* parent = nullptr);
    ~tlinsWPilotSetVelocityMeasurment();

private:
    Ui::tlinsWPilotSetVelocityMeasurment* ui;
};

#endif // TLINSWPILOTSETVELOCITYMEASURMENT_H
