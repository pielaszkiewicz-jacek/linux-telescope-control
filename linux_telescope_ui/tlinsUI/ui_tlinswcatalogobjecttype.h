/********************************************************************************
** Form generated from reading UI file 'tlinswcatalogobjecttype.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWCATALOGOBJECTTYPE_H
#define UI_TLINSWCATALOGOBJECTTYPE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsWCatalogObjectType
{
public:
    QGridLayout *gridLayout;
    QLineEdit *catalogObjectId;

    void setupUi(QWidget *tlinsWCatalogObjectType)
    {
        if (tlinsWCatalogObjectType->objectName().isEmpty())
            tlinsWCatalogObjectType->setObjectName(QString::fromUtf8("tlinsWCatalogObjectType"));
        tlinsWCatalogObjectType->resize(289, 73);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tlinsWCatalogObjectType->sizePolicy().hasHeightForWidth());
        tlinsWCatalogObjectType->setSizePolicy(sizePolicy);
        tlinsWCatalogObjectType->setMinimumSize(QSize(0, 40));
        tlinsWCatalogObjectType->setMaximumSize(QSize(16777215, 16777215));
        gridLayout = new QGridLayout(tlinsWCatalogObjectType);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        catalogObjectId = new QLineEdit(tlinsWCatalogObjectType);
        catalogObjectId->setObjectName(QString::fromUtf8("catalogObjectId"));
        catalogObjectId->setMinimumSize(QSize(0, 40));
        catalogObjectId->setMaximumSize(QSize(16777215, 40));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        catalogObjectId->setFont(font);

        gridLayout->addWidget(catalogObjectId, 0, 0, 1, 1);


        retranslateUi(tlinsWCatalogObjectType);

        QMetaObject::connectSlotsByName(tlinsWCatalogObjectType);
    } // setupUi

    void retranslateUi(QWidget *tlinsWCatalogObjectType)
    {
        tlinsWCatalogObjectType->setWindowTitle(QApplication::translate("tlinsWCatalogObjectType", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWCatalogObjectType: public Ui_tlinsWCatalogObjectType {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWCATALOGOBJECTTYPE_H
