/********************************************************************************
** Form generated from reading UI file 'tlinswcoordinatedegris.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWCOORDINATEDEGRIS_H
#define UI_TLINSWCOORDINATEDEGRIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsWCoordinateDegris
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *coordinateName;
    QLineEdit *degris;

    void setupUi(QWidget *tlinsWCoordinateDegris)
    {
        if (tlinsWCoordinateDegris->objectName().isEmpty())
            tlinsWCoordinateDegris->setObjectName(QString::fromUtf8("tlinsWCoordinateDegris"));
        tlinsWCoordinateDegris->resize(219, 76);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tlinsWCoordinateDegris->sizePolicy().hasHeightForWidth());
        tlinsWCoordinateDegris->setSizePolicy(sizePolicy);
        tlinsWCoordinateDegris->setMinimumSize(QSize(165, 40));
        tlinsWCoordinateDegris->setMaximumSize(QSize(16777215, 16777215));
        tlinsWCoordinateDegris->setAutoFillBackground(false);
        horizontalLayout = new QHBoxLayout(tlinsWCoordinateDegris);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        coordinateName = new QLabel(tlinsWCoordinateDegris);
        coordinateName->setObjectName(QString::fromUtf8("coordinateName"));
        QFont font;
        font.setPointSize(11);
        coordinateName->setFont(font);

        horizontalLayout->addWidget(coordinateName);

        degris = new QLineEdit(tlinsWCoordinateDegris);
        degris->setObjectName(QString::fromUtf8("degris"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(degris->sizePolicy().hasHeightForWidth());
        degris->setSizePolicy(sizePolicy1);
        degris->setMinimumSize(QSize(0, 40));
        degris->setMaximumSize(QSize(16777215, 40));
        degris->setSizeIncrement(QSize(2, 2));
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(false);
        font1.setWeight(50);
        font1.setKerning(true);
        degris->setFont(font1);
        degris->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(degris);


        retranslateUi(tlinsWCoordinateDegris);
        QObject::connect(degris, SIGNAL(editingFinished()), tlinsWCoordinateDegris, SLOT(update()));

        QMetaObject::connectSlotsByName(tlinsWCoordinateDegris);
    } // setupUi

    void retranslateUi(QWidget *tlinsWCoordinateDegris)
    {
        tlinsWCoordinateDegris->setWindowTitle(QApplication::translate("tlinsWCoordinateDegris", "Form", nullptr));
        coordinateName->setText(QString());
        degris->setInputMask(QApplication::translate("tlinsWCoordinateDegris", "#009:09:09.9000", nullptr));
        degris->setText(QApplication::translate("tlinsWCoordinateDegris", "000:00:00.0000", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWCoordinateDegris: public Ui_tlinsWCoordinateDegris {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWCOORDINATEDEGRIS_H
