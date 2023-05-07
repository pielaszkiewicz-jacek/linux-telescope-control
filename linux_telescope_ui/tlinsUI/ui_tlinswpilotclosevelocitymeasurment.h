/********************************************************************************
** Form generated from reading UI file 'tlinswpilotclosevelocitymeasurment.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWPILOTCLOSEVELOCITYMEASURMENT_H
#define UI_TLINSWPILOTCLOSEVELOCITYMEASURMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsWPilotCloseVelocityMeasurment
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *tlinsWPilotCloseVelocityMeasurment)
    {
        if (tlinsWPilotCloseVelocityMeasurment->objectName().isEmpty())
            tlinsWPilotCloseVelocityMeasurment->setObjectName(QString::fromUtf8("tlinsWPilotCloseVelocityMeasurment"));
        tlinsWPilotCloseVelocityMeasurment->resize(219, 39);
        verticalLayout = new QVBoxLayout(tlinsWPilotCloseVelocityMeasurment);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(tlinsWPilotCloseVelocityMeasurment);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(tlinsWPilotCloseVelocityMeasurment);

        QMetaObject::connectSlotsByName(tlinsWPilotCloseVelocityMeasurment);
    } // setupUi

    void retranslateUi(QWidget *tlinsWPilotCloseVelocityMeasurment)
    {
        tlinsWPilotCloseVelocityMeasurment->setWindowTitle(QApplication::translate("tlinsWPilotCloseVelocityMeasurment", "Form", nullptr));
        label->setText(QApplication::translate("tlinsWPilotCloseVelocityMeasurment", "No configuration", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWPilotCloseVelocityMeasurment: public Ui_tlinsWPilotCloseVelocityMeasurment {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWPILOTCLOSEVELOCITYMEASURMENT_H
