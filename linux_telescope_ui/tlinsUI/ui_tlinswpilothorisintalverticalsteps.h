/********************************************************************************
** Form generated from reading UI file 'tlinswpilothorisintalverticalsteps.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWPILOTHORISINTALVERTICALSTEPS_H
#define UI_TLINSWPILOTHORISINTALVERTICALSTEPS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsWPilotHorisintalVerticalSteps
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupAxis;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioHorisontal;
    QRadioButton *radioVertical;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioDirLeft;
    QRadioButton *radioDirRight;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *radioModeSteps;
    QRadioButton *radioModeDegris;
    QRadioButton *radioModeAstro;

    void setupUi(QWidget *tlinsWPilotHorisintalVerticalSteps)
    {
        if (tlinsWPilotHorisintalVerticalSteps->objectName().isEmpty())
            tlinsWPilotHorisintalVerticalSteps->setObjectName(QString::fromUtf8("tlinsWPilotHorisintalVerticalSteps"));
        tlinsWPilotHorisintalVerticalSteps->resize(344, 227);
        verticalLayout = new QVBoxLayout(tlinsWPilotHorisintalVerticalSteps);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupAxis = new QGroupBox(tlinsWPilotHorisintalVerticalSteps);
        groupAxis->setObjectName(QString::fromUtf8("groupAxis"));
        QFont font;
        font.setItalic(true);
        groupAxis->setFont(font);
        groupAxis->setFlat(false);
        horizontalLayout = new QHBoxLayout(groupAxis);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        radioHorisontal = new QRadioButton(groupAxis);
        radioHorisontal->setObjectName(QString::fromUtf8("radioHorisontal"));
        QFont font1;
        font1.setItalic(false);
        font1.setUnderline(false);
        radioHorisontal->setFont(font1);

        horizontalLayout->addWidget(radioHorisontal);

        radioVertical = new QRadioButton(groupAxis);
        radioVertical->setObjectName(QString::fromUtf8("radioVertical"));
        radioVertical->setFont(font1);

        horizontalLayout->addWidget(radioVertical);


        verticalLayout->addWidget(groupAxis);

        groupBox = new QGroupBox(tlinsWPilotHorisintalVerticalSteps);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setFont(font);
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        radioDirLeft = new QRadioButton(groupBox);
        radioDirLeft->setObjectName(QString::fromUtf8("radioDirLeft"));
        QFont font2;
        font2.setItalic(false);
        radioDirLeft->setFont(font2);

        horizontalLayout_2->addWidget(radioDirLeft);

        radioDirRight = new QRadioButton(groupBox);
        radioDirRight->setObjectName(QString::fromUtf8("radioDirRight"));
        radioDirRight->setFont(font2);

        horizontalLayout_2->addWidget(radioDirRight);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(tlinsWPilotHorisintalVerticalSteps);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setFont(font);
        horizontalLayout_3 = new QHBoxLayout(groupBox_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        radioModeSteps = new QRadioButton(groupBox_2);
        radioModeSteps->setObjectName(QString::fromUtf8("radioModeSteps"));
        radioModeSteps->setFont(font2);

        horizontalLayout_3->addWidget(radioModeSteps);

        radioModeDegris = new QRadioButton(groupBox_2);
        radioModeDegris->setObjectName(QString::fromUtf8("radioModeDegris"));
        radioModeDegris->setFont(font2);

        horizontalLayout_3->addWidget(radioModeDegris);

        radioModeAstro = new QRadioButton(groupBox_2);
        radioModeAstro->setObjectName(QString::fromUtf8("radioModeAstro"));
        radioModeAstro->setFont(font2);

        horizontalLayout_3->addWidget(radioModeAstro);


        verticalLayout->addWidget(groupBox_2);


        retranslateUi(tlinsWPilotHorisintalVerticalSteps);

        QMetaObject::connectSlotsByName(tlinsWPilotHorisintalVerticalSteps);
    } // setupUi

    void retranslateUi(QWidget *tlinsWPilotHorisintalVerticalSteps)
    {
        tlinsWPilotHorisintalVerticalSteps->setWindowTitle(QApplication::translate("tlinsWPilotHorisintalVerticalSteps", "Form", nullptr));
        groupAxis->setTitle(QApplication::translate("tlinsWPilotHorisintalVerticalSteps", "Axis", nullptr));
        radioHorisontal->setText(QApplication::translate("tlinsWPilotHorisintalVerticalSteps", " Horisontal/RA", nullptr));
        radioVertical->setText(QApplication::translate("tlinsWPilotHorisintalVerticalSteps", " Vertical/DC", nullptr));
        groupBox->setTitle(QApplication::translate("tlinsWPilotHorisintalVerticalSteps", "Direction", nullptr));
        radioDirLeft->setText(QApplication::translate("tlinsWPilotHorisintalVerticalSteps", "Left/Down", nullptr));
        radioDirRight->setText(QApplication::translate("tlinsWPilotHorisintalVerticalSteps", "Right/Up", nullptr));
        groupBox_2->setTitle(QApplication::translate("tlinsWPilotHorisintalVerticalSteps", "Mode", nullptr));
        radioModeSteps->setText(QApplication::translate("tlinsWPilotHorisintalVerticalSteps", "Steps", nullptr));
        radioModeDegris->setText(QApplication::translate("tlinsWPilotHorisintalVerticalSteps", "Degris", nullptr));
        radioModeAstro->setText(QApplication::translate("tlinsWPilotHorisintalVerticalSteps", "Astro", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWPilotHorisintalVerticalSteps: public Ui_tlinsWPilotHorisintalVerticalSteps {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWPILOTHORISINTALVERTICALSTEPS_H
