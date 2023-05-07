/********************************************************************************
** Form generated from reading UI file 'tlinswpilotstartresetcalibration.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWPILOTSTARTRESETCALIBRATION_H
#define UI_TLINSWPILOTSTARTRESETCALIBRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsWPilotStartResetCalibration
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *tlinsWPilotStartResetCalibration)
    {
        if (tlinsWPilotStartResetCalibration->objectName().isEmpty())
            tlinsWPilotStartResetCalibration->setObjectName(QString::fromUtf8("tlinsWPilotStartResetCalibration"));
        tlinsWPilotStartResetCalibration->resize(300, 39);
        verticalLayout = new QVBoxLayout(tlinsWPilotStartResetCalibration);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(tlinsWPilotStartResetCalibration);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(tlinsWPilotStartResetCalibration);

        QMetaObject::connectSlotsByName(tlinsWPilotStartResetCalibration);
    } // setupUi

    void retranslateUi(QWidget *tlinsWPilotStartResetCalibration)
    {
        tlinsWPilotStartResetCalibration->setWindowTitle(QApplication::translate("tlinsWPilotStartResetCalibration", "Form", nullptr));
        label->setText(QApplication::translate("tlinsWPilotStartResetCalibration", "No configuration", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWPilotStartResetCalibration: public Ui_tlinsWPilotStartResetCalibration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWPILOTSTARTRESETCALIBRATION_H
