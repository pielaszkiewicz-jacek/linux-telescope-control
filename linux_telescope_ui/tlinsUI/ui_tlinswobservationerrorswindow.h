/********************************************************************************
** Form generated from reading UI file 'tlinswobservationerrorswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWOBSERVATIONERRORSWINDOW_H
#define UI_TLINSWOBSERVATIONERRORSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QVBoxLayout>
#include "tlinswobservationerror.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsWObservationErrorsWindow
{
public:
    QVBoxLayout *verticalLayout;
    tlinsWObservationError *wData;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *tlinsWObservationErrorsWindow)
    {
        if (tlinsWObservationErrorsWindow->objectName().isEmpty())
            tlinsWObservationErrorsWindow->setObjectName(QString::fromUtf8("tlinsWObservationErrorsWindow"));
        tlinsWObservationErrorsWindow->resize(400, 300);
        verticalLayout = new QVBoxLayout(tlinsWObservationErrorsWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        wData = new tlinsWObservationError(tlinsWObservationErrorsWindow);
        wData->setObjectName(QString::fromUtf8("wData"));

        verticalLayout->addWidget(wData);

        buttonBox = new QDialogButtonBox(tlinsWObservationErrorsWindow);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(tlinsWObservationErrorsWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), tlinsWObservationErrorsWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), tlinsWObservationErrorsWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(tlinsWObservationErrorsWindow);
    } // setupUi

    void retranslateUi(QDialog *tlinsWObservationErrorsWindow)
    {
        tlinsWObservationErrorsWindow->setWindowTitle(QApplication::translate("tlinsWObservationErrorsWindow", "Observation place", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWObservationErrorsWindow: public Ui_tlinsWObservationErrorsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWOBSERVATIONERRORSWINDOW_H
