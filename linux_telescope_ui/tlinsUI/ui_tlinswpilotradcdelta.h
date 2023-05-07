/********************************************************************************
** Form generated from reading UI file 'tlinswpilotradcdelta.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWPILOTRADCDELTA_H
#define UI_TLINSWPILOTRADCDELTA_H

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

class Ui_tlinsWPilotRaDcDelta
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *radioRa;
    QRadioButton *radioDc;
    QGroupBox *groupDeclination;
    QHBoxLayout *horizontalLayout;
    tlinsWCoordinateDeclination *declinationValue;
    QLabel *label;
    QGroupBox *groupHourAngle;
    QGridLayout *gridLayout;
    tlinsWCoordinateHourAngle *hourAngleValue;
    QLabel *label_2;
    QCheckBox *negative;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *tlinsWPilotRaDcDelta)
    {
        if (tlinsWPilotRaDcDelta->objectName().isEmpty())
            tlinsWPilotRaDcDelta->setObjectName(QString::fromUtf8("tlinsWPilotRaDcDelta"));
        tlinsWPilotRaDcDelta->resize(459, 221);
        verticalLayout = new QVBoxLayout(tlinsWPilotRaDcDelta);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(tlinsWPilotRaDcDelta);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QFont font;
        font.setItalic(true);
        groupBox->setFont(font);
        horizontalLayout_3 = new QHBoxLayout(groupBox);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        radioRa = new QRadioButton(groupBox);
        radioRa->setObjectName(QString::fromUtf8("radioRa"));
        QFont font1;
        font1.setItalic(false);
        radioRa->setFont(font1);

        horizontalLayout_3->addWidget(radioRa);

        radioDc = new QRadioButton(groupBox);
        radioDc->setObjectName(QString::fromUtf8("radioDc"));
        radioDc->setFont(font1);

        horizontalLayout_3->addWidget(radioDc);


        verticalLayout->addWidget(groupBox);

        groupDeclination = new QGroupBox(tlinsWPilotRaDcDelta);
        groupDeclination->setObjectName(QString::fromUtf8("groupDeclination"));
        groupDeclination->setFont(font);
        horizontalLayout = new QHBoxLayout(groupDeclination);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        declinationValue = new tlinsWCoordinateDeclination(groupDeclination);
        declinationValue->setObjectName(QString::fromUtf8("declinationValue"));

        horizontalLayout->addWidget(declinationValue);

        label = new QLabel(groupDeclination);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);


        verticalLayout->addWidget(groupDeclination);

        groupHourAngle = new QGroupBox(tlinsWPilotRaDcDelta);
        groupHourAngle->setObjectName(QString::fromUtf8("groupHourAngle"));
        groupHourAngle->setFont(font);
        gridLayout = new QGridLayout(groupHourAngle);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        hourAngleValue = new tlinsWCoordinateHourAngle(groupHourAngle);
        hourAngleValue->setObjectName(QString::fromUtf8("hourAngleValue"));

        gridLayout->addWidget(hourAngleValue, 0, 0, 1, 1);

        label_2 = new QLabel(groupHourAngle);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        negative = new QCheckBox(groupHourAngle);
        negative->setObjectName(QString::fromUtf8("negative"));

        gridLayout->addWidget(negative, 1, 0, 1, 1);


        verticalLayout->addWidget(groupHourAngle);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(tlinsWPilotRaDcDelta);
        QObject::connect(radioRa, SIGNAL(clicked()), tlinsWPilotRaDcDelta, SLOT(raSelected()));
        QObject::connect(radioDc, SIGNAL(clicked()), tlinsWPilotRaDcDelta, SLOT(dcSelected()));

        QMetaObject::connectSlotsByName(tlinsWPilotRaDcDelta);
    } // setupUi

    void retranslateUi(QWidget *tlinsWPilotRaDcDelta)
    {
        tlinsWPilotRaDcDelta->setWindowTitle(QApplication::translate("tlinsWPilotRaDcDelta", "Form", nullptr));
        groupBox->setTitle(QApplication::translate("tlinsWPilotRaDcDelta", "Axis", nullptr));
        radioRa->setText(QApplication::translate("tlinsWPilotRaDcDelta", " Hour angle", nullptr));
        radioDc->setText(QApplication::translate("tlinsWPilotRaDcDelta", " Declination", nullptr));
        groupDeclination->setTitle(QApplication::translate("tlinsWPilotRaDcDelta", "Declination", nullptr));
        label->setText(QApplication::translate("tlinsWPilotRaDcDelta", "[degris]", nullptr));
        groupHourAngle->setTitle(QApplication::translate("tlinsWPilotRaDcDelta", "Hour angle", nullptr));
        label_2->setText(QApplication::translate("tlinsWPilotRaDcDelta", "[hour]", nullptr));
        negative->setText(QApplication::translate("tlinsWPilotRaDcDelta", "Negative", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWPilotRaDcDelta: public Ui_tlinsWPilotRaDcDelta {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWPILOTRADCDELTA_H
