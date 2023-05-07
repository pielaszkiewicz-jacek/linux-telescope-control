/********************************************************************************
** Form generated from reading UI file 'tlinswapplayastroconfiguration.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWAPPLAYASTROCONFIGURATION_H
#define UI_TLINSWAPPLAYASTROCONFIGURATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsWApplayAstroConfiguration
{
public:
    QGridLayout *gridLayout;
    QCheckBox *chbEnv;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *chbIERSApplay;
    QCheckBox *chbIERSOverwrite;
    QCheckBox *chnIERSStoreLocaly;
    QCheckBox *chbObservationPLace;

    void setupUi(QWidget *tlinsWApplayAstroConfiguration)
    {
        if (tlinsWApplayAstroConfiguration->objectName().isEmpty())
            tlinsWApplayAstroConfiguration->setObjectName(QString::fromUtf8("tlinsWApplayAstroConfiguration"));
        tlinsWApplayAstroConfiguration->resize(418, 147);
        gridLayout = new QGridLayout(tlinsWApplayAstroConfiguration);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        chbEnv = new QCheckBox(tlinsWApplayAstroConfiguration);
        chbEnv->setObjectName(QString::fromUtf8("chbEnv"));

        gridLayout->addWidget(chbEnv, 1, 0, 1, 1);

        groupBox = new QGroupBox(tlinsWApplayAstroConfiguration);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        chbIERSApplay = new QCheckBox(groupBox);
        chbIERSApplay->setObjectName(QString::fromUtf8("chbIERSApplay"));

        horizontalLayout_2->addWidget(chbIERSApplay);

        chbIERSOverwrite = new QCheckBox(groupBox);
        chbIERSOverwrite->setObjectName(QString::fromUtf8("chbIERSOverwrite"));

        horizontalLayout_2->addWidget(chbIERSOverwrite);

        chnIERSStoreLocaly = new QCheckBox(groupBox);
        chnIERSStoreLocaly->setObjectName(QString::fromUtf8("chnIERSStoreLocaly"));

        horizontalLayout_2->addWidget(chnIERSStoreLocaly);


        gridLayout->addWidget(groupBox, 2, 0, 1, 1);

        chbObservationPLace = new QCheckBox(tlinsWApplayAstroConfiguration);
        chbObservationPLace->setObjectName(QString::fromUtf8("chbObservationPLace"));

        gridLayout->addWidget(chbObservationPLace, 3, 0, 1, 1);


        retranslateUi(tlinsWApplayAstroConfiguration);

        QMetaObject::connectSlotsByName(tlinsWApplayAstroConfiguration);
    } // setupUi

    void retranslateUi(QWidget *tlinsWApplayAstroConfiguration)
    {
        tlinsWApplayAstroConfiguration->setWindowTitle(QApplication::translate("tlinsWApplayAstroConfiguration", "Form", nullptr));
        chbEnv->setText(QApplication::translate("tlinsWApplayAstroConfiguration", "Environment", nullptr));
        groupBox->setTitle(QApplication::translate("tlinsWApplayAstroConfiguration", "IERS data", nullptr));
        chbIERSApplay->setText(QApplication::translate("tlinsWApplayAstroConfiguration", "Applay", nullptr));
        chbIERSOverwrite->setText(QApplication::translate("tlinsWApplayAstroConfiguration", "Overwrite", nullptr));
        chnIERSStoreLocaly->setText(QApplication::translate("tlinsWApplayAstroConfiguration", "Store localy", nullptr));
        chbObservationPLace->setText(QApplication::translate("tlinsWApplayAstroConfiguration", "Observation place", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWApplayAstroConfiguration: public Ui_tlinsWApplayAstroConfiguration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWAPPLAYASTROCONFIGURATION_H
