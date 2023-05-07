/********************************************************************************
** Form generated from reading UI file 'tlinswpilottrackingstart.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWPILOTTRACKINGSTART_H
#define UI_TLINSWPILOTTRACKINGSTART_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsWPilotTrackingStart
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label;

    void setupUi(QWidget *tlinsWPilotTrackingStart)
    {
        if (tlinsWPilotTrackingStart->objectName().isEmpty())
            tlinsWPilotTrackingStart->setObjectName(QString::fromUtf8("tlinsWPilotTrackingStart"));
        tlinsWPilotTrackingStart->resize(182, 34);
        horizontalLayout = new QHBoxLayout(tlinsWPilotTrackingStart);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(tlinsWPilotTrackingStart);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);


        retranslateUi(tlinsWPilotTrackingStart);

        QMetaObject::connectSlotsByName(tlinsWPilotTrackingStart);
    } // setupUi

    void retranslateUi(QWidget *tlinsWPilotTrackingStart)
    {
        tlinsWPilotTrackingStart->setWindowTitle(QApplication::translate("tlinsWPilotTrackingStart", "Form", nullptr));
        label->setText(QApplication::translate("tlinsWPilotTrackingStart", "No configuration", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWPilotTrackingStart: public Ui_tlinsWPilotTrackingStart {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWPILOTTRACKINGSTART_H
