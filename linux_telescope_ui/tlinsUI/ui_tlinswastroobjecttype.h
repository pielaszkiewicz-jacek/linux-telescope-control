/********************************************************************************
** Form generated from reading UI file 'tlinswastroobjecttype.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWASTROOBJECTTYPE_H
#define UI_TLINSWASTROOBJECTTYPE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsWAstroObjectType
{
public:
    QGridLayout *gridLayout;
    QComboBox *astroObjectType;

    void setupUi(QWidget *tlinsWAstroObjectType)
    {
        if (tlinsWAstroObjectType->objectName().isEmpty())
            tlinsWAstroObjectType->setObjectName(QString::fromUtf8("tlinsWAstroObjectType"));
        tlinsWAstroObjectType->resize(300, 117);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tlinsWAstroObjectType->sizePolicy().hasHeightForWidth());
        tlinsWAstroObjectType->setSizePolicy(sizePolicy);
        tlinsWAstroObjectType->setMinimumSize(QSize(300, 40));
        tlinsWAstroObjectType->setMaximumSize(QSize(16777215, 16777215));
        gridLayout = new QGridLayout(tlinsWAstroObjectType);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        astroObjectType = new QComboBox(tlinsWAstroObjectType);
        astroObjectType->setObjectName(QString::fromUtf8("astroObjectType"));
        sizePolicy.setHeightForWidth(astroObjectType->sizePolicy().hasHeightForWidth());
        astroObjectType->setSizePolicy(sizePolicy);
        astroObjectType->setMinimumSize(QSize(0, 40));
        astroObjectType->setMaximumSize(QSize(16777215, 40));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        astroObjectType->setFont(font);
        astroObjectType->setFrame(true);

        gridLayout->addWidget(astroObjectType, 0, 0, 1, 1);


        retranslateUi(tlinsWAstroObjectType);

        QMetaObject::connectSlotsByName(tlinsWAstroObjectType);
    } // setupUi

    void retranslateUi(QWidget *tlinsWAstroObjectType)
    {
        tlinsWAstroObjectType->setWindowTitle(QApplication::translate("tlinsWAstroObjectType", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWAstroObjectType: public Ui_tlinsWAstroObjectType {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWASTROOBJECTTYPE_H
