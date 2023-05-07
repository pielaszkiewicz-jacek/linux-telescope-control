/********************************************************************************
** Form generated from reading UI file 'tlinsastroobjectcoordinate.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSASTROOBJECTCOORDINATE_H
#define UI_TLINSASTROOBJECTCOORDINATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <tlinswdecimalvalue.h>
#include "tlinswcoordinatedeclination.h"
#include "tlinswcoordinatehourangle.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsAstroObjectCoordinate
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_4;
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer_11;
    tlinsWCoordinateHourAngle *ra;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_12;
    tlinsWCoordinateDeclination *dc;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    tlinsWCoordinateHourAngle *raMeanError;
    tlinsWCoordinateHourAngle *raMinError;
    tlinsWCoordinateDeclination *dcMeanError;
    QLabel *label_11;
    QLabel *label_5;
    QLabel *label_12;
    tlinsWCoordinateDeclination *dcMinError;
    QLabel *label_16;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer_5;
    tlinsWDecimalValue *raCentralEpoch;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_6;
    tlinsWDecimalValue *dcCentralEpoch;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_5;
    tlinsWDecimalValue *raProperMotion;
    QLabel *label_13;
    QLabel *label_15;
    QLabel *label_18;
    tlinsWDecimalValue *dcProperMotion;
    tlinsWCoordinateHourAngle *raProperMotionError;
    tlinsWCoordinateDeclination *dcProperMotionError;
    QLabel *label_6;

    void setupUi(QWidget *tlinsAstroObjectCoordinate)
    {
        if (tlinsAstroObjectCoordinate->objectName().isEmpty())
            tlinsAstroObjectCoordinate->setObjectName(QString::fromUtf8("tlinsAstroObjectCoordinate"));
        tlinsAstroObjectCoordinate->resize(749, 321);
        verticalLayout_2 = new QVBoxLayout(tlinsAstroObjectCoordinate);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_4 = new QGroupBox(tlinsAstroObjectCoordinate);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(11);
        groupBox_4->setFont(font);
        formLayout = new QFormLayout(groupBox_4);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setHorizontalSpacing(0);
        formLayout->setVerticalSpacing(0);
        formLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(5, -1, 5, -1);
        label = new QLabel(groupBox_4);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer_11 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_11);

        ra = new tlinsWCoordinateHourAngle(groupBox_4);
        ra->setObjectName(QString::fromUtf8("ra"));
        ra->setMinimumSize(QSize(0, 0));

        horizontalLayout->addWidget(ra);

        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        horizontalSpacer_12 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_12);

        dc = new tlinsWCoordinateDeclination(groupBox_4);
        dc->setObjectName(QString::fromUtf8("dc"));

        horizontalLayout->addWidget(dc);


        formLayout->setLayout(0, QFormLayout::SpanningRole, horizontalLayout);


        verticalLayout->addWidget(groupBox_4);

        groupBox_3 = new QGroupBox(tlinsAstroObjectCoordinate);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        groupBox_3->setFont(font);
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(5, 0, 0, 0);
        raMeanError = new tlinsWCoordinateHourAngle(groupBox_3);
        raMeanError->setObjectName(QString::fromUtf8("raMeanError"));

        gridLayout_3->addWidget(raMeanError, 1, 1, 1, 1);

        raMinError = new tlinsWCoordinateHourAngle(groupBox_3);
        raMinError->setObjectName(QString::fromUtf8("raMinError"));

        gridLayout_3->addWidget(raMinError, 0, 1, 1, 1);

        dcMeanError = new tlinsWCoordinateDeclination(groupBox_3);
        dcMeanError->setObjectName(QString::fromUtf8("dcMeanError"));

        gridLayout_3->addWidget(dcMeanError, 1, 3, 1, 1);

        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_3->addWidget(label_11, 0, 2, 1, 1);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_3->addWidget(label_5, 0, 0, 1, 1);

        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_3->addWidget(label_12, 1, 0, 1, 1);

        dcMinError = new tlinsWCoordinateDeclination(groupBox_3);
        dcMinError->setObjectName(QString::fromUtf8("dcMinError"));

        gridLayout_3->addWidget(dcMinError, 0, 3, 1, 1);

        label_16 = new QLabel(groupBox_3);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_3->addWidget(label_16, 1, 2, 1, 1);


        verticalLayout->addWidget(groupBox_3);

        groupBox = new QGroupBox(tlinsAstroObjectCoordinate);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setFont(font);
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setHorizontalSpacing(0);
        gridLayout_4->setVerticalSpacing(6);
        gridLayout_4->setContentsMargins(5, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_5->addWidget(label_8);

        horizontalSpacer_5 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        raCentralEpoch = new tlinsWDecimalValue(groupBox);
        raCentralEpoch->setObjectName(QString::fromUtf8("raCentralEpoch"));

        horizontalLayout_5->addWidget(raCentralEpoch);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_5->addWidget(label_7);

        horizontalSpacer_6 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);

        dcCentralEpoch = new tlinsWDecimalValue(groupBox);
        dcCentralEpoch->setObjectName(QString::fromUtf8("dcCentralEpoch"));

        horizontalLayout_5->addWidget(dcCentralEpoch);


        gridLayout_4->addLayout(horizontalLayout_5, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(tlinsAstroObjectCoordinate);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        groupBox_2->setFont(font);
        gridLayout_5 = new QGridLayout(groupBox_2);
        gridLayout_5->setSpacing(0);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(5, 0, 0, 0);
        raProperMotion = new tlinsWDecimalValue(groupBox_2);
        raProperMotion->setObjectName(QString::fromUtf8("raProperMotion"));

        gridLayout_5->addWidget(raProperMotion, 0, 1, 1, 1);

        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_5->addWidget(label_13, 0, 0, 1, 1);

        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_5->addWidget(label_15, 1, 0, 1, 1);

        label_18 = new QLabel(groupBox_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_5->addWidget(label_18, 1, 2, 1, 1);

        dcProperMotion = new tlinsWDecimalValue(groupBox_2);
        dcProperMotion->setObjectName(QString::fromUtf8("dcProperMotion"));

        gridLayout_5->addWidget(dcProperMotion, 0, 3, 1, 1);

        raProperMotionError = new tlinsWCoordinateHourAngle(groupBox_2);
        raProperMotionError->setObjectName(QString::fromUtf8("raProperMotionError"));

        gridLayout_5->addWidget(raProperMotionError, 1, 1, 1, 1);

        dcProperMotionError = new tlinsWCoordinateDeclination(groupBox_2);
        dcProperMotionError->setObjectName(QString::fromUtf8("dcProperMotionError"));

        gridLayout_5->addWidget(dcProperMotionError, 1, 3, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_5->addWidget(label_6, 0, 2, 1, 1);


        verticalLayout->addWidget(groupBox_2);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(tlinsAstroObjectCoordinate);

        QMetaObject::connectSlotsByName(tlinsAstroObjectCoordinate);
    } // setupUi

    void retranslateUi(QWidget *tlinsAstroObjectCoordinate)
    {
        tlinsAstroObjectCoordinate->setWindowTitle(QApplication::translate("tlinsAstroObjectCoordinate", "Form", nullptr));
        groupBox_4->setTitle(QApplication::translate("tlinsAstroObjectCoordinate", "Object Coordinates", nullptr));
        label->setText(QApplication::translate("tlinsAstroObjectCoordinate", "RA ", nullptr));
        label_2->setText(QApplication::translate("tlinsAstroObjectCoordinate", "DC ", nullptr));
        groupBox_3->setTitle(QApplication::translate("tlinsAstroObjectCoordinate", "Object coordinates error", nullptr));
        label_11->setText(QApplication::translate("tlinsAstroObjectCoordinate", "Min error (DC) ", nullptr));
        label_5->setText(QApplication::translate("tlinsAstroObjectCoordinate", "Min error (RA) ", nullptr));
        label_12->setText(QApplication::translate("tlinsAstroObjectCoordinate", "Mean error (RA) ", nullptr));
        label_16->setText(QApplication::translate("tlinsAstroObjectCoordinate", "Mean error (DC) ", nullptr));
        groupBox->setTitle(QApplication::translate("tlinsAstroObjectCoordinate", "Central epoch", nullptr));
        label_8->setText(QApplication::translate("tlinsAstroObjectCoordinate", "Central epoch (RA) ", nullptr));
        label_7->setText(QApplication::translate("tlinsAstroObjectCoordinate", "Central epoch (DC) ", nullptr));
        groupBox_2->setTitle(QApplication::translate("tlinsAstroObjectCoordinate", "Proper motion", nullptr));
        label_13->setText(QApplication::translate("tlinsAstroObjectCoordinate", "Proper motion (RA) ", nullptr));
        label_15->setText(QApplication::translate("tlinsAstroObjectCoordinate", "Proper motion Error (RA) ", nullptr));
        label_18->setText(QApplication::translate("tlinsAstroObjectCoordinate", "Proper motion Error (DC) ", nullptr));
        label_6->setText(QApplication::translate("tlinsAstroObjectCoordinate", "Proper motion (DC) ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsAstroObjectCoordinate: public Ui_tlinsAstroObjectCoordinate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSASTROOBJECTCOORDINATE_H
