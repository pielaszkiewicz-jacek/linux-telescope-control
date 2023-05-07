/********************************************************************************
** Form generated from reading UI file 'tlinswconstelation.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWCONSTELATION_H
#define UI_TLINSWCONSTELATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsWConstelation
{
public:
    QGridLayout *gridLayout;
    QComboBox *constelation;

    void setupUi(QWidget *tlinsWConstelation)
    {
        if (tlinsWConstelation->objectName().isEmpty())
            tlinsWConstelation->setObjectName(QString::fromUtf8("tlinsWConstelation"));
        tlinsWConstelation->resize(300, 58);
        tlinsWConstelation->setMinimumSize(QSize(300, 40));
        tlinsWConstelation->setMaximumSize(QSize(300, 16777215));
        gridLayout = new QGridLayout(tlinsWConstelation);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        constelation = new QComboBox(tlinsWConstelation);
        constelation->setObjectName(QString::fromUtf8("constelation"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(constelation->sizePolicy().hasHeightForWidth());
        constelation->setSizePolicy(sizePolicy);
        constelation->setMinimumSize(QSize(0, 40));
        constelation->setMaximumSize(QSize(16777215, 40));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        constelation->setFont(font);

        gridLayout->addWidget(constelation, 0, 0, 1, 1);


        retranslateUi(tlinsWConstelation);

        QMetaObject::connectSlotsByName(tlinsWConstelation);
    } // setupUi

    void retranslateUi(QWidget *tlinsWConstelation)
    {
        tlinsWConstelation->setWindowTitle(QApplication::translate("tlinsWConstelation", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWConstelation: public Ui_tlinsWConstelation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWCONSTELATION_H
