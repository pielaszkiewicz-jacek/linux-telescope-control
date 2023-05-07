/********************************************************************************
** Form generated from reading UI file 'tlinswdatetime.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWDATETIME_H
#define UI_TLINSWDATETIME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <tlinswdecimalvalue.h>

QT_BEGIN_NAMESPACE

class Ui_tlinsWDateTime
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    tlinsWDecimalValue *hour;
    QLabel *label_5;
    tlinsWDecimalValue *minute;
    QLabel *label_6;
    tlinsWDecimalValue *second;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    tlinsWDecimalValue *year;
    QLabel *label_2;
    tlinsWDecimalValue *month;
    QLabel *label_3;
    tlinsWDecimalValue *day;
    QCheckBox *useLocalTime;

    void setupUi(QWidget *tlinsWDateTime)
    {
        if (tlinsWDateTime->objectName().isEmpty())
            tlinsWDateTime->setObjectName(QString::fromUtf8("tlinsWDateTime"));
        tlinsWDateTime->resize(598, 205);
        gridLayout = new QGridLayout(tlinsWDateTime);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_2 = new QGroupBox(tlinsWDateTime);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);

        hour = new tlinsWDecimalValue(groupBox_2);
        hour->setObjectName(QString::fromUtf8("hour"));

        horizontalLayout->addWidget(hour);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout->addWidget(label_5);

        minute = new tlinsWDecimalValue(groupBox_2);
        minute->setObjectName(QString::fromUtf8("minute"));

        horizontalLayout->addWidget(minute);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout->addWidget(label_6);

        second = new tlinsWDecimalValue(groupBox_2);
        second->setObjectName(QString::fromUtf8("second"));

        horizontalLayout->addWidget(second);


        gridLayout->addWidget(groupBox_2, 2, 0, 1, 1);

        groupBox = new QGroupBox(tlinsWDateTime);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        year = new tlinsWDecimalValue(groupBox);
        year->setObjectName(QString::fromUtf8("year"));

        horizontalLayout_2->addWidget(year);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        month = new tlinsWDecimalValue(groupBox);
        month->setObjectName(QString::fromUtf8("month"));

        horizontalLayout_2->addWidget(month);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        day = new tlinsWDecimalValue(groupBox);
        day->setObjectName(QString::fromUtf8("day"));

        horizontalLayout_2->addWidget(day);


        gridLayout->addWidget(groupBox, 1, 0, 1, 1);

        useLocalTime = new QCheckBox(tlinsWDateTime);
        useLocalTime->setObjectName(QString::fromUtf8("useLocalTime"));

        gridLayout->addWidget(useLocalTime, 0, 0, 1, 1);


        retranslateUi(tlinsWDateTime);

        QMetaObject::connectSlotsByName(tlinsWDateTime);
    } // setupUi

    void retranslateUi(QWidget *tlinsWDateTime)
    {
        tlinsWDateTime->setWindowTitle(QApplication::translate("tlinsWDateTime", "Form", nullptr));
        groupBox_2->setTitle(QApplication::translate("tlinsWDateTime", "Time", nullptr));
        label_4->setText(QApplication::translate("tlinsWDateTime", "Hour:", nullptr));
        label_5->setText(QApplication::translate("tlinsWDateTime", "Minute:", nullptr));
        label_6->setText(QApplication::translate("tlinsWDateTime", "Second", nullptr));
        groupBox->setTitle(QApplication::translate("tlinsWDateTime", "Date", nullptr));
        label->setText(QApplication::translate("tlinsWDateTime", "Year:", nullptr));
        label_2->setText(QApplication::translate("tlinsWDateTime", "Month:", nullptr));
        label_3->setText(QApplication::translate("tlinsWDateTime", "Day:", nullptr));
        useLocalTime->setText(QApplication::translate("tlinsWDateTime", "Use current device time", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWDateTime: public Ui_tlinsWDateTime {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWDATETIME_H
