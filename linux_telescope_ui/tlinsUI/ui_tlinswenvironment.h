/********************************************************************************
** Form generated from reading UI file 'tlinswenvironment.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWENVIRONMENT_H
#define UI_TLINSWENVIRONMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <tlinswdecimalvalue.h>

QT_BEGIN_NAMESPACE

class Ui_tlinsWEnvironment
{
public:
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *label_5;
    tlinsWDecimalValue *realHumidity;
    QLabel *label_4;
    QLabel *label;
    QLabel *label_2;
    tlinsWDecimalValue *temperature;
    tlinsWDecimalValue *ambientPressure;
    QLabel *label_7;
    tlinsWDecimalValue *effectiveColor;
    QLabel *label_6;

    void setupUi(QWidget *tlinsWEnvironment)
    {
        if (tlinsWEnvironment->objectName().isEmpty())
            tlinsWEnvironment->setObjectName(QString::fromUtf8("tlinsWEnvironment"));
        tlinsWEnvironment->resize(537, 193);
        gridLayout = new QGridLayout(tlinsWEnvironment);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(tlinsWEnvironment);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        label_5 = new QLabel(tlinsWEnvironment);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        realHumidity = new tlinsWDecimalValue(tlinsWEnvironment);
        realHumidity->setObjectName(QString::fromUtf8("realHumidity"));

        gridLayout->addWidget(realHumidity, 2, 1, 1, 1);

        label_4 = new QLabel(tlinsWEnvironment);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_4, 1, 2, 1, 1);

        label = new QLabel(tlinsWEnvironment);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(tlinsWEnvironment);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        temperature = new tlinsWDecimalValue(tlinsWEnvironment);
        temperature->setObjectName(QString::fromUtf8("temperature"));

        gridLayout->addWidget(temperature, 1, 1, 1, 1);

        ambientPressure = new tlinsWDecimalValue(tlinsWEnvironment);
        ambientPressure->setObjectName(QString::fromUtf8("ambientPressure"));

        gridLayout->addWidget(ambientPressure, 0, 1, 1, 1);

        label_7 = new QLabel(tlinsWEnvironment);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 3, 0, 1, 1);

        effectiveColor = new tlinsWDecimalValue(tlinsWEnvironment);
        effectiveColor->setObjectName(QString::fromUtf8("effectiveColor"));

        gridLayout->addWidget(effectiveColor, 3, 1, 1, 1);

        label_6 = new QLabel(tlinsWEnvironment);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_6, 2, 2, 1, 1);


        retranslateUi(tlinsWEnvironment);

        QMetaObject::connectSlotsByName(tlinsWEnvironment);
    } // setupUi

    void retranslateUi(QWidget *tlinsWEnvironment)
    {
        tlinsWEnvironment->setWindowTitle(QApplication::translate("tlinsWEnvironment", "Form", nullptr));
        label_3->setText(QApplication::translate("tlinsWEnvironment", "Temperature", nullptr));
        label_5->setText(QApplication::translate("tlinsWEnvironment", "Real Humidity", nullptr));
        label_4->setText(QApplication::translate("tlinsWEnvironment", "[C]", nullptr));
        label->setText(QApplication::translate("tlinsWEnvironment", "Ambient pressure", nullptr));
        label_2->setText(QApplication::translate("tlinsWEnvironment", "[hPa]", nullptr));
        label_7->setText(QApplication::translate("tlinsWEnvironment", "Effective color", nullptr));
        label_6->setText(QApplication::translate("tlinsWEnvironment", "%", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWEnvironment: public Ui_tlinsWEnvironment {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWENVIRONMENT_H
