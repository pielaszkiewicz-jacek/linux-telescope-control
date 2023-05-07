#include "tlinswobjectname.h"
#include "tlinsuistylesmanager.h"
#include "ui_tlinswobjectname.h"

#include <QDebug>

tlinsWObjectName::tlinsWObjectName(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWObjectName)
{
    ui->setupUi(this);

    // Control styles
    //    std:: string style;
    //    bool res = tlinsUiStylesManager:: getStyle( tlinsUiStylesManager:: OBJECT_NAME,
    //                                                 tlinsUiStylesManager:: FieldType:: GROUP_BOX,
    //                                                 style );
    //    if( res )
    //        ui -> groupBox -> setStyleSheet( QString( style.c_str() ) );

    //    res = tlinsUiStylesManager:: getStyle( tlinsUiStylesManager:: OBJECT_NAME,
    //                                            tlinsUiStylesManager:: FieldType:: EDIT,
    //                                            style );
    //    if( res )
    //        ui -> objectName -> setStyleSheet( QString( style.c_str() ) );
}

void tlinsWObjectName::update()
{
    qDebug() << "void tlinsWObjectName:: update()";
    emit valueChanged(std::string(ui->objectName->text().toStdString()));
}

void tlinsWObjectName::setValue(const std::string& value)
{
    ui->objectName->setText(QString(value.c_str()));
}

std::string tlinsWObjectName::getValue() const
{
    return std::string(ui->objectName->text().toStdString());
}

tlinsWObjectName::~tlinsWObjectName()
{
    delete ui;
}
