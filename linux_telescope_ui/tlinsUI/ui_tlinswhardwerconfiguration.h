/********************************************************************************
** Form generated from reading UI file 'tlinswhardwerconfiguration.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWHARDWERCONFIGURATION_H
#define UI_TLINSWHARDWERCONFIGURATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsWHardwerConfiguration
{
public:
    QTabWidget *tabWidget;
    QWidget *encoders;
    QListView *encodersHardwerInfo;
    QWidget *ctrlGpio;
    QListView *ctrlGpioHardwerInfo;
    QWidget *parameters;
    QListView *listView;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *mainDeviceName;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *deviceName;

    void setupUi(QWidget *tlinsWHardwerConfiguration)
    {
        if (tlinsWHardwerConfiguration->objectName().isEmpty())
            tlinsWHardwerConfiguration->setObjectName(QString::fromUtf8("tlinsWHardwerConfiguration"));
        tlinsWHardwerConfiguration->resize(579, 766);
        tabWidget = new QTabWidget(tlinsWHardwerConfiguration);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 100, 561, 331));
        tabWidget->setTabPosition(QTabWidget::West);
        encoders = new QWidget();
        encoders->setObjectName(QString::fromUtf8("encoders"));
        encodersHardwerInfo = new QListView(encoders);
        encodersHardwerInfo->setObjectName(QString::fromUtf8("encodersHardwerInfo"));
        encodersHardwerInfo->setGeometry(QRect(10, 10, 511, 301));
        tabWidget->addTab(encoders, QString());
        ctrlGpio = new QWidget();
        ctrlGpio->setObjectName(QString::fromUtf8("ctrlGpio"));
        ctrlGpioHardwerInfo = new QListView(ctrlGpio);
        ctrlGpioHardwerInfo->setObjectName(QString::fromUtf8("ctrlGpioHardwerInfo"));
        ctrlGpioHardwerInfo->setGeometry(QRect(10, 10, 511, 301));
        tabWidget->addTab(ctrlGpio, QString());
        parameters = new QWidget();
        parameters->setObjectName(QString::fromUtf8("parameters"));
        listView = new QListView(parameters);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(10, 10, 511, 301));
        tabWidget->addTab(parameters, QString());
        layoutWidget = new QWidget(tlinsWHardwerConfiguration);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 20, 359, 70));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(15);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(150, 0));

        horizontalLayout->addWidget(label);

        mainDeviceName = new QLineEdit(layoutWidget);
        mainDeviceName->setObjectName(QString::fromUtf8("mainDeviceName"));
        mainDeviceName->setMinimumSize(QSize(190, 25));

        horizontalLayout->addWidget(mainDeviceName);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(15);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(150, 0));

        horizontalLayout_2->addWidget(label_2);

        deviceName = new QLineEdit(layoutWidget);
        deviceName->setObjectName(QString::fromUtf8("deviceName"));
        deviceName->setMinimumSize(QSize(190, 0));

        horizontalLayout_2->addWidget(deviceName);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(tlinsWHardwerConfiguration);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(tlinsWHardwerConfiguration);
    } // setupUi

    void retranslateUi(QWidget *tlinsWHardwerConfiguration)
    {
        tlinsWHardwerConfiguration->setWindowTitle(QApplication::translate("tlinsWHardwerConfiguration", "Form", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(encoders), QApplication::translate("tlinsWHardwerConfiguration", "Encoders", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(ctrlGpio), QApplication::translate("tlinsWHardwerConfiguration", "Control GPIO", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(parameters), QApplication::translate("tlinsWHardwerConfiguration", "Parameters", nullptr));
        label->setText(QApplication::translate("tlinsWHardwerConfiguration", "Device name", nullptr));
        label_2->setText(QApplication::translate("tlinsWHardwerConfiguration", "Slave device name (axis)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWHardwerConfiguration: public Ui_tlinsWHardwerConfiguration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWHARDWERCONFIGURATION_H
