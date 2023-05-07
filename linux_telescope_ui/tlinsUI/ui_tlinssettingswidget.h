/********************************************************************************
** Form generated from reading UI file 'tlinssettingswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSSETTINGSWIDGET_H
#define UI_TLINSSETTINGSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "tlinswcalibrationsettings.h"
#include "tlinswobservationerrorsettings.h"
#include "tlinswpilotsettings.h"
#include "tlinswsettingsconnection.h"
#include "tlinswsettingsdatabase.h"
#include "tlinswsettingsrampparameters.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsSettingsWidget
{
public:
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tabPilot;
    QGridLayout *gridLayout_6;
    QSpacerItem *verticalSpacer_6;
    tlinsWPilotSettings *pilot;
    QWidget *tabObservationErrors;
    QGridLayout *gridLayout_5;
    QSpacerItem *verticalSpacer_4;
    tlinsWObservationErrorSettings *observationErrors;
    QSpacerItem *horizontalSpacer_3;
    QWidget *tabCalibration;
    QGridLayout *gridLayout_3;
    tlinsWCalibrationSettings *calibration;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_5;
    QWidget *tabRampSettings;
    QGridLayout *gridLayout;
    tlinsWSettingsRampParameters *rampConfiguration;
    QSpacerItem *verticalSpacer_3;
    QWidget *tabConnection;
    QGridLayout *gridLayout_2;
    tlinsWSettingsConnection *connectionConfiguration;
    QSpacerItem *verticalSpacer_2;
    QWidget *tabDatabase;
    QGridLayout *gridLayout_4;
    tlinsWSettingsDatabase *databaseConfiguration;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QDialogButtonBox *buttonBox;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *tlinsSettingsWidget)
    {
        if (tlinsSettingsWidget->objectName().isEmpty())
            tlinsSettingsWidget->setObjectName(QString::fromUtf8("tlinsSettingsWidget"));
        tlinsSettingsWidget->resize(672, 491);
        verticalLayout = new QVBoxLayout(tlinsSettingsWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tabWidget = new QTabWidget(tlinsSettingsWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabPilot = new QWidget();
        tabPilot->setObjectName(QString::fromUtf8("tabPilot"));
        gridLayout_6 = new QGridLayout(tabPilot);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_6, 1, 0, 1, 1);

        pilot = new tlinsWPilotSettings(tabPilot);
        pilot->setObjectName(QString::fromUtf8("pilot"));

        gridLayout_6->addWidget(pilot, 0, 0, 1, 1);

        tabWidget->addTab(tabPilot, QString());
        tabObservationErrors = new QWidget();
        tabObservationErrors->setObjectName(QString::fromUtf8("tabObservationErrors"));
        gridLayout_5 = new QGridLayout(tabObservationErrors);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer_4, 1, 0, 1, 1);

        observationErrors = new tlinsWObservationErrorSettings(tabObservationErrors);
        observationErrors->setObjectName(QString::fromUtf8("observationErrors"));

        gridLayout_5->addWidget(observationErrors, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_3, 0, 2, 1, 1);

        tabWidget->addTab(tabObservationErrors, QString());
        tabCalibration = new QWidget();
        tabCalibration->setObjectName(QString::fromUtf8("tabCalibration"));
        gridLayout_3 = new QGridLayout(tabCalibration);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        calibration = new tlinsWCalibrationSettings(tabCalibration);
        calibration->setObjectName(QString::fromUtf8("calibration"));

        gridLayout_3->addWidget(calibration, 0, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 0, 1, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_5, 1, 0, 1, 1);

        tabWidget->addTab(tabCalibration, QString());
        tabRampSettings = new QWidget();
        tabRampSettings->setObjectName(QString::fromUtf8("tabRampSettings"));
        gridLayout = new QGridLayout(tabRampSettings);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        rampConfiguration = new tlinsWSettingsRampParameters(tabRampSettings);
        rampConfiguration->setObjectName(QString::fromUtf8("rampConfiguration"));

        gridLayout->addWidget(rampConfiguration, 0, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 1, 0, 1, 1);

        tabWidget->addTab(tabRampSettings, QString());
        tabConnection = new QWidget();
        tabConnection->setObjectName(QString::fromUtf8("tabConnection"));
        gridLayout_2 = new QGridLayout(tabConnection);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        connectionConfiguration = new tlinsWSettingsConnection(tabConnection);
        connectionConfiguration->setObjectName(QString::fromUtf8("connectionConfiguration"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(connectionConfiguration->sizePolicy().hasHeightForWidth());
        connectionConfiguration->setSizePolicy(sizePolicy);
        connectionConfiguration->setMinimumSize(QSize(100, 0));

        gridLayout_2->addWidget(connectionConfiguration, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 1, 0, 1, 1);

        tabWidget->addTab(tabConnection, QString());
        tabDatabase = new QWidget();
        tabDatabase->setObjectName(QString::fromUtf8("tabDatabase"));
        gridLayout_4 = new QGridLayout(tabDatabase);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        databaseConfiguration = new tlinsWSettingsDatabase(tabDatabase);
        databaseConfiguration->setObjectName(QString::fromUtf8("databaseConfiguration"));

        gridLayout_4->addWidget(databaseConfiguration, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 1, 0, 1, 1);

        tabWidget->addTab(tabDatabase, QString());

        verticalLayout_2->addWidget(tabWidget);


        verticalLayout->addLayout(verticalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        buttonBox = new QDialogButtonBox(tlinsSettingsWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setMinimumSize(QSize(0, 25));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::NoButton);
        buttonBox->setCenterButtons(true);

        horizontalLayout->addWidget(buttonBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(tlinsSettingsWidget);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(tlinsSettingsWidget);
    } // setupUi

    void retranslateUi(QWidget *tlinsSettingsWidget)
    {
        tlinsSettingsWidget->setWindowTitle(QApplication::translate("tlinsSettingsWidget", "Form", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabPilot), QApplication::translate("tlinsSettingsWidget", "Pilot", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabObservationErrors), QApplication::translate("tlinsSettingsWidget", "Observation error", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabCalibration), QApplication::translate("tlinsSettingsWidget", "Calibration", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabRampSettings), QApplication::translate("tlinsSettingsWidget", "Ramp settings", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabConnection), QApplication::translate("tlinsSettingsWidget", "Connection", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabDatabase), QApplication::translate("tlinsSettingsWidget", "Database", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsSettingsWidget: public Ui_tlinsSettingsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSSETTINGSWIDGET_H
