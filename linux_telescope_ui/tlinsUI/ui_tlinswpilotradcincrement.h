/********************************************************************************
** Form generated from reading UI file 'tlinswpilotradcincrement.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWPILOTRADCINCREMENT_H
#define UI_TLINSWPILOTRADCINCREMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsWPilotRaDcIncrement
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioRA;
    QRadioButton *radioDC;
    QGroupBox *groupRA;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioRaLeft;
    QRadioButton *radioRaRight;
    QGroupBox *groupDC;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *radioDcUp;
    QRadioButton *radioDcDown;

    void setupUi(QWidget *tlinsWPilotRaDcIncrement)
    {
        if (tlinsWPilotRaDcIncrement->objectName().isEmpty())
            tlinsWPilotRaDcIncrement->setObjectName(QString::fromUtf8("tlinsWPilotRaDcIncrement"));
        tlinsWPilotRaDcIncrement->resize(469, 227);
        verticalLayout = new QVBoxLayout(tlinsWPilotRaDcIncrement);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(tlinsWPilotRaDcIncrement);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QFont font;
        font.setItalic(true);
        groupBox->setFont(font);
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        radioRA = new QRadioButton(groupBox);
        radioRA->setObjectName(QString::fromUtf8("radioRA"));
        QFont font1;
        font1.setItalic(false);
        radioRA->setFont(font1);

        horizontalLayout->addWidget(radioRA);

        radioDC = new QRadioButton(groupBox);
        radioDC->setObjectName(QString::fromUtf8("radioDC"));
        radioDC->setFont(font1);

        horizontalLayout->addWidget(radioDC);


        verticalLayout->addWidget(groupBox);

        groupRA = new QGroupBox(tlinsWPilotRaDcIncrement);
        groupRA->setObjectName(QString::fromUtf8("groupRA"));
        groupRA->setFont(font);
        horizontalLayout_2 = new QHBoxLayout(groupRA);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        radioRaLeft = new QRadioButton(groupRA);
        radioRaLeft->setObjectName(QString::fromUtf8("radioRaLeft"));
        radioRaLeft->setFont(font1);

        horizontalLayout_2->addWidget(radioRaLeft);

        radioRaRight = new QRadioButton(groupRA);
        radioRaRight->setObjectName(QString::fromUtf8("radioRaRight"));
        radioRaRight->setFont(font1);

        horizontalLayout_2->addWidget(radioRaRight);


        verticalLayout->addWidget(groupRA);

        groupDC = new QGroupBox(tlinsWPilotRaDcIncrement);
        groupDC->setObjectName(QString::fromUtf8("groupDC"));
        groupDC->setFont(font);
        horizontalLayout_3 = new QHBoxLayout(groupDC);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        radioDcUp = new QRadioButton(groupDC);
        radioDcUp->setObjectName(QString::fromUtf8("radioDcUp"));
        radioDcUp->setFont(font1);

        horizontalLayout_3->addWidget(radioDcUp);

        radioDcDown = new QRadioButton(groupDC);
        radioDcDown->setObjectName(QString::fromUtf8("radioDcDown"));
        radioDcDown->setFont(font1);

        horizontalLayout_3->addWidget(radioDcDown);


        verticalLayout->addWidget(groupDC);


        retranslateUi(tlinsWPilotRaDcIncrement);
        QObject::connect(radioRA, SIGNAL(clicked()), tlinsWPilotRaDcIncrement, SLOT(raAxisSelected()));
        QObject::connect(radioDC, SIGNAL(clicked()), tlinsWPilotRaDcIncrement, SLOT(dcAxisSelected()));

        QMetaObject::connectSlotsByName(tlinsWPilotRaDcIncrement);
    } // setupUi

    void retranslateUi(QWidget *tlinsWPilotRaDcIncrement)
    {
        tlinsWPilotRaDcIncrement->setWindowTitle(QApplication::translate("tlinsWPilotRaDcIncrement", "Form", nullptr));
        groupBox->setTitle(QApplication::translate("tlinsWPilotRaDcIncrement", "Axis:", nullptr));
        radioRA->setText(QApplication::translate("tlinsWPilotRaDcIncrement", " Hour angle", nullptr));
        radioDC->setText(QApplication::translate("tlinsWPilotRaDcIncrement", " Declination", nullptr));
        groupRA->setTitle(QApplication::translate("tlinsWPilotRaDcIncrement", "Direction Hour Angle:", nullptr));
        radioRaLeft->setText(QApplication::translate("tlinsWPilotRaDcIncrement", " Left", nullptr));
        radioRaRight->setText(QApplication::translate("tlinsWPilotRaDcIncrement", " Right", nullptr));
        groupDC->setTitle(QApplication::translate("tlinsWPilotRaDcIncrement", "Direction Declination:", nullptr));
        radioDcUp->setText(QApplication::translate("tlinsWPilotRaDcIncrement", " Up", nullptr));
        radioDcDown->setText(QApplication::translate("tlinsWPilotRaDcIncrement", " Down", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWPilotRaDcIncrement: public Ui_tlinsWPilotRaDcIncrement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWPILOTRADCINCREMENT_H
