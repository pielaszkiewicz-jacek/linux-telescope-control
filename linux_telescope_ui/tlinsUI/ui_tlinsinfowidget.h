/********************************************************************************
** Form generated from reading UI file 'tlinsinfowidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSINFOWIDGET_H
#define UI_TLINSINFOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <tlinswdecimalvalue.h>
#include "tlinswcoordinatedeclination.h"
#include "tlinswcoordinatedegris.h"
#include "tlinswcoordinatehourangle.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsInfoWidget
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_7;
    QPushButton *reloadPB;
    QPushButton *storePB;
    QPushButton *updatePB;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *loadPB;
    QSpacerItem *horizontalSpacer_5;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_8;
    tlinsWCoordinateDeclination *decDelta;
    tlinsWDecimalValue *scaleX;
    QLabel *label_30;
    QLabel *label_36;
    tlinsWCoordinateDegris *xDegrisSpeed;
    QLabel *label_26;
    QLabel *label_8;
    QLabel *label_21;
    QLabel *label_17;
    tlinsWDecimalValue *yStepsDelta;
    tlinsWCoordinateDegris *xDegrisDelta;
    QLabel *label_15;
    QLabel *label_23;
    QLabel *label_19;
    QLabel *label_28;
    QLabel *label_20;
    tlinsWDecimalValue *xStepsDelta;
    tlinsWCoordinateDeclination *decSpeed;
    QLabel *label_16;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_27;
    QLabel *label_13;
    QLabel *label_10;
    tlinsWCoordinateHourAngle *raSpeed;
    QLabel *label_7;
    QLabel *label_9;
    QLabel *label_29;
    tlinsWCoordinateDegris *yDegrisDelta;
    QLabel *label_22;
    QLabel *label_12;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_5;
    tlinsWDecimalValue *xStepsSpeed;
    QLabel *label_33;
    QLabel *label_34;
    QLabel *label_24;
    tlinsWCoordinateDegris *yDegrisSpeed;
    QLabel *label_35;
    QLabel *label_14;
    tlinsWCoordinateHourAngle *raDelta;
    QLabel *label_25;
    QLabel *label_6;
    tlinsWDecimalValue *scaleY;
    tlinsWDecimalValue *yStepsSpeed;
    QSpacerItem *verticalSpacer_8;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QTextEdit *textEdit;
    QPushButton *pbClear;
    QWidget *tab_5;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer_7;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_6;
    QLineEdit *directoryEdit;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *downloadButton;
    QSpacerItem *horizontalSpacer_14;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *directorySelectionButton;
    QCheckBox *removeAfterDownload;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_9;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_18;
    tlinsWDecimalValue *numberFilesToLeave;
    QSpacerItem *horizontalSpacer_13;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_15;
    QPushButton *removeFilesButton;
    QSpacerItem *horizontalSpacer_16;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_10;
    QSpacerItem *horizontalSpacer_18;
    tlinsWDecimalValue *baseInterval;
    QLabel *label_31;
    QCheckBox *checkBox_2;
    QSpacerItem *horizontalSpacer_19;
    QPushButton *pushButton_3;
    QSpacerItem *verticalSpacer_6;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QLineEdit *updateInputFile;
    QPushButton *sofUpdateSelectFile;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *sofUpdatePerfome;
    QSpacerItem *horizontalSpacer_12;
    QSpacerItem *verticalSpacer_5;
    QLabel *label_11;
    QTextEdit *updateDetails;
    QCheckBox *sendUpdateLogsIntoAppLog;
    QSpacerItem *verticalSpacer;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_3;
    QTextEdit *textEdit_4;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_13;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer_14;
    QPushButton *pushButton_5;
    QSpacerItem *verticalSpacer_12;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_4;
    QTextEdit *textEdit_3;
    QVBoxLayout *verticalLayout_6;
    QSpacerItem *verticalSpacer_10;
    QPushButton *pushButton_2;
    QSpacerItem *verticalSpacer_15;
    QPushButton *pushButton_7;
    QSpacerItem *verticalSpacer_11;
    QGroupBox *groupBox_6;
    QHBoxLayout *horizontalLayout_8;
    QTextEdit *textEdit_2;
    QVBoxLayout *verticalLayout_7;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton_10;
    QSpacerItem *verticalSpacer_16;
    QPushButton *pushButton_9;
    QSpacerItem *verticalSpacer_9;

    void setupUi(QWidget *tlinsInfoWidget)
    {
        if (tlinsInfoWidget->objectName().isEmpty())
            tlinsInfoWidget->setObjectName(QString::fromUtf8("tlinsInfoWidget"));
        tlinsInfoWidget->resize(1053, 748);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tlinsInfoWidget->sizePolicy().hasHeightForWidth());
        tlinsInfoWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(tlinsInfoWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(tlinsInfoWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayout_5 = new QGridLayout(tab_3);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(24);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setContentsMargins(24, 12, 24, 12);
        reloadPB = new QPushButton(tab_3);
        reloadPB->setObjectName(QString::fromUtf8("reloadPB"));
        reloadPB->setMinimumSize(QSize(140, 40));

        gridLayout_7->addWidget(reloadPB, 0, 3, 1, 1);

        storePB = new QPushButton(tab_3);
        storePB->setObjectName(QString::fromUtf8("storePB"));
        storePB->setMinimumSize(QSize(140, 40));

        gridLayout_7->addWidget(storePB, 0, 4, 1, 1);

        updatePB = new QPushButton(tab_3);
        updatePB->setObjectName(QString::fromUtf8("updatePB"));
        updatePB->setMinimumSize(QSize(140, 40));

        gridLayout_7->addWidget(updatePB, 0, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_3, 0, 0, 1, 1);

        loadPB = new QPushButton(tab_3);
        loadPB->setObjectName(QString::fromUtf8("loadPB"));
        loadPB->setMinimumSize(QSize(140, 40));

        gridLayout_7->addWidget(loadPB, 0, 5, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_5, 0, 6, 1, 1);


        gridLayout_5->addLayout(gridLayout_7, 1, 0, 1, 1);

        scrollArea_2 = new QScrollArea(tab_3);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 1011, 607));
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        gridLayout_8 = new QGridLayout();
        gridLayout_8->setSpacing(6);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_8->setContentsMargins(6, 6, 6, 6);
        decDelta = new tlinsWCoordinateDeclination(scrollAreaWidgetContents_2);
        decDelta->setObjectName(QString::fromUtf8("decDelta"));
        decDelta->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(decDelta->sizePolicy().hasHeightForWidth());
        decDelta->setSizePolicy(sizePolicy1);
        decDelta->setMinimumSize(QSize(0, 0));

        gridLayout_8->addWidget(decDelta, 1, 2, 1, 1);

        scaleX = new tlinsWDecimalValue(scrollAreaWidgetContents_2);
        scaleX->setObjectName(QString::fromUtf8("scaleX"));
        sizePolicy1.setHeightForWidth(scaleX->sizePolicy().hasHeightForWidth());
        scaleX->setSizePolicy(sizePolicy1);

        gridLayout_8->addWidget(scaleX, 12, 2, 1, 1);

        label_30 = new QLabel(scrollAreaWidgetContents_2);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        sizePolicy1.setHeightForWidth(label_30->sizePolicy().hasHeightForWidth());
        label_30->setSizePolicy(sizePolicy1);
        label_30->setMinimumSize(QSize(0, 0));
        label_30->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_30, 11, 3, 1, 1);

        label_36 = new QLabel(scrollAreaWidgetContents_2);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        sizePolicy1.setHeightForWidth(label_36->sizePolicy().hasHeightForWidth());
        label_36->setSizePolicy(sizePolicy1);
        label_36->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_36, 13, 3, 1, 1);

        xDegrisSpeed = new tlinsWCoordinateDegris(scrollAreaWidgetContents_2);
        xDegrisSpeed->setObjectName(QString::fromUtf8("xDegrisSpeed"));
        xDegrisSpeed->setEnabled(true);
        sizePolicy1.setHeightForWidth(xDegrisSpeed->sizePolicy().hasHeightForWidth());
        xDegrisSpeed->setSizePolicy(sizePolicy1);
        xDegrisSpeed->setMinimumSize(QSize(0, 0));

        gridLayout_8->addWidget(xDegrisSpeed, 6, 2, 1, 1);

        label_26 = new QLabel(scrollAreaWidgetContents_2);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        sizePolicy1.setHeightForWidth(label_26->sizePolicy().hasHeightForWidth());
        label_26->setSizePolicy(sizePolicy1);
        label_26->setMinimumSize(QSize(0, 0));
        label_26->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_26, 7, 3, 1, 1);

        label_8 = new QLabel(scrollAreaWidgetContents_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy2);
        label_8->setMinimumSize(QSize(100, 0));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_8, 3, 1, 1, 1);

        label_21 = new QLabel(scrollAreaWidgetContents_2);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        sizePolicy1.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
        label_21->setSizePolicy(sizePolicy1);
        label_21->setMinimumSize(QSize(0, 0));
        label_21->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_21, 2, 3, 1, 1);

        label_17 = new QLabel(scrollAreaWidgetContents_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        sizePolicy2.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
        label_17->setSizePolicy(sizePolicy2);
        label_17->setMinimumSize(QSize(100, 0));
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_17, 11, 1, 1, 1);

        yStepsDelta = new tlinsWDecimalValue(scrollAreaWidgetContents_2);
        yStepsDelta->setObjectName(QString::fromUtf8("yStepsDelta"));
        yStepsDelta->setEnabled(true);
        sizePolicy1.setHeightForWidth(yStepsDelta->sizePolicy().hasHeightForWidth());
        yStepsDelta->setSizePolicy(sizePolicy1);
        yStepsDelta->setMinimumSize(QSize(0, 0));

        gridLayout_8->addWidget(yStepsDelta, 9, 2, 1, 1);

        xDegrisDelta = new tlinsWCoordinateDegris(scrollAreaWidgetContents_2);
        xDegrisDelta->setObjectName(QString::fromUtf8("xDegrisDelta"));
        xDegrisDelta->setEnabled(true);
        sizePolicy1.setHeightForWidth(xDegrisDelta->sizePolicy().hasHeightForWidth());
        xDegrisDelta->setSizePolicy(sizePolicy1);
        xDegrisDelta->setMinimumSize(QSize(0, 0));

        gridLayout_8->addWidget(xDegrisDelta, 4, 2, 1, 1);

        label_15 = new QLabel(scrollAreaWidgetContents_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        sizePolicy2.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy2);
        label_15->setMinimumSize(QSize(100, 0));
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_15, 5, 1, 1, 1);

        label_23 = new QLabel(scrollAreaWidgetContents_2);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        sizePolicy1.setHeightForWidth(label_23->sizePolicy().hasHeightForWidth());
        label_23->setSizePolicy(sizePolicy1);
        label_23->setMinimumSize(QSize(0, 0));
        label_23->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_23, 4, 3, 1, 1);

        label_19 = new QLabel(scrollAreaWidgetContents_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        sizePolicy1.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
        label_19->setSizePolicy(sizePolicy1);
        label_19->setMinimumSize(QSize(0, 0));
        label_19->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_19, 1, 3, 1, 1);

        label_28 = new QLabel(scrollAreaWidgetContents_2);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        sizePolicy1.setHeightForWidth(label_28->sizePolicy().hasHeightForWidth());
        label_28->setSizePolicy(sizePolicy1);
        label_28->setMinimumSize(QSize(0, 0));
        label_28->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_28, 9, 3, 1, 1);

        label_20 = new QLabel(scrollAreaWidgetContents_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        sizePolicy1.setHeightForWidth(label_20->sizePolicy().hasHeightForWidth());
        label_20->setSizePolicy(sizePolicy1);
        label_20->setMinimumSize(QSize(0, 0));
        label_20->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_20, 0, 3, 1, 1);

        xStepsDelta = new tlinsWDecimalValue(scrollAreaWidgetContents_2);
        xStepsDelta->setObjectName(QString::fromUtf8("xStepsDelta"));
        xStepsDelta->setEnabled(true);
        sizePolicy1.setHeightForWidth(xStepsDelta->sizePolicy().hasHeightForWidth());
        xStepsDelta->setSizePolicy(sizePolicy1);
        xStepsDelta->setMinimumSize(QSize(0, 0));

        gridLayout_8->addWidget(xStepsDelta, 8, 2, 1, 1);

        decSpeed = new tlinsWCoordinateDeclination(scrollAreaWidgetContents_2);
        decSpeed->setObjectName(QString::fromUtf8("decSpeed"));
        decSpeed->setEnabled(true);
        sizePolicy1.setHeightForWidth(decSpeed->sizePolicy().hasHeightForWidth());
        decSpeed->setSizePolicy(sizePolicy1);
        decSpeed->setMinimumSize(QSize(0, 0));

        gridLayout_8->addWidget(decSpeed, 3, 2, 1, 1);

        label_16 = new QLabel(scrollAreaWidgetContents_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        sizePolicy2.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy2);
        label_16->setMinimumSize(QSize(100, 0));
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_16, 9, 1, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(100, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_8, 6, 4, 1, 1);

        label_27 = new QLabel(scrollAreaWidgetContents_2);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        sizePolicy1.setHeightForWidth(label_27->sizePolicy().hasHeightForWidth());
        label_27->setSizePolicy(sizePolicy1);
        label_27->setMinimumSize(QSize(0, 0));
        label_27->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_27, 8, 3, 1, 1);

        label_13 = new QLabel(scrollAreaWidgetContents_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        sizePolicy2.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy2);
        label_13->setMinimumSize(QSize(100, 0));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_13, 7, 1, 1, 1);

        label_10 = new QLabel(scrollAreaWidgetContents_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy2.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy2);
        label_10->setMinimumSize(QSize(100, 0));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_10, 10, 1, 1, 1);

        raSpeed = new tlinsWCoordinateHourAngle(scrollAreaWidgetContents_2);
        raSpeed->setObjectName(QString::fromUtf8("raSpeed"));
        raSpeed->setEnabled(true);
        sizePolicy1.setHeightForWidth(raSpeed->sizePolicy().hasHeightForWidth());
        raSpeed->setSizePolicy(sizePolicy1);
        raSpeed->setMinimumSize(QSize(0, 0));

        gridLayout_8->addWidget(raSpeed, 2, 2, 1, 1);

        label_7 = new QLabel(scrollAreaWidgetContents_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy2.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy2);
        label_7->setMinimumSize(QSize(100, 0));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_7, 2, 1, 1, 1);

        label_9 = new QLabel(scrollAreaWidgetContents_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy2.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy2);
        label_9->setMinimumSize(QSize(100, 0));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_9, 4, 1, 1, 1);

        label_29 = new QLabel(scrollAreaWidgetContents_2);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        sizePolicy1.setHeightForWidth(label_29->sizePolicy().hasHeightForWidth());
        label_29->setSizePolicy(sizePolicy1);
        label_29->setMinimumSize(QSize(0, 0));
        label_29->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_29, 10, 3, 1, 1);

        yDegrisDelta = new tlinsWCoordinateDegris(scrollAreaWidgetContents_2);
        yDegrisDelta->setObjectName(QString::fromUtf8("yDegrisDelta"));
        yDegrisDelta->setEnabled(true);
        sizePolicy1.setHeightForWidth(yDegrisDelta->sizePolicy().hasHeightForWidth());
        yDegrisDelta->setSizePolicy(sizePolicy1);
        yDegrisDelta->setMinimumSize(QSize(0, 0));

        gridLayout_8->addWidget(yDegrisDelta, 5, 2, 1, 1);

        label_22 = new QLabel(scrollAreaWidgetContents_2);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        sizePolicy1.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
        label_22->setSizePolicy(sizePolicy1);
        label_22->setMinimumSize(QSize(0, 0));
        label_22->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_22, 3, 3, 1, 1);

        label_12 = new QLabel(scrollAreaWidgetContents_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        sizePolicy2.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy2);
        label_12->setMinimumSize(QSize(100, 0));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_12, 8, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(100, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_7, 6, 0, 1, 1);

        label_5 = new QLabel(scrollAreaWidgetContents_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);
        label_5->setMinimumSize(QSize(100, 0));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_5, 0, 1, 1, 1);

        xStepsSpeed = new tlinsWDecimalValue(scrollAreaWidgetContents_2);
        xStepsSpeed->setObjectName(QString::fromUtf8("xStepsSpeed"));
        xStepsSpeed->setEnabled(true);
        sizePolicy1.setHeightForWidth(xStepsSpeed->sizePolicy().hasHeightForWidth());
        xStepsSpeed->setSizePolicy(sizePolicy1);
        xStepsSpeed->setMinimumSize(QSize(0, 0));

        gridLayout_8->addWidget(xStepsSpeed, 10, 2, 1, 1);

        label_33 = new QLabel(scrollAreaWidgetContents_2);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        sizePolicy2.setHeightForWidth(label_33->sizePolicy().hasHeightForWidth());
        label_33->setSizePolicy(sizePolicy2);
        label_33->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_33, 12, 1, 1, 1);

        label_34 = new QLabel(scrollAreaWidgetContents_2);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        sizePolicy1.setHeightForWidth(label_34->sizePolicy().hasHeightForWidth());
        label_34->setSizePolicy(sizePolicy1);
        label_34->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_34, 12, 3, 1, 1);

        label_24 = new QLabel(scrollAreaWidgetContents_2);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        sizePolicy1.setHeightForWidth(label_24->sizePolicy().hasHeightForWidth());
        label_24->setSizePolicy(sizePolicy1);
        label_24->setMinimumSize(QSize(0, 0));
        label_24->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_24, 5, 3, 1, 1);

        yDegrisSpeed = new tlinsWCoordinateDegris(scrollAreaWidgetContents_2);
        yDegrisSpeed->setObjectName(QString::fromUtf8("yDegrisSpeed"));
        yDegrisSpeed->setEnabled(true);
        sizePolicy1.setHeightForWidth(yDegrisSpeed->sizePolicy().hasHeightForWidth());
        yDegrisSpeed->setSizePolicy(sizePolicy1);
        yDegrisSpeed->setMinimumSize(QSize(0, 0));

        gridLayout_8->addWidget(yDegrisSpeed, 7, 2, 1, 1);

        label_35 = new QLabel(scrollAreaWidgetContents_2);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        sizePolicy2.setHeightForWidth(label_35->sizePolicy().hasHeightForWidth());
        label_35->setSizePolicy(sizePolicy2);
        label_35->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_35, 13, 1, 1, 1);

        label_14 = new QLabel(scrollAreaWidgetContents_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        sizePolicy2.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy2);
        label_14->setMinimumSize(QSize(100, 0));
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_14, 6, 1, 1, 1);

        raDelta = new tlinsWCoordinateHourAngle(scrollAreaWidgetContents_2);
        raDelta->setObjectName(QString::fromUtf8("raDelta"));
        raDelta->setEnabled(true);
        sizePolicy1.setHeightForWidth(raDelta->sizePolicy().hasHeightForWidth());
        raDelta->setSizePolicy(sizePolicy1);
        raDelta->setMinimumSize(QSize(0, 0));

        gridLayout_8->addWidget(raDelta, 0, 2, 1, 1);

        label_25 = new QLabel(scrollAreaWidgetContents_2);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        sizePolicy1.setHeightForWidth(label_25->sizePolicy().hasHeightForWidth());
        label_25->setSizePolicy(sizePolicy1);
        label_25->setMinimumSize(QSize(0, 0));
        label_25->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_25, 6, 3, 1, 1);

        label_6 = new QLabel(scrollAreaWidgetContents_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy2.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy2);
        label_6->setMinimumSize(QSize(100, 0));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_6, 1, 1, 1, 1);

        scaleY = new tlinsWDecimalValue(scrollAreaWidgetContents_2);
        scaleY->setObjectName(QString::fromUtf8("scaleY"));
        sizePolicy1.setHeightForWidth(scaleY->sizePolicy().hasHeightForWidth());
        scaleY->setSizePolicy(sizePolicy1);

        gridLayout_8->addWidget(scaleY, 13, 2, 1, 1);

        yStepsSpeed = new tlinsWDecimalValue(scrollAreaWidgetContents_2);
        yStepsSpeed->setObjectName(QString::fromUtf8("yStepsSpeed"));
        yStepsSpeed->setEnabled(true);
        sizePolicy1.setHeightForWidth(yStepsSpeed->sizePolicy().hasHeightForWidth());
        yStepsSpeed->setSizePolicy(sizePolicy1);
        yStepsSpeed->setMinimumSize(QSize(0, 0));

        gridLayout_8->addWidget(yStepsSpeed, 11, 2, 1, 1);


        verticalLayout_3->addLayout(gridLayout_8);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_8);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        gridLayout_5->addWidget(scrollArea_2, 0, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        textEdit = new QTextEdit(tab);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setEnabled(true);
        QFont font;
        font.setFamily(QString::fromUtf8("Courier [PfEd]"));
        font.setPointSize(10);
        textEdit->setFont(font);
        textEdit->setFrameShadow(QFrame::Plain);
        textEdit->setReadOnly(true);

        gridLayout_2->addWidget(textEdit, 0, 0, 1, 1);

        pbClear = new QPushButton(tab);
        pbClear->setObjectName(QString::fromUtf8("pbClear"));
        pbClear->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(pbClear, 0, 1, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        verticalLayout_4 = new QVBoxLayout(tab_5);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalSpacer_7 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout_4->addItem(verticalSpacer_7);

        groupBox_3 = new QGroupBox(tab_5);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_6 = new QGridLayout(groupBox_3);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        directoryEdit = new QLineEdit(groupBox_3);
        directoryEdit->setObjectName(QString::fromUtf8("directoryEdit"));

        gridLayout_6->addWidget(directoryEdit, 0, 1, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        downloadButton = new QPushButton(groupBox_3);
        downloadButton->setObjectName(QString::fromUtf8("downloadButton"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(downloadButton->sizePolicy().hasHeightForWidth());
        downloadButton->setSizePolicy(sizePolicy3);
        downloadButton->setMinimumSize(QSize(200, 40));

        horizontalLayout_7->addWidget(downloadButton);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_14);


        gridLayout_6->addLayout(horizontalLayout_7, 2, 1, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(150, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_9, 0, 0, 1, 1);

        directorySelectionButton = new QPushButton(groupBox_3);
        directorySelectionButton->setObjectName(QString::fromUtf8("directorySelectionButton"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(directorySelectionButton->sizePolicy().hasHeightForWidth());
        directorySelectionButton->setSizePolicy(sizePolicy4);
        directorySelectionButton->setMinimumSize(QSize(150, 40));

        gridLayout_6->addWidget(directorySelectionButton, 0, 2, 1, 1);

        removeAfterDownload = new QCheckBox(groupBox_3);
        removeAfterDownload->setObjectName(QString::fromUtf8("removeAfterDownload"));

        gridLayout_6->addWidget(removeAfterDownload, 1, 1, 1, 1);


        verticalLayout_4->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(tab_5);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_9 = new QGridLayout(groupBox_4);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_10 = new QSpacerItem(150, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_10);

        label_18 = new QLabel(groupBox_4);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        horizontalLayout_5->addWidget(label_18);

        numberFilesToLeave = new tlinsWDecimalValue(groupBox_4);
        numberFilesToLeave->setObjectName(QString::fromUtf8("numberFilesToLeave"));

        horizontalLayout_5->addWidget(numberFilesToLeave);

        horizontalSpacer_13 = new QSpacerItem(150, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_13);


        gridLayout_9->addLayout(horizontalLayout_5, 0, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_15 = new QSpacerItem(150, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_15);

        removeFilesButton = new QPushButton(groupBox_4);
        removeFilesButton->setObjectName(QString::fromUtf8("removeFilesButton"));
        sizePolicy4.setHeightForWidth(removeFilesButton->sizePolicy().hasHeightForWidth());
        removeFilesButton->setSizePolicy(sizePolicy4);
        removeFilesButton->setMinimumSize(QSize(200, 40));

        horizontalLayout_6->addWidget(removeFilesButton);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_16);


        gridLayout_9->addLayout(horizontalLayout_6, 1, 0, 1, 1);


        verticalLayout_4->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(tab_5);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        gridLayout_10 = new QGridLayout(groupBox_5);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        horizontalSpacer_18 = new QSpacerItem(150, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_18, 0, 0, 1, 1);

        baseInterval = new tlinsWDecimalValue(groupBox_5);
        baseInterval->setObjectName(QString::fromUtf8("baseInterval"));

        gridLayout_10->addWidget(baseInterval, 0, 2, 1, 1);

        label_31 = new QLabel(groupBox_5);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setMinimumSize(QSize(150, 0));

        gridLayout_10->addWidget(label_31, 0, 1, 1, 1);

        checkBox_2 = new QCheckBox(groupBox_5);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setMinimumSize(QSize(150, 0));

        gridLayout_10->addWidget(checkBox_2, 1, 1, 1, 1);

        horizontalSpacer_19 = new QSpacerItem(150, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_19, 0, 4, 1, 1);

        pushButton_3 = new QPushButton(groupBox_5);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        sizePolicy4.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy4);
        pushButton_3->setMinimumSize(QSize(200, 40));

        gridLayout_10->addWidget(pushButton_3, 2, 1, 1, 1);


        verticalLayout_4->addWidget(groupBox_5);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_6);

        tabWidget->addTab(tab_5, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalLayout_2 = new QVBoxLayout(tab_4);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_3 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        updateInputFile = new QLineEdit(tab_4);
        updateInputFile->setObjectName(QString::fromUtf8("updateInputFile"));
        updateInputFile->setMinimumSize(QSize(500, 0));

        horizontalLayout->addWidget(updateInputFile);

        sofUpdateSelectFile = new QPushButton(tab_4);
        sofUpdateSelectFile->setObjectName(QString::fromUtf8("sofUpdateSelectFile"));
        sizePolicy4.setHeightForWidth(sofUpdateSelectFile->sizePolicy().hasHeightForWidth());
        sofUpdateSelectFile->setSizePolicy(sizePolicy4);
        sofUpdateSelectFile->setMinimumSize(QSize(200, 40));
        sofUpdateSelectFile->setIconSize(QSize(24, 24));
        sofUpdateSelectFile->setFlat(false);

        horizontalLayout->addWidget(sofUpdateSelectFile);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalSpacer_4 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_11);

        sofUpdatePerfome = new QPushButton(tab_4);
        sofUpdatePerfome->setObjectName(QString::fromUtf8("sofUpdatePerfome"));
        sofUpdatePerfome->setMinimumSize(QSize(200, 40));
        sofUpdatePerfome->setIconSize(QSize(32, 32));
        sofUpdatePerfome->setFlat(false);

        horizontalLayout_2->addWidget(sofUpdatePerfome);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_12);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalSpacer_5 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer_5);

        label_11 = new QLabel(tab_4);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        verticalLayout_2->addWidget(label_11);

        updateDetails = new QTextEdit(tab_4);
        updateDetails->setObjectName(QString::fromUtf8("updateDetails"));
        updateDetails->setFont(font);
        updateDetails->setReadOnly(true);

        verticalLayout_2->addWidget(updateDetails);

        sendUpdateLogsIntoAppLog = new QCheckBox(tab_4);
        sendUpdateLogsIntoAppLog->setObjectName(QString::fromUtf8("sendUpdateLogsIntoAppLog"));
        sendUpdateLogsIntoAppLog->setChecked(false);

        verticalLayout_2->addWidget(sendUpdateLogsIntoAppLog);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer);

        tabWidget->addTab(tab_4, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout = new QVBoxLayout(tab_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_3 = new QHBoxLayout(groupBox);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        textEdit_4 = new QTextEdit(groupBox);
        textEdit_4->setObjectName(QString::fromUtf8("textEdit_4"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Courier [PfEd]"));
        textEdit_4->setFont(font1);

        horizontalLayout_3->addWidget(textEdit_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalSpacer_13 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_13);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_5->addWidget(pushButton);

        verticalSpacer_14 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_14);

        pushButton_5 = new QPushButton(groupBox);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        verticalLayout_5->addWidget(pushButton_5);

        verticalSpacer_12 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_12);


        horizontalLayout_3->addLayout(verticalLayout_5);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(tab_2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_2);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        textEdit_3 = new QTextEdit(groupBox_2);
        textEdit_3->setObjectName(QString::fromUtf8("textEdit_3"));
        textEdit_3->setFont(font1);

        horizontalLayout_4->addWidget(textEdit_3);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_10);

        pushButton_2 = new QPushButton(groupBox_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout_6->addWidget(pushButton_2);

        verticalSpacer_15 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_15);

        pushButton_7 = new QPushButton(groupBox_2);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));

        verticalLayout_6->addWidget(pushButton_7);

        verticalSpacer_11 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_11);


        horizontalLayout_4->addLayout(verticalLayout_6);


        verticalLayout->addWidget(groupBox_2);

        groupBox_6 = new QGroupBox(tab_2);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        horizontalLayout_8 = new QHBoxLayout(groupBox_6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        textEdit_2 = new QTextEdit(groupBox_6);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setFont(font1);

        horizontalLayout_8->addWidget(textEdit_2);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_2);

        pushButton_10 = new QPushButton(groupBox_6);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));

        verticalLayout_7->addWidget(pushButton_10);

        verticalSpacer_16 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_16);

        pushButton_9 = new QPushButton(groupBox_6);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));

        verticalLayout_7->addWidget(pushButton_9);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_9);


        horizontalLayout_8->addLayout(verticalLayout_7);


        verticalLayout->addWidget(groupBox_6);

        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(tlinsInfoWidget);
        QObject::connect(directorySelectionButton, SIGNAL(clicked()), tlinsInfoWidget, SLOT(selectOutputDirForLogsCb()));
        QObject::connect(removeFilesButton, SIGNAL(clicked()), tlinsInfoWidget, SLOT(removeLogsCb()));
        QObject::connect(sofUpdateSelectFile, SIGNAL(clicked()), tlinsInfoWidget, SLOT(sofUpdateSelectFileCb()));
        QObject::connect(sofUpdatePerfome, SIGNAL(clicked()), tlinsInfoWidget, SLOT(sofUpdatePerfomeCb()));
        QObject::connect(loadPB, SIGNAL(clicked()), tlinsInfoWidget, SLOT(loadCb()));
        QObject::connect(downloadButton, SIGNAL(clicked()), tlinsInfoWidget, SLOT(downloadLogsCb()));
        QObject::connect(updatePB, SIGNAL(clicked()), tlinsInfoWidget, SLOT(updateCb()));
        QObject::connect(reloadPB, SIGNAL(clicked()), tlinsInfoWidget, SLOT(reloadCb()));
        QObject::connect(pbClear, SIGNAL(clicked()), tlinsInfoWidget, SLOT(clearLog()));
        QObject::connect(storePB, SIGNAL(clicked()), tlinsInfoWidget, SLOT(storeCb()));
        QObject::connect(pushButton_5, SIGNAL(clicked()), tlinsInfoWidget, SLOT(uploadCfg()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), tlinsInfoWidget, SLOT(downloadCfgAstro()));
        QObject::connect(pushButton_7, SIGNAL(clicked()), tlinsInfoWidget, SLOT(uploadCfgAstro()));
        QObject::connect(pushButton_10, SIGNAL(clicked()), tlinsInfoWidget, SLOT(downloadCfgAstroService()));
        QObject::connect(pushButton_9, SIGNAL(clicked()), tlinsInfoWidget, SLOT(uploadCfgAstroService()));
        QObject::connect(pushButton, SIGNAL(clicked()), tlinsInfoWidget, SLOT(downloadCfg()));

        tabWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(tlinsInfoWidget);
    } // setupUi

    void retranslateUi(QWidget *tlinsInfoWidget)
    {
        tlinsInfoWidget->setWindowTitle(QApplication::translate("tlinsInfoWidget", "Form", nullptr));
        reloadPB->setText(QApplication::translate("tlinsInfoWidget", "Reload", nullptr));
        storePB->setText(QApplication::translate("tlinsInfoWidget", "Store", nullptr));
        updatePB->setText(QApplication::translate("tlinsInfoWidget", "Update", nullptr));
        loadPB->setText(QApplication::translate("tlinsInfoWidget", "Load", nullptr));
        label_30->setText(QApplication::translate("tlinsInfoWidget", "[steps/s]", nullptr));
        label_36->setText(QApplication::translate("tlinsInfoWidget", "[number]", nullptr));
        label_26->setText(QApplication::translate("tlinsInfoWidget", "[deg/s]", nullptr));
        label_8->setText(QApplication::translate("tlinsInfoWidget", "Dec sped delta:", nullptr));
        label_21->setText(QApplication::translate("tlinsInfoWidget", "[hour/s]", nullptr));
        label_17->setText(QApplication::translate("tlinsInfoWidget", "Y steps speed delta:", nullptr));
        label_15->setText(QApplication::translate("tlinsInfoWidget", "Y degris delta:", nullptr));
        label_23->setText(QApplication::translate("tlinsInfoWidget", "[degris]", nullptr));
        label_19->setText(QApplication::translate("tlinsInfoWidget", "[degris]", nullptr));
        label_28->setText(QApplication::translate("tlinsInfoWidget", "[steps]", nullptr));
        label_20->setText(QApplication::translate("tlinsInfoWidget", "[hour]", nullptr));
        label_16->setText(QApplication::translate("tlinsInfoWidget", "Y steps delta:", nullptr));
        label_27->setText(QApplication::translate("tlinsInfoWidget", "[steps]", nullptr));
        label_13->setText(QApplication::translate("tlinsInfoWidget", "Y degris speed delta:", nullptr));
        label_10->setText(QApplication::translate("tlinsInfoWidget", "X steps speed delta:", nullptr));
        label_7->setText(QApplication::translate("tlinsInfoWidget", "Ra speed delta:", nullptr));
        label_9->setText(QApplication::translate("tlinsInfoWidget", "X degris delta:", nullptr));
        label_29->setText(QApplication::translate("tlinsInfoWidget", "[steps/s]", nullptr));
        label_22->setText(QApplication::translate("tlinsInfoWidget", "[deg/s]", nullptr));
        label_12->setText(QApplication::translate("tlinsInfoWidget", "X steps delta:", nullptr));
        label_5->setText(QApplication::translate("tlinsInfoWidget", "  RA delta:", nullptr));
        label_33->setText(QApplication::translate("tlinsInfoWidget", "X scale:", nullptr));
        label_34->setText(QApplication::translate("tlinsInfoWidget", "[number]", nullptr));
        label_24->setText(QApplication::translate("tlinsInfoWidget", "[degris]", nullptr));
        label_35->setText(QApplication::translate("tlinsInfoWidget", "Y scale:", nullptr));
        label_14->setText(QApplication::translate("tlinsInfoWidget", "X degris speed delta:", nullptr));
        label_25->setText(QApplication::translate("tlinsInfoWidget", "[deg/s]", nullptr));
        label_6->setText(QApplication::translate("tlinsInfoWidget", "Dec delta:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("tlinsInfoWidget", "Pilot state", nullptr));
        pbClear->setText(QApplication::translate("tlinsInfoWidget", "Clear", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("tlinsInfoWidget", "Application log", nullptr));
        groupBox_3->setTitle(QApplication::translate("tlinsInfoWidget", "Logs download", nullptr));
        downloadButton->setText(QApplication::translate("tlinsInfoWidget", "Download", nullptr));
        directorySelectionButton->setText(QApplication::translate("tlinsInfoWidget", "Select directory", nullptr));
        removeAfterDownload->setText(QApplication::translate("tlinsInfoWidget", "Remove after download", nullptr));
        groupBox_4->setTitle(QApplication::translate("tlinsInfoWidget", "Manual logs retention", nullptr));
        label_18->setText(QApplication::translate("tlinsInfoWidget", "Leave last N log files", nullptr));
        removeFilesButton->setText(QApplication::translate("tlinsInfoWidget", "Remove logs", nullptr));
        groupBox_5->setTitle(QApplication::translate("tlinsInfoWidget", "Automatic log retenation", nullptr));
        label_31->setText(QApplication::translate("tlinsInfoWidget", "Base interval", nullptr));
        checkBox_2->setText(QApplication::translate("tlinsInfoWidget", "Enable", nullptr));
        pushButton_3->setText(QApplication::translate("tlinsInfoWidget", "Update service", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("tlinsInfoWidget", "Remote logs", nullptr));
        sofUpdateSelectFile->setText(QApplication::translate("tlinsInfoWidget", "Select file", nullptr));
        sofUpdatePerfome->setText(QApplication::translate("tlinsInfoWidget", "Update", nullptr));
        label_11->setText(QApplication::translate("tlinsInfoWidget", "Update log:", nullptr));
        sendUpdateLogsIntoAppLog->setText(QApplication::translate("tlinsInfoWidget", "Send progress into application log", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("tlinsInfoWidget", "Software updatea", nullptr));
        groupBox->setTitle(QApplication::translate("tlinsInfoWidget", "Device config", nullptr));
        pushButton->setText(QApplication::translate("tlinsInfoWidget", "Download", nullptr));
        pushButton_5->setText(QApplication::translate("tlinsInfoWidget", "Upload", nullptr));
        groupBox_2->setTitle(QApplication::translate("tlinsInfoWidget", "Astro engine config", nullptr));
        pushButton_2->setText(QApplication::translate("tlinsInfoWidget", "Download", nullptr));
        pushButton_7->setText(QApplication::translate("tlinsInfoWidget", "Upload", nullptr));
        groupBox_6->setTitle(QApplication::translate("tlinsInfoWidget", "System monitor config", nullptr));
        pushButton_10->setText(QApplication::translate("tlinsInfoWidget", "Download", nullptr));
        pushButton_9->setText(QApplication::translate("tlinsInfoWidget", "Upload", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("tlinsInfoWidget", "Config", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsInfoWidget: public Ui_tlinsInfoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSINFOWIDGET_H
