/********************************************************************************
** Form generated from reading UI file 'tlinspilotwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSPILOTWINDOW_H
#define UI_TLINSPILOTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "tlinsuipolit4.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsPilotWindow
{
public:
    QVBoxLayout *verticalLayout;
    tlinsUiPolit4 *widget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *hideButton;

    void setupUi(QDialog *tlinsPilotWindow)
    {
        if (tlinsPilotWindow->objectName().isEmpty())
            tlinsPilotWindow->setObjectName(QString::fromUtf8("tlinsPilotWindow"));
        tlinsPilotWindow->setWindowModality(Qt::NonModal);
        tlinsPilotWindow->resize(538, 660);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/remote-control.svg"), QSize(), QIcon::Normal, QIcon::Off);
        tlinsPilotWindow->setWindowIcon(icon);
        tlinsPilotWindow->setToolTipDuration(-1);
        tlinsPilotWindow->setSizeGripEnabled(false);
        tlinsPilotWindow->setModal(true);
        verticalLayout = new QVBoxLayout(tlinsPilotWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new tlinsUiPolit4(tlinsPilotWindow);
        widget->setObjectName(QString::fromUtf8("widget"));

        verticalLayout->addWidget(widget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        hideButton = new QPushButton(tlinsPilotWindow);
        hideButton->setObjectName(QString::fromUtf8("hideButton"));
        hideButton->setMinimumSize(QSize(35, 35));
        hideButton->setMaximumSize(QSize(35, 35));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/close-button.svg"), QSize(), QIcon::Normal, QIcon::Off);
        hideButton->setIcon(icon1);
        hideButton->setFlat(true);

        horizontalLayout_2->addWidget(hideButton);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(tlinsPilotWindow);
        QObject::connect(hideButton, SIGNAL(clicked()), tlinsPilotWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(tlinsPilotWindow);
    } // setupUi

    void retranslateUi(QDialog *tlinsPilotWindow)
    {
        tlinsPilotWindow->setWindowTitle(QCoreApplication::translate("tlinsPilotWindow", "Pilot", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsPilotWindow: public Ui_tlinsPilotWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSPILOTWINDOW_H
