/********************************************************************************
** Form generated from reading UI file 'tlinsstatusicons.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSSTATUSICONS_H
#define UI_TLINSSTATUSICONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <tlinswdecimalvalue.h>
#include "tlinswcoordinatedeclination.h"
#include "tlinswcoordinatehourangle.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsStatusIcons
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QCheckBox *isConnected;
    QFrame *line;
    QLabel *label_5;
    QLabel *calibrationStatus;
    QFrame *line_2;
    QLabel *label;
    tlinsWDecimalValue *posX;
    QFrame *line_3;
    QLabel *label_2;
    tlinsWDecimalValue *posY;
    QFrame *line_4;
    QLabel *label_3;
    tlinsWCoordinateHourAngle *posRA;
    QFrame *line_5;
    QLabel *label_4;
    tlinsWCoordinateDeclination *posDEC;

    void setupUi(QWidget *tlinsStatusIcons)
    {
        if (tlinsStatusIcons->objectName().isEmpty())
            tlinsStatusIcons->setObjectName(QString::fromUtf8("tlinsStatusIcons"));
        tlinsStatusIcons->resize(669, 46);
        horizontalLayout_2 = new QHBoxLayout(tlinsStatusIcons);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, -1, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        isConnected = new QCheckBox(tlinsStatusIcons);
        isConnected->setObjectName(QString::fromUtf8("isConnected"));
        isConnected->setEnabled(false);

        horizontalLayout->addWidget(isConnected);

        line = new QFrame(tlinsStatusIcons);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShadow(QFrame::Raised);
        line->setLineWidth(2);
        line->setFrameShape(QFrame::VLine);

        horizontalLayout->addWidget(line);

        label_5 = new QLabel(tlinsStatusIcons);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout->addWidget(label_5);

        calibrationStatus = new QLabel(tlinsStatusIcons);
        calibrationStatus->setObjectName(QString::fromUtf8("calibrationStatus"));

        horizontalLayout->addWidget(calibrationStatus);

        line_2 = new QFrame(tlinsStatusIcons);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShadow(QFrame::Raised);
        line_2->setLineWidth(2);
        line_2->setFrameShape(QFrame::VLine);

        horizontalLayout->addWidget(line_2);


        horizontalLayout_2->addLayout(horizontalLayout);

        label = new QLabel(tlinsStatusIcons);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        posX = new tlinsWDecimalValue(tlinsStatusIcons);
        posX->setObjectName(QString::fromUtf8("posX"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(posX->sizePolicy().hasHeightForWidth());
        posX->setSizePolicy(sizePolicy);
        posX->setMaximumSize(QSize(15, 16777215));

        horizontalLayout_2->addWidget(posX);

        line_3 = new QFrame(tlinsStatusIcons);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShadow(QFrame::Raised);
        line_3->setLineWidth(2);
        line_3->setFrameShape(QFrame::VLine);

        horizontalLayout_2->addWidget(line_3);

        label_2 = new QLabel(tlinsStatusIcons);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        posY = new tlinsWDecimalValue(tlinsStatusIcons);
        posY->setObjectName(QString::fromUtf8("posY"));
        sizePolicy.setHeightForWidth(posY->sizePolicy().hasHeightForWidth());
        posY->setSizePolicy(sizePolicy);
        posY->setMaximumSize(QSize(15, 16777215));

        horizontalLayout_2->addWidget(posY);

        line_4 = new QFrame(tlinsStatusIcons);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShadow(QFrame::Raised);
        line_4->setLineWidth(2);
        line_4->setFrameShape(QFrame::VLine);

        horizontalLayout_2->addWidget(line_4);

        label_3 = new QLabel(tlinsStatusIcons);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        posRA = new tlinsWCoordinateHourAngle(tlinsStatusIcons);
        posRA->setObjectName(QString::fromUtf8("posRA"));
        sizePolicy.setHeightForWidth(posRA->sizePolicy().hasHeightForWidth());
        posRA->setSizePolicy(sizePolicy);
        posRA->setMaximumSize(QSize(25, 16777215));

        horizontalLayout_2->addWidget(posRA);

        line_5 = new QFrame(tlinsStatusIcons);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShadow(QFrame::Raised);
        line_5->setLineWidth(2);
        line_5->setFrameShape(QFrame::VLine);

        horizontalLayout_2->addWidget(line_5);

        label_4 = new QLabel(tlinsStatusIcons);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        posDEC = new tlinsWCoordinateDeclination(tlinsStatusIcons);
        posDEC->setObjectName(QString::fromUtf8("posDEC"));
        sizePolicy.setHeightForWidth(posDEC->sizePolicy().hasHeightForWidth());
        posDEC->setSizePolicy(sizePolicy);
        posDEC->setMaximumSize(QSize(25, 16777215));

        horizontalLayout_2->addWidget(posDEC);


        retranslateUi(tlinsStatusIcons);

        QMetaObject::connectSlotsByName(tlinsStatusIcons);
    } // setupUi

    void retranslateUi(QWidget *tlinsStatusIcons)
    {
        tlinsStatusIcons->setWindowTitle(QApplication::translate("tlinsStatusIcons", "Form", nullptr));
        isConnected->setText(QApplication::translate("tlinsStatusIcons", "Connected", nullptr));
        label_5->setText(QApplication::translate("tlinsStatusIcons", "Device status: ", nullptr));
        calibrationStatus->setText(QApplication::translate("tlinsStatusIcons", "dddd", nullptr));
        label->setText(QApplication::translate("tlinsStatusIcons", "X:", nullptr));
        label_2->setText(QApplication::translate("tlinsStatusIcons", "Y:", nullptr));
        label_3->setText(QApplication::translate("tlinsStatusIcons", "RA:", nullptr));
        label_4->setText(QApplication::translate("tlinsStatusIcons", "DEC:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsStatusIcons: public Ui_tlinsStatusIcons {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSSTATUSICONS_H
