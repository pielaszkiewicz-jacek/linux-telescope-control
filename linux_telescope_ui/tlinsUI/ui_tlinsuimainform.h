/********************************************************************************
** Form generated from reading UI file 'tlinsuimainform.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSUIMAINFORM_H
#define UI_TLINSUIMAINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsUiMainForm
{
public:

    void setupUi(QWidget *tlinsUiMainForm)
    {
        if (tlinsUiMainForm->objectName().isEmpty())
            tlinsUiMainForm->setObjectName(QString::fromUtf8("tlinsUiMainForm"));
        tlinsUiMainForm->resize(400, 300);

        retranslateUi(tlinsUiMainForm);

        QMetaObject::connectSlotsByName(tlinsUiMainForm);
    } // setupUi

    void retranslateUi(QWidget *tlinsUiMainForm)
    {
        tlinsUiMainForm->setWindowTitle(QApplication::translate("tlinsUiMainForm", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsUiMainForm: public Ui_tlinsUiMainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSUIMAINFORM_H
