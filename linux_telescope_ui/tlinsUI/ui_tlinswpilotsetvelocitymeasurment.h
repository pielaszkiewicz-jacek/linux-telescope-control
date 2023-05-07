/********************************************************************************
** Form generated from reading UI file 'tlinswpilotsetvelocitymeasurment.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWPILOTSETVELOCITYMEASURMENT_H
#define UI_TLINSWPILOTSETVELOCITYMEASURMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsWPilotSetVelocityMeasurment
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *tlinsWPilotSetVelocityMeasurment)
    {
        if (tlinsWPilotSetVelocityMeasurment->objectName().isEmpty())
            tlinsWPilotSetVelocityMeasurment->setObjectName(QString::fromUtf8("tlinsWPilotSetVelocityMeasurment"));
        tlinsWPilotSetVelocityMeasurment->resize(275, 39);
        verticalLayout = new QVBoxLayout(tlinsWPilotSetVelocityMeasurment);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(tlinsWPilotSetVelocityMeasurment);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(tlinsWPilotSetVelocityMeasurment);

        QMetaObject::connectSlotsByName(tlinsWPilotSetVelocityMeasurment);
    } // setupUi

    void retranslateUi(QWidget *tlinsWPilotSetVelocityMeasurment)
    {
        tlinsWPilotSetVelocityMeasurment->setWindowTitle(QApplication::translate("tlinsWPilotSetVelocityMeasurment", "Form", nullptr));
        label->setText(QApplication::translate("tlinsWPilotSetVelocityMeasurment", "No configuration", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWPilotSetVelocityMeasurment: public Ui_tlinsWPilotSetVelocityMeasurment {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWPILOTSETVELOCITYMEASURMENT_H
