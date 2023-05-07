/********************************************************************************
** Form generated from reading UI file 'tlinswpilothorisontalverticalkeys.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWPILOTHORISONTALVERTICALKEYS_H
#define UI_TLINSWPILOTHORISONTALVERTICALKEYS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsWPilotHorisontalVerticalKeys
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QRadioButton *rbHorisintal;
    QRadioButton *rbVertical;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QRadioButton *rbLeftUp;
    QRadioButton *rbRightDown;

    void setupUi(QWidget *tlinsWPilotHorisontalVerticalKeys)
    {
        if (tlinsWPilotHorisontalVerticalKeys->objectName().isEmpty())
            tlinsWPilotHorisontalVerticalKeys->setObjectName(QString::fromUtf8("tlinsWPilotHorisontalVerticalKeys"));
        tlinsWPilotHorisontalVerticalKeys->resize(496, 162);
        verticalLayout = new QVBoxLayout(tlinsWPilotHorisontalVerticalKeys);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(tlinsWPilotHorisontalVerticalKeys);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        rbHorisintal = new QRadioButton(groupBox);
        rbHorisintal->setObjectName(QString::fromUtf8("rbHorisintal"));

        horizontalLayout->addWidget(rbHorisintal);

        rbVertical = new QRadioButton(groupBox);
        rbVertical->setObjectName(QString::fromUtf8("rbVertical"));

        horizontalLayout->addWidget(rbVertical);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(tlinsWPilotHorisontalVerticalKeys);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        rbLeftUp = new QRadioButton(groupBox_2);
        rbLeftUp->setObjectName(QString::fromUtf8("rbLeftUp"));

        gridLayout->addWidget(rbLeftUp, 0, 0, 1, 1);

        rbRightDown = new QRadioButton(groupBox_2);
        rbRightDown->setObjectName(QString::fromUtf8("rbRightDown"));

        gridLayout->addWidget(rbRightDown, 0, 1, 1, 1);


        verticalLayout->addWidget(groupBox_2);


        retranslateUi(tlinsWPilotHorisontalVerticalKeys);

        QMetaObject::connectSlotsByName(tlinsWPilotHorisontalVerticalKeys);
    } // setupUi

    void retranslateUi(QWidget *tlinsWPilotHorisontalVerticalKeys)
    {
        tlinsWPilotHorisontalVerticalKeys->setWindowTitle(QApplication::translate("tlinsWPilotHorisontalVerticalKeys", "Form", nullptr));
        groupBox->setTitle(QApplication::translate("tlinsWPilotHorisontalVerticalKeys", "Horisontal/RA-Vertical/Dec", nullptr));
        rbHorisintal->setText(QApplication::translate("tlinsWPilotHorisontalVerticalKeys", "RA/Horisontal", nullptr));
        rbVertical->setText(QApplication::translate("tlinsWPilotHorisontalVerticalKeys", "Dec/Veritcal", nullptr));
        groupBox_2->setTitle(QApplication::translate("tlinsWPilotHorisontalVerticalKeys", "Direction", nullptr));
        rbLeftUp->setText(QApplication::translate("tlinsWPilotHorisontalVerticalKeys", "Left/Up", nullptr));
        rbRightDown->setText(QApplication::translate("tlinsWPilotHorisontalVerticalKeys", "Right/Down", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWPilotHorisontalVerticalKeys: public Ui_tlinsWPilotHorisontalVerticalKeys {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWPILOTHORISONTALVERTICALKEYS_H
