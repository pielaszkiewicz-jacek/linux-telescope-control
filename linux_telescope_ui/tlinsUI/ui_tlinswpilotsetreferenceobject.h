/********************************************************************************
** Form generated from reading UI file 'tlinswpilotsetreferenceobject.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWPILOTSETREFERENCEOBJECT_H
#define UI_TLINSWPILOTSETREFERENCEOBJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsWPilotSetReferenceObject
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *tlinsWPilotSetReferenceObject)
    {
        if (tlinsWPilotSetReferenceObject->objectName().isEmpty())
            tlinsWPilotSetReferenceObject->setObjectName(QString::fromUtf8("tlinsWPilotSetReferenceObject"));
        tlinsWPilotSetReferenceObject->resize(400, 39);
        verticalLayout = new QVBoxLayout(tlinsWPilotSetReferenceObject);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(tlinsWPilotSetReferenceObject);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(tlinsWPilotSetReferenceObject);

        QMetaObject::connectSlotsByName(tlinsWPilotSetReferenceObject);
    } // setupUi

    void retranslateUi(QWidget *tlinsWPilotSetReferenceObject)
    {
        tlinsWPilotSetReferenceObject->setWindowTitle(QApplication::translate("tlinsWPilotSetReferenceObject", "Form", nullptr));
        label->setText(QApplication::translate("tlinsWPilotSetReferenceObject", "No configuration", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWPilotSetReferenceObject: public Ui_tlinsWPilotSetReferenceObject {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWPILOTSETREFERENCEOBJECT_H
