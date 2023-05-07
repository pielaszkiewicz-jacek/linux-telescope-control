#include "tlinswastrodatabaseobject.h"
#include "ui_tlinswastrodatabaseobject.h"

tlinsWAstroDatabaseObject::tlinsWAstroDatabaseObject(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWAstroDatabaseObject)
{
    ui->setupUi(this);

    ui->magnitude->setMinMax(-100.0, 100.0);
    ui->magnitude->disableButtons();
    ui->magnitudeError->setMinMax(-100.0, 100.0);
    ui->magnitudeError->disableButtons();
    ui->pmDc->setDecimal(6);
    ui->pmDc->disableButtons();
    ui->pmDcErr->setDecimal(6);
    ui->pmDcErr->disableButtons();
    ui->pmRa->setDecimal(6);
    ui->pmRa->disableButtons();
    ui->pmRaErr->setDecimal(6);
    ui->pmRaErr->disableButtons();
    ui->dcMinErr->setDecimal(6);
    ui->dcMinErr->disableButtons();
    ui->raMinErr->setDecimal(6);
    ui->raMinErr->disableButtons();
    ui->dcMeanErr->setDecimal(6);
    ui->dcMinErr->disableButtons();
    ui->raMeanErr->setDecimal(6);
    ui->raMeanErr->disableButtons();
    ui->parallex->setDecimal(6);
    ui->parallex->disableButtons();
    ui->radialVelocity->setDecimal(6);
    ui->radialVelocity->disableButtons();
    ui->centralEpochDc->setDecimal(6);
    ui->centralEpochDc->disableButtons();
    ui->centralEpochRa->setDecimal(6);
    ui->centralEpochRa->disableButtons();
}

void tlinsWAstroDatabaseObject::disableaTab(const int idx, const bool v)
{
    for (int i = 0; i < ui->tabWidget->count(); i++) {
        if (i == idx) {
            ui->tabWidget->widget(i)->setDisabled(v);
            return;
        }
    }
}

void tlinsWAstroDatabaseObject::setCatalogItem(const TlinsAstroBase::tlinsAstroCatalogItem& v)
{
    ui->objName->setValue(v.getName());
    ui->description->setPlainText(v.getDescription().c_str());
    ui->objConstelation->setCurrent(v.getConstelation().label);

    // Object type
    ui->objType->setCurrent(v.getType().label);
    ui->objectTypeDetails1->setText(QString(v.getTypeDetails1().c_str()));
    ui->objectTypeDetails2->setText(QString(v.getTypeDetails2().c_str()));
    ui->objectTypeDetails3->setText(QString(v.getTypeDetails3().c_str()));

    // Katalog
    ui->catalogID->setCurrent(v.getCatalogType().label);
    ui->objCatalogObjectId->setID(v.getObjectIdInCatalog());
    ui->catalogDescription->setText(QString(v.getObjectDescription().c_str()));

    // Wspolrzedne
    ui->ra->setValue(v.getRA());
    ui->raMinErr->setValue(v.getMinErrRA());
    ui->raMeanErr->setValue(v.getErrMeanRA());

    ui->dc->setValue(v.getDC());
    ui->dcMinErr->setValue(v.getMinErrDC());
    ui->dcMeanErr->setValue(v.getErrMeanDC());

    // Ruch wlasny
    ui->pmRa->setValue(v.getPmRA());
    ui->pmRaErr->setValue(v.getErrMeanPmRA());

    ui->pmDc->setValue(v.getPmDC());
    ui->pmDcErr->setValue(v.getErrMeanPmDC());

    // Epoka
    ui->centralEpochRa->setValue(v.getEpRA());
    ui->centralEpochDc->setValue(v.getEpDC());

    // Jasnosc
    ui->magnitude->setValue(v.getMagnitude());
    ui->magnitudeError->setValue(v.getErrMagnitude());

    ui->radialVelocity->setValue(v.getRadialVelocity());
    ui->parallex->setValue(v.getParallex());
}

