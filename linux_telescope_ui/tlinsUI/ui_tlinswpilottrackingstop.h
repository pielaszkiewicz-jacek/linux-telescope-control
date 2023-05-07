/********************************************************************************
** Form generated from reading UI file 'tlinswpilottrackingstop.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWPILOTTRACKINGSTOP_H
#define UI_TLINSWPILOTTRACKINGSTOP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsWPilotTrackingStop
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label;

    void setupUi(QWidget *tlinsWPilotTrackingStop)
    {
        if (tlinsWPilotTrackingStop->objectName().isEmpty())
            tlinsWPilotTrackingStop->setObjectName(QString::fromUtf8("tlinsWPilotTrackingStop"));
        tlinsWPilotTrackingStop->resize(238, 34);
        horizontalLayout = new QHBoxLayout(tlinsWPilotTrackingStop);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(tlinsWPilotTrackingStop);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);


        retranslateUi(tlinsWPilotTrackingStop);

        QMetaObject::connectSlotsByName(tlinsWPilotTrackingStop);
    } // setupUi

    void retranslateUi(QWidget *tlinsWPilotTrackingStop)
    {
        tlinsWPilotTrackingStop->setWindowTitle(QApplication::translate("tlinsWPilotTrackingStop", "Form", nullptr));
        label->setText(QApplication::translate("tlinsWPilotTrackingStop", "No configuration", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWPilotTrackingStop: public Ui_tlinsWPilotTrackingStop {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWPILOTTRACKINGSTOP_H
