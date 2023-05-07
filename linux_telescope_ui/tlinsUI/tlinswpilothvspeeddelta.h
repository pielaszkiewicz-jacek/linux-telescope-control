#ifndef TLINSWPILOTHVSPEEDDELTA_H
#define TLINSWPILOTHVSPEEDDELTA_H

#include <QJsonObject>
#include <QWidget>
#include <tlinspilotshortcutsdefinitioninterface.h>

namespace Ui {
class tlinsWPilotHVSpeedDelta;
}

class tlinsWPilotHVSpeedDelta
    : public QWidget,
      public TlinsAstroBase::tlinsPilotShortcutsDefinitionInterface {
    Q_OBJECT

public slots:
    void stepsSelected();
    void degrisSelected();

public:
    virtual void setParameters(const QJsonObject& doc);
    virtual void getParameters(QJsonObject& doc);
    virtual QWidget* getWidget();
    virtual void reset();
    virtual TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode
    getValidMode();

    explicit tlinsWPilotHVSpeedDelta(QWidget* parent = nullptr);
    ~tlinsWPilotHVSpeedDelta();

private:
    Ui::tlinsWPilotHVSpeedDelta* ui;
};

#endif // TLINSWPILOTHVSPEEDDELTA_H