void tlinsWAstroDatabaseObject::resetCatalogItem()
{
    ui->objName->setValue("");
    ui->description->setPlainText("");
    ui->objConstelation->setCurrent(0);

    // Object type
    ui->objType->setCurrent(0);
    ui->objectTypeDetails1->setText("");
    ui->objectTypeDetails2->setText("");
    ui->objectTypeDetails3->setText("");

    // Katalog
    //    objCatalog -> setCurrent( 0 );
    ui->objCatalogObjectId->setID("");
    ui->catalogDescription->setText("");

    // Wspolrzedne
    ui->ra->setValue(0.0);
    ui->raMinErr->setValue(0.0);
    ui->raMeanErr->setValue(0.0);

    ui->dc->setValue(0.0);
    ui->dcMinErr->setValue(0.0);
    ui->dcMeanErr->setValue(0.0);

    // Ruch wlasny
    ui->pmRa->setValue(0.0);
    ui->pmRaErr->setValue(0.0);

    ui->pmDc->setValue(0.0);
    ui->pmDcErr->setValue(0.0);

    // Epoka
    ui->centralEpochRa->setValue(0.0);
    ui->centralEpochDc->setValue(0.0);

    // Jasnosc
    ui->magnitude->setValue(0.0);
    ui->magnitudeError->setValue(0.0);

    ui->radialVelocity->setValue(0.0);
    ui->parallex->setValue(0.0);
}

void tlinsWAstroDatabaseObject::setMinimalInfo()
{
    for (int i = 0; i < ui->tabWidget->count(); i++) {
        if (ui->tabWidget->widget(i) == ui->tabCatalog) {
            ui->tabWidget->removeTab(i);
        }
    }

    ui->gbDescription->setVisible(false);
    ui->gbObjectType->setVisible(false);
}

void tlinsWAstroDatabaseObject::setReadOnly(const bool v)
{
    ui->tabCatalog->setDisabled(v);
    ui->tabCoordinate->setDisabled(v);
    ui->tabGeneralInfo->setDisabled(v);
}

void tlinsWAstroDatabaseObject::blockCatalogInfo(bool block)
{
    if (block) {
        ui->catalogID->setDisabled(true);
        ui->objCatalogObjectId->setDisabled(true);
        ui->catalogID->setEnabled(false);
        ui->objCatalogObjectId->setEnabled(false);
    } else {
        ui->catalogID->setDisabled(true);
        ui->objCatalogObjectId->setDisabled(true);
        ui->catalogID->setEnabled(true);
        ui->objCatalogObjectId->setEnabled(true);
    }
}

TlinsAstroBase::tlinsAstroCatalogItem tlinsWAstroDatabaseObject::getCatalogItem()
{
    TlinsAstroBase::tlinsAstroCatalogItem item;

    // Nazwa i opis obiektu
    item.setName(ui->objName->getValue());
    item.setDescription(ui->description->toPlainText().toStdString());

    // Typ obiektu
    {
        TlinsAstroBase::ObjectType::ObjectTypeInfo objTypeInfo;
        TlinsAstroBase::ObjectType::get(ui->objType->getType(), objTypeInfo);
        item.setType(objTypeInfo);
    }
    item.setTypeDetails1(ui->objectTypeDetails1->toPlainText().toStdString());
    item.setTypeDetails2(ui->objectTypeDetails2->toPlainText().toStdString());
    item.setTypeDetails3(ui->objectTypeDetails3->toPlainText().toStdString());
    {
        TlinsAstroBase::Constelations::ConstelationInfo constelationInfo;
        TlinsAstroBase::Constelations::get(ui->objConstelation->getConstelation(), constelationInfo);
        item.setConstelation(constelationInfo);
    }

    // Wspolrzedne
    item.setRA(ui->ra->getValue());
    item.setDC(ui->dc->getValue());
    item.setMinErrRA(ui->raMinErr->getValue());
    item.setMinErrDC(ui->dcMinErr->getValue());
    item.setErrMeanRA(ui->raMeanErr->getValue());
    item.setErrMeanDC(ui->dcMeanErr->getValue());

    item.setPmRA(ui->pmRa->getValue());
    item.setPmDC(ui->pmDc->getValue());
    item.setErrMeanPmRA(ui->pmRaErr->getValue());
    item.setErrMeanPmDC(ui->pmDcErr->getValue());

    // Epoka
    item.setEpRA(ui->centralEpochRa->getValue());
    item.setEpDC(ui->centralEpochDc->getValue());

    // Jasnosc
    item.setMagnitude(ui->magnitude->getValue());
    item.setErrMagnitude(ui->magnitudeError->getValue());

    // Katalog
    {
        TlinsAstroBase::CatalogType::CatalogTypeInfo catalogTypeInfo;
        TlinsAstroBase::CatalogType::get(ui->catalogID->getType(), catalogTypeInfo);
        item.setCatalogType(catalogTypeInfo);
    }
    item.setObjectIdInCatalog(ui->objCatalogObjectId->getID());
    item.setObjectDescription(ui->catalogDescription->toPlainText().toStdString());

    item.setRadialVelocity(ui->radialVelocity->getValue());
    item.setParallex(ui->parallex->getValue());

    return item;
}

tlinsWAstroDatabaseObject::~tlinsWAstroDatabaseObject()
{
    delete ui;
}
