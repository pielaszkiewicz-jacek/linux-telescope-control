/********************************************************************************
** Form generated from reading UI file 'tlinswsettingsconnection.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWSETTINGSCONNECTION_H
#define UI_TLINSWSETTINGSCONNECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <tlinswdecimalvalue.h>

QT_BEGIN_NAMESPACE

class Ui_tlinsWSettingsConnection
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QCheckBox *sysMonitorAutoConnectDisconnect;
    QGroupBox *groupBoxAddresses;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout_4;
    QLineEdit *urlDeviceEngineAsynch;
    QLabel *label_5;
    QLineEdit *urlDeviceEngine;
    QLineEdit *urlAstroEngine;
    QLabel *label_4;
    QComboBox *deviceEngineAsyncAuthType;
    QLineEdit *urlSystemService;
    QComboBox *systemServiceAuthType;
    QComboBox *astroEngineAsyncAuthType;
    QComboBox *astroEngineAuthType;
    QLabel *label_2;
    QLabel *label;
    QComboBox *deviceEngineAuthType;
    QLabel *label_3;
    QLineEdit *urlAstroEngineAsynch;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *commonAddress;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_5;
    tlinsWDecimalValue *astroEngineAsyncPort;
    QSpacerItem *horizontalSpacer;
    tlinsWDecimalValue *astroEnginePort;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_10;
    tlinsWDecimalValue *systemServicePort;
    tlinsWDecimalValue *deviceEnginePort;
    tlinsWDecimalValue *deviceEngineAsyncPort;
    QLabel *label_11;
    QLabel *label_9;
    QLabel *label_6;
    QLineEdit *commonAddressIp;
    QSpacerItem *verticalSpacer;
    QCheckBox *useCommonAddressIp;

    void setupUi(QWidget *tlinsWSettingsConnection)
    {
        if (tlinsWSettingsConnection->objectName().isEmpty())
            tlinsWSettingsConnection->setObjectName(QString::fromUtf8("tlinsWSettingsConnection"));
        tlinsWSettingsConnection->resize(754, 509);
        gridLayout = new QGridLayout(tlinsWSettingsConnection);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(tlinsWSettingsConnection);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, -1, 5);
        sysMonitorAutoConnectDisconnect = new QCheckBox(groupBox);
        sysMonitorAutoConnectDisconnect->setObjectName(QString::fromUtf8("sysMonitorAutoConnectDisconnect"));
        sysMonitorAutoConnectDisconnect->setLayoutDirection(Qt::LeftToRight);

        verticalLayout->addWidget(sysMonitorAutoConnectDisconnect);


        gridLayout->addWidget(groupBox, 4, 0, 1, 1);

        groupBoxAddresses = new QGroupBox(tlinsWSettingsConnection);
        groupBoxAddresses->setObjectName(QString::fromUtf8("groupBoxAddresses"));
        verticalLayout_2 = new QVBoxLayout(groupBoxAddresses);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        urlDeviceEngineAsynch = new QLineEdit(groupBoxAddresses);
        urlDeviceEngineAsynch->setObjectName(QString::fromUtf8("urlDeviceEngineAsynch"));

        gridLayout_4->addWidget(urlDeviceEngineAsynch, 4, 2, 1, 1);

        label_5 = new QLabel(groupBoxAddresses);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QFont font;
        font.setPointSize(10);
        label_5->setFont(font);

        gridLayout_4->addWidget(label_5, 3, 0, 1, 1);

        urlDeviceEngine = new QLineEdit(groupBoxAddresses);
        urlDeviceEngine->setObjectName(QString::fromUtf8("urlDeviceEngine"));
        urlDeviceEngine->setMinimumSize(QSize(0, 0));
        urlDeviceEngine->setFont(font);
        urlDeviceEngine->setFrame(true);

        gridLayout_4->addWidget(urlDeviceEngine, 3, 2, 1, 1);

        urlAstroEngine = new QLineEdit(groupBoxAddresses);
        urlAstroEngine->setObjectName(QString::fromUtf8("urlAstroEngine"));
        urlAstroEngine->setMinimumSize(QSize(0, 0));
        urlAstroEngine->setFont(font);
        urlAstroEngine->setFrame(true);

        gridLayout_4->addWidget(urlAstroEngine, 1, 2, 1, 1);

        label_4 = new QLabel(groupBoxAddresses);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_4->addWidget(label_4, 5, 0, 1, 1);

        deviceEngineAsyncAuthType = new QComboBox(groupBoxAddresses);
        deviceEngineAsyncAuthType->setObjectName(QString::fromUtf8("deviceEngineAsyncAuthType"));
        deviceEngineAsyncAuthType->setEnabled(false);

        gridLayout_4->addWidget(deviceEngineAsyncAuthType, 4, 3, 1, 1);

        urlSystemService = new QLineEdit(groupBoxAddresses);
        urlSystemService->setObjectName(QString::fromUtf8("urlSystemService"));

        gridLayout_4->addWidget(urlSystemService, 5, 2, 1, 1);

        systemServiceAuthType = new QComboBox(groupBoxAddresses);
        systemServiceAuthType->setObjectName(QString::fromUtf8("systemServiceAuthType"));

        gridLayout_4->addWidget(systemServiceAuthType, 5, 3, 1, 1);

        astroEngineAsyncAuthType = new QComboBox(groupBoxAddresses);
        astroEngineAsyncAuthType->setObjectName(QString::fromUtf8("astroEngineAsyncAuthType"));
        astroEngineAsyncAuthType->setEnabled(false);

        gridLayout_4->addWidget(astroEngineAsyncAuthType, 2, 3, 1, 1);

        astroEngineAuthType = new QComboBox(groupBoxAddresses);
        astroEngineAuthType->setObjectName(QString::fromUtf8("astroEngineAuthType"));
        astroEngineAuthType->setEnabled(false);

        gridLayout_4->addWidget(astroEngineAuthType, 1, 3, 1, 1);

        label_2 = new QLabel(groupBoxAddresses);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_4->addWidget(label_2, 4, 0, 1, 1);

        label = new QLabel(groupBoxAddresses);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_4->addWidget(label, 2, 0, 1, 1);

        deviceEngineAuthType = new QComboBox(groupBoxAddresses);
        deviceEngineAuthType->setObjectName(QString::fromUtf8("deviceEngineAuthType"));
        deviceEngineAuthType->setEnabled(false);

        gridLayout_4->addWidget(deviceEngineAuthType, 3, 3, 1, 1);

        label_3 = new QLabel(groupBoxAddresses);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        gridLayout_4->addWidget(label_3, 1, 0, 1, 1);

        urlAstroEngineAsynch = new QLineEdit(groupBoxAddresses);
        urlAstroEngineAsynch->setObjectName(QString::fromUtf8("urlAstroEngineAsynch"));

        gridLayout_4->addWidget(urlAstroEngineAsynch, 2, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 3, 4, 1, 1);


        verticalLayout_2->addLayout(gridLayout_4);


        gridLayout->addWidget(groupBoxAddresses, 2, 0, 1, 1);

        commonAddress = new QGroupBox(tlinsWSettingsConnection);
        commonAddress->setObjectName(QString::fromUtf8("commonAddress"));
        verticalLayout_3 = new QVBoxLayout(commonAddress);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));

        verticalLayout_3->addLayout(gridLayout_3);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        astroEngineAsyncPort = new tlinsWDecimalValue(commonAddress);
        astroEngineAsyncPort->setObjectName(QString::fromUtf8("astroEngineAsyncPort"));

        gridLayout_5->addWidget(astroEngineAsyncPort, 2, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 5, 2, 1, 1);

        astroEnginePort = new tlinsWDecimalValue(commonAddress);
        astroEnginePort->setObjectName(QString::fromUtf8("astroEnginePort"));

        gridLayout_5->addWidget(astroEnginePort, 1, 1, 1, 1);

        label_7 = new QLabel(commonAddress);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_5->addWidget(label_7, 1, 0, 1, 1);

        label_8 = new QLabel(commonAddress);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_5->addWidget(label_8, 2, 0, 1, 1);

        label_10 = new QLabel(commonAddress);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_5->addWidget(label_10, 4, 0, 1, 1);

        systemServicePort = new tlinsWDecimalValue(commonAddress);
        systemServicePort->setObjectName(QString::fromUtf8("systemServicePort"));

        gridLayout_5->addWidget(systemServicePort, 5, 1, 1, 1);

        deviceEnginePort = new tlinsWDecimalValue(commonAddress);
        deviceEnginePort->setObjectName(QString::fromUtf8("deviceEnginePort"));

        gridLayout_5->addWidget(deviceEnginePort, 3, 1, 1, 1);

        deviceEngineAsyncPort = new tlinsWDecimalValue(commonAddress);
        deviceEngineAsyncPort->setObjectName(QString::fromUtf8("deviceEngineAsyncPort"));

        gridLayout_5->addWidget(deviceEngineAsyncPort, 4, 1, 1, 1);

        label_11 = new QLabel(commonAddress);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_5->addWidget(label_11, 5, 0, 1, 1);

        label_9 = new QLabel(commonAddress);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_5->addWidget(label_9, 3, 0, 1, 1);

        label_6 = new QLabel(commonAddress);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_5->addWidget(label_6, 0, 0, 1, 1);

        commonAddressIp = new QLineEdit(commonAddress);
        commonAddressIp->setObjectName(QString::fromUtf8("commonAddressIp"));

        gridLayout_5->addWidget(commonAddressIp, 0, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout_5);


        gridLayout->addWidget(commonAddress, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout->addItem(verticalSpacer, 3, 0, 1, 1);

        useCommonAddressIp = new QCheckBox(tlinsWSettingsConnection);
        useCommonAddressIp->setObjectName(QString::fromUtf8("useCommonAddressIp"));

        gridLayout->addWidget(useCommonAddressIp, 0, 0, 1, 1);


        retranslateUi(tlinsWSettingsConnection);
        QObject::connect(useCommonAddressIp, SIGNAL(clicked(bool)), tlinsWSettingsConnection, SLOT(useCommonIp(bool)));

        QMetaObject::connectSlotsByName(tlinsWSettingsConnection);
    } // setupUi

    void retranslateUi(QWidget *tlinsWSettingsConnection)
    {
        tlinsWSettingsConnection->setWindowTitle(QApplication::translate("tlinsWSettingsConnection", "Form", nullptr));
        groupBox->setTitle(QApplication::translate("tlinsWSettingsConnection", "System event monitor (keyboard and joystick)", nullptr));
        sysMonitorAutoConnectDisconnect->setText(QApplication::translate("tlinsWSettingsConnection", "Connect/disconnect automatically", nullptr));
        groupBoxAddresses->setTitle(QString());
        label_5->setText(QApplication::translate("tlinsWSettingsConnection", "Device engine address", nullptr));
        label_4->setText(QApplication::translate("tlinsWSettingsConnection", "System service", nullptr));
        label_2->setText(QApplication::translate("tlinsWSettingsConnection", "Device engine address asynch", nullptr));
        label->setText(QApplication::translate("tlinsWSettingsConnection", "Astro engine address asynch", nullptr));
        label_3->setText(QApplication::translate("tlinsWSettingsConnection", "Astro engine address", nullptr));
        commonAddress->setTitle(QString());
        label_7->setText(QApplication::translate("tlinsWSettingsConnection", "Astro engine port", nullptr));
        label_8->setText(QApplication::translate("tlinsWSettingsConnection", "Astro engine asynch port", nullptr));
        label_10->setText(QApplication::translate("tlinsWSettingsConnection", "Device engine asynch port", nullptr));
        label_11->setText(QApplication::translate("tlinsWSettingsConnection", "System service port", nullptr));
        label_9->setText(QApplication::translate("tlinsWSettingsConnection", "Device engine port", nullptr));
        label_6->setText(QApplication::translate("tlinsWSettingsConnection", "Address IP", nullptr));
        useCommonAddressIp->setText(QApplication::translate("tlinsWSettingsConnection", "Use the same address", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWSettingsConnection: public Ui_tlinsWSettingsConnection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWSETTINGSCONNECTION_H
