#ifndef TLINSWPILOTSETREFERENCEOBJECT_H
#define TLINSWPILOTSETREFERENCEOBJECT_H

#include <QWidget>
#include <tlinspilotshortcutsdefinitioninterface.h>

namespace Ui {
class tlinsWPilotSetReferenceObject;
}

class tlinsWPilotSetReferenceObject : public QWidget,
                                      public TlinsAstroBase::tlinsPilotShortcutsDefinitionInterface {
    Q_OBJECT

public:
    virtual void setParameters(const QJsonObject& doc);
    virtual void getParameters(QJsonObject& doc);
    virtual QWidget* getWidget();
    virtual void reset();
    virtual TlinsAstroBase::tlinsPilotShortcutsDefinitionValidMode getValidMode();

    explicit tlinsWPilotSetReferenceObject(QWidget* parent = nullptr);
    ~tlinsWPilotSetReferenceObject();

private:
    Ui::tlinsWPilotSetReferenceObject* ui;
};

#endif // TLINSWPILOTSETREFERENCEOBJECT_H
