/********************************************************************************
** Form generated from reading UI file 'tlinswpilothorisintalverticalincrement.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWPILOTHORISINTALVERTICALINCREMENT_H
#define UI_TLINSWPILOTHORISINTALVERTICALINCREMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsWPilotHorisintalVerticalIncrement
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *tlinsWPilotHorisintalVerticalIncrement)
    {
        if (tlinsWPilotHorisintalVerticalIncrement->objectName().isEmpty())
            tlinsWPilotHorisintalVerticalIncrement->setObjectName(QString::fromUtf8("tlinsWPilotHorisintalVerticalIncrement"));
        tlinsWPilotHorisintalVerticalIncrement->resize(316, 39);
        gridLayout = new QGridLayout(tlinsWPilotHorisintalVerticalIncrement);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(tlinsWPilotHorisintalVerticalIncrement);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);


        retranslateUi(tlinsWPilotHorisintalVerticalIncrement);

        QMetaObject::connectSlotsByName(tlinsWPilotHorisintalVerticalIncrement);
    } // setupUi

    void retranslateUi(QWidget *tlinsWPilotHorisintalVerticalIncrement)
    {
        tlinsWPilotHorisintalVerticalIncrement->setWindowTitle(QApplication::translate("tlinsWPilotHorisintalVerticalIncrement", "Form", nullptr));
        label->setText(QApplication::translate("tlinsWPilotHorisintalVerticalIncrement", "No configuration", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWPilotHorisintalVerticalIncrement: public Ui_tlinsWPilotHorisintalVerticalIncrement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWPILOTHORISINTALVERTICALINCREMENT_H
