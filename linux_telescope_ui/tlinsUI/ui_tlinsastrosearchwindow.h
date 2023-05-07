/********************************************************************************
** Form generated from reading UI file 'tlinsastrosearchwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSASTROSEARCHWINDOW_H
#define UI_TLINSASTROSEARCHWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include "tlinswdatabasesearchmain.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsAstroSearchWindow
{
public:
    QGridLayout *gridLayout;
    tlinsWDatabaseSearchMain *searchWidget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *tlinsAstroSearchWindow)
    {
        if (tlinsAstroSearchWindow->objectName().isEmpty())
            tlinsAstroSearchWindow->setObjectName(QString::fromUtf8("tlinsAstroSearchWindow"));
        tlinsAstroSearchWindow->resize(1162, 856);
        gridLayout = new QGridLayout(tlinsAstroSearchWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        searchWidget = new tlinsWDatabaseSearchMain(tlinsAstroSearchWindow);
        searchWidget->setObjectName(QString::fromUtf8("searchWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(searchWidget->sizePolicy().hasHeightForWidth());
        searchWidget->setSizePolicy(sizePolicy);
        searchWidget->setMinimumSize(QSize(0, 0));
        searchWidget->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(searchWidget, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(tlinsAstroSearchWindow);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(tlinsAstroSearchWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), tlinsAstroSearchWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), tlinsAstroSearchWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(tlinsAstroSearchWindow);
    } // setupUi

    void retranslateUi(QDialog *tlinsAstroSearchWindow)
    {
        tlinsAstroSearchWindow->setWindowTitle(QApplication::translate("tlinsAstroSearchWindow", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsAstroSearchWindow: public Ui_tlinsAstroSearchWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSASTROSEARCHWINDOW_H
