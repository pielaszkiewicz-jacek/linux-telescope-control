/********************************************************************************
** Form generated from reading UI file 'tlinspilotshortcutsdefinitionswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSPILOTSHORTCUTSDEFINITIONSWINDOW_H
#define UI_TLINSPILOTSHORTCUTSDEFINITIONSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include "tlinswpilotshortcutsdefinitions.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsPilotShortcutsDefinitionsWindow
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    tlinsWPilotShortcutsDefinitions *scrollAreaWidgetContents;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *tlinsPilotShortcutsDefinitionsWindow)
    {
        if (tlinsPilotShortcutsDefinitionsWindow->objectName().isEmpty())
            tlinsPilotShortcutsDefinitionsWindow->setObjectName(QString::fromUtf8("tlinsPilotShortcutsDefinitionsWindow"));
        tlinsPilotShortcutsDefinitionsWindow->resize(736, 760);
        verticalLayout = new QVBoxLayout(tlinsPilotShortcutsDefinitionsWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(tlinsPilotShortcutsDefinitionsWindow);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new tlinsWPilotShortcutsDefinitions();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 716, 708));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        buttonBox = new QDialogButtonBox(tlinsPilotShortcutsDefinitionsWindow);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(tlinsPilotShortcutsDefinitionsWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), tlinsPilotShortcutsDefinitionsWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), tlinsPilotShortcutsDefinitionsWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(tlinsPilotShortcutsDefinitionsWindow);
    } // setupUi

    void retranslateUi(QDialog *tlinsPilotShortcutsDefinitionsWindow)
    {
        tlinsPilotShortcutsDefinitionsWindow->setWindowTitle(QApplication::translate("tlinsPilotShortcutsDefinitionsWindow", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsPilotShortcutsDefinitionsWindow: public Ui_tlinsPilotShortcutsDefinitionsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSPILOTSHORTCUTSDEFINITIONSWINDOW_H
