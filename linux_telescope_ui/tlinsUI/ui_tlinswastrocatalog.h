/********************************************************************************
** Form generated from reading UI file 'tlinswastrocatalog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWASTROCATALOG_H
#define UI_TLINSWASTROCATALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsWAstroCatalog
{
public:
    QGridLayout *gridLayout;
    QComboBox *astroCatalog;

    void setupUi(QWidget *tlinsWAstroCatalog)
    {
        if (tlinsWAstroCatalog->objectName().isEmpty())
            tlinsWAstroCatalog->setObjectName(QString::fromUtf8("tlinsWAstroCatalog"));
        tlinsWAstroCatalog->resize(382, 102);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tlinsWAstroCatalog->sizePolicy().hasHeightForWidth());
        tlinsWAstroCatalog->setSizePolicy(sizePolicy);
        tlinsWAstroCatalog->setMinimumSize(QSize(0, 30));
        tlinsWAstroCatalog->setMaximumSize(QSize(16777215, 16777215));
        gridLayout = new QGridLayout(tlinsWAstroCatalog);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        astroCatalog = new QComboBox(tlinsWAstroCatalog);
        astroCatalog->setObjectName(QString::fromUtf8("astroCatalog"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(astroCatalog->sizePolicy().hasHeightForWidth());
        astroCatalog->setSizePolicy(sizePolicy1);
        astroCatalog->setMinimumSize(QSize(0, 40));
        astroCatalog->setMaximumSize(QSize(16777215, 40));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        astroCatalog->setFont(font);

        gridLayout->addWidget(astroCatalog, 0, 0, 1, 1);


        retranslateUi(tlinsWAstroCatalog);

        QMetaObject::connectSlotsByName(tlinsWAstroCatalog);
    } // setupUi

    void retranslateUi(QWidget *tlinsWAstroCatalog)
    {
        tlinsWAstroCatalog->setWindowTitle(QApplication::translate("tlinsWAstroCatalog", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWAstroCatalog: public Ui_tlinsWAstroCatalog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWASTROCATALOG_H
