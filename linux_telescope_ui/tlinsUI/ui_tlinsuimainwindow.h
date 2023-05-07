/********************************************************************************
** Form generated from reading UI file 'tlinsuimainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSUIMAINWINDOW_H
#define UI_TLINSUIMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "tlinsstatusicons.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsUIMainWindow
{
public:
    QAction *actionHelp;
    QAction *actionAbout;
    QAction *actionProperties;
    QAction *actionManageDatabase;
    QAction *actionPilot;
    QAction *actionConfiguration;
    QAction *actionCalibration;
    QAction *actionPilot_3;
    QAction *actionConnect_3;
    QAction *actionExit_2;
    QAction *actionIERS;
    QAction *actionObservationPlace;
    QAction *actionEnvironment;
    QAction *actionDateTime;
    QAction *actionShortcuts;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page_3;
    QGridLayout *gridLayout;
    QFrame *line;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_2;
    tlinsStatusIcons *statusWidget;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menuBar;
    QToolBar *toolBar;
    QToolBar *toolBar_2;

    void setupUi(QMainWindow *tlinsUIMainWindow)
    {
        if (tlinsUIMainWindow->objectName().isEmpty())
            tlinsUIMainWindow->setObjectName(QString::fromUtf8("tlinsUIMainWindow"));
        tlinsUIMainWindow->resize(1068, 722);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tlinsUIMainWindow->sizePolicy().hasHeightForWidth());
        tlinsUIMainWindow->setSizePolicy(sizePolicy);
        tlinsUIMainWindow->setUnifiedTitleAndToolBarOnMac(false);
        actionHelp = new QAction(tlinsUIMainWindow);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        actionAbout = new QAction(tlinsUIMainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionProperties = new QAction(tlinsUIMainWindow);
        actionProperties->setObjectName(QString::fromUtf8("actionProperties"));
        actionManageDatabase = new QAction(tlinsUIMainWindow);
        actionManageDatabase->setObjectName(QString::fromUtf8("actionManageDatabase"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/database.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionManageDatabase->setIcon(icon);
        actionPilot = new QAction(tlinsUIMainWindow);
        actionPilot->setObjectName(QString::fromUtf8("actionPilot"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/remote-control.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionPilot->setIcon(icon1);
        actionConfiguration = new QAction(tlinsUIMainWindow);
        actionConfiguration->setObjectName(QString::fromUtf8("actionConfiguration"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/settings.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionConfiguration->setIcon(icon2);
        actionCalibration = new QAction(tlinsUIMainWindow);
        actionCalibration->setObjectName(QString::fromUtf8("actionCalibration"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/calibration-mark.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionCalibration->setIcon(icon3);
        actionPilot_3 = new QAction(tlinsUIMainWindow);
        actionPilot_3->setObjectName(QString::fromUtf8("actionPilot_3"));
        actionConnect_3 = new QAction(tlinsUIMainWindow);
        actionConnect_3->setObjectName(QString::fromUtf8("actionConnect_3"));
        actionExit_2 = new QAction(tlinsUIMainWindow);
        actionExit_2->setObjectName(QString::fromUtf8("actionExit_2"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/exit.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit_2->setIcon(icon4);
        actionIERS = new QAction(tlinsUIMainWindow);
        actionIERS->setObjectName(QString::fromUtf8("actionIERS"));
        actionObservationPlace = new QAction(tlinsUIMainWindow);
        actionObservationPlace->setObjectName(QString::fromUtf8("actionObservationPlace"));
        actionEnvironment = new QAction(tlinsUIMainWindow);
        actionEnvironment->setObjectName(QString::fromUtf8("actionEnvironment"));
        actionDateTime = new QAction(tlinsUIMainWindow);
        actionDateTime->setObjectName(QString::fromUtf8("actionDateTime"));
        actionShortcuts = new QAction(tlinsUIMainWindow);
        actionShortcuts->setObjectName(QString::fromUtf8("actionShortcuts"));
        centralWidget = new QWidget(tlinsUIMainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        centralWidget->setMinimumSize(QSize(0, 0));
        centralWidget->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Ignored);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy2);
        stackedWidget->setMaximumSize(QSize(16777215, 16777215));
        stackedWidget->setFrameShadow(QFrame::Plain);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        sizePolicy1.setHeightForWidth(page_3->sizePolicy().hasHeightForWidth());
        page_3->setSizePolicy(sizePolicy1);
        page_3->setMaximumSize(QSize(16777215, 16777215));
        gridLayout = new QGridLayout(page_3);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        stackedWidget->addWidget(page_3);

        verticalLayout->addWidget(stackedWidget);

        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        statusWidget = new tlinsStatusIcons(centralWidget);
        statusWidget->setObjectName(QString::fromUtf8("statusWidget"));

        horizontalLayout_5->addWidget(statusWidget);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_5);

        tlinsUIMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(tlinsUIMainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1068, 25));
        tlinsUIMainWindow->setMenuBar(menuBar);
        toolBar = new QToolBar(tlinsUIMainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(toolBar->sizePolicy().hasHeightForWidth());
        toolBar->setSizePolicy(sizePolicy3);
        toolBar->setMinimumSize(QSize(0, 0));
        toolBar->setStyleSheet(QString::fromUtf8(""));
        toolBar->setMovable(false);
        toolBar->setAllowedAreas(Qt::NoToolBarArea);
        toolBar->setOrientation(Qt::Vertical);
        toolBar->setIconSize(QSize(32, 32));
        toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolBar->setFloatable(false);
        tlinsUIMainWindow->addToolBar(Qt::LeftToolBarArea, toolBar);
        toolBar_2 = new QToolBar(tlinsUIMainWindow);
        toolBar_2->setObjectName(QString::fromUtf8("toolBar_2"));
        sizePolicy3.setHeightForWidth(toolBar_2->sizePolicy().hasHeightForWidth());
        toolBar_2->setSizePolicy(sizePolicy3);
        toolBar_2->setMinimumSize(QSize(0, 0));
        toolBar_2->setMovable(false);
        toolBar_2->setAllowedAreas(Qt::NoToolBarArea);
        toolBar_2->setOrientation(Qt::Vertical);
        toolBar_2->setIconSize(QSize(32, 32));
        toolBar_2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolBar_2->setFloatable(false);
        tlinsUIMainWindow->addToolBar(Qt::RightToolBarArea, toolBar_2);

        toolBar_2->addSeparator();

        retranslateUi(tlinsUIMainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(tlinsUIMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *tlinsUIMainWindow)
    {
        tlinsUIMainWindow->setWindowTitle(QApplication::translate("tlinsUIMainWindow", "tlinsUIMainWindow", nullptr));
        actionHelp->setText(QApplication::translate("tlinsUIMainWindow", "Help", nullptr));
        actionAbout->setText(QApplication::translate("tlinsUIMainWindow", "About", nullptr));
        actionProperties->setText(QApplication::translate("tlinsUIMainWindow", "Properties", nullptr));
        actionManageDatabase->setText(QApplication::translate("tlinsUIMainWindow", "Database", nullptr));
        actionPilot->setText(QApplication::translate("tlinsUIMainWindow", "        Pilot       ", nullptr));
        actionConfiguration->setText(QApplication::translate("tlinsUIMainWindow", "Configuration", nullptr));
        actionCalibration->setText(QApplication::translate("tlinsUIMainWindow", "Calibration", nullptr));
        actionPilot_3->setText(QApplication::translate("tlinsUIMainWindow", "Pilot", nullptr));
        actionConnect_3->setText(QApplication::translate("tlinsUIMainWindow", "Connect", nullptr));
        actionExit_2->setText(QApplication::translate("tlinsUIMainWindow", "Exit", nullptr));
        actionIERS->setText(QApplication::translate("tlinsUIMainWindow", "IERS", nullptr));
        actionObservationPlace->setText(QApplication::translate("tlinsUIMainWindow", "Observation place", nullptr));
        actionEnvironment->setText(QApplication::translate("tlinsUIMainWindow", "Environment", nullptr));
        actionDateTime->setText(QApplication::translate("tlinsUIMainWindow", "Date time", nullptr));
        actionShortcuts->setText(QApplication::translate("tlinsUIMainWindow", "Pilot shortcuts", nullptr));
        toolBar->setWindowTitle(QApplication::translate("tlinsUIMainWindow", "toolBar", nullptr));
        toolBar_2->setWindowTitle(QApplication::translate("tlinsUIMainWindow", "toolBar_2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsUIMainWindow: public Ui_tlinsUIMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSUIMAINWINDOW_H
