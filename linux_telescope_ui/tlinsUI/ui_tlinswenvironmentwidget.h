/********************************************************************************
** Form generated from reading UI file 'tlinswenvironmentwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWENVIRONMENTWIDGET_H
#define UI_TLINSWENVIRONMENTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "tlinswenvironment.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsWEnvironmentWidget
{
public:
    QGridLayout *gridLayout;
    tlinsWEnvironment *env;
    QDialogButtonBox *buttons;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *tlinsWEnvironmentWidget)
    {
        if (tlinsWEnvironmentWidget->objectName().isEmpty())
            tlinsWEnvironmentWidget->setObjectName(QString::fromUtf8("tlinsWEnvironmentWidget"));
        tlinsWEnvironmentWidget->resize(488, 337);
        gridLayout = new QGridLayout(tlinsWEnvironmentWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        env = new tlinsWEnvironment(tlinsWEnvironmentWidget);
        env->setObjectName(QString::fromUtf8("env"));

        gridLayout->addWidget(env, 0, 0, 1, 1);

        buttons = new QDialogButtonBox(tlinsWEnvironmentWidget);
        buttons->setObjectName(QString::fromUtf8("buttons"));
        buttons->setOrientation(Qt::Horizontal);
        buttons->setStandardButtons(QDialogButtonBox::Ok);

        gridLayout->addWidget(buttons, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 0, 1, 1);


        retranslateUi(tlinsWEnvironmentWidget);

        QMetaObject::connectSlotsByName(tlinsWEnvironmentWidget);
    } // setupUi

    void retranslateUi(QWidget *tlinsWEnvironmentWidget)
    {
        tlinsWEnvironmentWidget->setWindowTitle(QApplication::translate("tlinsWEnvironmentWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWEnvironmentWidget: public Ui_tlinsWEnvironmentWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWENVIRONMENTWIDGET_H
