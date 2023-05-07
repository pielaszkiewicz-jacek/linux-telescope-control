#include "tlinswastrodatabasesearch3.h"
#include "tlinsuistylesmanager.h"
#include "ui_tlinswastrodatabasesearch3.h"
#include <QDebug>
#include <string>

tlinsWAstroDatabaseSearch3::tlinsWAstroDatabaseSearch3(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWAstroDatabaseSearch3)
{
    ui->setupUi(this);

    ui->deg->setMinMax(0, 90);

    QSize s;

    // Control styles
    std::string style;
    bool res = tlinsUiStylesManager::getStyle(tlinsUiStylesManager::COMMON,
        tlinsUiStylesManager::FieldType::GROUP_BOX,
        style);
    if (res) {
        ui->sqlAdanced->setStyleSheet(QString(style.c_str()));
    }

    res = tlinsUiStylesManager::getStyle(tlinsUiStylesManager::COMMON,
        tlinsUiStylesManager::FieldType::TEXT_EDIT,
        style);
    if (res) {
        ui->sqlText->setStyleSheet(QString(style.c_str()));
    }

    // Magnitude
    ui->magnitudeFrom->setDecimal(4);
    ui->magnitudeFrom->setMinMax(-100.0, +100.0);
    ui->magnitudeFrom->disableButtons();

    ui->magnitudeTo->setDecimal(4);
    ui->magnitudeTo->setMinMax(-100.0, +100.0);
    ui->magnitudeTo->disableButtons();

    // Sygnaly
    connect(ui->useRa, SIGNAL(stateChanged(int)),
        this, SLOT(disableEnableRA()));
    connect(ui->useDc, SIGNAL(stateChanged(int)),
        this, SLOT(disableEnableDC()));
    connect(ui->useObjectConstelation, SIGNAL(stateChanged(int)),
        this, SLOT(disableEnableObjectConstelation()));
    connect(ui->useObjectType, SIGNAL(stateChanged(int)),
        this, SLOT(disableEnableObjectType()));
    connect(ui->useObjectCatalog, SIGNAL(stateChanged(int)),
        this, SLOT(disableEnableCatalog()));
    connect(ui->useObjectName, SIGNAL(stateChanged(int)),
        this, SLOT(disableEnableObjectName()));
    connect(ui->useRadius, SIGNAL(stateChanged(int)),
        this, SLOT(disableEnableRadius()));
    connect(ui->useObjectIdInCatalog, SIGNAL(stateChanged(int)),
        this, SLOT(disableEnableObjectIdInCatalog()));
    connect(ui->useMagnitudeFrom, SIGNAL(stateChanged(int)),
        this, SLOT(disableEnableMagnitudeFrom()));
    connect(ui->useMagnitudeTo, SIGNAL(stateChanged(int)),
        this, SLOT(disableEnableMagnitudeTo()));
}

std::string replaceComa(double in)
{
    std::string v = std::to_string(in);
    std::replace(v.begin(), v.end(), ',', '.');
    return v;
}

