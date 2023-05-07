/********************************************************************************
** Form generated from reading UI file 'tlinssettingswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSSETTINGSWINDOW_H
#define UI_TLINSSETTINGSWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QVBoxLayout>
#include "tlinssettingswidget.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsSettingsWindow
{
public:
    QVBoxLayout *verticalLayout_3;
    tlinsSettingsWidget *widget;

    void setupUi(QDialog *tlinsSettingsWindow)
    {
        if (tlinsSettingsWindow->objectName().isEmpty())
            tlinsSettingsWindow->setObjectName(QString::fromUtf8("tlinsSettingsWindow"));
        tlinsSettingsWindow->resize(776, 481);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/settings.svg"), QSize(), QIcon::Normal, QIcon::Off);
        tlinsSettingsWindow->setWindowIcon(icon);
        tlinsSettingsWindow->setModal(true);
        verticalLayout_3 = new QVBoxLayout(tlinsSettingsWindow);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        widget = new tlinsSettingsWidget(tlinsSettingsWindow);
        widget->setObjectName(QString::fromUtf8("widget"));

        verticalLayout_3->addWidget(widget);


        retranslateUi(tlinsSettingsWindow);

        QMetaObject::connectSlotsByName(tlinsSettingsWindow);
    } // setupUi

    void retranslateUi(QDialog *tlinsSettingsWindow)
    {
        tlinsSettingsWindow->setWindowTitle(QApplication::translate("tlinsSettingsWindow", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsSettingsWindow: public Ui_tlinsSettingsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSSETTINGSWINDOW_H
