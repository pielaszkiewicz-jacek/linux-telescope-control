#ifndef TLINSWPILOTHVDELTA_H
#define TLINSWPILOTHVDELTA_H

#include <QJsonObject>
#include <QWidget>
#include <tlinspilotshortcutsdefinitioninterface.h>

namespace Ui {
class tlinsWPilotHVDelta;
}

class tlinsWPilotHVDelta : public QWidget,
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
    virtual TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode getValidMode();

    explicit tlinsWPilotHVDelta(QWidget* parent = nullptr);
    ~tlinsWPilotHVDelta();

private:
    Ui::tlinsWPilotHVDelta* ui;
};

#endif // TLINSWPILOTHVDELTA_H
