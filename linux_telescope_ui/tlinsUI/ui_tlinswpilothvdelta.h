/********************************************************************************
** Form generated from reading UI file 'tlinswpilothvdelta.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWPILOTHVDELTA_H
#define UI_TLINSWPILOTHVDELTA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "tlinswcoordinatedegris.h"
#include "tlinswdecimalvalue.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsWPilotHVDelta
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioTypeSteps;
    QRadioButton *radioTypeDegris;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioAxisHorisontal;
    QRadioButton *radioAxisVertical;
    QGroupBox *groupDegris;
    QHBoxLayout *horizontalLayout_3;
    tlinsWCoordinateDegris *deltaDegris;
    QLabel *label;
    QGroupBox *groupSteps;
    QHBoxLayout *horizontalLayout_4;
    tlinsWDecimalValue *deltaSteps;
    QLabel *label_2;

    void setupUi(QWidget *tlinsWPilotHVDelta)
    {
        if (tlinsWPilotHVDelta->objectName().isEmpty())
            tlinsWPilotHVDelta->setObjectName(QString::fromUtf8("tlinsWPilotHVDelta"));
        tlinsWPilotHVDelta->resize(455, 287);
        verticalLayout = new QVBoxLayout(tlinsWPilotHVDelta);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(tlinsWPilotHVDelta);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QFont font;
        font.setItalic(true);
        groupBox->setFont(font);
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        radioTypeSteps = new QRadioButton(groupBox);
        radioTypeSteps->setObjectName(QString::fromUtf8("radioTypeSteps"));
        QFont font1;
        font1.setItalic(false);
        radioTypeSteps->setFont(font1);

        horizontalLayout->addWidget(radioTypeSteps);

        radioTypeDegris = new QRadioButton(groupBox);
        radioTypeDegris->setObjectName(QString::fromUtf8("radioTypeDegris"));
        radioTypeDegris->setFont(font1);

        horizontalLayout->addWidget(radioTypeDegris);


        verticalLayout->addWidget(groupBox);

        groupBox_4 = new QGroupBox(tlinsWPilotHVDelta);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setFont(font);
        horizontalLayout_2 = new QHBoxLayout(groupBox_4);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        radioAxisHorisontal = new QRadioButton(groupBox_4);
        radioAxisHorisontal->setObjectName(QString::fromUtf8("radioAxisHorisontal"));
        radioAxisHorisontal->setFont(font1);

        horizontalLayout_2->addWidget(radioAxisHorisontal);

        radioAxisVertical = new QRadioButton(groupBox_4);
        radioAxisVertical->setObjectName(QString::fromUtf8("radioAxisVertical"));
        radioAxisVertical->setFont(font1);

        horizontalLayout_2->addWidget(radioAxisVertical);


        verticalLayout->addWidget(groupBox_4);

        groupDegris = new QGroupBox(tlinsWPilotHVDelta);
        groupDegris->setObjectName(QString::fromUtf8("groupDegris"));
        groupDegris->setFont(font);
        horizontalLayout_3 = new QHBoxLayout(groupDegris);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        deltaDegris = new tlinsWCoordinateDegris(groupDegris);
        deltaDegris->setObjectName(QString::fromUtf8("deltaDegris"));
        deltaDegris->setFont(font1);

        horizontalLayout_3->addWidget(deltaDegris);

        label = new QLabel(groupDegris);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label);


        verticalLayout->addWidget(groupDegris);

        groupSteps = new QGroupBox(tlinsWPilotHVDelta);
        groupSteps->setObjectName(QString::fromUtf8("groupSteps"));
        groupSteps->setFont(font);
        horizontalLayout_4 = new QHBoxLayout(groupSteps);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        deltaSteps = new tlinsWDecimalValue(groupSteps);
        deltaSteps->setObjectName(QString::fromUtf8("deltaSteps"));
        deltaSteps->setFont(font1);

        horizontalLayout_4->addWidget(deltaSteps);

        label_2 = new QLabel(groupSteps);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_2);


        verticalLayout->addWidget(groupSteps);


        retranslateUi(tlinsWPilotHVDelta);
        QObject::connect(radioTypeDegris, SIGNAL(clicked()), tlinsWPilotHVDelta, SLOT(degrisSelected()));
        QObject::connect(radioTypeSteps, SIGNAL(clicked()), tlinsWPilotHVDelta, SLOT(stepsSelected()));
        QObject::connect(radioAxisHorisontal, SIGNAL(clicked()), tlinsWPilotHVDelta, SLOT(hSelected()));
        QObject::connect(radioAxisVertical, SIGNAL(clicked()), tlinsWPilotHVDelta, SLOT(vSelected()));

        QMetaObject::connectSlotsByName(tlinsWPilotHVDelta);
    } // setupUi

    void retranslateUi(QWidget *tlinsWPilotHVDelta)
    {
        tlinsWPilotHVDelta->setWindowTitle(QApplication::translate("tlinsWPilotHVDelta", "Form", nullptr));
        groupBox->setTitle(QApplication::translate("tlinsWPilotHVDelta", "Type", nullptr));
        radioTypeSteps->setText(QApplication::translate("tlinsWPilotHVDelta", " Steps", nullptr));
        radioTypeDegris->setText(QApplication::translate("tlinsWPilotHVDelta", " Degris", nullptr));
        groupBox_4->setTitle(QApplication::translate("tlinsWPilotHVDelta", "Axis", nullptr));
        radioAxisHorisontal->setText(QApplication::translate("tlinsWPilotHVDelta", " Horisontal/RA", nullptr));
        radioAxisVertical->setText(QApplication::translate("tlinsWPilotHVDelta", " Vertical/DC", nullptr));
        groupDegris->setTitle(QApplication::translate("tlinsWPilotHVDelta", "Delta degris", nullptr));
        label->setText(QApplication::translate("tlinsWPilotHVDelta", "[degris]", nullptr));
        groupSteps->setTitle(QApplication::translate("tlinsWPilotHVDelta", "Delta steps", nullptr));
        label_2->setText(QApplication::translate("tlinsWPilotHVDelta", "[steps]", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWPilotHVDelta: public Ui_tlinsWPilotHVDelta {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWPILOTHVDELTA_H
