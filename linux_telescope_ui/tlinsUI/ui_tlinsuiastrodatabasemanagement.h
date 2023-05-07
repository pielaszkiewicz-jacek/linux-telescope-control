/********************************************************************************
** Form generated from reading UI file 'tlinsuiastrodatabasemanagement.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSUIASTRODATABASEMANAGEMENT_H
#define UI_TLINSUIASTRODATABASEMANAGEMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QVBoxLayout>
#include "tlinsuiastrodatabasemanagementwidget.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsUiAstroDatabaseManagement
{
public:
    QVBoxLayout *verticalLayout;
    tlinsUiAstroDatabaseManagementWidget *widget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *tlinsUiAstroDatabaseManagement)
    {
        if (tlinsUiAstroDatabaseManagement->objectName().isEmpty())
            tlinsUiAstroDatabaseManagement->setObjectName(QString::fromUtf8("tlinsUiAstroDatabaseManagement"));
        tlinsUiAstroDatabaseManagement->resize(890, 664);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tlinsUiAstroDatabaseManagement->sizePolicy().hasHeightForWidth());
        tlinsUiAstroDatabaseManagement->setSizePolicy(sizePolicy);
        tlinsUiAstroDatabaseManagement->setMinimumSize(QSize(890, 605));
        tlinsUiAstroDatabaseManagement->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout = new QVBoxLayout(tlinsUiAstroDatabaseManagement);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new tlinsUiAstroDatabaseManagementWidget(tlinsUiAstroDatabaseManagement);
        widget->setObjectName(QString::fromUtf8("widget"));

        verticalLayout->addWidget(widget);

        buttonBox = new QDialogButtonBox(tlinsUiAstroDatabaseManagement);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(tlinsUiAstroDatabaseManagement);
        QObject::connect(buttonBox, SIGNAL(accepted()), tlinsUiAstroDatabaseManagement, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), tlinsUiAstroDatabaseManagement, SLOT(reject()));

        QMetaObject::connectSlotsByName(tlinsUiAstroDatabaseManagement);
    } // setupUi

    void retranslateUi(QDialog *tlinsUiAstroDatabaseManagement)
    {
        tlinsUiAstroDatabaseManagement->setWindowTitle(QApplication::translate("tlinsUiAstroDatabaseManagement", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsUiAstroDatabaseManagement: public Ui_tlinsUiAstroDatabaseManagement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSUIASTRODATABASEMANAGEMENT_H
