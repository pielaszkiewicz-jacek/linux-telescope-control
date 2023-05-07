/********************************************************************************
** Form generated from reading UI file 'tlinsuiastrodatabasemanagementwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSUIASTRODATABASEMANAGEMENTWIDGET_H
#define UI_TLINSUIASTRODATABASEMANAGEMENTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "tlinswdatabasesearchmain.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsUiAstroDatabaseManagementWidget
{
public:
    QVBoxLayout *verticalLayout;
    tlinsWDatabaseSearchMain *searchWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *importButton;
    QPushButton *deleteButton;
    QPushButton *editButton;
    QPushButton *addButton;
    QVBoxLayout *verticalLayout_2;

    void setupUi(QWidget *tlinsUiAstroDatabaseManagementWidget)
    {
        if (tlinsUiAstroDatabaseManagementWidget->objectName().isEmpty())
            tlinsUiAstroDatabaseManagementWidget->setObjectName(QString::fromUtf8("tlinsUiAstroDatabaseManagementWidget"));
        tlinsUiAstroDatabaseManagementWidget->resize(730, 448);
        verticalLayout = new QVBoxLayout(tlinsUiAstroDatabaseManagementWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        searchWidget = new tlinsWDatabaseSearchMain(tlinsUiAstroDatabaseManagementWidget);
        searchWidget->setObjectName(QString::fromUtf8("searchWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(searchWidget->sizePolicy().hasHeightForWidth());
        searchWidget->setSizePolicy(sizePolicy);
        searchWidget->setMinimumSize(QSize(0, 0));
        searchWidget->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout->addWidget(searchWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, -1, 24);
        importButton = new QPushButton(tlinsUiAstroDatabaseManagementWidget);
        importButton->setObjectName(QString::fromUtf8("importButton"));
        importButton->setMinimumSize(QSize(150, 45));
        importButton->setMaximumSize(QSize(115, 25));

        horizontalLayout_2->addWidget(importButton);

        deleteButton = new QPushButton(tlinsUiAstroDatabaseManagementWidget);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));
        deleteButton->setMinimumSize(QSize(150, 45));
        deleteButton->setMaximumSize(QSize(115, 25));

        horizontalLayout_2->addWidget(deleteButton);

        editButton = new QPushButton(tlinsUiAstroDatabaseManagementWidget);
        editButton->setObjectName(QString::fromUtf8("editButton"));
        editButton->setMinimumSize(QSize(150, 45));
        editButton->setMaximumSize(QSize(115, 25));

        horizontalLayout_2->addWidget(editButton);

        addButton = new QPushButton(tlinsUiAstroDatabaseManagementWidget);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        addButton->setMinimumSize(QSize(150, 45));
        addButton->setMaximumSize(QSize(115, 25));

        horizontalLayout_2->addWidget(addButton);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));

        verticalLayout->addLayout(verticalLayout_2);


        retranslateUi(tlinsUiAstroDatabaseManagementWidget);

        QMetaObject::connectSlotsByName(tlinsUiAstroDatabaseManagementWidget);
    } // setupUi

    void retranslateUi(QWidget *tlinsUiAstroDatabaseManagementWidget)
    {
        tlinsUiAstroDatabaseManagementWidget->setWindowTitle(QApplication::translate("tlinsUiAstroDatabaseManagementWidget", "Form", nullptr));
        importButton->setText(QApplication::translate("tlinsUiAstroDatabaseManagementWidget", "Import from file", nullptr));
        deleteButton->setText(QApplication::translate("tlinsUiAstroDatabaseManagementWidget", "Delete items", nullptr));
        editButton->setText(QApplication::translate("tlinsUiAstroDatabaseManagementWidget", "Edit item/View", nullptr));
        addButton->setText(QApplication::translate("tlinsUiAstroDatabaseManagementWidget", "Add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsUiAstroDatabaseManagementWidget: public Ui_tlinsUiAstroDatabaseManagementWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSUIASTRODATABASEMANAGEMENTWIDGET_H