std::string tlinsWAstroDatabaseSearch3::getCondition() const
{
    // Czytanie poszczegolnych kontrolek

    // Wartosci parameterow
    double vdc = ui->dc->getValue();
    double vra = ui->ra->getValue();
    double vrad = ui->deg->getValue();
    double vradh = 24.0 * (ui->deg->getValue() / 360.0);

    std::string type = ui->objType->getType();
    std::string name = ui->objName->getValue();
    std::string constelation = ui->objConstelation->getConstelation();
    std::string astroCatalog = ui->objCatalog->getType();
    std::string objectIdInCatalog = ui->objCatalogObjectId->getID();
    double objMagnitudeFrom = ui->magnitudeFrom->getValue();
    double objMagnitudeTo = ui->magnitudeTo->getValue();
    std::string plainSql = ui->sqlText->toPlainText().toStdString();

    bool useType = ui->useObjectType->isChecked();
    bool useRa = ui->useRa->isChecked();
    bool useDc = ui->useDc->isChecked();
    bool useRad = ui->useRadius->isChecked();
    bool useName = ui->useObjectName->isChecked();
    bool useConstelation = ui->useObjectConstelation->isChecked();
    bool useAstroCatalog = ui->useObjectCatalog->isChecked();
    bool useObjectIdInCatalog = ui->useObjectIdInCatalog->isChecked();
    bool useObjMagnitudeFrom = ui->useMagnitudeFrom->isChecked();
    bool useObjMagnitudeTo = ui->useMagnitudeTo->isChecked();
    bool usePlainSql = ui->sqlAdanced->isChecked();

    if (!ui->gbBasic->isChecked()) {
        useType = false;
        useRa = false;
        useDc = false;
        useRad = false;
        useName = false;
        useConstelation = false;
        useAstroCatalog = false;
        useObjectIdInCatalog = false;
        useObjMagnitudeFrom = false;
        useObjMagnitudeTo = false;
    } else {
        // Okreslenie ktore parametery beda brane pod uwage
        if (!ui->gbBasic->isChecked()) {
            useType = false;
            useName = false;
            useAstroCatalog = false;
            useConstelation = false;
            useObjectIdInCatalog = false;
        } else {
            if (name.length() == 0)
                useName = false;

            if (objectIdInCatalog.length() == 0)
                useObjectIdInCatalog = false;
        }

        if (!ui->gbCoordinate->isChecked()) {
            useRa = false;
            useDc = false;
            useRad = false;
        }

        if (!ui->gbMagnitude->isChecked()) {
            useObjMagnitudeFrom = false;
            useObjMagnitudeTo = false;
        }
    }
    if (!useRad) {
        vrad = 0.0;
        vradh = 0.0;
    }

    if (usePlainSql && ui->sqlText->toPlainText().length() == 0) {
        usePlainSql = false;
    }

    //
    // Budowanie wynikowego
    //
    std::string resultSql = " 1 = 1 ";

    if (useRa) {
        double vrap = vra + vradh;
        double vram = vra - vradh;

        if (vram >= 0.00 && vrap < 24.0) {
            resultSql.append(" and ra <= ");
            resultSql.append(replaceComa(vrap));
            resultSql.append(" and ra >= ");
            resultSql.append(replaceComa(vram));
        }

        if (vrap >= 24.0) {
            resultSql.append(" and ( ( ra >= ");
            resultSql.append(replaceComa(vram));
            resultSql.append(" and ra < 24. 0 ) ");
            resultSql.append("       or ( ra < ");
            resultSql.append(replaceComa(vrap - 24.0));
            resultSql.append(" ) ) ");
        }

        if (vram < 0.0) {
            resultSql.append(" and ( ( ra < 24.0 and ra >= ");
            resultSql.append(replaceComa(24.0 - vra + vram));
            resultSql.append(" ) ");
            if (vra > 0.0) {
                resultSql.append("       or ( ra < ");
                resultSql.append(replaceComa(vrap));
                resultSql.append(" ) ");
            }
            resultSql.append(" ) ");
        }
    }

    if (useDc) {
        double vdcp = vdc + vrad;
        double vdcm = vdc - vrad;

        if (vdcp > 90.0)
            vdcp = 90.0;
        if (vdcm < -90.0)
            vdcm = -90.0;

        resultSql.append(" and dc <= ");
        resultSql.append(replaceComa(vdcp));
        resultSql.append(" and dc >= ");
        resultSql.append(replaceComa(vdcm));
    }

    if (useName) {
        resultSql.append(" and name like('");
        resultSql.append(name);
        resultSql.append("')");
    }

    if (useType) {
        resultSql.append(" and type = '");
        resultSql.append(type);
        resultSql.append("'");
    }

    if (useConstelation) {
        resultSql.append(" and constelation = '");
        resultSql.append(constelation);
        resultSql.append("'");
    }

    if (useAstroCatalog) {
        resultSql.append(" and catalog_type = '");
        resultSql.append(astroCatalog);
        resultSql.append("'");
    }

    if (useObjectIdInCatalog) {
        resultSql.append(" and object_id_in_catalog like( '");
        resultSql.append(objectIdInCatalog);
        resultSql.append("')");
    }

    if (usePlainSql) {
        resultSql.append(" and ");
        resultSql.append(plainSql);
    }

    if (useObjMagnitudeFrom) {
        resultSql.append(" and magnitude >= ");
        resultSql.append(replaceComa(objMagnitudeFrom));
    }

    if (useObjMagnitudeTo) {
        resultSql.append(" and magnitude <= ");
        resultSql.append(replaceComa(objMagnitudeTo));
    }

    // Budowanie klazuli where
    qDebug() << "Where ++[" << resultSql.c_str() << "]++";

    return resultSql;
}

