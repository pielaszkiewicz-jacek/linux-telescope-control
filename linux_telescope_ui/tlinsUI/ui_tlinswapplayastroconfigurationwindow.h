/********************************************************************************
** Form generated from reading UI file 'tlinswapplayastroconfigurationwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWAPPLAYASTROCONFIGURATIONWINDOW_H
#define UI_TLINSWAPPLAYASTROCONFIGURATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QVBoxLayout>
#include "tlinswapplayastroconfiguration.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsWApplayAstroConfigurationWindow
{
public:
    QVBoxLayout *verticalLayout;
    tlinsWApplayAstroConfiguration *cfg;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *tlinsWApplayAstroConfigurationWindow)
    {
        if (tlinsWApplayAstroConfigurationWindow->objectName().isEmpty())
            tlinsWApplayAstroConfigurationWindow->setObjectName(QString::fromUtf8("tlinsWApplayAstroConfigurationWindow"));
        tlinsWApplayAstroConfigurationWindow->resize(382, 133);
        verticalLayout = new QVBoxLayout(tlinsWApplayAstroConfigurationWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        cfg = new tlinsWApplayAstroConfiguration(tlinsWApplayAstroConfigurationWindow);
        cfg->setObjectName(QString::fromUtf8("cfg"));

        verticalLayout->addWidget(cfg);

        buttonBox = new QDialogButtonBox(tlinsWApplayAstroConfigurationWindow);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(tlinsWApplayAstroConfigurationWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), tlinsWApplayAstroConfigurationWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), tlinsWApplayAstroConfigurationWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(tlinsWApplayAstroConfigurationWindow);
    } // setupUi

    void retranslateUi(QDialog *tlinsWApplayAstroConfigurationWindow)
    {
        tlinsWApplayAstroConfigurationWindow->setWindowTitle(QApplication::translate("tlinsWApplayAstroConfigurationWindow", "Environment", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWApplayAstroConfigurationWindow: public Ui_tlinsWApplayAstroConfigurationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWAPPLAYASTROCONFIGURATIONWINDOW_H
