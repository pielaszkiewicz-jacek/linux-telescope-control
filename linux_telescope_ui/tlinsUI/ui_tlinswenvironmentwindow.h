/********************************************************************************
** Form generated from reading UI file 'tlinswenvironmentwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWENVIRONMENTWINDOW_H
#define UI_TLINSWENVIRONMENTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include "tlinswenvironment.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsWEnvironmentWindow
{
public:
    QGridLayout *gridLayout;
    QDialogButtonBox *buttons;
    tlinsWEnvironment *env;

    void setupUi(QDialog *tlinsWEnvironmentWindow)
    {
        if (tlinsWEnvironmentWindow->objectName().isEmpty())
            tlinsWEnvironmentWindow->setObjectName(QString::fromUtf8("tlinsWEnvironmentWindow"));
        tlinsWEnvironmentWindow->resize(460, 336);
        gridLayout = new QGridLayout(tlinsWEnvironmentWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        buttons = new QDialogButtonBox(tlinsWEnvironmentWindow);
        buttons->setObjectName(QString::fromUtf8("buttons"));
        buttons->setOrientation(Qt::Horizontal);
        buttons->setStandardButtons(QDialogButtonBox::Close|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttons, 1, 0, 1, 1);

        env = new tlinsWEnvironment(tlinsWEnvironmentWindow);
        env->setObjectName(QString::fromUtf8("env"));

        gridLayout->addWidget(env, 0, 0, 1, 1);


        retranslateUi(tlinsWEnvironmentWindow);
        QObject::connect(buttons, SIGNAL(accepted()), tlinsWEnvironmentWindow, SLOT(accept()));
        QObject::connect(buttons, SIGNAL(rejected()), tlinsWEnvironmentWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(tlinsWEnvironmentWindow);
    } // setupUi

    void retranslateUi(QDialog *tlinsWEnvironmentWindow)
    {
        tlinsWEnvironmentWindow->setWindowTitle(QApplication::translate("tlinsWEnvironmentWindow", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWEnvironmentWindow: public Ui_tlinsWEnvironmentWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWENVIRONMENTWINDOW_H
