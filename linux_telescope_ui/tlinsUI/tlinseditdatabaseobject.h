#ifndef TLINSEDITDATABASEOBJECT_H
#define TLINSEDITDATABASEOBJECT_H

#include "ui_tlinseditdatabaseobject.h"

#include "tlinswastrodatabaseobject.h"

#include <QDialog>
#include <QVBoxLayout>

namespace Ui {
class tlinsEditDatabaseObject;
}

class tlinsEditDatabaseObject : public QDialog {
    Q_OBJECT

private:
    Ui::tlinsEditDatabaseObject* ui;

public:
    void reset()
    {
        ui->databaseObject->resetCatalogItem();
    }

    void setIsUpdate(bool v);

    void setCatalogItem(const TlinsAstroBase::tlinsAstroCatalogItem& v, int id_)
    {
        ui->databaseObject->setCatalogItem(v);
        id = id_;
    }

    void setReadOnly(const bool v);
    void setCatalogItem(const TlinsAstroBase::tlinsAstroCatalogItem& v);

    explicit tlinsEditDatabaseObject(QWidget* parent = 0);
    ~tlinsEditDatabaseObject();

signals:
    void objectChanged(TlinsAstroBase::tlinsAstroCatalogItem v, int id);
    void objectCreated(TlinsAstroBase::tlinsAstroCatalogItem v);

private slots:
    void on_buttons_accepted();
    void on_buttons_rejected();

private:
    int id;

    bool isUpdate;
};

#endif // TLINSEDITDATABASEOBJECT_H
