/********************************************************************************
** Form generated from reading UI file 'tlinsdatetimewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSDATETIMEWIDGET_H
#define UI_TLINSDATETIMEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "tlinswdatetime.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsDateTimeWidget
{
public:
    QVBoxLayout *verticalLayout;
    tlinsWDateTime *dateTime;
    QDialogButtonBox *buttonBox;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *tlinsDateTimeWidget)
    {
        if (tlinsDateTimeWidget->objectName().isEmpty())
            tlinsDateTimeWidget->setObjectName(QString::fromUtf8("tlinsDateTimeWidget"));
        tlinsDateTimeWidget->resize(559, 362);
        verticalLayout = new QVBoxLayout(tlinsDateTimeWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        dateTime = new tlinsWDateTime(tlinsDateTimeWidget);
        dateTime->setObjectName(QString::fromUtf8("dateTime"));

        verticalLayout->addWidget(dateTime);

        buttonBox = new QDialogButtonBox(tlinsDateTimeWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(tlinsDateTimeWidget);

        QMetaObject::connectSlotsByName(tlinsDateTimeWidget);
    } // setupUi

    void retranslateUi(QWidget *tlinsDateTimeWidget)
    {
        tlinsDateTimeWidget->setWindowTitle(QApplication::translate("tlinsDateTimeWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsDateTimeWidget: public Ui_tlinsDateTimeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSDATETIMEWIDGET_H
