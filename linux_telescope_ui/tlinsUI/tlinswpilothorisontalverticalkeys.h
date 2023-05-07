#ifndef TLINSWPILOTHORISONTALVERTICALKEYS_H
#define TLINSWPILOTHORISONTALVERTICALKEYS_H

#include <QWidget>
#include <tlinspilotshortcutsdefinitioninterface.h>

namespace Ui {
class tlinsWPilotHorisontalVerticalKeys;
}

class tlinsWPilotHorisontalVerticalKeys : public QWidget,
                                          public TlinsAstroBase::tlinsPilotShortcutsDefinitionInterface {
    Q_OBJECT

public:
    virtual void setParameters(const QJsonObject& doc);
    virtual void getParameters(QJsonObject& doc);
    virtual QWidget* getWidget();
    virtual void reset();
    virtual TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode getValidMode();

    explicit tlinsWPilotHorisontalVerticalKeys(QWidget* parent = nullptr);
    ~tlinsWPilotHorisontalVerticalKeys();

private:
    Ui::tlinsWPilotHorisontalVerticalKeys* ui;
};

#endif // TLINSWPILOTHORISONTALVERTICALKEYS_H
