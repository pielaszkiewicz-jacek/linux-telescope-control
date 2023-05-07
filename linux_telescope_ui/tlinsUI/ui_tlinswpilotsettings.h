/********************************************************************************
** Form generated from reading UI file 'tlinswpilotsettings.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWPILOTSETTINGS_H
#define UI_TLINSWPILOTSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <tlinswdecimalvalue.h>
#include "tlinswcoordinatedeclination.h"
#include "tlinswcoordinatedegris.h"
#include "tlinswcoordinatehourangle.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsWPilotSettings
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    tlinsWDecimalValue *stepsVX;
    tlinsWDecimalValue *stepsVY;
    QLabel *label_8;
    QLabel *label_6;
    QLabel *label_9;
    QLabel *label_11;
    tlinsWDecimalValue *stepsY;
    tlinsWDecimalValue *stepsX;
    QLabel *label;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_15;
    QLabel *label_7;
    QLabel *label_10;
    tlinsWCoordinateDegris *degrisY;
    QLabel *label_5;
    QLabel *label_2;
    tlinsWCoordinateDegris *degrisVY;
    tlinsWCoordinateDegris *degrisX;
    tlinsWCoordinateDegris *degrisVX;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QLabel *label_3;
    tlinsWCoordinateDeclination *astroVDC;
    QLabel *label_20;
    QLabel *label_19;
    QLabel *label_21;
    tlinsWCoordinateHourAngle *astroVRA;
    QLabel *label_22;
    tlinsWCoordinateHourAngle *astroRA;
    QLabel *label_23;
    QLabel *label_24;
    tlinsWCoordinateDeclination *astroDC;
    QLabel *label_25;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    QLabel *label_4;
    QLabel *label_29;
    QLabel *label_26;
    tlinsWCoordinateHourAngle *guideVX;
    tlinsWCoordinateDeclination *guideVY;
    QLabel *label_27;
    tlinsWCoordinateDeclination *guideY;
    QLabel *label_28;
    QLabel *label_30;
    tlinsWCoordinateHourAngle *guideX;
    QLabel *label_31;
    QLabel *label_32;

    void setupUi(QWidget *tlinsWPilotSettings)
    {
        if (tlinsWPilotSettings->objectName().isEmpty())
            tlinsWPilotSettings->setObjectName(QString::fromUtf8("tlinsWPilotSettings"));
        tlinsWPilotSettings->resize(807, 475);
        verticalLayout_2 = new QVBoxLayout(tlinsWPilotSettings);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(tlinsWPilotSettings);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QFont font;
        font.setItalic(true);
        groupBox->setFont(font);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        stepsVX = new tlinsWDecimalValue(groupBox);
        stepsVX->setObjectName(QString::fromUtf8("stepsVX"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(stepsVX->sizePolicy().hasHeightForWidth());
        stepsVX->setSizePolicy(sizePolicy);
        stepsVX->setMinimumSize(QSize(165, 0));
        QFont font1;
        font1.setItalic(false);
        stepsVX->setFont(font1);

        gridLayout->addWidget(stepsVX, 0, 1, 1, 1);

        stepsVY = new tlinsWDecimalValue(groupBox);
        stepsVY->setObjectName(QString::fromUtf8("stepsVY"));
        stepsVY->setMinimumSize(QSize(165, 0));
        stepsVY->setFont(font1);

        gridLayout->addWidget(stepsVY, 0, 4, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font1);
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_8, 1, 0, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font1);
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_6, 0, 3, 1, 1);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font1);
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_9, 1, 3, 1, 1);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font1);

        gridLayout->addWidget(label_11, 0, 2, 1, 1);

        stepsY = new tlinsWDecimalValue(groupBox);
        stepsY->setObjectName(QString::fromUtf8("stepsY"));
        stepsY->setMinimumSize(QSize(165, 0));
        stepsY->setFont(font1);

        gridLayout->addWidget(stepsY, 1, 4, 1, 1);

        stepsX = new tlinsWDecimalValue(groupBox);
        stepsX->setObjectName(QString::fromUtf8("stepsX"));
        sizePolicy.setHeightForWidth(stepsX->sizePolicy().hasHeightForWidth());
        stepsX->setSizePolicy(sizePolicy);
        stepsX->setMinimumSize(QSize(165, 0));
        stepsX->setFont(font1);

        gridLayout->addWidget(stepsX, 1, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font1);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font1);

        gridLayout->addWidget(label_12, 0, 5, 1, 1);

        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font1);

        gridLayout->addWidget(label_13, 1, 2, 1, 1);

        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setFont(font1);

        gridLayout->addWidget(label_14, 1, 5, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(tlinsWPilotSettings);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setFont(font);
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setFont(font1);

        gridLayout_2->addWidget(label_15, 0, 2, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font1);
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_7, 1, 0, 1, 1);

        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font1);
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_10, 1, 3, 1, 1);

        degrisY = new tlinsWCoordinateDegris(groupBox_2);
        degrisY->setObjectName(QString::fromUtf8("degrisY"));
        degrisY->setMinimumSize(QSize(165, 0));
        degrisY->setFont(font1);

        gridLayout_2->addWidget(degrisY, 1, 4, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font1);
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_5, 0, 3, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        degrisVY = new tlinsWCoordinateDegris(groupBox_2);
        degrisVY->setObjectName(QString::fromUtf8("degrisVY"));
        degrisVY->setMinimumSize(QSize(165, 0));
        degrisVY->setFont(font1);

        gridLayout_2->addWidget(degrisVY, 0, 4, 1, 1);

        degrisX = new tlinsWCoordinateDegris(groupBox_2);
        degrisX->setObjectName(QString::fromUtf8("degrisX"));
        sizePolicy.setHeightForWidth(degrisX->sizePolicy().hasHeightForWidth());
        degrisX->setSizePolicy(sizePolicy);
        degrisX->setMinimumSize(QSize(165, 0));
        degrisX->setFont(font1);

        gridLayout_2->addWidget(degrisX, 1, 1, 1, 1);

        degrisVX = new tlinsWCoordinateDegris(groupBox_2);
        degrisVX->setObjectName(QString::fromUtf8("degrisVX"));
        sizePolicy.setHeightForWidth(degrisVX->sizePolicy().hasHeightForWidth());
        degrisVX->setSizePolicy(sizePolicy);
        degrisVX->setMinimumSize(QSize(165, 0));
        degrisVX->setFont(font1);

        gridLayout_2->addWidget(degrisVX, 0, 1, 1, 1);

        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setFont(font1);

        gridLayout_2->addWidget(label_16, 1, 2, 1, 1);

        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setFont(font1);

        gridLayout_2->addWidget(label_17, 0, 5, 1, 1);

        label_18 = new QLabel(groupBox_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setFont(font1);

        gridLayout_2->addWidget(label_18, 1, 5, 1, 1);


        verticalLayout_2->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(tlinsWPilotSettings);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setFont(font);
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_3, 0, 0, 1, 1);

        astroVDC = new tlinsWCoordinateDeclination(groupBox_3);
        astroVDC->setObjectName(QString::fromUtf8("astroVDC"));
        astroVDC->setMinimumSize(QSize(165, 0));
        astroVDC->setFont(font1);

        gridLayout_3->addWidget(astroVDC, 0, 4, 1, 1);

        label_20 = new QLabel(groupBox_3);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setFont(font1);

        gridLayout_3->addWidget(label_20, 0, 2, 1, 1);

        label_19 = new QLabel(groupBox_3);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setFont(font1);
        label_19->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_19, 0, 3, 1, 1);

        label_21 = new QLabel(groupBox_3);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setFont(font1);

        gridLayout_3->addWidget(label_21, 0, 5, 1, 1);

        astroVRA = new tlinsWCoordinateHourAngle(groupBox_3);
        astroVRA->setObjectName(QString::fromUtf8("astroVRA"));
        sizePolicy.setHeightForWidth(astroVRA->sizePolicy().hasHeightForWidth());
        astroVRA->setSizePolicy(sizePolicy);
        astroVRA->setMinimumSize(QSize(165, 0));
        astroVRA->setFont(font1);

        gridLayout_3->addWidget(astroVRA, 0, 1, 1, 1);

        label_22 = new QLabel(groupBox_3);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setFont(font1);
        label_22->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_22, 1, 0, 1, 1);

        astroRA = new tlinsWCoordinateHourAngle(groupBox_3);
        astroRA->setObjectName(QString::fromUtf8("astroRA"));
        sizePolicy.setHeightForWidth(astroRA->sizePolicy().hasHeightForWidth());
        astroRA->setSizePolicy(sizePolicy);
        astroRA->setMinimumSize(QSize(165, 0));
        astroRA->setFont(font1);

        gridLayout_3->addWidget(astroRA, 1, 1, 1, 1);

        label_23 = new QLabel(groupBox_3);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setFont(font1);

        gridLayout_3->addWidget(label_23, 1, 2, 1, 1);

        label_24 = new QLabel(groupBox_3);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setFont(font1);
        label_24->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_24, 1, 3, 1, 1);

        astroDC = new tlinsWCoordinateDeclination(groupBox_3);
        astroDC->setObjectName(QString::fromUtf8("astroDC"));
        astroDC->setMinimumSize(QSize(165, 0));
        astroDC->setFont(font1);

        gridLayout_3->addWidget(astroDC, 1, 4, 1, 1);

        label_25 = new QLabel(groupBox_3);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setFont(font1);

        gridLayout_3->addWidget(label_25, 1, 5, 1, 1);


        verticalLayout_2->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(tlinsWPilotSettings);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setFont(font);
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font1);
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_4, 0, 0, 1, 1);

        label_29 = new QLabel(groupBox_4);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setFont(font1);

        gridLayout_4->addWidget(label_29, 0, 2, 1, 1);

        label_26 = new QLabel(groupBox_4);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setFont(font1);
        label_26->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_26, 0, 3, 1, 1);

        guideVX = new tlinsWCoordinateHourAngle(groupBox_4);
        guideVX->setObjectName(QString::fromUtf8("guideVX"));
        sizePolicy.setHeightForWidth(guideVX->sizePolicy().hasHeightForWidth());
        guideVX->setSizePolicy(sizePolicy);
        guideVX->setMinimumSize(QSize(165, 0));

        gridLayout_4->addWidget(guideVX, 0, 1, 1, 1);

        guideVY = new tlinsWCoordinateDeclination(groupBox_4);
        guideVY->setObjectName(QString::fromUtf8("guideVY"));
        guideVY->setMinimumSize(QSize(165, 0));

        gridLayout_4->addWidget(guideVY, 0, 4, 1, 1);

        label_27 = new QLabel(groupBox_4);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setFont(font1);
        label_27->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_27, 1, 0, 1, 1);

        guideY = new tlinsWCoordinateDeclination(groupBox_4);
        guideY->setObjectName(QString::fromUtf8("guideY"));
        guideY->setMinimumSize(QSize(165, 0));

        gridLayout_4->addWidget(guideY, 1, 4, 1, 1);

        label_28 = new QLabel(groupBox_4);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setFont(font1);
        label_28->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_28, 1, 3, 1, 1);

        label_30 = new QLabel(groupBox_4);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setFont(font1);

        gridLayout_4->addWidget(label_30, 1, 2, 1, 1);

        guideX = new tlinsWCoordinateHourAngle(groupBox_4);
        guideX->setObjectName(QString::fromUtf8("guideX"));
        sizePolicy.setHeightForWidth(guideX->sizePolicy().hasHeightForWidth());
        guideX->setSizePolicy(sizePolicy);
        guideX->setMinimumSize(QSize(165, 0));

        gridLayout_4->addWidget(guideX, 1, 1, 1, 1);

        label_31 = new QLabel(groupBox_4);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setFont(font1);

        gridLayout_4->addWidget(label_31, 0, 5, 1, 1);

        label_32 = new QLabel(groupBox_4);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setFont(font1);

        gridLayout_4->addWidget(label_32, 1, 5, 1, 1);


        verticalLayout_2->addWidget(groupBox_4);


        retranslateUi(tlinsWPilotSettings);

        QMetaObject::connectSlotsByName(tlinsWPilotSettings);
    } // setupUi

    void retranslateUi(QWidget *tlinsWPilotSettings)
    {
        tlinsWPilotSettings->setWindowTitle(QApplication::translate("tlinsWPilotSettings", "Form", nullptr));
        groupBox->setTitle(QApplication::translate("tlinsWPilotSettings", "Steps defaults", nullptr));
        label_8->setText(QApplication::translate("tlinsWPilotSettings", "Distance(X)", nullptr));
        label_6->setText(QApplication::translate("tlinsWPilotSettings", "V(Y)", nullptr));
        label_9->setText(QApplication::translate("tlinsWPilotSettings", "Distance(Y)", nullptr));
        label_11->setText(QApplication::translate("tlinsWPilotSettings", "[steps/s]", nullptr));
        label->setText(QApplication::translate("tlinsWPilotSettings", "V(X)", nullptr));
        label_12->setText(QApplication::translate("tlinsWPilotSettings", "[steps/s]", nullptr));
        label_13->setText(QApplication::translate("tlinsWPilotSettings", "[steps]", nullptr));
        label_14->setText(QApplication::translate("tlinsWPilotSettings", "[steps]", nullptr));
        groupBox_2->setTitle(QApplication::translate("tlinsWPilotSettings", "Degris defaults", nullptr));
        label_15->setText(QApplication::translate("tlinsWPilotSettings", "[degris/s]", nullptr));
        label_7->setText(QApplication::translate("tlinsWPilotSettings", "Distance(X)", nullptr));
        label_10->setText(QApplication::translate("tlinsWPilotSettings", "Distance(Y)", nullptr));
        label_5->setText(QApplication::translate("tlinsWPilotSettings", "V(Y)", nullptr));
        label_2->setText(QApplication::translate("tlinsWPilotSettings", "V(X)", nullptr));
        label_16->setText(QApplication::translate("tlinsWPilotSettings", "[degris]", nullptr));
        label_17->setText(QApplication::translate("tlinsWPilotSettings", "[degris/s]", nullptr));
        label_18->setText(QApplication::translate("tlinsWPilotSettings", "[degris]", nullptr));
        groupBox_3->setTitle(QApplication::translate("tlinsWPilotSettings", "Astro defaults", nullptr));
        label_3->setText(QApplication::translate("tlinsWPilotSettings", "V(RA)", nullptr));
        label_20->setText(QApplication::translate("tlinsWPilotSettings", "[hours/s]", nullptr));
        label_19->setText(QApplication::translate("tlinsWPilotSettings", "V(DC)", nullptr));
        label_21->setText(QApplication::translate("tlinsWPilotSettings", "[degris/s]", nullptr));
        label_22->setText(QApplication::translate("tlinsWPilotSettings", "Distance(RA)", nullptr));
        label_23->setText(QApplication::translate("tlinsWPilotSettings", "[hours]", nullptr));
        label_24->setText(QApplication::translate("tlinsWPilotSettings", "Distance(DC)", nullptr));
        label_25->setText(QApplication::translate("tlinsWPilotSettings", "[degris]", nullptr));
        groupBox_4->setTitle(QApplication::translate("tlinsWPilotSettings", "Guiding defaults", nullptr));
        label_4->setText(QApplication::translate("tlinsWPilotSettings", "V(X)", nullptr));
        label_29->setText(QApplication::translate("tlinsWPilotSettings", "[steps/s]", nullptr));
        label_26->setText(QApplication::translate("tlinsWPilotSettings", "V(Y)", nullptr));
        label_27->setText(QApplication::translate("tlinsWPilotSettings", "Distance(X)", nullptr));
        label_28->setText(QApplication::translate("tlinsWPilotSettings", "Distance(Y)", nullptr));
        label_30->setText(QApplication::translate("tlinsWPilotSettings", "[steps]", nullptr));
        label_31->setText(QApplication::translate("tlinsWPilotSettings", "[steps/s]", nullptr));
        label_32->setText(QApplication::translate("tlinsWPilotSettings", "[steps]", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWPilotSettings: public Ui_tlinsWPilotSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWPILOTSETTINGS_H
