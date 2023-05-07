/********************************************************************************
** Form generated from reading UI file 'tlinswguidercorrections.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWGUIDERCORRECTIONS_H
#define UI_TLINSWGUIDERCORRECTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <tlinswdecimalvalue.h>

QT_BEGIN_NAMESPACE

class Ui_tlinsWGuiderCorrections
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_5;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout;
    tlinsWDecimalValue *raCorrection;
    QLabel *label_5;
    QSlider *horizontalSlider;
    QLabel *label_6;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_2;
    tlinsWDecimalValue *decCorrection;
    QLabel *label;
    QSlider *horizontalSlider_2;
    QLabel *label_7;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    tlinsWDecimalValue *raRatio;
    QLabel *label_3;
    tlinsWDecimalValue *decRatio;
    QLabel *label_2;
    QCheckBox *checkBox;

    void setupUi(QWidget *tlinsWGuiderCorrections)
    {
        if (tlinsWGuiderCorrections->objectName().isEmpty())
            tlinsWGuiderCorrections->setObjectName(QString::fromUtf8("tlinsWGuiderCorrections"));
        tlinsWGuiderCorrections->resize(1096, 628);
        gridLayout = new QGridLayout(tlinsWGuiderCorrections);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_5 = new QGroupBox(tlinsWGuiderCorrections);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_5);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton_2 = new QPushButton(groupBox_5);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(0, 60));

        horizontalLayout_3->addWidget(pushButton_2);

        pushButton = new QPushButton(groupBox_5);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(0, 60));

        horizontalLayout_3->addWidget(pushButton);

        pushButton_3 = new QPushButton(groupBox_5);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(0, 60));

        horizontalLayout_3->addWidget(pushButton_3);


        gridLayout->addWidget(groupBox_5, 3, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 0, 1, 1);

        groupBox = new QGroupBox(tlinsWGuiderCorrections);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        horizontalLayout = new QHBoxLayout(groupBox_3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        raCorrection = new tlinsWDecimalValue(groupBox_3);
        raCorrection->setObjectName(QString::fromUtf8("raCorrection"));

        horizontalLayout->addWidget(raCorrection);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout->addWidget(label_5);

        horizontalSlider = new QSlider(groupBox_3);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setMaximum(10000);
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSlider);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout->addWidget(label_6);


        gridLayout_2->addWidget(groupBox_3, 0, 0, 1, 1);

        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_4);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        decCorrection = new tlinsWDecimalValue(groupBox_4);
        decCorrection->setObjectName(QString::fromUtf8("decCorrection"));

        horizontalLayout_2->addWidget(decCorrection);

        label = new QLabel(groupBox_4);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        horizontalSlider_2 = new QSlider(groupBox_4);
        horizontalSlider_2->setObjectName(QString::fromUtf8("horizontalSlider_2"));
        horizontalSlider_2->setMaximum(10000);
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider_2);

        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_2->addWidget(label_7);


        gridLayout_2->addWidget(groupBox_4, 1, 0, 1, 1);


        gridLayout->addWidget(groupBox, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(tlinsWGuiderCorrections);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        raRatio = new tlinsWDecimalValue(groupBox_2);
        raRatio->setObjectName(QString::fromUtf8("raRatio"));

        gridLayout_3->addWidget(raRatio, 0, 1, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_3->addWidget(label_3, 1, 0, 1, 1);

        decRatio = new tlinsWDecimalValue(groupBox_2);
        decRatio->setObjectName(QString::fromUtf8("decRatio"));

        gridLayout_3->addWidget(decRatio, 1, 1, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_2, 2, 0, 1, 1);

        checkBox = new QCheckBox(tlinsWGuiderCorrections);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayout->addWidget(checkBox, 0, 0, 1, 1);


        retranslateUi(tlinsWGuiderCorrections);

        QMetaObject::connectSlotsByName(tlinsWGuiderCorrections);
    } // setupUi

    void retranslateUi(QWidget *tlinsWGuiderCorrections)
    {
        tlinsWGuiderCorrections->setWindowTitle(QApplication::translate("tlinsWGuiderCorrections", "Form", nullptr));
        groupBox_5->setTitle(QApplication::translate("tlinsWGuiderCorrections", "GroupBox", nullptr));
        pushButton_2->setText(QApplication::translate("tlinsWGuiderCorrections", "Store", nullptr));
        pushButton->setText(QApplication::translate("tlinsWGuiderCorrections", "Load", nullptr));
        pushButton_3->setText(QApplication::translate("tlinsWGuiderCorrections", "Send", nullptr));
        groupBox->setTitle(QApplication::translate("tlinsWGuiderCorrections", "Manual correction", nullptr));
        groupBox_3->setTitle(QApplication::translate("tlinsWGuiderCorrections", "RA", nullptr));
        label_5->setText(QApplication::translate("tlinsWGuiderCorrections", "0.0", nullptr));
        label_6->setText(QApplication::translate("tlinsWGuiderCorrections", "1.0", nullptr));
        groupBox_4->setTitle(QApplication::translate("tlinsWGuiderCorrections", "DEC", nullptr));
        label->setText(QApplication::translate("tlinsWGuiderCorrections", "0.0", nullptr));
        label_7->setText(QApplication::translate("tlinsWGuiderCorrections", "1.0", nullptr));
        groupBox_2->setTitle(QApplication::translate("tlinsWGuiderCorrections", "Guider", nullptr));
        label_3->setText(QApplication::translate("tlinsWGuiderCorrections", "DEC ratio", nullptr));
        label_2->setText(QApplication::translate("tlinsWGuiderCorrections", "RA ratio", nullptr));
        checkBox->setText(QApplication::translate("tlinsWGuiderCorrections", "Manula correction", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWGuiderCorrections: public Ui_tlinsWGuiderCorrections {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWGUIDERCORRECTIONS_H
