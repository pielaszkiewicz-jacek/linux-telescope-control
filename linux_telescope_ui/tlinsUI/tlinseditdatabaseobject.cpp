#include "tlinseditdatabaseobject.h"
#include "ui_tlinseditdatabaseobject.h"

#include <QDebug>
#include <QSize>

tlinsEditDatabaseObject::tlinsEditDatabaseObject(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::tlinsEditDatabaseObject)
{
    ui->setupUi(this);

    // Set dialog as modal window
    this->setModal(true);
}

tlinsEditDatabaseObject::~tlinsEditDatabaseObject()
{
    delete ui;
}

void tlinsEditDatabaseObject::setCatalogItem(const TlinsAstroBase::tlinsAstroCatalogItem& v)
{
    ui->databaseObject->setCatalogItem(v);
}

void tlinsEditDatabaseObject::setReadOnly(const bool v)
{
    ui->databaseObject->setReadOnly(v);
}

void tlinsEditDatabaseObject::setIsUpdate(bool v)
{
    isUpdate = v;
    ui->databaseObject->blockCatalogInfo(v);
}

void tlinsEditDatabaseObject::on_buttons_accepted()
{
    TlinsAstroBase::tlinsAstroCatalogItem v = ui->databaseObject->getCatalogItem();

    if (isUpdate) {
        emit objectChanged(v, id);
    } else {
        emit objectCreated(v);
    }
}

void tlinsEditDatabaseObject::on_buttons_rejected()
{
}
