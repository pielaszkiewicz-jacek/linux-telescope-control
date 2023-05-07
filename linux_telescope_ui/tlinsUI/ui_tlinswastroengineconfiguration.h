/********************************************************************************
** Form generated from reading UI file 'tlinswastroengineconfiguration.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWASTROENGINECONFIGURATION_H
#define UI_TLINSWASTROENGINECONFIGURATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsWAstroEngineConfiguration
{
public:
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox_3;
    QGroupBox *groupBox_4;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_7;
    QSpinBox *percantageUpdateRunFequency;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_8;
    QSpinBox *runFrequency;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_9;
    QSpinBox *minRunFrequency;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_10;
    QSpinBox *firstRunFrequency;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_11;
    QSpinBox *firstRunFrequencyUpdateCount;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_12;
    QSpinBox *firstRunFrequencyErrorCount;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_13;
    QSpinBox *maxHistoryLength;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_14;
    QSpinBox *frequencyEstimationPeriod;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_15;
    QLineEdit *connUrlRequestResponse;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_16;
    QLineEdit *connUrlNotyfication;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_17;
    QLineEdit *clientConnUrl;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout;
    QLabel *label;
    QDoubleSpinBox *acelerationX;
    QLabel *label_3;
    QDoubleSpinBox *acelerationY;
    QLabel *label_2;
    QDoubleSpinBox *speedX;
    QLabel *label_4;
    QDoubleSpinBox *speedY;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_5;
    QDoubleSpinBox *calibrarionErrorX;
    QLabel *label_6;
    QDoubleSpinBox *calibrarionErrorY;

    void setupUi(QWidget *tlinsWAstroEngineConfiguration)
    {
        if (tlinsWAstroEngineConfiguration->objectName().isEmpty())
            tlinsWAstroEngineConfiguration->setObjectName(QString::fromUtf8("tlinsWAstroEngineConfiguration"));
        tlinsWAstroEngineConfiguration->resize(671, 731);
        groupBox = new QGroupBox(tlinsWAstroEngineConfiguration);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 0, 491, 101));
        QFont font;
        font.setItalic(true);
        groupBox->setFont(font);
        groupBox_2 = new QGroupBox(tlinsWAstroEngineConfiguration);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 110, 491, 71));
        groupBox_2->setFont(font);
        groupBox_3 = new QGroupBox(tlinsWAstroEngineConfiguration);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 190, 491, 371));
        groupBox_3->setFont(font);
        groupBox_4 = new QGroupBox(tlinsWAstroEngineConfiguration);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(20, 570, 641, 151));
        groupBox_4->setFont(font);
        layoutWidget = new QWidget(tlinsWAstroEngineConfiguration);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 220, 354, 323));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(60);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMinimumSize(QSize(190, 0));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        label_7->setFont(font1);

        horizontalLayout_2->addWidget(label_7);

        percantageUpdateRunFequency = new QSpinBox(layoutWidget);
        percantageUpdateRunFequency->setObjectName(QString::fromUtf8("percantageUpdateRunFequency"));
        percantageUpdateRunFequency->setMinimumSize(QSize(100, 0));
        percantageUpdateRunFequency->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        percantageUpdateRunFequency->setMaximum(1000);

        horizontalLayout_2->addWidget(percantageUpdateRunFequency);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(60);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(190, 0));
        label_8->setFont(font1);

        horizontalLayout_3->addWidget(label_8);

        runFrequency = new QSpinBox(layoutWidget);
        runFrequency->setObjectName(QString::fromUtf8("runFrequency"));
        runFrequency->setMinimumSize(QSize(100, 0));
        runFrequency->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        runFrequency->setMaximum(100000);

        horizontalLayout_3->addWidget(runFrequency);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(60);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMinimumSize(QSize(190, 0));
        label_9->setFont(font1);

        horizontalLayout_4->addWidget(label_9);

        minRunFrequency = new QSpinBox(layoutWidget);
        minRunFrequency->setObjectName(QString::fromUtf8("minRunFrequency"));
        minRunFrequency->setMinimumSize(QSize(100, 0));
        minRunFrequency->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        minRunFrequency->setMaximum(100000);

        horizontalLayout_4->addWidget(minRunFrequency);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(60);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMinimumSize(QSize(190, 0));
        label_10->setFont(font1);

        horizontalLayout_5->addWidget(label_10);

        firstRunFrequency = new QSpinBox(layoutWidget);
        firstRunFrequency->setObjectName(QString::fromUtf8("firstRunFrequency"));
        firstRunFrequency->setMinimumSize(QSize(100, 0));
        firstRunFrequency->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        firstRunFrequency->setMaximum(100000);

        horizontalLayout_5->addWidget(firstRunFrequency);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(60);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setMinimumSize(QSize(190, 0));
        label_11->setFont(font1);

        horizontalLayout_6->addWidget(label_11);

        firstRunFrequencyUpdateCount = new QSpinBox(layoutWidget);
        firstRunFrequencyUpdateCount->setObjectName(QString::fromUtf8("firstRunFrequencyUpdateCount"));
        firstRunFrequencyUpdateCount->setMinimumSize(QSize(100, 0));
        firstRunFrequencyUpdateCount->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        firstRunFrequencyUpdateCount->setMaximum(100000);

        horizontalLayout_6->addWidget(firstRunFrequencyUpdateCount);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(60);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_12 = new QLabel(layoutWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setMinimumSize(QSize(190, 0));
        label_12->setFont(font1);

        horizontalLayout_7->addWidget(label_12);

        firstRunFrequencyErrorCount = new QSpinBox(layoutWidget);
        firstRunFrequencyErrorCount->setObjectName(QString::fromUtf8("firstRunFrequencyErrorCount"));
        firstRunFrequencyErrorCount->setMinimumSize(QSize(100, 0));
        firstRunFrequencyErrorCount->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        firstRunFrequencyErrorCount->setMaximum(100000);

        horizontalLayout_7->addWidget(firstRunFrequencyErrorCount);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(60);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_13 = new QLabel(layoutWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setMinimumSize(QSize(190, 0));
        label_13->setFont(font1);

        horizontalLayout_8->addWidget(label_13);

        maxHistoryLength = new QSpinBox(layoutWidget);
        maxHistoryLength->setObjectName(QString::fromUtf8("maxHistoryLength"));
        maxHistoryLength->setMinimumSize(QSize(100, 0));
        maxHistoryLength->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        maxHistoryLength->setMaximum(100000);

        horizontalLayout_8->addWidget(maxHistoryLength);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(60);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_14 = new QLabel(layoutWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setMinimumSize(QSize(190, 0));
        label_14->setFont(font1);

        horizontalLayout_9->addWidget(label_14);

        frequencyEstimationPeriod = new QSpinBox(layoutWidget);
        frequencyEstimationPeriod->setObjectName(QString::fromUtf8("frequencyEstimationPeriod"));
        frequencyEstimationPeriod->setMinimumSize(QSize(100, 0));
        frequencyEstimationPeriod->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        frequencyEstimationPeriod->setMaximum(100000);

        horizontalLayout_9->addWidget(frequencyEstimationPeriod);


        verticalLayout->addLayout(horizontalLayout_9);

        layoutWidget1 = new QWidget(tlinsWAstroEngineConfiguration);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(40, 600, 601, 116));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(15);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(15);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_15 = new QLabel(layoutWidget1);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setMinimumSize(QSize(190, 0));
        label_15->setFont(font1);

        horizontalLayout_10->addWidget(label_15);

        connUrlRequestResponse = new QLineEdit(layoutWidget1);
        connUrlRequestResponse->setObjectName(QString::fromUtf8("connUrlRequestResponse"));

        horizontalLayout_10->addWidget(connUrlRequestResponse);


        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(15);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_16 = new QLabel(layoutWidget1);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setMinimumSize(QSize(190, 0));
        label_16->setFont(font1);

        horizontalLayout_11->addWidget(label_16);

        connUrlNotyfication = new QLineEdit(layoutWidget1);
        connUrlNotyfication->setObjectName(QString::fromUtf8("connUrlNotyfication"));

        horizontalLayout_11->addWidget(connUrlNotyfication);


        verticalLayout_2->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(15);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_17 = new QLabel(layoutWidget1);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setMinimumSize(QSize(190, 0));
        label_17->setFont(font1);

        horizontalLayout_12->addWidget(label_17);

        clientConnUrl = new QLineEdit(layoutWidget1);
        clientConnUrl->setObjectName(QString::fromUtf8("clientConnUrl"));

        horizontalLayout_12->addWidget(clientConnUrl);


        verticalLayout_2->addLayout(horizontalLayout_12);

        layoutWidget2 = new QWidget(tlinsWAstroEngineConfiguration);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(42, 32, 440, 58));
        gridLayout = new QGridLayout(layoutWidget2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(110, 25));
        label->setMaximumSize(QSize(110, 16777215));
        label->setFont(font1);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        acelerationX = new QDoubleSpinBox(layoutWidget2);
        acelerationX->setObjectName(QString::fromUtf8("acelerationX"));
        acelerationX->setMinimumSize(QSize(100, 25));
        acelerationX->setMaximumSize(QSize(100, 25));
        acelerationX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        acelerationX->setDecimals(6);
        acelerationX->setMaximum(1000.000000000000000);

        gridLayout->addWidget(acelerationX, 0, 1, 1, 1);

        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(110, 25));
        label_3->setMaximumSize(QSize(110, 16777215));
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 0, 2, 1, 1);

        acelerationY = new QDoubleSpinBox(layoutWidget2);
        acelerationY->setObjectName(QString::fromUtf8("acelerationY"));
        acelerationY->setMinimumSize(QSize(100, 25));
        acelerationY->setMaximumSize(QSize(100, 25));
        acelerationY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        acelerationY->setDecimals(6);
        acelerationY->setMaximum(1000.000000000000000);

        gridLayout->addWidget(acelerationY, 0, 3, 1, 1);

        label_2 = new QLabel(layoutWidget2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(110, 25));
        label_2->setMaximumSize(QSize(110, 5555555));
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        speedX = new QDoubleSpinBox(layoutWidget2);
        speedX->setObjectName(QString::fromUtf8("speedX"));
        speedX->setMinimumSize(QSize(100, 25));
        speedX->setMaximumSize(QSize(100, 25));
        speedX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        speedX->setDecimals(6);
        speedX->setMaximum(1000.000000000000000);

        gridLayout->addWidget(speedX, 1, 1, 1, 1);

        label_4 = new QLabel(layoutWidget2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(110, 25));
        label_4->setMaximumSize(QSize(110, 5555555));
        label_4->setFont(font1);
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 1, 2, 1, 1);

        speedY = new QDoubleSpinBox(layoutWidget2);
        speedY->setObjectName(QString::fromUtf8("speedY"));
        speedY->setMinimumSize(QSize(100, 25));
        speedY->setMaximumSize(QSize(100, 25));
        speedY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        speedY->setDecimals(6);
        speedY->setMaximum(1000.000000000000000);

        gridLayout->addWidget(speedY, 1, 3, 1, 1);

        layoutWidget3 = new QWidget(tlinsWAstroEngineConfiguration);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(40, 140, 440, 27));
        horizontalLayout = new QHBoxLayout(layoutWidget3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(110, 25));
        label_5->setMaximumSize(QSize(110, 16777215));
        label_5->setFont(font1);
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_5);

        calibrarionErrorX = new QDoubleSpinBox(layoutWidget3);
        calibrarionErrorX->setObjectName(QString::fromUtf8("calibrarionErrorX"));
        calibrarionErrorX->setMinimumSize(QSize(100, 25));
        calibrarionErrorX->setMaximumSize(QSize(100, 25));
        calibrarionErrorX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        calibrarionErrorX->setDecimals(6);
        calibrarionErrorX->setMaximum(1000.000000000000000);

        horizontalLayout->addWidget(calibrarionErrorX);

        label_6 = new QLabel(layoutWidget3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(110, 25));
        label_6->setMaximumSize(QSize(110, 16777215));
        label_6->setFont(font1);
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_6);

        calibrarionErrorY = new QDoubleSpinBox(layoutWidget3);
        calibrarionErrorY->setObjectName(QString::fromUtf8("calibrarionErrorY"));
        calibrarionErrorY->setMinimumSize(QSize(100, 25));
        calibrarionErrorY->setMaximumSize(QSize(100, 25));
        calibrarionErrorY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        calibrarionErrorY->setDecimals(6);
        calibrarionErrorY->setMaximum(1000.000000000000000);

        horizontalLayout->addWidget(calibrarionErrorY);

        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        groupBox_4->raise();
        groupBox_3->raise();
        groupBox->raise();
        groupBox_2->raise();

        retranslateUi(tlinsWAstroEngineConfiguration);

        QMetaObject::connectSlotsByName(tlinsWAstroEngineConfiguration);
    } // setupUi

    void retranslateUi(QWidget *tlinsWAstroEngineConfiguration)
    {
        tlinsWAstroEngineConfiguration->setWindowTitle(QApplication::translate("tlinsWAstroEngineConfiguration", "Form", nullptr));
        groupBox->setTitle(QApplication::translate("tlinsWAstroEngineConfiguration", "Tracking speed and aceleration", nullptr));
        groupBox_2->setTitle(QApplication::translate("tlinsWAstroEngineConfiguration", "Calibration default errors", nullptr));
        groupBox_3->setTitle(QApplication::translate("tlinsWAstroEngineConfiguration", "Tracking engine configuration", nullptr));
        groupBox_4->setTitle(QApplication::translate("tlinsWAstroEngineConfiguration", "Tracking engin connection settings", nullptr));
        label_7->setText(QApplication::translate("tlinsWAstroEngineConfiguration", "Percantage update run fequency", nullptr));
        label_8->setText(QApplication::translate("tlinsWAstroEngineConfiguration", "Run fequency", nullptr));
        label_9->setText(QApplication::translate("tlinsWAstroEngineConfiguration", "Minimum run fequency", nullptr));
        label_10->setText(QApplication::translate("tlinsWAstroEngineConfiguration", "First run fequency", nullptr));
        label_11->setText(QApplication::translate("tlinsWAstroEngineConfiguration", "First run fequency update count", nullptr));
        label_12->setText(QApplication::translate("tlinsWAstroEngineConfiguration", "First run fequency error count", nullptr));
        label_13->setText(QApplication::translate("tlinsWAstroEngineConfiguration", "Max history length", nullptr));
        label_14->setText(QApplication::translate("tlinsWAstroEngineConfiguration", "Frequency estymation period", nullptr));
        label_15->setText(QApplication::translate("tlinsWAstroEngineConfiguration", "Connection URL request-response", nullptr));
        label_16->setText(QApplication::translate("tlinsWAstroEngineConfiguration", "Connection URL notyfications", nullptr));
        label_17->setText(QApplication::translate("tlinsWAstroEngineConfiguration", "Client connection URL", nullptr));
        label->setText(QApplication::translate("tlinsWAstroEngineConfiguration", "Ax", nullptr));
        label_3->setText(QApplication::translate("tlinsWAstroEngineConfiguration", "Ay", nullptr));
        label_2->setText(QApplication::translate("tlinsWAstroEngineConfiguration", "Vx", nullptr));
        label_4->setText(QApplication::translate("tlinsWAstroEngineConfiguration", "Vy", nullptr));
        label_5->setText(QApplication::translate("tlinsWAstroEngineConfiguration", "Calibration error X", nullptr));
        label_6->setText(QApplication::translate("tlinsWAstroEngineConfiguration", "Calibration error Y", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWAstroEngineConfiguration: public Ui_tlinsWAstroEngineConfiguration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWASTROENGINECONFIGURATION_H
