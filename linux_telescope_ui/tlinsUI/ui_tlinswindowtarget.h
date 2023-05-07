/********************************************************************************
** Form generated from reading UI file 'tlinswindowtarget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWINDOWTARGET_H
#define UI_TLINSWINDOWTARGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QVBoxLayout>
#include "tlinswtarget.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsWindowTarget
{
public:
    QVBoxLayout *verticalLayout;
    tlinsWTarget *widget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *tlinsWindowTarget)
    {
        if (tlinsWindowTarget->objectName().isEmpty())
            tlinsWindowTarget->setObjectName(QString::fromUtf8("tlinsWindowTarget"));
        tlinsWindowTarget->resize(523, 383);
        verticalLayout = new QVBoxLayout(tlinsWindowTarget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new tlinsWTarget(tlinsWindowTarget);
        widget->setObjectName(QString::fromUtf8("widget"));

        verticalLayout->addWidget(widget);

        buttonBox = new QDialogButtonBox(tlinsWindowTarget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(tlinsWindowTarget);
        QObject::connect(buttonBox, SIGNAL(accepted()), tlinsWindowTarget, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), tlinsWindowTarget, SLOT(reject()));

        QMetaObject::connectSlotsByName(tlinsWindowTarget);
    } // setupUi

    void retranslateUi(QDialog *tlinsWindowTarget)
    {
        tlinsWindowTarget->setWindowTitle(QApplication::translate("tlinsWindowTarget", "Observation target", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWindowTarget: public Ui_tlinsWindowTarget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWINDOWTARGET_H
