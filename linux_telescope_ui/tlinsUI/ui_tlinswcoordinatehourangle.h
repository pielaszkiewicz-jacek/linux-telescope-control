/********************************************************************************
** Form generated from reading UI file 'tlinswcoordinatehourangle.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWCOORDINATEHOURANGLE_H
#define UI_TLINSWCOORDINATEHOURANGLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsWCoordinateHourAngle
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *ra;

    void setupUi(QWidget *tlinsWCoordinateHourAngle)
    {
        if (tlinsWCoordinateHourAngle->objectName().isEmpty())
            tlinsWCoordinateHourAngle->setObjectName(QString::fromUtf8("tlinsWCoordinateHourAngle"));
        tlinsWCoordinateHourAngle->resize(194, 74);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tlinsWCoordinateHourAngle->sizePolicy().hasHeightForWidth());
        tlinsWCoordinateHourAngle->setSizePolicy(sizePolicy);
        tlinsWCoordinateHourAngle->setMinimumSize(QSize(165, 32));
        tlinsWCoordinateHourAngle->setMaximumSize(QSize(16777215, 16777215));
        tlinsWCoordinateHourAngle->setSizeIncrement(QSize(0, 25));
        tlinsWCoordinateHourAngle->setBaseSize(QSize(0, 25));
        QFont font;
        font.setItalic(true);
        tlinsWCoordinateHourAngle->setFont(font);
        horizontalLayout = new QHBoxLayout(tlinsWCoordinateHourAngle);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(tlinsWCoordinateHourAngle);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        ra = new QLineEdit(tlinsWCoordinateHourAngle);
        ra->setObjectName(QString::fromUtf8("ra"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ra->sizePolicy().hasHeightForWidth());
        ra->setSizePolicy(sizePolicy1);
        ra->setMinimumSize(QSize(165, 40));
        ra->setMaximumSize(QSize(16777215, 40));
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        ra->setFont(font1);
        ra->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(ra);


        retranslateUi(tlinsWCoordinateHourAngle);

        QMetaObject::connectSlotsByName(tlinsWCoordinateHourAngle);
    } // setupUi

    void retranslateUi(QWidget *tlinsWCoordinateHourAngle)
    {
        tlinsWCoordinateHourAngle->setWindowTitle(QApplication::translate("tlinsWCoordinateHourAngle", "Form", nullptr));
        label->setText(QString());
        ra->setInputMask(QApplication::translate("tlinsWCoordinateHourAngle", "09:09:09.9000", nullptr));
        ra->setText(QApplication::translate("tlinsWCoordinateHourAngle", "00:00:00.0000", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWCoordinateHourAngle: public Ui_tlinsWCoordinateHourAngle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWCOORDINATEHOURANGLE_H
