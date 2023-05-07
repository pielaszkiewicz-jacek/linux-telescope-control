#ifndef TLINSWPILOTRADCDELTA_H
#define TLINSWPILOTRADCDELTA_H

#include <QJsonObject>
#include <QWidget>
#include <tlinspilotshortcutsdefinitioninterface.h>

namespace Ui {
class tlinsWPilotRaDcDelta;
}

class tlinsWPilotRaDcDelta : public QWidget,
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
    virtual TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode getValidMode();

    explicit tlinsWPilotRaDcDelta(QWidget* parent = nullptr);
    ~tlinsWPilotRaDcDelta();

private:
    Ui::tlinsWPilotRaDcDelta* ui;
};

#endif // TLINSWPILOTRADCDELTA_H
