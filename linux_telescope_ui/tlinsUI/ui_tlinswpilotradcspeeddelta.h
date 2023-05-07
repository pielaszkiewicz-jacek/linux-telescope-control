/********************************************************************************
** Form generated from reading UI file 'tlinswpilotradcspeeddelta.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWPILOTRADCSPEEDDELTA_H
#define UI_TLINSWPILOTRADCSPEEDDELTA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "tlinswcoordinatedeclination.h"
#include "tlinswcoordinatehourangle.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsWPilotRaDcSpeedDelta
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioHourAngle;
    QRadioButton *radioDeclination;
    QGroupBox *groupHourAngle;
    QGridLayout *gridLayout_2;
    tlinsWCoordinateHourAngle *valueHourAngle;
    QLabel *label;
    QCheckBox *negative;
    QGroupBox *groupDeclination;
    QGridLayout *gridLayout;
    tlinsWCoordinateDeclination *valueDeclination;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *tlinsWPilotRaDcSpeedDelta)
    {
        if (tlinsWPilotRaDcSpeedDelta->objectName().isEmpty())
            tlinsWPilotRaDcSpeedDelta->setObjectName(QString::fromUtf8("tlinsWPilotRaDcSpeedDelta"));
        tlinsWPilotRaDcSpeedDelta->resize(469, 244);
        verticalLayout = new QVBoxLayout(tlinsWPilotRaDcSpeedDelta);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(tlinsWPilotRaDcSpeedDelta);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QFont font;
        font.setItalic(true);
        groupBox->setFont(font);
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        radioHourAngle = new QRadioButton(groupBox);
        radioHourAngle->setObjectName(QString::fromUtf8("radioHourAngle"));
        QFont font1;
        font1.setItalic(false);
        radioHourAngle->setFont(font1);

        horizontalLayout->addWidget(radioHourAngle);

        radioDeclination = new QRadioButton(groupBox);
        radioDeclination->setObjectName(QString::fromUtf8("radioDeclination"));

        horizontalLayout->addWidget(radioDeclination);


        verticalLayout->addWidget(groupBox);

        groupHourAngle = new QGroupBox(tlinsWPilotRaDcSpeedDelta);
        groupHourAngle->setObjectName(QString::fromUtf8("groupHourAngle"));
        groupHourAngle->setFont(font);
        gridLayout_2 = new QGridLayout(groupHourAngle);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        valueHourAngle = new tlinsWCoordinateHourAngle(groupHourAngle);
        valueHourAngle->setObjectName(QString::fromUtf8("valueHourAngle"));
        valueHourAngle->setFont(font1);

        gridLayout_2->addWidget(valueHourAngle, 0, 0, 1, 1);

        label = new QLabel(groupHourAngle);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font1);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label, 0, 1, 1, 1);

        negative = new QCheckBox(groupHourAngle);
        negative->setObjectName(QString::fromUtf8("negative"));
        negative->setFont(font1);

        gridLayout_2->addWidget(negative, 1, 0, 1, 1);


        verticalLayout->addWidget(groupHourAngle);

        groupDeclination = new QGroupBox(tlinsWPilotRaDcSpeedDelta);
        groupDeclination->setObjectName(QString::fromUtf8("groupDeclination"));
        groupDeclination->setFont(font);
        gridLayout = new QGridLayout(groupDeclination);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        valueDeclination = new tlinsWCoordinateDeclination(groupDeclination);
        valueDeclination->setObjectName(QString::fromUtf8("valueDeclination"));
        valueDeclination->setFont(font1);

        gridLayout->addWidget(valueDeclination, 0, 0, 1, 1);

        label_2 = new QLabel(groupDeclination);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 0, 1, 1, 1);


        verticalLayout->addWidget(groupDeclination);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(tlinsWPilotRaDcSpeedDelta);
        QObject::connect(radioHourAngle, SIGNAL(clicked()), tlinsWPilotRaDcSpeedDelta, SLOT(raSelected()));
        QObject::connect(radioDeclination, SIGNAL(clicked()), tlinsWPilotRaDcSpeedDelta, SLOT(dcSelected()));

        QMetaObject::connectSlotsByName(tlinsWPilotRaDcSpeedDelta);
    } // setupUi

    void retranslateUi(QWidget *tlinsWPilotRaDcSpeedDelta)
    {
        tlinsWPilotRaDcSpeedDelta->setWindowTitle(QApplication::translate("tlinsWPilotRaDcSpeedDelta", "Form", nullptr));
        groupBox->setTitle(QApplication::translate("tlinsWPilotRaDcSpeedDelta", "Axis", nullptr));
        radioHourAngle->setText(QApplication::translate("tlinsWPilotRaDcSpeedDelta", " Hour angle", nullptr));
        radioDeclination->setText(QApplication::translate("tlinsWPilotRaDcSpeedDelta", " Declination", nullptr));
        groupHourAngle->setTitle(QApplication::translate("tlinsWPilotRaDcSpeedDelta", "Hour angle", nullptr));
        label->setText(QApplication::translate("tlinsWPilotRaDcSpeedDelta", "[hours/s]", nullptr));
        negative->setText(QApplication::translate("tlinsWPilotRaDcSpeedDelta", "Negative", nullptr));
        groupDeclination->setTitle(QApplication::translate("tlinsWPilotRaDcSpeedDelta", "Declination", nullptr));
        label_2->setText(QApplication::translate("tlinsWPilotRaDcSpeedDelta", "[degris/s]", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWPilotRaDcSpeedDelta: public Ui_tlinsWPilotRaDcSpeedDelta {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWPILOTRADCSPEEDDELTA_H
