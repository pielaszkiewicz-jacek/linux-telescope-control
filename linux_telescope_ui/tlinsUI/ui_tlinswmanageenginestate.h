/********************************************************************************
** Form generated from reading UI file 'tlinswmanageenginestate.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWMANAGEENGINESTATE_H
#define UI_TLINSWMANAGEENGINESTATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <tlinswastrocatalog.h>
#include <tlinswdecimalvalue.h>
#include "tlinswcoordinatedeclination.h"
#include "tlinswcoordinatehourangle.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsWManageEngineState
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_10;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioButtonStateView;
    QRadioButton *radioButtonCtrlView;
    QRadioButton *radioButtonAllView;
    QGroupBox *gbStateControl;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_6;
    QRadioButton *rbStandardSpeed;
    QSpacerItem *verticalSpacer_2;
    QRadioButton *rbStandard;
    QRadioButton *rbGuider;
    QSpacerItem *verticalSpacer_3;
    QPushButton *btStop;
    QPushButton *btStart;
    QGroupBox *groupBoxGuider;
    QGridLayout *gridLayout_7;
    QLabel *label_25;
    QLabel *label_24;
    tlinsWDecimalValue *guiderDecRatio;
    QDial *dialDECRatio;
    tlinsWDecimalValue *guiderRaRatio;
    QDial *dialRARatio;
    QFrame *line_3;
    QFrame *frameGuider;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pbSReadFromDeviceGuider;
    QPushButton *pbUpdateDeviceGuider;
    QPushButton *pbStoreGuider;
    QPushButton *pbLoadGuider;
    QGroupBox *groupBoxManualCorrections;
    QGridLayout *gridLayout_8;
    QLabel *label_26;
    QDial *dialDECCorrection;
    QLabel *label_27;
    tlinsWDecimalValue *manualDecCorrection;
    tlinsWDecimalValue *manualRaCorrection;
    QDial *dialRACorrection;
    QFrame *line_4;
    QFrame *frameManual;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *pbReadFromDeviceManual;
    QPushButton *pbUpdateDeviceManual;
    QGroupBox *groupBoxState;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_9;
    QHBoxLayout *horizontalLayout;
    QPushButton *btDownloadState;
    QPushButton *btUploadState;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QTableView *statesList;
    QGridLayout *gridLayout_5;
    QPushButton *btAdd;
    QPushButton *btLoad;
    QPushButton *btSave;
    QSpacerItem *verticalSpacer;
    QPushButton *btRemove;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_9;
    QLineEdit *name;
    QGroupBox *groupBox_6;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_12;
    QLabel *engineMode;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_7;
    QLabel *engineState;
    QSpacerItem *horizontalSpacer_6;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer;
    QCheckBox *xReverse;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *yReverse;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *gMatrix;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_8;
    QGridLayout *gridLayout;
    tlinsWDecimalValue *a22;
    tlinsWDecimalValue *a23;
    tlinsWDecimalValue *a21;
    tlinsWDecimalValue *a11;
    tlinsWDecimalValue *a12;
    tlinsWDecimalValue *a13;
    tlinsWDecimalValue *a31;
    tlinsWDecimalValue *a32;
    tlinsWDecimalValue *a33;
    QSpacerItem *horizontalSpacer_9;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_2;
    tlinsWDecimalValue *aY;
    QLabel *label_22;
    QLabel *label_3;
    QLabel *label_20;
    QLabel *label_13;
    tlinsWDecimalValue *aX;
    QLabel *label_5;
    tlinsWDecimalValue *aXEncoder;
    QLabel *label_21;
    QLabel *label_6;
    tlinsWDecimalValue *aYEncoder;
    QLabel *label_23;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_4;
    tlinsWAstroCatalog *catalogType;
    tlinsWDecimalValue *pmDC;
    QLabel *label_8;
    QLabel *label_11;
    QLabel *label_10;
    QLabel *label_16;
    QLabel *label_14;
    QLabel *label_7;
    tlinsWDecimalValue *pmRA;
    QLabel *label_12;
    tlinsWDecimalValue *paralex;
    tlinsWCoordinateHourAngle *targetRA;
    QLabel *label_15;
    tlinsWCoordinateDeclination *targetDC;
    tlinsWDecimalValue *radialVelocity;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_5;

    void setupUi(QWidget *tlinsWManageEngineState)
    {
        if (tlinsWManageEngineState->objectName().isEmpty())
            tlinsWManageEngineState->setObjectName(QString::fromUtf8("tlinsWManageEngineState"));
        tlinsWManageEngineState->setEnabled(true);
        tlinsWManageEngineState->resize(1448, 1642);
        verticalLayout = new QVBoxLayout(tlinsWManageEngineState);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 0, -1, -1);
        scrollArea = new QScrollArea(tlinsWManageEngineState);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, -91, 1414, 1800));
        verticalLayout_4 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(13, 26, -1, 26);
        groupBox_10 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_10);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        radioButtonStateView = new QRadioButton(groupBox_10);
        radioButtonStateView->setObjectName(QString::fromUtf8("radioButtonStateView"));

        horizontalLayout_2->addWidget(radioButtonStateView);

        radioButtonCtrlView = new QRadioButton(groupBox_10);
        radioButtonCtrlView->setObjectName(QString::fromUtf8("radioButtonCtrlView"));

        horizontalLayout_2->addWidget(radioButtonCtrlView);

        radioButtonAllView = new QRadioButton(groupBox_10);
        radioButtonAllView->setObjectName(QString::fromUtf8("radioButtonAllView"));

        horizontalLayout_2->addWidget(radioButtonAllView);


        verticalLayout_4->addWidget(groupBox_10);

        gbStateControl = new QGroupBox(scrollAreaWidgetContents);
        gbStateControl->setObjectName(QString::fromUtf8("gbStateControl"));
        gridLayout_3 = new QGridLayout(gbStateControl);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setVerticalSpacing(15);
        gridLayout_3->setContentsMargins(-1, 5, -1, 5);
        groupBox = new QGroupBox(gbStateControl);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_6 = new QGridLayout(groupBox);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(-1, 0, -1, 0);
        rbStandardSpeed = new QRadioButton(groupBox);
        rbStandardSpeed->setObjectName(QString::fromUtf8("rbStandardSpeed"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(rbStandardSpeed->sizePolicy().hasHeightForWidth());
        rbStandardSpeed->setSizePolicy(sizePolicy);

        gridLayout_6->addWidget(rbStandardSpeed, 1, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout_6->addItem(verticalSpacer_2, 0, 1, 1, 1);

        rbStandard = new QRadioButton(groupBox);
        rbStandard->setObjectName(QString::fromUtf8("rbStandard"));
        sizePolicy.setHeightForWidth(rbStandard->sizePolicy().hasHeightForWidth());
        rbStandard->setSizePolicy(sizePolicy);
        rbStandard->setChecked(true);

        gridLayout_6->addWidget(rbStandard, 1, 0, 1, 1);

        rbGuider = new QRadioButton(groupBox);
        rbGuider->setObjectName(QString::fromUtf8("rbGuider"));
        rbGuider->setEnabled(true);
        sizePolicy.setHeightForWidth(rbGuider->sizePolicy().hasHeightForWidth());
        rbGuider->setSizePolicy(sizePolicy);

        gridLayout_6->addWidget(rbGuider, 1, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        gridLayout_6->addItem(verticalSpacer_3, 2, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        btStop = new QPushButton(gbStateControl);
        btStop->setObjectName(QString::fromUtf8("btStop"));
        btStop->setMinimumSize(QSize(80, 60));
        btStop->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_3->addWidget(btStop, 0, 2, 1, 1);

        btStart = new QPushButton(gbStateControl);
        btStart->setObjectName(QString::fromUtf8("btStart"));
        btStart->setMinimumSize(QSize(80, 60));
        btStart->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_3->addWidget(btStart, 0, 1, 1, 1);


        verticalLayout_4->addWidget(gbStateControl);

        groupBoxGuider = new QGroupBox(scrollAreaWidgetContents);
        groupBoxGuider->setObjectName(QString::fromUtf8("groupBoxGuider"));
        gridLayout_7 = new QGridLayout(groupBoxGuider);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label_25 = new QLabel(groupBoxGuider);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        gridLayout_7->addWidget(label_25, 0, 4, 1, 1);

        label_24 = new QLabel(groupBoxGuider);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        gridLayout_7->addWidget(label_24, 0, 0, 1, 1);

        guiderDecRatio = new tlinsWDecimalValue(groupBoxGuider);
        guiderDecRatio->setObjectName(QString::fromUtf8("guiderDecRatio"));

        gridLayout_7->addWidget(guiderDecRatio, 0, 5, 1, 1);

        dialDECRatio = new QDial(groupBoxGuider);
        dialDECRatio->setObjectName(QString::fromUtf8("dialDECRatio"));
        dialDECRatio->setEnabled(true);
        dialDECRatio->setMinimumSize(QSize(100, 100));
        dialDECRatio->setMinimum(0);
        dialDECRatio->setMaximum(1000000);

        gridLayout_7->addWidget(dialDECRatio, 0, 6, 1, 1);

        guiderRaRatio = new tlinsWDecimalValue(groupBoxGuider);
        guiderRaRatio->setObjectName(QString::fromUtf8("guiderRaRatio"));

        gridLayout_7->addWidget(guiderRaRatio, 0, 1, 1, 1);

        dialRARatio = new QDial(groupBoxGuider);
        dialRARatio->setObjectName(QString::fromUtf8("dialRARatio"));
        dialRARatio->setMinimumSize(QSize(100, 100));
        dialRARatio->setMinimum(0);
        dialRARatio->setMaximum(1000000);

        gridLayout_7->addWidget(dialRARatio, 0, 2, 1, 1);

        line_3 = new QFrame(groupBoxGuider);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout_7->addWidget(line_3, 0, 3, 1, 1);


        verticalLayout_4->addWidget(groupBoxGuider);

        frameGuider = new QFrame(scrollAreaWidgetContents);
        frameGuider->setObjectName(QString::fromUtf8("frameGuider"));
        frameGuider->setFrameShape(QFrame::StyledPanel);
        frameGuider->setFrameShadow(QFrame::Raised);
        horizontalLayout_7 = new QHBoxLayout(frameGuider);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        pbSReadFromDeviceGuider = new QPushButton(frameGuider);
        pbSReadFromDeviceGuider->setObjectName(QString::fromUtf8("pbSReadFromDeviceGuider"));
        pbSReadFromDeviceGuider->setMinimumSize(QSize(0, 60));

        horizontalLayout_7->addWidget(pbSReadFromDeviceGuider);

        pbUpdateDeviceGuider = new QPushButton(frameGuider);
        pbUpdateDeviceGuider->setObjectName(QString::fromUtf8("pbUpdateDeviceGuider"));
        pbUpdateDeviceGuider->setMinimumSize(QSize(0, 60));

        horizontalLayout_7->addWidget(pbUpdateDeviceGuider);

        pbStoreGuider = new QPushButton(frameGuider);
        pbStoreGuider->setObjectName(QString::fromUtf8("pbStoreGuider"));
        pbStoreGuider->setMinimumSize(QSize(0, 60));

        horizontalLayout_7->addWidget(pbStoreGuider);

        pbLoadGuider = new QPushButton(frameGuider);
        pbLoadGuider->setObjectName(QString::fromUtf8("pbLoadGuider"));
        pbLoadGuider->setMinimumSize(QSize(0, 60));

        horizontalLayout_7->addWidget(pbLoadGuider);


        verticalLayout_4->addWidget(frameGuider);

        groupBoxManualCorrections = new QGroupBox(scrollAreaWidgetContents);
        groupBoxManualCorrections->setObjectName(QString::fromUtf8("groupBoxManualCorrections"));
        gridLayout_8 = new QGridLayout(groupBoxManualCorrections);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        label_26 = new QLabel(groupBoxManualCorrections);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        gridLayout_8->addWidget(label_26, 0, 0, 1, 1);

        dialDECCorrection = new QDial(groupBoxManualCorrections);
        dialDECCorrection->setObjectName(QString::fromUtf8("dialDECCorrection"));
        dialDECCorrection->setMinimumSize(QSize(100, 100));
        dialDECCorrection->setMinimum(-1000000);
        dialDECCorrection->setMaximum(1000000);

        gridLayout_8->addWidget(dialDECCorrection, 0, 6, 1, 1);

        label_27 = new QLabel(groupBoxManualCorrections);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        gridLayout_8->addWidget(label_27, 0, 4, 1, 1);

        manualDecCorrection = new tlinsWDecimalValue(groupBoxManualCorrections);
        manualDecCorrection->setObjectName(QString::fromUtf8("manualDecCorrection"));

        gridLayout_8->addWidget(manualDecCorrection, 0, 5, 1, 1);

        manualRaCorrection = new tlinsWDecimalValue(groupBoxManualCorrections);
        manualRaCorrection->setObjectName(QString::fromUtf8("manualRaCorrection"));

        gridLayout_8->addWidget(manualRaCorrection, 0, 1, 1, 1);

        dialRACorrection = new QDial(groupBoxManualCorrections);
        dialRACorrection->setObjectName(QString::fromUtf8("dialRACorrection"));
        dialRACorrection->setMinimumSize(QSize(100, 100));
        dialRACorrection->setMinimum(-1000000);
        dialRACorrection->setMaximum(1000000);

        gridLayout_8->addWidget(dialRACorrection, 0, 2, 1, 1);

        line_4 = new QFrame(groupBoxManualCorrections);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout_8->addWidget(line_4, 0, 3, 1, 1);


        verticalLayout_4->addWidget(groupBoxManualCorrections);

        frameManual = new QFrame(scrollAreaWidgetContents);
        frameManual->setObjectName(QString::fromUtf8("frameManual"));
        frameManual->setFrameShape(QFrame::StyledPanel);
        frameManual->setFrameShadow(QFrame::Raised);
        horizontalLayout_8 = new QHBoxLayout(frameManual);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        pbReadFromDeviceManual = new QPushButton(frameManual);
        pbReadFromDeviceManual->setObjectName(QString::fromUtf8("pbReadFromDeviceManual"));
        pbReadFromDeviceManual->setMinimumSize(QSize(0, 60));

        horizontalLayout_8->addWidget(pbReadFromDeviceManual);

        pbUpdateDeviceManual = new QPushButton(frameManual);
        pbUpdateDeviceManual->setObjectName(QString::fromUtf8("pbUpdateDeviceManual"));
        pbUpdateDeviceManual->setMinimumSize(QSize(0, 60));

        horizontalLayout_8->addWidget(pbUpdateDeviceManual);


        verticalLayout_4->addWidget(frameManual);

        groupBoxState = new QGroupBox(scrollAreaWidgetContents);
        groupBoxState->setObjectName(QString::fromUtf8("groupBoxState"));
        verticalLayout_2 = new QVBoxLayout(groupBoxState);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 5, -1, -1);
        groupBox_9 = new QGroupBox(groupBoxState);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        horizontalLayout = new QHBoxLayout(groupBox_9);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btDownloadState = new QPushButton(groupBox_9);
        btDownloadState->setObjectName(QString::fromUtf8("btDownloadState"));
        btDownloadState->setMinimumSize(QSize(80, 60));
        btDownloadState->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(btDownloadState);

        btUploadState = new QPushButton(groupBox_9);
        btUploadState->setObjectName(QString::fromUtf8("btUploadState"));
        btUploadState->setMinimumSize(QSize(80, 60));
        btUploadState->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(btUploadState);


        verticalLayout_2->addWidget(groupBox_9);

        label = new QLabel(groupBoxState);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        statesList = new QTableView(groupBoxState);
        statesList->setObjectName(QString::fromUtf8("statesList"));
        statesList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        statesList->setDragDropOverwriteMode(false);
        statesList->verticalHeader()->setVisible(false);

        horizontalLayout_3->addWidget(statesList);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        btAdd = new QPushButton(groupBoxState);
        btAdd->setObjectName(QString::fromUtf8("btAdd"));
        btAdd->setMinimumSize(QSize(0, 60));

        gridLayout_5->addWidget(btAdd, 1, 0, 1, 1);

        btLoad = new QPushButton(groupBoxState);
        btLoad->setObjectName(QString::fromUtf8("btLoad"));
        btLoad->setMinimumSize(QSize(0, 60));

        gridLayout_5->addWidget(btLoad, 2, 0, 1, 1);

        btSave = new QPushButton(groupBoxState);
        btSave->setObjectName(QString::fromUtf8("btSave"));
        btSave->setMinimumSize(QSize(0, 60));

        gridLayout_5->addWidget(btSave, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer, 3, 0, 1, 1);

        btRemove = new QPushButton(groupBoxState);
        btRemove->setObjectName(QString::fromUtf8("btRemove"));
        btRemove->setMinimumSize(QSize(0, 60));

        gridLayout_5->addWidget(btRemove, 4, 0, 1, 1);


        horizontalLayout_3->addLayout(gridLayout_5);


        verticalLayout_2->addLayout(horizontalLayout_3);

        groupBox_3 = new QGroupBox(groupBoxState);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(-1, 5, -1, 5);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_6->addWidget(label_9);

        name = new QLineEdit(groupBox_3);
        name->setObjectName(QString::fromUtf8("name"));

        horizontalLayout_6->addWidget(name);


        verticalLayout_3->addLayout(horizontalLayout_6);

        groupBox_6 = new QGroupBox(groupBox_3);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        horizontalLayout_5 = new QHBoxLayout(groupBox_6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, 5, -1, 5);
        label_2 = new QLabel(groupBox_6);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_5->addWidget(label_2);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_12);

        engineMode = new QLabel(groupBox_6);
        engineMode->setObjectName(QString::fromUtf8("engineMode"));
        QFont font;
        font.setBold(true);
        font.setItalic(true);
        font.setUnderline(true);
        engineMode->setFont(font);

        horizontalLayout_5->addWidget(engineMode);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_10);

        label_4 = new QLabel(groupBox_6);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);

        engineState = new QLabel(groupBox_6);
        engineState->setObjectName(QString::fromUtf8("engineState"));
        engineState->setFont(font);

        horizontalLayout_5->addWidget(engineState);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);


        verticalLayout_3->addWidget(groupBox_6);

        groupBox_2 = new QGroupBox(groupBox_3);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_9 = new QHBoxLayout(groupBox_2);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer);

        xReverse = new QCheckBox(groupBox_2);
        xReverse->setObjectName(QString::fromUtf8("xReverse"));
        xReverse->setEnabled(false);

        horizontalLayout_9->addWidget(xReverse);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_3);

        yReverse = new QCheckBox(groupBox_2);
        yReverse->setObjectName(QString::fromUtf8("yReverse"));
        yReverse->setEnabled(false);

        horizontalLayout_9->addWidget(yReverse);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_2);


        verticalLayout_3->addWidget(groupBox_2);

        gMatrix = new QGroupBox(groupBox_3);
        gMatrix->setObjectName(QString::fromUtf8("gMatrix"));
        gMatrix->setEnabled(true);
        horizontalLayout_4 = new QHBoxLayout(gMatrix);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 5, 5, 5);
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        a22 = new tlinsWDecimalValue(gMatrix);
        a22->setObjectName(QString::fromUtf8("a22"));
        a22->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(a22->sizePolicy().hasHeightForWidth());
        a22->setSizePolicy(sizePolicy1);
        a22->setMinimumSize(QSize(0, 48));

        gridLayout->addWidget(a22, 1, 1, 1, 1);

        a23 = new tlinsWDecimalValue(gMatrix);
        a23->setObjectName(QString::fromUtf8("a23"));
        a23->setEnabled(true);
        sizePolicy1.setHeightForWidth(a23->sizePolicy().hasHeightForWidth());
        a23->setSizePolicy(sizePolicy1);
        a23->setMinimumSize(QSize(0, 48));

        gridLayout->addWidget(a23, 1, 2, 1, 1);

        a21 = new tlinsWDecimalValue(gMatrix);
        a21->setObjectName(QString::fromUtf8("a21"));
        a21->setEnabled(true);
        sizePolicy1.setHeightForWidth(a21->sizePolicy().hasHeightForWidth());
        a21->setSizePolicy(sizePolicy1);
        a21->setMinimumSize(QSize(0, 48));

        gridLayout->addWidget(a21, 1, 0, 1, 1);

        a11 = new tlinsWDecimalValue(gMatrix);
        a11->setObjectName(QString::fromUtf8("a11"));
        a11->setEnabled(true);
        sizePolicy1.setHeightForWidth(a11->sizePolicy().hasHeightForWidth());
        a11->setSizePolicy(sizePolicy1);
        a11->setMinimumSize(QSize(0, 48));

        gridLayout->addWidget(a11, 0, 0, 1, 1);

        a12 = new tlinsWDecimalValue(gMatrix);
        a12->setObjectName(QString::fromUtf8("a12"));
        a12->setEnabled(true);
        sizePolicy1.setHeightForWidth(a12->sizePolicy().hasHeightForWidth());
        a12->setSizePolicy(sizePolicy1);
        a12->setMinimumSize(QSize(0, 48));

        gridLayout->addWidget(a12, 0, 1, 1, 1);

        a13 = new tlinsWDecimalValue(gMatrix);
        a13->setObjectName(QString::fromUtf8("a13"));
        a13->setEnabled(true);
        sizePolicy1.setHeightForWidth(a13->sizePolicy().hasHeightForWidth());
        a13->setSizePolicy(sizePolicy1);
        a13->setMinimumSize(QSize(0, 48));

        gridLayout->addWidget(a13, 0, 2, 1, 1);

        a31 = new tlinsWDecimalValue(gMatrix);
        a31->setObjectName(QString::fromUtf8("a31"));
        a31->setEnabled(true);
        sizePolicy1.setHeightForWidth(a31->sizePolicy().hasHeightForWidth());
        a31->setSizePolicy(sizePolicy1);
        a31->setMinimumSize(QSize(0, 48));

        gridLayout->addWidget(a31, 2, 0, 1, 1);

        a32 = new tlinsWDecimalValue(gMatrix);
        a32->setObjectName(QString::fromUtf8("a32"));
        a32->setEnabled(true);
        sizePolicy1.setHeightForWidth(a32->sizePolicy().hasHeightForWidth());
        a32->setSizePolicy(sizePolicy1);
        a32->setMinimumSize(QSize(0, 48));

        gridLayout->addWidget(a32, 2, 1, 1, 1);

        a33 = new tlinsWDecimalValue(gMatrix);
        a33->setObjectName(QString::fromUtf8("a33"));
        a33->setEnabled(true);
        sizePolicy1.setHeightForWidth(a33->sizePolicy().hasHeightForWidth());
        a33->setSizePolicy(sizePolicy1);
        a33->setMinimumSize(QSize(0, 48));

        gridLayout->addWidget(a33, 2, 2, 1, 1);


        horizontalLayout_4->addLayout(gridLayout);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_9);


        verticalLayout_3->addWidget(gMatrix);

        groupBox_4 = new QGroupBox(groupBox_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_2 = new QGridLayout(groupBox_4);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(-1, 5, -1, 5);
        aY = new tlinsWDecimalValue(groupBox_4);
        aY->setObjectName(QString::fromUtf8("aY"));
        aY->setEnabled(false);

        gridLayout_2->addWidget(aY, 0, 7, 1, 1);

        label_22 = new QLabel(groupBox_4);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        QFont font1;
        font1.setItalic(true);
        label_22->setFont(font1);

        gridLayout_2->addWidget(label_22, 0, 8, 1, 1);

        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        label_20 = new QLabel(groupBox_4);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setFont(font1);

        gridLayout_2->addWidget(label_20, 0, 2, 1, 1);

        label_13 = new QLabel(groupBox_4);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_2->addWidget(label_13, 0, 6, 1, 1);

        aX = new tlinsWDecimalValue(groupBox_4);
        aX->setObjectName(QString::fromUtf8("aX"));
        aX->setEnabled(false);

        gridLayout_2->addWidget(aX, 0, 1, 1, 1);

        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 1, 0, 1, 1);

        aXEncoder = new tlinsWDecimalValue(groupBox_4);
        aXEncoder->setObjectName(QString::fromUtf8("aXEncoder"));
        aXEncoder->setEnabled(false);

        gridLayout_2->addWidget(aXEncoder, 1, 1, 1, 1);

        label_21 = new QLabel(groupBox_4);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setFont(font1);

        gridLayout_2->addWidget(label_21, 1, 2, 1, 1);

        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 1, 6, 1, 1);

        aYEncoder = new tlinsWDecimalValue(groupBox_4);
        aYEncoder->setObjectName(QString::fromUtf8("aYEncoder"));
        aYEncoder->setEnabled(false);

        gridLayout_2->addWidget(aYEncoder, 1, 7, 1, 1);

        label_23 = new QLabel(groupBox_4);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setFont(font1);

        gridLayout_2->addWidget(label_23, 1, 8, 1, 1);


        verticalLayout_3->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(groupBox_3);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy2);
        gridLayout_4 = new QGridLayout(groupBox_5);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setHorizontalSpacing(10);
        gridLayout_4->setContentsMargins(-1, 5, -1, 5);
        catalogType = new tlinsWAstroCatalog(groupBox_5);
        catalogType->setObjectName(QString::fromUtf8("catalogType"));
        catalogType->setEnabled(false);

        gridLayout_4->addWidget(catalogType, 3, 1, 1, 1);

        pmDC = new tlinsWDecimalValue(groupBox_5);
        pmDC->setObjectName(QString::fromUtf8("pmDC"));
        pmDC->setEnabled(false);

        gridLayout_4->addWidget(pmDC, 1, 4, 1, 1);

        label_8 = new QLabel(groupBox_5);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_4->addWidget(label_8, 0, 3, 1, 1);

        label_11 = new QLabel(groupBox_5);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_4->addWidget(label_11, 1, 0, 1, 1);

        label_10 = new QLabel(groupBox_5);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_4->addWidget(label_10, 2, 0, 1, 1);

        label_16 = new QLabel(groupBox_5);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setFont(font1);
        label_16->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_16, 1, 2, 1, 1);

        label_14 = new QLabel(groupBox_5);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_4->addWidget(label_14, 1, 3, 1, 1);

        label_7 = new QLabel(groupBox_5);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_4->addWidget(label_7, 0, 0, 1, 1);

        pmRA = new tlinsWDecimalValue(groupBox_5);
        pmRA->setObjectName(QString::fromUtf8("pmRA"));
        pmRA->setEnabled(false);

        gridLayout_4->addWidget(pmRA, 1, 1, 1, 1);

        label_12 = new QLabel(groupBox_5);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_4->addWidget(label_12, 2, 3, 1, 1);

        paralex = new tlinsWDecimalValue(groupBox_5);
        paralex->setObjectName(QString::fromUtf8("paralex"));
        paralex->setEnabled(false);

        gridLayout_4->addWidget(paralex, 2, 1, 1, 1);

        targetRA = new tlinsWCoordinateHourAngle(groupBox_5);
        targetRA->setObjectName(QString::fromUtf8("targetRA"));
        targetRA->setEnabled(false);

        gridLayout_4->addWidget(targetRA, 0, 1, 1, 1);

        label_15 = new QLabel(groupBox_5);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_4->addWidget(label_15, 3, 0, 1, 1);

        targetDC = new tlinsWCoordinateDeclination(groupBox_5);
        targetDC->setObjectName(QString::fromUtf8("targetDC"));
        targetDC->setEnabled(false);

        gridLayout_4->addWidget(targetDC, 0, 4, 1, 1);

        radialVelocity = new tlinsWDecimalValue(groupBox_5);
        radialVelocity->setObjectName(QString::fromUtf8("radialVelocity"));
        radialVelocity->setEnabled(false);

        gridLayout_4->addWidget(radialVelocity, 2, 4, 1, 1);

        label_17 = new QLabel(groupBox_5);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setFont(font1);
        label_17->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_17, 1, 5, 1, 1);

        label_18 = new QLabel(groupBox_5);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setFont(font1);

        gridLayout_4->addWidget(label_18, 0, 2, 1, 1);

        label_19 = new QLabel(groupBox_5);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setFont(font1);

        gridLayout_4->addWidget(label_19, 0, 5, 1, 1);


        verticalLayout_3->addWidget(groupBox_5);


        verticalLayout_2->addWidget(groupBox_3);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_4);


        verticalLayout_4->addWidget(groupBoxState);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_5);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        retranslateUi(tlinsWManageEngineState);
        QObject::connect(radioButtonCtrlView, SIGNAL(clicked(bool)), tlinsWManageEngineState, SLOT(slotViewSelection(bool)));
        QObject::connect(radioButtonStateView, SIGNAL(clicked(bool)), tlinsWManageEngineState, SLOT(slotViewSelection(bool)));
        QObject::connect(radioButtonAllView, SIGNAL(clicked(bool)), tlinsWManageEngineState, SLOT(slotViewSelection(bool)));
        QObject::connect(rbStandard, SIGNAL(clicked(bool)), tlinsWManageEngineState, SLOT(slotViewSelection(bool)));
        QObject::connect(rbStandardSpeed, SIGNAL(clicked(bool)), tlinsWManageEngineState, SLOT(slotViewSelection(bool)));
        QObject::connect(rbGuider, SIGNAL(clicked(bool)), tlinsWManageEngineState, SLOT(slotViewSelection(bool)));
        QObject::connect(dialRARatio, SIGNAL(sliderMoved(int)), tlinsWManageEngineState, SLOT(slot_dialRARatio(int)));
        QObject::connect(dialDECRatio, SIGNAL(sliderMoved(int)), tlinsWManageEngineState, SLOT(slot_dialDECRatio(int)));
        QObject::connect(dialRACorrection, SIGNAL(sliderMoved(int)), tlinsWManageEngineState, SLOT(slot_dialRACorrection(int)));
        QObject::connect(dialDECCorrection, SIGNAL(sliderMoved(int)), tlinsWManageEngineState, SLOT(slot_dialDECCorrection(int)));

        QMetaObject::connectSlotsByName(tlinsWManageEngineState);
    } // setupUi

    void retranslateUi(QWidget *tlinsWManageEngineState)
    {
        tlinsWManageEngineState->setWindowTitle(QApplication::translate("tlinsWManageEngineState", "Form", nullptr));
        groupBox_10->setTitle(QApplication::translate("tlinsWManageEngineState", "View selection", nullptr));
        radioButtonStateView->setText(QApplication::translate("tlinsWManageEngineState", "Mount and calibration state", nullptr));
        radioButtonCtrlView->setText(QApplication::translate("tlinsWManageEngineState", "Guider/Manual corrections", nullptr));
        radioButtonAllView->setText(QApplication::translate("tlinsWManageEngineState", "Control and state view", nullptr));
        gbStateControl->setTitle(QString());
        groupBox->setTitle(QString());
        rbStandardSpeed->setText(QApplication::translate("tlinsWManageEngineState", "Standard/Manual corrections", nullptr));
        rbStandard->setText(QApplication::translate("tlinsWManageEngineState", "Step mode", nullptr));
        rbGuider->setText(QApplication::translate("tlinsWManageEngineState", "Guider", nullptr));
        btStop->setText(QApplication::translate("tlinsWManageEngineState", "Stop tracking", nullptr));
        btStart->setText(QApplication::translate("tlinsWManageEngineState", "Start tracking", nullptr));
        groupBoxGuider->setTitle(QApplication::translate("tlinsWManageEngineState", "Guider settings", nullptr));
        label_25->setText(QApplication::translate("tlinsWManageEngineState", "DEC ratio", nullptr));
        label_24->setText(QApplication::translate("tlinsWManageEngineState", "RA ratio", nullptr));
        pbSReadFromDeviceGuider->setText(QApplication::translate("tlinsWManageEngineState", "Read from device", nullptr));
        pbUpdateDeviceGuider->setText(QApplication::translate("tlinsWManageEngineState", "Update device", nullptr));
        pbStoreGuider->setText(QApplication::translate("tlinsWManageEngineState", "Store", nullptr));
        pbLoadGuider->setText(QApplication::translate("tlinsWManageEngineState", "Load", nullptr));
        groupBoxManualCorrections->setTitle(QApplication::translate("tlinsWManageEngineState", "Manual corrections", nullptr));
        label_26->setText(QApplication::translate("tlinsWManageEngineState", "RA correction", nullptr));
        label_27->setText(QApplication::translate("tlinsWManageEngineState", "DEC correction", nullptr));
        pbReadFromDeviceManual->setText(QApplication::translate("tlinsWManageEngineState", "Read from device", nullptr));
        pbUpdateDeviceManual->setText(QApplication::translate("tlinsWManageEngineState", "Update device", nullptr));
        groupBoxState->setTitle(QApplication::translate("tlinsWManageEngineState", "State management", nullptr));
        groupBox_9->setTitle(QApplication::translate("tlinsWManageEngineState", "GroupBox", nullptr));
        btDownloadState->setText(QApplication::translate("tlinsWManageEngineState", "Download state", nullptr));
        btUploadState->setText(QApplication::translate("tlinsWManageEngineState", "Upload state", nullptr));
        label->setText(QApplication::translate("tlinsWManageEngineState", "Saved states", nullptr));
        btAdd->setText(QApplication::translate("tlinsWManageEngineState", "Add", nullptr));
        btLoad->setText(QApplication::translate("tlinsWManageEngineState", "Load", nullptr));
        btSave->setText(QApplication::translate("tlinsWManageEngineState", "Save", nullptr));
        btRemove->setText(QApplication::translate("tlinsWManageEngineState", "Remove", nullptr));
        groupBox_3->setTitle(QApplication::translate("tlinsWManageEngineState", "State", nullptr));
        label_9->setText(QApplication::translate("tlinsWManageEngineState", "Name", nullptr));
        groupBox_6->setTitle(QApplication::translate("tlinsWManageEngineState", "State info", nullptr));
        label_2->setText(QApplication::translate("tlinsWManageEngineState", "Engine mode:", nullptr));
        engineMode->setText(QApplication::translate("tlinsWManageEngineState", "__mode__", nullptr));
        label_4->setText(QApplication::translate("tlinsWManageEngineState", "Engine state:", nullptr));
        engineState->setText(QApplication::translate("tlinsWManageEngineState", "__state__", nullptr));
        groupBox_2->setTitle(QApplication::translate("tlinsWManageEngineState", "Device axies direction", nullptr));
        xReverse->setText(QApplication::translate("tlinsWManageEngineState", "X reverse", nullptr));
        yReverse->setText(QApplication::translate("tlinsWManageEngineState", "Y reverse", nullptr));
        gMatrix->setTitle(QApplication::translate("tlinsWManageEngineState", "Matrix", nullptr));
        groupBox_4->setTitle(QApplication::translate("tlinsWManageEngineState", "Axies", nullptr));
        label_22->setText(QApplication::translate("tlinsWManageEngineState", "[steps]", nullptr));
        label_3->setText(QApplication::translate("tlinsWManageEngineState", "X", nullptr));
        label_20->setText(QApplication::translate("tlinsWManageEngineState", "[steps]", nullptr));
        label_13->setText(QApplication::translate("tlinsWManageEngineState", "Y", nullptr));
        label_5->setText(QApplication::translate("tlinsWManageEngineState", "X Encoder", nullptr));
        label_21->setText(QApplication::translate("tlinsWManageEngineState", "[steps]", nullptr));
        label_6->setText(QApplication::translate("tlinsWManageEngineState", "Y Encoder", nullptr));
        label_23->setText(QApplication::translate("tlinsWManageEngineState", "[steps]", nullptr));
        groupBox_5->setTitle(QApplication::translate("tlinsWManageEngineState", "Target", nullptr));
        label_8->setText(QApplication::translate("tlinsWManageEngineState", "DC", nullptr));
        label_11->setText(QApplication::translate("tlinsWManageEngineState", "Proper motion RA", nullptr));
        label_10->setText(QApplication::translate("tlinsWManageEngineState", "Paralex", nullptr));
        label_16->setText(QApplication::translate("tlinsWManageEngineState", "[mas/year]", nullptr));
        label_14->setText(QApplication::translate("tlinsWManageEngineState", "Proper Motion DC", nullptr));
        label_7->setText(QApplication::translate("tlinsWManageEngineState", "RA", nullptr));
        label_12->setText(QApplication::translate("tlinsWManageEngineState", "Radial velocity", nullptr));
        label_15->setText(QApplication::translate("tlinsWManageEngineState", "Catalog type", nullptr));
        label_17->setText(QApplication::translate("tlinsWManageEngineState", "[mas/year]", nullptr));
        label_18->setText(QApplication::translate("tlinsWManageEngineState", "[hours]", nullptr));
        label_19->setText(QApplication::translate("tlinsWManageEngineState", "[degris]", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWManageEngineState: public Ui_tlinsWManageEngineState {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWMANAGEENGINESTATE_H
