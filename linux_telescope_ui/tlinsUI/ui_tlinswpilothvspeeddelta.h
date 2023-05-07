/********************************************************************************
** Form generated from reading UI file 'tlinswpilothvspeeddelta.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWPILOTHVSPEEDDELTA_H
#define UI_TLINSWPILOTHVSPEEDDELTA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "tlinswcoordinatedegris.h"
#include "tlinswdecimalvalue.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsWPilotHVSpeedDelta
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioSteps;
    QRadioButton *radioDegris;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioHorisontal;
    QRadioButton *radioVertical;
    QGroupBox *groupSteps;
    QHBoxLayout *horizontalLayout_3;
    tlinsWDecimalValue *stepsValue;
    QLabel *label;
    QGroupBox *groupDegris;
    QHBoxLayout *horizontalLayout_4;
    tlinsWCoordinateDegris *degrisValue;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *tlinsWPilotHVSpeedDelta)
    {
        if (tlinsWPilotHVSpeedDelta->objectName().isEmpty())
            tlinsWPilotHVSpeedDelta->setObjectName(QString::fromUtf8("tlinsWPilotHVSpeedDelta"));
        tlinsWPilotHVSpeedDelta->resize(542, 287);
        verticalLayout = new QVBoxLayout(tlinsWPilotHVSpeedDelta);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(tlinsWPilotHVSpeedDelta);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        radioSteps = new QRadioButton(groupBox);
        radioSteps->setObjectName(QString::fromUtf8("radioSteps"));

        horizontalLayout_2->addWidget(radioSteps);

        radioDegris = new QRadioButton(groupBox);
        radioDegris->setObjectName(QString::fromUtf8("radioDegris"));

        horizontalLayout_2->addWidget(radioDegris);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(tlinsWPilotHVSpeedDelta);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        radioHorisontal = new QRadioButton(groupBox_2);
        radioHorisontal->setObjectName(QString::fromUtf8("radioHorisontal"));

        horizontalLayout->addWidget(radioHorisontal);

        radioVertical = new QRadioButton(groupBox_2);
        radioVertical->setObjectName(QString::fromUtf8("radioVertical"));

        horizontalLayout->addWidget(radioVertical);


        verticalLayout->addWidget(groupBox_2);

        groupSteps = new QGroupBox(tlinsWPilotHVSpeedDelta);
        groupSteps->setObjectName(QString::fromUtf8("groupSteps"));
        horizontalLayout_3 = new QHBoxLayout(groupSteps);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        stepsValue = new tlinsWDecimalValue(groupSteps);
        stepsValue->setObjectName(QString::fromUtf8("stepsValue"));

        horizontalLayout_3->addWidget(stepsValue);

        label = new QLabel(groupSteps);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setItalic(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label);


        verticalLayout->addWidget(groupSteps);

        groupDegris = new QGroupBox(tlinsWPilotHVSpeedDelta);
        groupDegris->setObjectName(QString::fromUtf8("groupDegris"));
        horizontalLayout_4 = new QHBoxLayout(groupDegris);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        degrisValue = new tlinsWCoordinateDegris(groupDegris);
        degrisValue->setObjectName(QString::fromUtf8("degrisValue"));

        horizontalLayout_4->addWidget(degrisValue);

        label_2 = new QLabel(groupDegris);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_2);


        verticalLayout->addWidget(groupDegris);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(tlinsWPilotHVSpeedDelta);
        QObject::connect(radioDegris, SIGNAL(clicked()), tlinsWPilotHVSpeedDelta, SLOT(degrisSelected()));
        QObject::connect(radioSteps, SIGNAL(clicked()), tlinsWPilotHVSpeedDelta, SLOT(stepsSelected()));

        QMetaObject::connectSlotsByName(tlinsWPilotHVSpeedDelta);
    } // setupUi

    void retranslateUi(QWidget *tlinsWPilotHVSpeedDelta)
    {
        tlinsWPilotHVSpeedDelta->setWindowTitle(QApplication::translate("tlinsWPilotHVSpeedDelta", "Form", nullptr));
        groupBox->setTitle(QApplication::translate("tlinsWPilotHVSpeedDelta", "Type", nullptr));
        radioSteps->setText(QApplication::translate("tlinsWPilotHVSpeedDelta", " Steps", nullptr));
        radioDegris->setText(QApplication::translate("tlinsWPilotHVSpeedDelta", " Degris", nullptr));
        groupBox_2->setTitle(QApplication::translate("tlinsWPilotHVSpeedDelta", "Axis", nullptr));
        radioHorisontal->setText(QApplication::translate("tlinsWPilotHVSpeedDelta", " Horisontal", nullptr));
        radioVertical->setText(QApplication::translate("tlinsWPilotHVSpeedDelta", " Vertical", nullptr));
        groupSteps->setTitle(QApplication::translate("tlinsWPilotHVSpeedDelta", "Steps value", nullptr));
        label->setText(QApplication::translate("tlinsWPilotHVSpeedDelta", "[steps/s]", nullptr));
        groupDegris->setTitle(QApplication::translate("tlinsWPilotHVSpeedDelta", "Degris value", nullptr));
        label_2->setText(QApplication::translate("tlinsWPilotHVSpeedDelta", "[degris/s]", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWPilotHVSpeedDelta: public Ui_tlinsWPilotHVSpeedDelta {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWPILOTHVSPEEDDELTA_H
