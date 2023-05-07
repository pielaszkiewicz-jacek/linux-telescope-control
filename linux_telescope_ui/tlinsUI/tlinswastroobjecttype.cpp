#include "tlinswastroobjecttype.h"
#include "tlinsastrocatalogitem.h"
#include "tlinsuistylesmanager.h"
#include "ui_tlinswastroobjecttype.h"
#include <QDebug>

tlinsWAstroObjectType::tlinsWAstroObjectType(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWAstroObjectType)
{
    ui->setupUi(this);

    for (int i = 0; i < TlinsAstroBase::ObjectType::count(); i++) {
        int id;
        std::string label;
        std::string name;
        TlinsAstroBase::ObjectType::get(i, id, label, name);

        QString qstrName(name.c_str());
        QString qstrLabel(label.c_str());
        QVariant qvarLabel(qstrLabel);

        ui->astroObjectType->addItem(qstrName, qvarLabel);
    }

    connect(ui->astroObjectType, SIGNAL(currentIndexChanged(QString)), this, SLOT(update()));
}

void tlinsWAstroObjectType::setCurrent(const int idx)
{
    ui->astroObjectType->setCurrentIndex(idx);
}

bool tlinsWAstroObjectType::setCurrent(const std::string& label)
{
    for (int i = 0; i < ui->astroObjectType->count(); i++) {
        QVariant v = ui->astroObjectType->itemData(i);
        if (v.toString() == QString(label.c_str())) {
            ui->astroObjectType->setCurrentIndex(i);
            return true;
        }
    }
    return false;
}

std::string tlinsWAstroObjectType::getType() const
{
    return ui->astroObjectType->currentData().toString().toStdString();
}

void tlinsWAstroObjectType::update()
{
    //	QVariant label = ui ->astroObjectType->currentData();
    QVariant label = ui->astroObjectType->currentText();
    emit valueChanged(label.toString().toStdString());
}

tlinsWAstroObjectType::~tlinsWAstroObjectType()
{
    delete ui;
}
