/********************************************************************************
** Form generated from reading UI file 'tlinswobjectname.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWOBJECTNAME_H
#define UI_TLINSWOBJECTNAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsWObjectName
{
public:
    QGridLayout *gridLayout;
    QLineEdit *objectName;

    void setupUi(QWidget *tlinsWObjectName)
    {
        if (tlinsWObjectName->objectName().isEmpty())
            tlinsWObjectName->setObjectName(QString::fromUtf8("tlinsWObjectName"));
        tlinsWObjectName->resize(300, 66);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tlinsWObjectName->sizePolicy().hasHeightForWidth());
        tlinsWObjectName->setSizePolicy(sizePolicy);
        tlinsWObjectName->setMinimumSize(QSize(300, 40));
        tlinsWObjectName->setMaximumSize(QSize(300, 16777215));
        gridLayout = new QGridLayout(tlinsWObjectName);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        objectName = new QLineEdit(tlinsWObjectName);
        objectName->setObjectName(QString::fromUtf8("objectName"));
        objectName->setMinimumSize(QSize(0, 40));
        objectName->setMaximumSize(QSize(16777215, 40));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        objectName->setFont(font);

        gridLayout->addWidget(objectName, 0, 0, 1, 1);


        retranslateUi(tlinsWObjectName);
        QObject::connect(objectName, SIGNAL(editingFinished()), tlinsWObjectName, SLOT(update()));

        QMetaObject::connectSlotsByName(tlinsWObjectName);
    } // setupUi

    void retranslateUi(QWidget *tlinsWObjectName)
    {
        tlinsWObjectName->setWindowTitle(QApplication::translate("tlinsWObjectName", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWObjectName: public Ui_tlinsWObjectName {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWOBJECTNAME_H
