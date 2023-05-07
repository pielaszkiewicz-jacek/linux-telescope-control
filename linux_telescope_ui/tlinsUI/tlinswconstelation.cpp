#include "tlinswconstelation.h"
#include "tlinsastrocatalogitem.h"
#include "tlinsuistylesmanager.h"
#include "ui_tlinswconstelation.h"
#include <qdebug.h>
#include <string>

tlinsWConstelation::tlinsWConstelation(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWConstelation)
{
    ui->setupUi(this);

    for (int i = 0; i < TlinsAstroBase::Constelations::count(); i++) {
        int id;
        std::string label;
        std::string name;
        TlinsAstroBase::Constelations::get(i, id, label, name);

        QString qstrName(name.c_str());
        QString qstrLabel(label.c_str());
        QVariant qvarLabel(qstrLabel);

        ui->constelation->addItem(qstrName, qstrLabel);
        //		ui -> constelation -> setItemData( i, qstrLabel );
    }

    connect(ui->constelation, SIGNAL(currentIndexChanged(QString)), this, SLOT(update()));
}

void tlinsWConstelation::setCurrent(const int idx)
{
    ui->constelation->setCurrentIndex(idx);
}

bool tlinsWConstelation::setCurrent(const std::string& label)
{
    for (int i = 0; i < ui->constelation->count(); i++) {
        QVariant v = ui->constelation->itemData(i);
        if (v.toString() == QString(label.c_str())) {
            ui->constelation->setCurrentIndex(i);
            return true;
        }
    }
    return false;
}

std::string tlinsWConstelation::getConstelation() const
{
    return ui->constelation->currentData().toString().toStdString();
}

void tlinsWConstelation::update()
{
    qDebug() << "void tlinsWConstelation:: update()";
    QVariant label = ui->constelation->currentText();
    //    QVariant label = ui ->constelation->currentData();
    emit valueChanged(label.toString().toStdString());
}

tlinsWConstelation::~tlinsWConstelation()
{
    delete ui;
}
