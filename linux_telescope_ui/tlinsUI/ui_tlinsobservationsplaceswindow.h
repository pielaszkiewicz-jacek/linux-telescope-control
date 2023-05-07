/********************************************************************************
** Form generated from reading UI file 'tlinsobservationsplaceswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSOBSERVATIONSPLACESWINDOW_H
#define UI_TLINSOBSERVATIONSPLACESWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QVBoxLayout>
#include "tlinswobservationplace.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsObservationsPlacesWindow
{
public:
    QVBoxLayout *verticalLayout;
    tlinsWObservationPlace *widget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *tlinsObservationsPlacesWindow)
    {
        if (tlinsObservationsPlacesWindow->objectName().isEmpty())
            tlinsObservationsPlacesWindow->setObjectName(QString::fromUtf8("tlinsObservationsPlacesWindow"));
        tlinsObservationsPlacesWindow->resize(704, 568);
        verticalLayout = new QVBoxLayout(tlinsObservationsPlacesWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new tlinsWObservationPlace(tlinsObservationsPlacesWindow);
        widget->setObjectName(QString::fromUtf8("widget"));

        verticalLayout->addWidget(widget);

        buttonBox = new QDialogButtonBox(tlinsObservationsPlacesWindow);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(tlinsObservationsPlacesWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), tlinsObservationsPlacesWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), tlinsObservationsPlacesWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(tlinsObservationsPlacesWindow);
    } // setupUi

    void retranslateUi(QDialog *tlinsObservationsPlacesWindow)
    {
        tlinsObservationsPlacesWindow->setWindowTitle(QApplication::translate("tlinsObservationsPlacesWindow", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsObservationsPlacesWindow: public Ui_tlinsObservationsPlacesWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSOBSERVATIONSPLACESWINDOW_H
