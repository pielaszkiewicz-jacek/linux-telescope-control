/********************************************************************************
** Form generated from reading UI file 'tlinseditdatabaseobject.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSEDITDATABASEOBJECT_H
#define UI_TLINSEDITDATABASEOBJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include "tlinswastrodatabaseobject.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsEditDatabaseObject
{
public:
    QGridLayout *gridLayout;
    tlinsWAstroDatabaseObject *databaseObject;
    QDialogButtonBox *buttons;

    void setupUi(QDialog *tlinsEditDatabaseObject)
    {
        if (tlinsEditDatabaseObject->objectName().isEmpty())
            tlinsEditDatabaseObject->setObjectName(QString::fromUtf8("tlinsEditDatabaseObject"));
        tlinsEditDatabaseObject->resize(936, 591);
        tlinsEditDatabaseObject->setMinimumSize(QSize(0, 0));
        tlinsEditDatabaseObject->setMaximumSize(QSize(16777215, 16777215));
        gridLayout = new QGridLayout(tlinsEditDatabaseObject);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        databaseObject = new tlinsWAstroDatabaseObject(tlinsEditDatabaseObject);
        databaseObject->setObjectName(QString::fromUtf8("databaseObject"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(databaseObject->sizePolicy().hasHeightForWidth());
        databaseObject->setSizePolicy(sizePolicy);
        databaseObject->setMinimumSize(QSize(10, 10));
        databaseObject->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(databaseObject, 0, 0, 1, 1);

        buttons = new QDialogButtonBox(tlinsEditDatabaseObject);
        buttons->setObjectName(QString::fromUtf8("buttons"));
        buttons->setOrientation(Qt::Horizontal);
        buttons->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttons, 1, 0, 1, 1);


        retranslateUi(tlinsEditDatabaseObject);
        QObject::connect(buttons, SIGNAL(accepted()), tlinsEditDatabaseObject, SLOT(accept()));
        QObject::connect(buttons, SIGNAL(rejected()), tlinsEditDatabaseObject, SLOT(reject()));

        QMetaObject::connectSlotsByName(tlinsEditDatabaseObject);
    } // setupUi

    void retranslateUi(QDialog *tlinsEditDatabaseObject)
    {
        tlinsEditDatabaseObject->setWindowTitle(QApplication::translate("tlinsEditDatabaseObject", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsEditDatabaseObject: public Ui_tlinsEditDatabaseObject {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSEDITDATABASEOBJECT_H
