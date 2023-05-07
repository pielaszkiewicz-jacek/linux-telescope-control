/********************************************************************************
** Form generated from reading UI file 'tlinswobservationerror.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWOBSERVATIONERROR_H
#define UI_TLINSWOBSERVATIONERROR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include "tlinswcoordinatedegris.h"
#include "tlinswdecimalvalue.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsWObservationError
{
public:
    QGridLayout *gridLayout;
    QLabel *label_2;
    tlinsWCoordinateDegris *longitudeError;
    QLabel *label_3;
    tlinsWCoordinateDegris *latitudeError;
    QLabel *label;
    tlinsWDecimalValue *weight;

    void setupUi(QWidget *tlinsWObservationError)
    {
        if (tlinsWObservationError->objectName().isEmpty())
            tlinsWObservationError->setObjectName(QString::fromUtf8("tlinsWObservationError"));
        tlinsWObservationError->resize(321, 99);
        gridLayout = new QGridLayout(tlinsWObservationError);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(tlinsWObservationError);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        longitudeError = new tlinsWCoordinateDegris(tlinsWObservationError);
        longitudeError->setObjectName(QString::fromUtf8("longitudeError"));

        gridLayout->addWidget(longitudeError, 0, 1, 1, 1);

        label_3 = new QLabel(tlinsWObservationError);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        latitudeError = new tlinsWCoordinateDegris(tlinsWObservationError);
        latitudeError->setObjectName(QString::fromUtf8("latitudeError"));

        gridLayout->addWidget(latitudeError, 1, 1, 1, 1);

        label = new QLabel(tlinsWObservationError);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        weight = new tlinsWDecimalValue(tlinsWObservationError);
        weight->setObjectName(QString::fromUtf8("weight"));

        gridLayout->addWidget(weight, 2, 1, 1, 1);


        retranslateUi(tlinsWObservationError);

        QMetaObject::connectSlotsByName(tlinsWObservationError);
    } // setupUi

    void retranslateUi(QWidget *tlinsWObservationError)
    {
        tlinsWObservationError->setWindowTitle(QApplication::translate("tlinsWObservationError", "Form", nullptr));
        label_2->setText(QApplication::translate("tlinsWObservationError", "Latitude Error", nullptr));
        label_3->setText(QApplication::translate("tlinsWObservationError", "Weight", nullptr));
        label->setText(QApplication::translate("tlinsWObservationError", "Longitude Error", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWObservationError: public Ui_tlinsWObservationError {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWOBSERVATIONERROR_H
