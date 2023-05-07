/********************************************************************************
** Form generated from reading UI file 'tlinswapplayastroconfigurationwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWAPPLAYASTROCONFIGURATIONWIDGET_H
#define UI_TLINSWAPPLAYASTROCONFIGURATIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "tlinswapplayastroconfiguration.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsWApplayAstroConfigurationWidget
{
public:
    QGridLayout *gridLayout;
    tlinsWApplayAstroConfiguration *cfg;
    QDialogButtonBox *buttonBox;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *tlinsWApplayAstroConfigurationWidget)
    {
        if (tlinsWApplayAstroConfigurationWidget->objectName().isEmpty())
            tlinsWApplayAstroConfigurationWidget->setObjectName(QString::fromUtf8("tlinsWApplayAstroConfigurationWidget"));
        tlinsWApplayAstroConfigurationWidget->resize(568, 397);
        gridLayout = new QGridLayout(tlinsWApplayAstroConfigurationWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        cfg = new tlinsWApplayAstroConfiguration(tlinsWApplayAstroConfigurationWidget);
        cfg->setObjectName(QString::fromUtf8("cfg"));

        gridLayout->addWidget(cfg, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(tlinsWApplayAstroConfigurationWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 0, 1, 1);


        retranslateUi(tlinsWApplayAstroConfigurationWidget);

        QMetaObject::connectSlotsByName(tlinsWApplayAstroConfigurationWidget);
    } // setupUi

    void retranslateUi(QWidget *tlinsWApplayAstroConfigurationWidget)
    {
        tlinsWApplayAstroConfigurationWidget->setWindowTitle(QApplication::translate("tlinsWApplayAstroConfigurationWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWApplayAstroConfigurationWidget: public Ui_tlinsWApplayAstroConfigurationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWAPPLAYASTROCONFIGURATIONWIDGET_H
