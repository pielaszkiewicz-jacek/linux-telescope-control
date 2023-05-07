/********************************************************************************
** Form generated from reading UI file 'tlinswrampsettings.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWRAMPSETTINGS_H
#define UI_TLINSWRAMPSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsWRampSettings
{
public:

    void setupUi(QWidget *tlinsWRampSettings)
    {
        if (tlinsWRampSettings->objectName().isEmpty())
            tlinsWRampSettings->setObjectName(QString::fromUtf8("tlinsWRampSettings"));
        tlinsWRampSettings->resize(488, 375);

        retranslateUi(tlinsWRampSettings);

        QMetaObject::connectSlotsByName(tlinsWRampSettings);
    } // setupUi

    void retranslateUi(QWidget *tlinsWRampSettings)
    {
        tlinsWRampSettings->setWindowTitle(QApplication::translate("tlinsWRampSettings", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWRampSettings: public Ui_tlinsWRampSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWRAMPSETTINGS_H