void tlinsWAstroDatabaseSearch3::disableEnableRA()
{
    if (!ui->useRa->isChecked()) {
        ui->ra->setDisabled(true);
        ui->ra->setEnabled(false);
    } else {
        ui->ra->setDisabled(false);
        ui->ra->setEnabled(true);
    }
}

void tlinsWAstroDatabaseSearch3::disableEnableDC()
{
    if (!ui->useDc->isChecked()) {
        ui->dc->setDisabled(true);
        ui->dc->setEnabled(false);
    } else {
        ui->dc->setDisabled(false);
        ui->dc->setEnabled(true);
    }
}

void tlinsWAstroDatabaseSearch3::disableEnableRadius()
{
    if (!ui->useRadius->isChecked()) {
        ui->deg->setDisabled(true);
        ui->deg->setEnabled(false);
    } else {
        ui->deg->setDisabled(false);
        ui->deg->setEnabled(true);
    }
}

void tlinsWAstroDatabaseSearch3::disableEnableMagnitudeFrom()
{
    if (!ui->useMagnitudeFrom->isChecked()) {
        ui->magnitudeFrom->setDisabled(true);
        ui->magnitudeFrom->setEnabled(false);
    } else {
        ui->magnitudeFrom->setDisabled(false);
        ui->magnitudeFrom->setEnabled(true);
    }
}

void tlinsWAstroDatabaseSearch3::disableEnableMagnitudeTo()
{
    if (!ui->useMagnitudeTo->isChecked()) {
        ui->magnitudeTo->setDisabled(true);
        ui->magnitudeTo->setEnabled(false);
    } else {
        ui->magnitudeTo->setDisabled(false);
        ui->magnitudeTo->setEnabled(true);
    }
}

void tlinsWAstroDatabaseSearch3::disableEnableCatalog()
{
    if (!ui->useObjectCatalog->isChecked()) {
        ui->objCatalog->setDisabled(true);
        ui->objCatalog->setEnabled(false);
    } else {
        ui->objCatalog->setDisabled(false);
        ui->objCatalog->setEnabled(true);
    }
}

void tlinsWAstroDatabaseSearch3::disableEnableObjectType()
{
    if (!ui->useObjectType->isChecked()) {
        ui->objType->setDisabled(true);
        ui->objType->setEnabled(false);
    } else {
        ui->objType->setDisabled(false);
        ui->objType->setEnabled(true);
    }
}

void tlinsWAstroDatabaseSearch3::disableEnableObjectName()
{
    if (!ui->useObjectName->isChecked()) {
        ui->objName->setDisabled(true);
        ui->objName->setEnabled(false);
    } else {
        ui->objName->setDisabled(false);
        ui->objName->setEnabled(true);
    }
}

void tlinsWAstroDatabaseSearch3::disableEnableObjectIdInCatalog()
{
    if (!ui->useObjectIdInCatalog->isChecked()) {
        ui->objCatalogObjectId->setDisabled(true);
        ui->objCatalogObjectId->setEnabled(false);
    } else {
        ui->objCatalogObjectId->setDisabled(false);
        ui->objCatalogObjectId->setEnabled(true);
    }
}

void tlinsWAstroDatabaseSearch3::disableEnableObjectConstelation()
{
    if (!ui->useObjectConstelation->isChecked()) {
        ui->objConstelation->setDisabled(true);
        ui->objConstelation->setEnabled(false);
    } else {
        ui->objConstelation->setDisabled(false);
        ui->objConstelation->setEnabled(true);
    }
}

tlinsWAstroDatabaseSearch3::~tlinsWAstroDatabaseSearch3()
{
    delete ui;
}
