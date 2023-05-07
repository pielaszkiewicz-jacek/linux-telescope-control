/********************************************************************************
** Form generated from reading UI file 'tlinswtrackingcontrol.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWTRACKINGCONTROL_H
#define UI_TLINSWTRACKINGCONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "tlinswcoordinatedegris.h"
#include "tlinswcoordinatehourangle.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsWTrackingControl
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label;
    tlinsWCoordinateDegris *dec;
    QLabel *label_2;
    tlinsWCoordinateHourAngle *ra;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *tlinsWTrackingControl)
    {
        if (tlinsWTrackingControl->objectName().isEmpty())
            tlinsWTrackingControl->setObjectName(QString::fromUtf8("tlinsWTrackingControl"));
        tlinsWTrackingControl->resize(657, 368);
        verticalLayout = new QVBoxLayout(tlinsWTrackingControl);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(40, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_3 = new QLabel(tlinsWTrackingControl);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 0, 3, 1, 1);

        label_4 = new QLabel(tlinsWTrackingControl);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 1, 3, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(80, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 0, 0, 1, 1);

        label = new QLabel(tlinsWTrackingControl);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label, 0, 1, 1, 1);

        dec = new tlinsWCoordinateDegris(tlinsWTrackingControl);
        dec->setObjectName(QString::fromUtf8("dec"));

        gridLayout_2->addWidget(dec, 1, 2, 1, 1);

        label_2 = new QLabel(tlinsWTrackingControl);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_2, 1, 1, 1, 1);

        ra = new tlinsWCoordinateHourAngle(tlinsWTrackingControl);
        ra->setObjectName(QString::fromUtf8("ra"));

        gridLayout_2->addWidget(ra, 0, 2, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(80, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 1, 4, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(80, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 1, 0, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(80, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 0, 4, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(tlinsWTrackingControl);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        pushButton_2 = new QPushButton(tlinsWTrackingControl);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(tlinsWTrackingControl);
        QObject::connect(pushButton, SIGNAL(clicked()), tlinsWTrackingControl, SLOT(start()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), tlinsWTrackingControl, SLOT(stop()));

        QMetaObject::connectSlotsByName(tlinsWTrackingControl);
    } // setupUi

    void retranslateUi(QWidget *tlinsWTrackingControl)
    {
        tlinsWTrackingControl->setWindowTitle(QApplication::translate("tlinsWTrackingControl", "Form", nullptr));
        label_3->setText(QApplication::translate("tlinsWTrackingControl", "[hour/s]", nullptr));
        label_4->setText(QApplication::translate("tlinsWTrackingControl", "[deg/s]", nullptr));
        label->setText(QApplication::translate("tlinsWTrackingControl", "RA speed", nullptr));
        label_2->setText(QApplication::translate("tlinsWTrackingControl", "DC speed", nullptr));
        pushButton->setText(QApplication::translate("tlinsWTrackingControl", "Start", nullptr));
        pushButton_2->setText(QApplication::translate("tlinsWTrackingControl", "Stop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWTrackingControl: public Ui_tlinsWTrackingControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWTRACKINGCONTROL_H
