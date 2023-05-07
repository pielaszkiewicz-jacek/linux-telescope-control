#ifndef TLINSWPILOTRADCINCREMENT_H
#define TLINSWPILOTRADCINCREMENT_H

#include <QJsonObject>
#include <QWidget>
#include <tlinspilotshortcutsdefinitioninterface.h>

namespace Ui {
class tlinsWPilotRaDcIncrement;
}

class tlinsWPilotRaDcIncrement : public QWidget,
                                 public TlinsAstroBase::tlinsPilotShortcutsDefinitionInterface {
    Q_OBJECT

public slots:
    void raAxisSelected();
    void dcAxisSelected();

public:
    virtual void setParameters(const QJsonObject& doc);
    virtual void getParameters(QJsonObject& doc);
    virtual QWidget* getWidget();
    virtual void reset();
    virtual TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode getValidMode();

    explicit tlinsWPilotRaDcIncrement(QWidget* parent = nullptr);
    ~tlinsWPilotRaDcIncrement();

private:
    Ui::tlinsWPilotRaDcIncrement* ui;
};

#endif // TLINSWPILOTRADCINCREMENT_H
