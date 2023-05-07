/********************************************************************************
** Form generated from reading UI file 'tlinswindowsenginestate.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWINDOWSENGINESTATE_H
#define UI_TLINSWINDOWSENGINESTATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QScrollArea>
#include "tlinswmanageenginestate.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsWindowsEngineState
{
public:
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    tlinsWManageEngineState *scrollAreaWidgetContents;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *tlinsWindowsEngineState)
    {
        if (tlinsWindowsEngineState->objectName().isEmpty())
            tlinsWindowsEngineState->setObjectName(QString::fromUtf8("tlinsWindowsEngineState"));
        tlinsWindowsEngineState->resize(975, 783);
        gridLayout = new QGridLayout(tlinsWindowsEngineState);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        scrollArea = new QScrollArea(tlinsWindowsEngineState);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new tlinsWManageEngineState();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 957, 735));
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(tlinsWindowsEngineState);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(tlinsWindowsEngineState);
        QObject::connect(buttonBox, SIGNAL(accepted()), tlinsWindowsEngineState, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), tlinsWindowsEngineState, SLOT(reject()));

        QMetaObject::connectSlotsByName(tlinsWindowsEngineState);
    } // setupUi

    void retranslateUi(QDialog *tlinsWindowsEngineState)
    {
        tlinsWindowsEngineState->setWindowTitle(QApplication::translate("tlinsWindowsEngineState", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWindowsEngineState: public Ui_tlinsWindowsEngineState {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWINDOWSENGINESTATE_H
