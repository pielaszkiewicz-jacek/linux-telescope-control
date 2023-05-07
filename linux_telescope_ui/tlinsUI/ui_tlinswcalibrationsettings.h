/********************************************************************************
** Form generated from reading UI file 'tlinswcalibrationsettings.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWCALIBRATIONSETTINGS_H
#define UI_TLINSWCALIBRATIONSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <tlinswdecimalvalue.h>

QT_BEGIN_NAMESPACE

class Ui_tlinsWCalibrationSettings
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    tlinsWDecimalValue *minNumberMeasurments;
    QLabel *label_2;
    tlinsWDecimalValue *minNumberReferenceObjects;

    void setupUi(QWidget *tlinsWCalibrationSettings)
    {
        if (tlinsWCalibrationSettings->objectName().isEmpty())
            tlinsWCalibrationSettings->setObjectName(QString::fromUtf8("tlinsWCalibrationSettings"));
        tlinsWCalibrationSettings->resize(351, 57);
        gridLayout = new QGridLayout(tlinsWCalibrationSettings);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(tlinsWCalibrationSettings);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        minNumberMeasurments = new tlinsWDecimalValue(tlinsWCalibrationSettings);
        minNumberMeasurments->setObjectName(QString::fromUtf8("minNumberMeasurments"));

        gridLayout->addWidget(minNumberMeasurments, 1, 1, 1, 1);

        label_2 = new QLabel(tlinsWCalibrationSettings);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        minNumberReferenceObjects = new tlinsWDecimalValue(tlinsWCalibrationSettings);
        minNumberReferenceObjects->setObjectName(QString::fromUtf8("minNumberReferenceObjects"));

        gridLayout->addWidget(minNumberReferenceObjects, 0, 1, 1, 1);


        retranslateUi(tlinsWCalibrationSettings);

        QMetaObject::connectSlotsByName(tlinsWCalibrationSettings);
    } // setupUi

    void retranslateUi(QWidget *tlinsWCalibrationSettings)
    {
        tlinsWCalibrationSettings->setWindowTitle(QApplication::translate("tlinsWCalibrationSettings", "Form", nullptr));
        label->setText(QApplication::translate("tlinsWCalibrationSettings", "Min. number mesurments", nullptr));
        label_2->setText(QApplication::translate("tlinsWCalibrationSettings", "Min. number reference objects", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWCalibrationSettings: public Ui_tlinsWCalibrationSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWCALIBRATIONSETTINGS_H
