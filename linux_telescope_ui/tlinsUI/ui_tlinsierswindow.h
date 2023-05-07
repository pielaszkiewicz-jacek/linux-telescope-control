/********************************************************************************
** Form generated from reading UI file 'tlinsierswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSIERSWINDOW_H
#define UI_TLINSIERSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include "tlinswtimedateierssettings.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsIERSWindow
{
public:
    QGridLayout *gridLayout;
    QDialogButtonBox *updateDevice;
    tlinsWTimeDateIERSSettings *widget;

    void setupUi(QDialog *tlinsIERSWindow)
    {
        if (tlinsIERSWindow->objectName().isEmpty())
            tlinsIERSWindow->setObjectName(QString::fromUtf8("tlinsIERSWindow"));
        tlinsIERSWindow->resize(800, 593);
        gridLayout = new QGridLayout(tlinsIERSWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        updateDevice = new QDialogButtonBox(tlinsIERSWindow);
        updateDevice->setObjectName(QString::fromUtf8("updateDevice"));
        updateDevice->setOrientation(Qt::Horizontal);
        updateDevice->setStandardButtons(QDialogButtonBox::Close);
        updateDevice->setCenterButtons(false);

        gridLayout->addWidget(updateDevice, 1, 0, 1, 1);

        widget = new tlinsWTimeDateIERSSettings(tlinsIERSWindow);
        widget->setObjectName(QString::fromUtf8("widget"));

        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(tlinsIERSWindow);
        QObject::connect(updateDevice, SIGNAL(accepted()), tlinsIERSWindow, SLOT(accept()));
        QObject::connect(updateDevice, SIGNAL(rejected()), tlinsIERSWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(tlinsIERSWindow);
    } // setupUi

    void retranslateUi(QDialog *tlinsIERSWindow)
    {
        tlinsIERSWindow->setWindowTitle(QApplication::translate("tlinsIERSWindow", "IERS data", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsIERSWindow: public Ui_tlinsIERSWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSIERSWINDOW_H
