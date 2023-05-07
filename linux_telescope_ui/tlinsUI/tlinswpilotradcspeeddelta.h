#ifndef TLINSWPILOTRADCSPEEDDELTA_H
#define TLINSWPILOTRADCSPEEDDELTA_H

#include <QJsonObject>
#include <QWidget>
#include <tlinspilotshortcutsdefinitioninterface.h>

namespace Ui {
class tlinsWPilotRaDcSpeedDelta;
}

class tlinsWPilotRaDcSpeedDelta
    : public QWidget,
      public TlinsAstroBase::tlinsPilotShortcutsDefinitionInterface {
    Q_OBJECT

public slots:
    void raSelected();
    void dcSelected();

public:
    virtual void setParameters(const QJsonObject& doc);
    virtual void getParameters(QJsonObject& doc);
    virtual QWidget* getWidget();
    virtual void reset();
    virtual TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode
    getValidMode();

    explicit tlinsWPilotRaDcSpeedDelta(QWidget* parent = nullptr);
    ~tlinsWPilotRaDcSpeedDelta();

private:
    Ui::tlinsWPilotRaDcSpeedDelta* ui;
};

#endif // TLINSWPILOTRADCSPEEDDELTA_H
