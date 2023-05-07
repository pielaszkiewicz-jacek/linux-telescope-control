/********************************************************************************
** Form generated from reading UI file 'tlinswsettingsdatabase.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWSETTINGSDATABASE_H
#define UI_TLINSWSETTINGSDATABASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsWSettingsDatabase
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QLineEdit *databaseType;
    QLabel *label;
    QLineEdit *host;
    QLabel *label_3;
    QLabel *label_5;
    QLineEdit *filePath;
    QLabel *label_2;
    QPushButton *selectFile;
    QLineEdit *user;
    QLineEdit *connectionName;
    QLabel *label_4;
    QLabel *label_6;
    QLineEdit *password;

    void setupUi(QWidget *tlinsWSettingsDatabase)
    {
        if (tlinsWSettingsDatabase->objectName().isEmpty())
            tlinsWSettingsDatabase->setObjectName(QString::fromUtf8("tlinsWSettingsDatabase"));
        tlinsWSettingsDatabase->resize(548, 159);
        gridLayout = new QGridLayout(tlinsWSettingsDatabase);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        databaseType = new QLineEdit(tlinsWSettingsDatabase);
        databaseType->setObjectName(QString::fromUtf8("databaseType"));

        gridLayout_2->addWidget(databaseType, 1, 2, 1, 1);

        label = new QLabel(tlinsWSettingsDatabase);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 1, 0, 1, 1);

        host = new QLineEdit(tlinsWSettingsDatabase);
        host->setObjectName(QString::fromUtf8("host"));

        gridLayout_2->addWidget(host, 3, 2, 1, 1);

        label_3 = new QLabel(tlinsWSettingsDatabase);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        label_5 = new QLabel(tlinsWSettingsDatabase);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 4, 0, 1, 1);

        filePath = new QLineEdit(tlinsWSettingsDatabase);
        filePath->setObjectName(QString::fromUtf8("filePath"));

        gridLayout_2->addWidget(filePath, 0, 2, 1, 1);

        label_2 = new QLabel(tlinsWSettingsDatabase);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        selectFile = new QPushButton(tlinsWSettingsDatabase);
        selectFile->setObjectName(QString::fromUtf8("selectFile"));

        gridLayout_2->addWidget(selectFile, 0, 4, 1, 1);

        user = new QLineEdit(tlinsWSettingsDatabase);
        user->setObjectName(QString::fromUtf8("user"));

        gridLayout_2->addWidget(user, 4, 2, 1, 1);

        connectionName = new QLineEdit(tlinsWSettingsDatabase);
        connectionName->setObjectName(QString::fromUtf8("connectionName"));

        gridLayout_2->addWidget(connectionName, 2, 2, 1, 1);

        label_4 = new QLabel(tlinsWSettingsDatabase);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        label_6 = new QLabel(tlinsWSettingsDatabase);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 5, 0, 1, 1);

        password = new QLineEdit(tlinsWSettingsDatabase);
        password->setObjectName(QString::fromUtf8("password"));
        password->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(password, 5, 2, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 1);


        retranslateUi(tlinsWSettingsDatabase);

        QMetaObject::connectSlotsByName(tlinsWSettingsDatabase);
    } // setupUi

    void retranslateUi(QWidget *tlinsWSettingsDatabase)
    {
        tlinsWSettingsDatabase->setWindowTitle(QApplication::translate("tlinsWSettingsDatabase", "Form", nullptr));
        label->setText(QApplication::translate("tlinsWSettingsDatabase", "Type", nullptr));
        label_3->setText(QApplication::translate("tlinsWSettingsDatabase", "Connection name", nullptr));
        label_5->setText(QApplication::translate("tlinsWSettingsDatabase", "User", nullptr));
        label_2->setText(QApplication::translate("tlinsWSettingsDatabase", "Name (path)", nullptr));
        selectFile->setText(QApplication::translate("tlinsWSettingsDatabase", "Select file", nullptr));
        label_4->setText(QApplication::translate("tlinsWSettingsDatabase", "Host", nullptr));
        label_6->setText(QApplication::translate("tlinsWSettingsDatabase", "Password", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWSettingsDatabase: public Ui_tlinsWSettingsDatabase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWSETTINGSDATABASE_H
