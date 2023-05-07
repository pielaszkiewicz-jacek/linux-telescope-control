#include "tlinswastrocatalog.h"
#include "tlinsastrocatalogitem.h"
#include "tlinsuistylesmanager.h"
#include "ui_tlinswastrocatalog.h"
#include <QDebug>

tlinsWAstroCatalog::tlinsWAstroCatalog(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWAstroCatalog)
{
    ui->setupUi(this);

    // Style
    //    std:: string style;
    //    bool res = tlinsUiStylesManager:: getStyle( tlinsUiStylesManager:: CATALOG_TYPE,
    //                                                 tlinsUiStylesManager:: FieldType:: GROUP_BOX,
    //                                                 style );
    //    if( res )
    //        ui -> groupBox -> setStyleSheet( QString( style.c_str() ) );

    //    res = tlinsUiStylesManager:: getStyle( tlinsUiStylesManager:: CATALOG_TYPE,
    //                                            tlinsUiStylesManager:: FieldType:: COMBO_BOX,
    //                                            style );
    //    if( res )
    //        ui -> astroCatalog -> setStyleSheet( QString( style.c_str() ) );

    for (int i = 0; i < TlinsAstroBase::CatalogType::count(); i++) {
        int id;
        std::string label;
        std::string name;
        TlinsAstroBase::CatalogType::get(i, id, label, name);

        QString qstrName(name.c_str());
        QString qstrLabel(label.c_str());
        QVariant qvarLabel(qstrLabel);

        ui->astroCatalog->addItem(qstrName, qvarLabel);
    }

    connect(ui->astroCatalog, SIGNAL(currentIndexChanged(QString)), this, SLOT(update()));
}

void tlinsWAstroCatalog::setCurrent(const int idx)
{
    ui->astroCatalog->setCurrentIndex(idx);
}

bool tlinsWAstroCatalog::setCurrent(const std::string& label)
{
    for (int i = 0; i < ui->astroCatalog->count(); i++) {
        QVariant v = ui->astroCatalog->itemData(i);
        if (v.toString() == QString(label.c_str())) {
            ui->astroCatalog->setCurrentIndex(i);
            return true;
        }
    }
    return false;
}

std::string tlinsWAstroCatalog::getType() const
{
    //	QString label = ui -> astroCatalog -> currentData().toString();
    //    QString label = ui -> astroCatalog -> currentText();
    //	qDebug() << "Catalog label = " << label;
    //	return label.toStdString();
    return ui->astroCatalog->currentData().toString().toStdString();
}

void tlinsWAstroCatalog::update()
{
    qDebug() << "void tlinsWAstroCatalog:: update()";
    //	QVariant label = ui -> astroCatalog ->currentData();
    QVariant label = ui->astroCatalog->currentText();
    emit valueChanged(label.toString().toStdString());
}

void tlinsWAstroCatalog::disable()
{
    ui->astroCatalog->setDisabled(true);
}

tlinsWAstroCatalog::~tlinsWAstroCatalog()
{
    delete ui;
}
