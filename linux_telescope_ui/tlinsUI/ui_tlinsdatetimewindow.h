/********************************************************************************
** Form generated from reading UI file 'tlinsdatetimewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSDATETIMEWINDOW_H
#define UI_TLINSDATETIMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QVBoxLayout>
#include "tlinswdatetime.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsDateTimeWindow
{
public:
    QVBoxLayout *verticalLayout;
    tlinsWDateTime *dateTime;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *tlinsDateTimeWindow)
    {
        if (tlinsDateTimeWindow->objectName().isEmpty())
            tlinsDateTimeWindow->setObjectName(QString::fromUtf8("tlinsDateTimeWindow"));
        tlinsDateTimeWindow->resize(464, 324);
        verticalLayout = new QVBoxLayout(tlinsDateTimeWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        dateTime = new tlinsWDateTime(tlinsDateTimeWindow);
        dateTime->setObjectName(QString::fromUtf8("dateTime"));

        verticalLayout->addWidget(dateTime);

        buttonBox = new QDialogButtonBox(tlinsDateTimeWindow);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(tlinsDateTimeWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), tlinsDateTimeWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), tlinsDateTimeWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(tlinsDateTimeWindow);
    } // setupUi

    void retranslateUi(QDialog *tlinsDateTimeWindow)
    {
        tlinsDateTimeWindow->setWindowTitle(QApplication::translate("tlinsDateTimeWindow", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsDateTimeWindow: public Ui_tlinsDateTimeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSDATETIMEWINDOW_H
