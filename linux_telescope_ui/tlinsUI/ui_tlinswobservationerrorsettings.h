/********************************************************************************
** Form generated from reading UI file 'tlinswobservationerrorsettings.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWOBSERVATIONERRORSETTINGS_H
#define UI_TLINSWOBSERVATIONERRORSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>
#include "tlinswobservationerror.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsWObservationErrorSettings
{
public:
    QGridLayout *gridLayout;
    tlinsWObservationError *wData;

    void setupUi(QWidget *tlinsWObservationErrorSettings)
    {
        if (tlinsWObservationErrorSettings->objectName().isEmpty())
            tlinsWObservationErrorSettings->setObjectName(QString::fromUtf8("tlinsWObservationErrorSettings"));
        tlinsWObservationErrorSettings->resize(400, 300);
        gridLayout = new QGridLayout(tlinsWObservationErrorSettings);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        wData = new tlinsWObservationError(tlinsWObservationErrorSettings);
        wData->setObjectName(QString::fromUtf8("wData"));

        gridLayout->addWidget(wData, 0, 0, 1, 1);


        retranslateUi(tlinsWObservationErrorSettings);

        QMetaObject::connectSlotsByName(tlinsWObservationErrorSettings);
    } // setupUi

    void retranslateUi(QWidget *tlinsWObservationErrorSettings)
    {
        tlinsWObservationErrorSettings->setWindowTitle(QApplication::translate("tlinsWObservationErrorSettings", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWObservationErrorSettings: public Ui_tlinsWObservationErrorSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWOBSERVATIONERRORSETTINGS_H
