/********************************************************************************
** Form generated from reading UI file 'tlinswtarget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWTARGET_H
#define UI_TLINSWTARGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <tlinswastrocatalog.h>
#include <tlinswdecimalvalue.h>
#include "tlinswastroobjecttype.h"
#include "tlinswconstelation.h"
#include "tlinswcoordinatedeclination.h"
#include "tlinswcoordinatehourangle.h"
#include "tlinswobjectname.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsWTarget
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    tlinsWDecimalValue *pmDC;
    QLabel *label_7;
    tlinsWDecimalValue *radialVelocity;
    QLabel *label_4;
    tlinsWDecimalValue *parallex;
    QLabel *label_5;
    QLabel *label;
    tlinsWDecimalValue *pmRA;
    tlinsWCoordinateHourAngle *RA;
    QLabel *label_3;
    QLabel *label_2;
    tlinsWAstroCatalog *catalogType;
    QLabel *label_6;
    tlinsWCoordinateDeclination *DC;
    QWidget *magnitutde;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    tlinsWConstelation *objectConstelation;
    QLabel *label_12;
    QLabel *label_11;
    QLabel *label_10;
    tlinsWAstroObjectType *objectType;
    QLabel *label_13;
    tlinsWObjectName *objectName;
    tlinsWDecimalValue *magnitude;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    tlinsWDecimalValue *aceleration;
    QLabel *label_8;
    tlinsWDecimalValue *speed;
    QLabel *label_9;
    QLabel *label_14;
    tlinsWDecimalValue *delta;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btFind;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btClear;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btSetTarget;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *tlinsWTarget)
    {
        if (tlinsWTarget->objectName().isEmpty())
            tlinsWTarget->setObjectName(QString::fromUtf8("tlinsWTarget"));
        tlinsWTarget->resize(1000, 765);
        verticalLayout_2 = new QVBoxLayout(tlinsWTarget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_2 = new QGroupBox(tlinsWTarget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pmDC = new tlinsWDecimalValue(groupBox_2);
        pmDC->setObjectName(QString::fromUtf8("pmDC"));
        pmDC->setEnabled(true);

        gridLayout_2->addWidget(pmDC, 1, 4, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 4, 0, 1, 1);

        radialVelocity = new tlinsWDecimalValue(groupBox_2);
        radialVelocity->setObjectName(QString::fromUtf8("radialVelocity"));
        radialVelocity->setEnabled(true);

        gridLayout_2->addWidget(radialVelocity, 3, 1, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 1, 3, 1, 1);

        parallex = new tlinsWDecimalValue(groupBox_2);
        parallex->setObjectName(QString::fromUtf8("parallex"));
        parallex->setEnabled(true);

        gridLayout_2->addWidget(parallex, 2, 1, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 2, 0, 1, 1);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        pmRA = new tlinsWDecimalValue(groupBox_2);
        pmRA->setObjectName(QString::fromUtf8("pmRA"));
        pmRA->setEnabled(true);

        gridLayout_2->addWidget(pmRA, 1, 1, 1, 1);

        RA = new tlinsWCoordinateHourAngle(groupBox_2);
        RA->setObjectName(QString::fromUtf8("RA"));
        RA->setEnabled(true);

        gridLayout_2->addWidget(RA, 0, 1, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 0, 3, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        catalogType = new tlinsWAstroCatalog(groupBox_2);
        catalogType->setObjectName(QString::fromUtf8("catalogType"));
        catalogType->setEnabled(true);

        gridLayout_2->addWidget(catalogType, 4, 1, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 3, 0, 1, 1);

        DC = new tlinsWCoordinateDeclination(groupBox_2);
        DC->setObjectName(QString::fromUtf8("DC"));
        DC->setEnabled(true);

        gridLayout_2->addWidget(DC, 0, 4, 1, 1);

        magnitutde = new QWidget(groupBox_2);
        magnitutde->setObjectName(QString::fromUtf8("magnitutde"));

        gridLayout_2->addWidget(magnitutde, 5, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(tlinsWTarget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        objectConstelation = new tlinsWConstelation(groupBox_3);
        objectConstelation->setObjectName(QString::fromUtf8("objectConstelation"));
        objectConstelation->setEnabled(false);

        gridLayout_4->addWidget(objectConstelation, 2, 1, 1, 1);

        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_4->addWidget(label_12, 2, 0, 1, 1);

        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_4->addWidget(label_11, 1, 0, 1, 1);

        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_4->addWidget(label_10, 0, 0, 1, 1);

        objectType = new tlinsWAstroObjectType(groupBox_3);
        objectType->setObjectName(QString::fromUtf8("objectType"));
        objectType->setEnabled(false);

        gridLayout_4->addWidget(objectType, 1, 1, 1, 1);

        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_4->addWidget(label_13, 3, 0, 1, 1);

        objectName = new tlinsWObjectName(groupBox_3);
        objectName->setObjectName(QString::fromUtf8("objectName"));
        objectName->setEnabled(false);

        gridLayout_4->addWidget(objectName, 0, 1, 1, 1);

        magnitude = new tlinsWDecimalValue(groupBox_3);
        magnitude->setObjectName(QString::fromUtf8("magnitude"));
        magnitude->setEnabled(false);

        gridLayout_4->addWidget(magnitude, 3, 1, 1, 1);


        verticalLayout_2->addWidget(groupBox_3);

        groupBox = new QGroupBox(tlinsWTarget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        aceleration = new tlinsWDecimalValue(groupBox);
        aceleration->setObjectName(QString::fromUtf8("aceleration"));
        aceleration->setEnabled(false);

        gridLayout->addWidget(aceleration, 1, 1, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 0, 0, 1, 1);

        speed = new tlinsWDecimalValue(groupBox);
        speed->setObjectName(QString::fromUtf8("speed"));
        speed->setEnabled(false);

        gridLayout->addWidget(speed, 0, 1, 1, 1);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 1, 0, 1, 1);

        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout->addWidget(label_14, 2, 0, 1, 1);

        delta = new tlinsWDecimalValue(groupBox);
        delta->setObjectName(QString::fromUtf8("delta"));
        delta->setEnabled(false);

        gridLayout->addWidget(delta, 2, 1, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 6, -1, 6);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btFind = new QPushButton(tlinsWTarget);
        btFind->setObjectName(QString::fromUtf8("btFind"));
        btFind->setMinimumSize(QSize(150, 60));

        horizontalLayout->addWidget(btFind);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        btClear = new QPushButton(tlinsWTarget);
        btClear->setObjectName(QString::fromUtf8("btClear"));
        btClear->setMinimumSize(QSize(150, 60));

        horizontalLayout->addWidget(btClear);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btSetTarget = new QPushButton(tlinsWTarget);
        btSetTarget->setObjectName(QString::fromUtf8("btSetTarget"));
        btSetTarget->setMinimumSize(QSize(150, 60));

        horizontalLayout->addWidget(btSetTarget);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        retranslateUi(tlinsWTarget);

        QMetaObject::connectSlotsByName(tlinsWTarget);
    } // setupUi

    void retranslateUi(QWidget *tlinsWTarget)
    {
        tlinsWTarget->setWindowTitle(QApplication::translate("tlinsWTarget", "Form", nullptr));
        groupBox_2->setTitle(QApplication::translate("tlinsWTarget", "Object", nullptr));
        label_7->setText(QApplication::translate("tlinsWTarget", "Catalog type", nullptr));
        label_4->setText(QApplication::translate("tlinsWTarget", "Proper Motion DC", nullptr));
        label_5->setText(QApplication::translate("tlinsWTarget", "Paralex", nullptr));
        label->setText(QApplication::translate("tlinsWTarget", "RA", nullptr));
        label_3->setText(QApplication::translate("tlinsWTarget", "DC", nullptr));
        label_2->setText(QApplication::translate("tlinsWTarget", "Proper Motion RA", nullptr));
        label_6->setText(QApplication::translate("tlinsWTarget", "Radial velocity", nullptr));
        groupBox_3->setTitle(QApplication::translate("tlinsWTarget", "Object info", nullptr));
        label_12->setText(QApplication::translate("tlinsWTarget", "Constelation", nullptr));
        label_11->setText(QApplication::translate("tlinsWTarget", "Type", nullptr));
        label_10->setText(QApplication::translate("tlinsWTarget", "Name", nullptr));
        label_13->setText(QApplication::translate("tlinsWTarget", "Magnitutde", nullptr));
        groupBox->setTitle(QApplication::translate("tlinsWTarget", "Speed/aceleration", nullptr));
        label_8->setText(QApplication::translate("tlinsWTarget", "Speed", nullptr));
        label_9->setText(QApplication::translate("tlinsWTarget", "Aceleration", nullptr));
        label_14->setText(QApplication::translate("tlinsWTarget", "Delta", nullptr));
        btFind->setText(QApplication::translate("tlinsWTarget", "Find object", nullptr));
        btClear->setText(QApplication::translate("tlinsWTarget", "Clear", nullptr));
        btSetTarget->setText(QApplication::translate("tlinsWTarget", "Set target", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWTarget: public Ui_tlinsWTarget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWTARGET_H
