/********************************************************************************
** Form generated from reading UI file 'tlinswpilotclosecalibration.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWPILOTCLOSECALIBRATION_H
#define UI_TLINSWPILOTCLOSECALIBRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsWPilotCloseCalibration
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *tlinsWPilotCloseCalibration)
    {
        if (tlinsWPilotCloseCalibration->objectName().isEmpty())
            tlinsWPilotCloseCalibration->setObjectName(QString::fromUtf8("tlinsWPilotCloseCalibration"));
        tlinsWPilotCloseCalibration->resize(279, 42);
        verticalLayout = new QVBoxLayout(tlinsWPilotCloseCalibration);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(tlinsWPilotCloseCalibration);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(tlinsWPilotCloseCalibration);

        QMetaObject::connectSlotsByName(tlinsWPilotCloseCalibration);
    } // setupUi

    void retranslateUi(QWidget *tlinsWPilotCloseCalibration)
    {
        tlinsWPilotCloseCalibration->setWindowTitle(QApplication::translate("tlinsWPilotCloseCalibration", "Form", nullptr));
        label->setText(QApplication::translate("tlinsWPilotCloseCalibration", "No configuration", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWPilotCloseCalibration: public Ui_tlinsWPilotCloseCalibration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWPILOTCLOSECALIBRATION_H
