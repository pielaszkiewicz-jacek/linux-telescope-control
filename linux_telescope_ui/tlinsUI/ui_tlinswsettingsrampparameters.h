/********************************************************************************
** Form generated from reading UI file 'tlinswsettingsrampparameters.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWSETTINGSRAMPPARAMETERS_H
#define UI_TLINSWSETTINGSRAMPPARAMETERS_H

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

class Ui_tlinsWSettingsRampParameters
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_4;
    tlinsWDecimalValue *stepsAY;
    tlinsWDecimalValue *stepsDY;
    QLabel *label_5;
    tlinsWDecimalValue *stepsAX;
    QLabel *label_6;
    QLabel *label_9;
    tlinsWDecimalValue *stepsDX;
    QLabel *label_8;
    QLabel *label_7;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    tlinsWDecimalValue *stepsVmaxX;
    tlinsWDecimalValue *stepsVmaxY;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_2;
    QLabel *label_19;
    tlinsWCoordinateDegris *degrisAX;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_2;
    QLabel *label_18;
    QLabel *label_15;
    tlinsWCoordinateDegris *degrisAY;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_25;
    tlinsWCoordinateDegris *degrisDX;
    tlinsWCoordinateDegris *degrisVmaxX;
    tlinsWCoordinateDegris *degrisDY;
    tlinsWCoordinateDegris *degrisVmaxY;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout_3;
    QLabel *label_30;
    tlinsWCoordinateDeclination *astroDDc;
    QLabel *label_3;
    QLabel *label_26;
    QLabel *label_27;
    tlinsWCoordinateHourAngle *astroDRa;
    QLabel *label_29;
    QLabel *label_28;
    tlinsWCoordinateHourAngle *astroARa;
    tlinsWCoordinateHourAngle *astroVmaxRa;
    tlinsWCoordinateDeclination *astroADc;
    tlinsWCoordinateDeclination *astroVmaxDc;
    QLabel *label_31;
    QLabel *label_32;
    QLabel *label_33;
    QLabel *label_34;
    QLabel *label_35;
    QLabel *label_36;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_5;
    QGridLayout *gridLayout_4;
    QLabel *label_51;
    QLabel *label_50;
    tlinsWCoordinateHourAngle *guidingVmaxRa;
    tlinsWCoordinateDeclination *guidingDDc;
    QLabel *label_38;
    QLabel *label_40;
    tlinsWCoordinateDeclination *guidingDRa;
    QLabel *label_45;
    QLabel *label_39;
    tlinsWCoordinateHourAngle *guidingARa;
    QLabel *label_47;
    QLabel *label_44;
    QLabel *label_41;
    QLabel *label_48;
    tlinsWCoordinateDeclination *guidingVmaxDc;
    tlinsWCoordinateDeclination *guidingADc;
    QLabel *label_43;
    QLabel *label_42;

    void setupUi(QWidget *tlinsWSettingsRampParameters)
    {
        if (tlinsWSettingsRampParameters->objectName().isEmpty())
            tlinsWSettingsRampParameters->setObjectName(QString::fromUtf8("tlinsWSettingsRampParameters"));
        tlinsWSettingsRampParameters->resize(790, 535);
        verticalLayout = new QVBoxLayout(tlinsWSettingsRampParameters);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(tlinsWSettingsRampParameters);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QFont font;
        font.setPointSize(11);
        font.setItalic(true);
        groupBox->setFont(font);
        groupBox->setFlat(true);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(10);
        gridLayout->setVerticalSpacing(5);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(105, 0));
        label->setMaximumSize(QSize(105, 16777215));
        QFont font1;
        font1.setPointSize(10);
        font1.setItalic(false);
        label->setFont(font1);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setMinimumSize(QSize(105, 0));
        label_4->setMaximumSize(QSize(105, 16777215));
        label_4->setFont(font1);
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 0, 3, 1, 1);

        stepsAY = new tlinsWDecimalValue(groupBox);
        stepsAY->setObjectName(QString::fromUtf8("stepsAY"));
        stepsAY->setMinimumSize(QSize(0, 0));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Noto Sans"));
        font2.setItalic(false);
        stepsAY->setFont(font2);

        gridLayout->addWidget(stepsAY, 0, 4, 1, 1);

        stepsDY = new tlinsWDecimalValue(groupBox);
        stepsDY->setObjectName(QString::fromUtf8("stepsDY"));
        stepsDY->setMinimumSize(QSize(165, 0));
        stepsDY->setFont(font2);

        gridLayout->addWidget(stepsDY, 1, 4, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(80, 0));
        label_5->setMaximumSize(QSize(80, 16777215));
        label_5->setFont(font1);

        gridLayout->addWidget(label_5, 0, 2, 1, 1);

        stepsAX = new tlinsWDecimalValue(groupBox);
        stepsAX->setObjectName(QString::fromUtf8("stepsAX"));
        stepsAX->setMinimumSize(QSize(165, 0));
        stepsAX->setFont(font2);

        gridLayout->addWidget(stepsAX, 0, 1, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(80, 0));
        label_6->setMaximumSize(QSize(80, 16777215));
        label_6->setFont(font1);

        gridLayout->addWidget(label_6, 0, 5, 1, 1);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);
        label_9->setMinimumSize(QSize(105, 0));
        label_9->setMaximumSize(QSize(105, 16777215));
        label_9->setFont(font1);
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_9, 1, 3, 1, 1);

        stepsDX = new tlinsWDecimalValue(groupBox);
        stepsDX->setObjectName(QString::fromUtf8("stepsDX"));
        stepsDX->setMinimumSize(QSize(0, 0));
        stepsDX->setFont(font2);

        gridLayout->addWidget(stepsDX, 1, 1, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(80, 0));
        label_8->setMaximumSize(QSize(80, 16777215));
        label_8->setFont(font1);

        gridLayout->addWidget(label_8, 1, 2, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_7->setMinimumSize(QSize(105, 0));
        label_7->setMaximumSize(QSize(105, 16777215));
        label_7->setFont(font1);
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_7, 1, 0, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMinimumSize(QSize(80, 0));
        label_10->setMaximumSize(QSize(80, 16777215));
        label_10->setFont(font1);

        gridLayout->addWidget(label_10, 1, 5, 1, 1);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy);
        label_11->setMinimumSize(QSize(105, 0));
        label_11->setMaximumSize(QSize(105, 16777215));
        label_11->setFont(font1);
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_11, 2, 0, 1, 1);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setMinimumSize(QSize(80, 0));
        label_12->setMaximumSize(QSize(80, 16777215));
        label_12->setFont(font1);

        gridLayout->addWidget(label_12, 2, 2, 1, 1);

        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setMinimumSize(QSize(80, 0));
        label_13->setMaximumSize(QSize(80, 16777215));
        label_13->setFont(font1);

        gridLayout->addWidget(label_13, 2, 5, 1, 1);

        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        sizePolicy.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy);
        label_14->setMinimumSize(QSize(105, 0));
        label_14->setMaximumSize(QSize(105, 16777215));
        label_14->setFont(font1);
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_14, 2, 3, 1, 1);

        stepsVmaxX = new tlinsWDecimalValue(groupBox);
        stepsVmaxX->setObjectName(QString::fromUtf8("stepsVmaxX"));
        stepsVmaxX->setMinimumSize(QSize(0, 0));
        stepsVmaxX->setFont(font2);

        gridLayout->addWidget(stepsVmaxX, 2, 1, 1, 1);

        stepsVmaxY = new tlinsWDecimalValue(groupBox);
        stepsVmaxY->setObjectName(QString::fromUtf8("stepsVmaxY"));
        stepsVmaxY->setMinimumSize(QSize(0, 0));
        stepsVmaxY->setFont(font2);

        gridLayout->addWidget(stepsVmaxY, 2, 4, 1, 1);


        verticalLayout_2->addLayout(gridLayout);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(tlinsWSettingsRampParameters);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setFont(font);
        groupBox_2->setFlat(true);
        groupBox_2->setCheckable(false);
        groupBox_2->setChecked(false);
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(10);
        label_19 = new QLabel(groupBox_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setMinimumSize(QSize(80, 0));
        label_19->setMaximumSize(QSize(80, 16777215));
        label_19->setFont(font1);

        gridLayout_2->addWidget(label_19, 0, 5, 1, 1);

        degrisAX = new tlinsWCoordinateDegris(groupBox_2);
        degrisAX->setObjectName(QString::fromUtf8("degrisAX"));
        degrisAX->setMinimumSize(QSize(0, 0));
        degrisAX->setFont(font2);

        gridLayout_2->addWidget(degrisAX, 0, 1, 1, 1);

        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        sizePolicy.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy);
        label_16->setMinimumSize(QSize(105, 0));
        label_16->setMaximumSize(QSize(105, 16777215));
        label_16->setFont(font1);
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_16, 2, 0, 1, 1);

        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        sizePolicy.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
        label_17->setSizePolicy(sizePolicy);
        label_17->setMinimumSize(QSize(105, 0));
        label_17->setMaximumSize(QSize(105, 16777215));
        label_17->setFont(font1);
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_17, 0, 3, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(105, 0));
        label_2->setMaximumSize(QSize(105, 16777215));
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        label_18 = new QLabel(groupBox_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setMinimumSize(QSize(80, 0));
        label_18->setMaximumSize(QSize(80, 16777215));
        label_18->setFont(font1);

        gridLayout_2->addWidget(label_18, 0, 2, 1, 1);

        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        sizePolicy.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy);
        label_15->setMinimumSize(QSize(105, 0));
        label_15->setMaximumSize(QSize(105, 16777215));
        label_15->setFont(font1);
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_15, 1, 0, 1, 1);

        degrisAY = new tlinsWCoordinateDegris(groupBox_2);
        degrisAY->setObjectName(QString::fromUtf8("degrisAY"));
        degrisAY->setMinimumSize(QSize(0, 0));
        degrisAY->setFont(font2);

        gridLayout_2->addWidget(degrisAY, 0, 4, 1, 1);

        label_20 = new QLabel(groupBox_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setMinimumSize(QSize(80, 0));
        label_20->setMaximumSize(QSize(80, 16777215));
        label_20->setFont(font1);

        gridLayout_2->addWidget(label_20, 2, 2, 1, 1);

        label_21 = new QLabel(groupBox_2);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        sizePolicy.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
        label_21->setSizePolicy(sizePolicy);
        label_21->setMinimumSize(QSize(105, 0));
        label_21->setMaximumSize(QSize(105, 16777215));
        label_21->setFont(font1);
        label_21->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_21, 2, 3, 1, 1);

        label_22 = new QLabel(groupBox_2);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setMinimumSize(QSize(80, 0));
        label_22->setMaximumSize(QSize(80, 16777215));
        label_22->setFont(font1);

        gridLayout_2->addWidget(label_22, 1, 2, 1, 1);

        label_23 = new QLabel(groupBox_2);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        sizePolicy.setHeightForWidth(label_23->sizePolicy().hasHeightForWidth());
        label_23->setSizePolicy(sizePolicy);
        label_23->setMinimumSize(QSize(105, 0));
        label_23->setMaximumSize(QSize(105, 16777215));
        label_23->setFont(font1);
        label_23->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_23, 1, 3, 1, 1);

        label_24 = new QLabel(groupBox_2);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setMinimumSize(QSize(80, 0));
        label_24->setMaximumSize(QSize(80, 16777215));
        label_24->setFont(font1);

        gridLayout_2->addWidget(label_24, 1, 5, 1, 1);

        label_25 = new QLabel(groupBox_2);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setMinimumSize(QSize(80, 0));
        label_25->setMaximumSize(QSize(80, 16777215));
        label_25->setFont(font1);

        gridLayout_2->addWidget(label_25, 2, 5, 1, 1);

        degrisDX = new tlinsWCoordinateDegris(groupBox_2);
        degrisDX->setObjectName(QString::fromUtf8("degrisDX"));
        degrisDX->setMinimumSize(QSize(165, 0));
        degrisDX->setFont(font2);

        gridLayout_2->addWidget(degrisDX, 1, 1, 1, 1);

        degrisVmaxX = new tlinsWCoordinateDegris(groupBox_2);
        degrisVmaxX->setObjectName(QString::fromUtf8("degrisVmaxX"));
        degrisVmaxX->setMinimumSize(QSize(0, 0));
        degrisVmaxX->setFont(font2);

        gridLayout_2->addWidget(degrisVmaxX, 2, 1, 1, 1);

        degrisDY = new tlinsWCoordinateDegris(groupBox_2);
        degrisDY->setObjectName(QString::fromUtf8("degrisDY"));
        degrisDY->setMinimumSize(QSize(165, 0));
        degrisDY->setFont(font2);

        gridLayout_2->addWidget(degrisDY, 1, 4, 1, 1);

        degrisVmaxY = new tlinsWCoordinateDegris(groupBox_2);
        degrisVmaxY->setObjectName(QString::fromUtf8("degrisVmaxY"));
        degrisVmaxY->setMinimumSize(QSize(0, 0));
        degrisVmaxY->setFont(font2);

        gridLayout_2->addWidget(degrisVmaxY, 2, 4, 1, 1);


        verticalLayout_3->addLayout(gridLayout_2);


        verticalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(tlinsWSettingsRampParameters);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setFont(font);
        groupBox_3->setFlat(true);
        verticalLayout_4 = new QVBoxLayout(groupBox_3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setHorizontalSpacing(10);
        label_30 = new QLabel(groupBox_3);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setMinimumSize(QSize(80, 0));
        label_30->setMaximumSize(QSize(80, 16777215));
        label_30->setFont(font1);

        gridLayout_3->addWidget(label_30, 1, 5, 1, 1);

        astroDDc = new tlinsWCoordinateDeclination(groupBox_3);
        astroDDc->setObjectName(QString::fromUtf8("astroDDc"));
        astroDDc->setMinimumSize(QSize(165, 0));
        astroDDc->setFont(font2);

        gridLayout_3->addWidget(astroDDc, 1, 4, 1, 1);

        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(105, 0));
        label_3->setMaximumSize(QSize(105, 16777215));
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_3, 0, 0, 1, 1);

        label_26 = new QLabel(groupBox_3);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        sizePolicy.setHeightForWidth(label_26->sizePolicy().hasHeightForWidth());
        label_26->setSizePolicy(sizePolicy);
        label_26->setMinimumSize(QSize(105, 0));
        label_26->setMaximumSize(QSize(105, 16777215));
        label_26->setFont(font1);
        label_26->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_26, 1, 0, 1, 1);

        label_27 = new QLabel(groupBox_3);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        sizePolicy.setHeightForWidth(label_27->sizePolicy().hasHeightForWidth());
        label_27->setSizePolicy(sizePolicy);
        label_27->setMinimumSize(QSize(105, 0));
        label_27->setMaximumSize(QSize(105, 16777215));
        label_27->setFont(font1);
        label_27->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_27, 2, 0, 1, 1);

        astroDRa = new tlinsWCoordinateHourAngle(groupBox_3);
        astroDRa->setObjectName(QString::fromUtf8("astroDRa"));
        astroDRa->setMinimumSize(QSize(165, 0));
        astroDRa->setFont(font2);

        gridLayout_3->addWidget(astroDRa, 1, 1, 1, 1);

        label_29 = new QLabel(groupBox_3);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        sizePolicy.setHeightForWidth(label_29->sizePolicy().hasHeightForWidth());
        label_29->setSizePolicy(sizePolicy);
        label_29->setMinimumSize(QSize(105, 0));
        label_29->setMaximumSize(QSize(105, 16777215));
        label_29->setFont(font1);
        label_29->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_29, 1, 3, 1, 1);

        label_28 = new QLabel(groupBox_3);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setMinimumSize(QSize(80, 0));
        label_28->setMaximumSize(QSize(80, 16777215));
        label_28->setFont(font1);

        gridLayout_3->addWidget(label_28, 1, 2, 1, 1);

        astroARa = new tlinsWCoordinateHourAngle(groupBox_3);
        astroARa->setObjectName(QString::fromUtf8("astroARa"));
        astroARa->setMinimumSize(QSize(0, 0));
        astroARa->setFont(font2);

        gridLayout_3->addWidget(astroARa, 0, 1, 1, 1);

        astroVmaxRa = new tlinsWCoordinateHourAngle(groupBox_3);
        astroVmaxRa->setObjectName(QString::fromUtf8("astroVmaxRa"));
        astroVmaxRa->setMinimumSize(QSize(0, 0));
        astroVmaxRa->setFont(font2);

        gridLayout_3->addWidget(astroVmaxRa, 2, 1, 1, 1);

        astroADc = new tlinsWCoordinateDeclination(groupBox_3);
        astroADc->setObjectName(QString::fromUtf8("astroADc"));
        astroADc->setMinimumSize(QSize(0, 0));
        astroADc->setFont(font2);

        gridLayout_3->addWidget(astroADc, 0, 4, 1, 1);

        astroVmaxDc = new tlinsWCoordinateDeclination(groupBox_3);
        astroVmaxDc->setObjectName(QString::fromUtf8("astroVmaxDc"));
        astroVmaxDc->setMinimumSize(QSize(0, 0));
        astroVmaxDc->setFont(font2);

        gridLayout_3->addWidget(astroVmaxDc, 2, 4, 1, 1);

        label_31 = new QLabel(groupBox_3);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setMinimumSize(QSize(80, 0));
        label_31->setMaximumSize(QSize(80, 16777215));
        label_31->setFont(font1);

        gridLayout_3->addWidget(label_31, 0, 5, 1, 1);

        label_32 = new QLabel(groupBox_3);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setMinimumSize(QSize(80, 0));
        label_32->setMaximumSize(QSize(80, 16777215));
        label_32->setFont(font1);

        gridLayout_3->addWidget(label_32, 2, 5, 1, 1);

        label_33 = new QLabel(groupBox_3);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setMinimumSize(QSize(80, 0));
        label_33->setMaximumSize(QSize(80, 16777215));
        label_33->setFont(font1);

        gridLayout_3->addWidget(label_33, 0, 2, 1, 1);

        label_34 = new QLabel(groupBox_3);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        sizePolicy.setHeightForWidth(label_34->sizePolicy().hasHeightForWidth());
        label_34->setSizePolicy(sizePolicy);
        label_34->setMinimumSize(QSize(105, 0));
        label_34->setMaximumSize(QSize(105, 16777215));
        label_34->setFont(font1);
        label_34->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_34, 0, 3, 1, 1);

        label_35 = new QLabel(groupBox_3);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        label_35->setMinimumSize(QSize(80, 0));
        label_35->setMaximumSize(QSize(80, 16777215));
        label_35->setFont(font1);

        gridLayout_3->addWidget(label_35, 2, 2, 1, 1);

        label_36 = new QLabel(groupBox_3);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        sizePolicy.setHeightForWidth(label_36->sizePolicy().hasHeightForWidth());
        label_36->setSizePolicy(sizePolicy);
        label_36->setMinimumSize(QSize(105, 0));
        label_36->setMaximumSize(QSize(105, 16777215));
        label_36->setFont(font1);
        label_36->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_36, 2, 3, 1, 1);


        verticalLayout_4->addLayout(gridLayout_3);


        verticalLayout->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(tlinsWSettingsRampParameters);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setFont(font);
        verticalLayout_5 = new QVBoxLayout(groupBox_4);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setHorizontalSpacing(10);
        label_51 = new QLabel(groupBox_4);
        label_51->setObjectName(QString::fromUtf8("label_51"));
        label_51->setMinimumSize(QSize(80, 0));
        label_51->setMaximumSize(QSize(80, 16777215));
        label_51->setFont(font1);

        gridLayout_4->addWidget(label_51, 2, 5, 1, 1);

        label_50 = new QLabel(groupBox_4);
        label_50->setObjectName(QString::fromUtf8("label_50"));
        label_50->setMinimumSize(QSize(80, 0));
        label_50->setMaximumSize(QSize(80, 16777215));
        label_50->setFont(font1);

        gridLayout_4->addWidget(label_50, 1, 5, 1, 1);

        guidingVmaxRa = new tlinsWCoordinateHourAngle(groupBox_4);
        guidingVmaxRa->setObjectName(QString::fromUtf8("guidingVmaxRa"));
        guidingVmaxRa->setMinimumSize(QSize(0, 0));
        guidingVmaxRa->setFont(font2);

        gridLayout_4->addWidget(guidingVmaxRa, 2, 1, 1, 1);

        guidingDDc = new tlinsWCoordinateDeclination(groupBox_4);
        guidingDDc->setObjectName(QString::fromUtf8("guidingDDc"));
        guidingDDc->setMinimumSize(QSize(165, 0));
        guidingDDc->setFont(font2);

        gridLayout_4->addWidget(guidingDDc, 1, 4, 1, 1);

        label_38 = new QLabel(groupBox_4);
        label_38->setObjectName(QString::fromUtf8("label_38"));
        sizePolicy.setHeightForWidth(label_38->sizePolicy().hasHeightForWidth());
        label_38->setSizePolicy(sizePolicy);
        label_38->setMinimumSize(QSize(105, 0));
        label_38->setMaximumSize(QSize(105, 16777215));
        label_38->setFont(font1);
        label_38->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_38, 2, 0, 1, 1);

        label_40 = new QLabel(groupBox_4);
        label_40->setObjectName(QString::fromUtf8("label_40"));
        sizePolicy.setHeightForWidth(label_40->sizePolicy().hasHeightForWidth());
        label_40->setSizePolicy(sizePolicy);
        label_40->setMinimumSize(QSize(105, 0));
        label_40->setMaximumSize(QSize(105, 16777215));
        label_40->setFont(font1);
        label_40->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_40, 0, 0, 1, 1);

        guidingDRa = new tlinsWCoordinateDeclination(groupBox_4);
        guidingDRa->setObjectName(QString::fromUtf8("guidingDRa"));
        guidingDRa->setMinimumSize(QSize(165, 0));
        guidingDRa->setFont(font2);

        gridLayout_4->addWidget(guidingDRa, 1, 1, 1, 1);

        label_45 = new QLabel(groupBox_4);
        label_45->setObjectName(QString::fromUtf8("label_45"));
        label_45->setMinimumSize(QSize(80, 0));
        label_45->setMaximumSize(QSize(80, 16777215));
        label_45->setFont(font1);

        gridLayout_4->addWidget(label_45, 2, 2, 1, 1);

        label_39 = new QLabel(groupBox_4);
        label_39->setObjectName(QString::fromUtf8("label_39"));
        sizePolicy.setHeightForWidth(label_39->sizePolicy().hasHeightForWidth());
        label_39->setSizePolicy(sizePolicy);
        label_39->setMinimumSize(QSize(105, 0));
        label_39->setMaximumSize(QSize(105, 16777215));
        label_39->setFont(font1);
        label_39->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_39, 1, 0, 1, 1);

        guidingARa = new tlinsWCoordinateHourAngle(groupBox_4);
        guidingARa->setObjectName(QString::fromUtf8("guidingARa"));
        guidingARa->setMinimumSize(QSize(0, 0));
        guidingARa->setFont(font2);

        gridLayout_4->addWidget(guidingARa, 0, 1, 1, 1);

        label_47 = new QLabel(groupBox_4);
        label_47->setObjectName(QString::fromUtf8("label_47"));
        sizePolicy.setHeightForWidth(label_47->sizePolicy().hasHeightForWidth());
        label_47->setSizePolicy(sizePolicy);
        label_47->setMinimumSize(QSize(105, 0));
        label_47->setMaximumSize(QSize(105, 16777215));
        label_47->setFont(font1);
        label_47->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_47, 1, 3, 1, 1);

        label_44 = new QLabel(groupBox_4);
        label_44->setObjectName(QString::fromUtf8("label_44"));
        label_44->setMinimumSize(QSize(80, 0));
        label_44->setMaximumSize(QSize(80, 16777215));
        label_44->setFont(font1);

        gridLayout_4->addWidget(label_44, 1, 2, 1, 1);

        label_41 = new QLabel(groupBox_4);
        label_41->setObjectName(QString::fromUtf8("label_41"));
        label_41->setMinimumSize(QSize(80, 0));
        label_41->setMaximumSize(QSize(80, 16777215));
        label_41->setFont(font1);

        gridLayout_4->addWidget(label_41, 0, 2, 1, 1);

        label_48 = new QLabel(groupBox_4);
        label_48->setObjectName(QString::fromUtf8("label_48"));
        sizePolicy.setHeightForWidth(label_48->sizePolicy().hasHeightForWidth());
        label_48->setSizePolicy(sizePolicy);
        label_48->setMinimumSize(QSize(105, 0));
        label_48->setMaximumSize(QSize(105, 16777215));
        label_48->setFont(font1);
        label_48->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_48, 2, 3, 1, 1);

        guidingVmaxDc = new tlinsWCoordinateDeclination(groupBox_4);
        guidingVmaxDc->setObjectName(QString::fromUtf8("guidingVmaxDc"));
        guidingVmaxDc->setMinimumSize(QSize(0, 0));
        guidingVmaxDc->setFont(font2);

        gridLayout_4->addWidget(guidingVmaxDc, 2, 4, 1, 1);

        guidingADc = new tlinsWCoordinateDeclination(groupBox_4);
        guidingADc->setObjectName(QString::fromUtf8("guidingADc"));
        guidingADc->setMinimumSize(QSize(0, 0));
        guidingADc->setFont(font2);

        gridLayout_4->addWidget(guidingADc, 0, 4, 1, 1);

        label_43 = new QLabel(groupBox_4);
        label_43->setObjectName(QString::fromUtf8("label_43"));
        label_43->setMinimumSize(QSize(80, 0));
        label_43->setMaximumSize(QSize(80, 16777215));
        label_43->setFont(font1);

        gridLayout_4->addWidget(label_43, 0, 5, 1, 1);

        label_42 = new QLabel(groupBox_4);
        label_42->setObjectName(QString::fromUtf8("label_42"));
        sizePolicy.setHeightForWidth(label_42->sizePolicy().hasHeightForWidth());
        label_42->setSizePolicy(sizePolicy);
        label_42->setMinimumSize(QSize(105, 0));
        label_42->setMaximumSize(QSize(105, 16777215));
        label_42->setFont(font1);
        label_42->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_42, 0, 3, 1, 1);


        verticalLayout_5->addLayout(gridLayout_4);


        verticalLayout->addWidget(groupBox_4);


        retranslateUi(tlinsWSettingsRampParameters);

        QMetaObject::connectSlotsByName(tlinsWSettingsRampParameters);
    } // setupUi

    void retranslateUi(QWidget *tlinsWSettingsRampParameters)
    {
        tlinsWSettingsRampParameters->setWindowTitle(QApplication::translate("tlinsWSettingsRampParameters", "Form", nullptr));
        groupBox->setTitle(QApplication::translate("tlinsWSettingsRampParameters", "Steps", nullptr));
        label->setText(QApplication::translate("tlinsWSettingsRampParameters", "A (X)", nullptr));
        label_4->setText(QApplication::translate("tlinsWSettingsRampParameters", "A (Y)", nullptr));
        label_5->setText(QApplication::translate("tlinsWSettingsRampParameters", "[steps/s^2]", nullptr));
        label_6->setText(QApplication::translate("tlinsWSettingsRampParameters", "[steps/s^2]", nullptr));
        label_9->setText(QApplication::translate("tlinsWSettingsRampParameters", "D (Y)", nullptr));
        label_8->setText(QApplication::translate("tlinsWSettingsRampParameters", "[steps/s^2]", nullptr));
        label_7->setText(QApplication::translate("tlinsWSettingsRampParameters", "D (X)", nullptr));
        label_10->setText(QApplication::translate("tlinsWSettingsRampParameters", "[steps/s^2]", nullptr));
        label_11->setText(QApplication::translate("tlinsWSettingsRampParameters", "Vmax (X)", nullptr));
        label_12->setText(QApplication::translate("tlinsWSettingsRampParameters", "[steps/s]", nullptr));
        label_13->setText(QApplication::translate("tlinsWSettingsRampParameters", "[steps/s]", nullptr));
        label_14->setText(QApplication::translate("tlinsWSettingsRampParameters", "Vmax (Y)", nullptr));
        groupBox_2->setTitle(QApplication::translate("tlinsWSettingsRampParameters", "Degris", nullptr));
        label_19->setText(QApplication::translate("tlinsWSettingsRampParameters", "[degris/s^2]", nullptr));
        label_16->setText(QApplication::translate("tlinsWSettingsRampParameters", "Vmax (X)", nullptr));
        label_17->setText(QApplication::translate("tlinsWSettingsRampParameters", "A (Y)", nullptr));
        label_2->setText(QApplication::translate("tlinsWSettingsRampParameters", "A (X)", nullptr));
        label_18->setText(QApplication::translate("tlinsWSettingsRampParameters", "[degris/s^2]", nullptr));
        label_15->setText(QApplication::translate("tlinsWSettingsRampParameters", "D (X)", nullptr));
        label_20->setText(QApplication::translate("tlinsWSettingsRampParameters", "[degris/s]", nullptr));
        label_21->setText(QApplication::translate("tlinsWSettingsRampParameters", "Vmax (Y)", nullptr));
        label_22->setText(QApplication::translate("tlinsWSettingsRampParameters", "[degris/s^2]", nullptr));
        label_23->setText(QApplication::translate("tlinsWSettingsRampParameters", "D (Y)", nullptr));
        label_24->setText(QApplication::translate("tlinsWSettingsRampParameters", "[degris/s^2]", nullptr));
        label_25->setText(QApplication::translate("tlinsWSettingsRampParameters", "[degris/s]", nullptr));
        groupBox_3->setTitle(QApplication::translate("tlinsWSettingsRampParameters", "Astro", nullptr));
        label_30->setText(QApplication::translate("tlinsWSettingsRampParameters", "[degris/s^2]", nullptr));
        label_3->setText(QApplication::translate("tlinsWSettingsRampParameters", "A (Ra/Lin)", nullptr));
        label_26->setText(QApplication::translate("tlinsWSettingsRampParameters", "D (Ra/Lin)", nullptr));
        label_27->setText(QApplication::translate("tlinsWSettingsRampParameters", "Vmax (Ra/Lin)", nullptr));
        label_29->setText(QApplication::translate("tlinsWSettingsRampParameters", "D (Dc)", nullptr));
        label_28->setText(QApplication::translate("tlinsWSettingsRampParameters", "[hours/s^2]", nullptr));
        label_31->setText(QApplication::translate("tlinsWSettingsRampParameters", "[degris/s^2]", nullptr));
        label_32->setText(QApplication::translate("tlinsWSettingsRampParameters", "[degris/s]", nullptr));
        label_33->setText(QApplication::translate("tlinsWSettingsRampParameters", "[hours/s^2]", nullptr));
        label_34->setText(QApplication::translate("tlinsWSettingsRampParameters", "A (Dc)", nullptr));
        label_35->setText(QApplication::translate("tlinsWSettingsRampParameters", "[hours/s]", nullptr));
        label_36->setText(QApplication::translate("tlinsWSettingsRampParameters", "Vmax (Dc)", nullptr));
        groupBox_4->setTitle(QApplication::translate("tlinsWSettingsRampParameters", "Guiding", nullptr));
        label_51->setText(QApplication::translate("tlinsWSettingsRampParameters", "[degris/s]", nullptr));
        label_50->setText(QApplication::translate("tlinsWSettingsRampParameters", "[degris/s^2]", nullptr));
        label_38->setText(QApplication::translate("tlinsWSettingsRampParameters", "Vmax (Ra)", nullptr));
        label_40->setText(QApplication::translate("tlinsWSettingsRampParameters", "A (Ra)", nullptr));
        label_45->setText(QApplication::translate("tlinsWSettingsRampParameters", "[hours/s]", nullptr));
        label_39->setText(QApplication::translate("tlinsWSettingsRampParameters", "D (Ra)", nullptr));
        label_47->setText(QApplication::translate("tlinsWSettingsRampParameters", "D (Dc)", nullptr));
        label_44->setText(QApplication::translate("tlinsWSettingsRampParameters", "[hours/s^2]", nullptr));
        label_41->setText(QApplication::translate("tlinsWSettingsRampParameters", "[hours/s^2]", nullptr));
        label_48->setText(QApplication::translate("tlinsWSettingsRampParameters", "Vmax (Dc)", nullptr));
        label_43->setText(QApplication::translate("tlinsWSettingsRampParameters", "[hours/s^2]", nullptr));
        label_42->setText(QApplication::translate("tlinsWSettingsRampParameters", "A (Dc)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWSettingsRampParameters: public Ui_tlinsWSettingsRampParameters {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWSETTINGSRAMPPARAMETERS_H
