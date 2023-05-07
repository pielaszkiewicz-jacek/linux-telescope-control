/********************************************************************************
** Form generated from reading UI file 'tlinsuicalibrationwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSUICALIBRATIONWIDGET_H
#define UI_TLINSUICALIBRATIONWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "tlinswcoordinatedegris.h"
#include "tlinswobservationerror.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsUICalibrationWidget
{
public:
    QVBoxLayout *verticalLayout_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBoxMatrix;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_7;
    QGridLayout *gridLayout_6;
    tlinsWCoordinateDegris *gamma;
    QLabel *label_10;
    tlinsWCoordinateDegris *beta;
    QLabel *label_9;
    QLabel *label_8;
    tlinsWCoordinateDegris *alfa;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pbGenerateMatrix;
    QSpacerItem *horizontalSpacer_6;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout;
    QDoubleSpinBox *a33;
    QDoubleSpinBox *a22;
    QDoubleSpinBox *a11;
    QDoubleSpinBox *a13;
    QDoubleSpinBox *a23;
    QDoubleSpinBox *a31;
    QDoubleSpinBox *a32;
    QDoubleSpinBox *a12;
    QDoubleSpinBox *a21;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *btStartCalibration;
    QSpacerItem *horizontalSpacer_9;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QPushButton *btMoveUp;
    QPushButton *btMoveDown;
    QSpacerItem *verticalSpacer;
    QCheckBox *checkBoxEnableDebug;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSpinBox *singleObjectMeasurments;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *confirmDeferred;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *checkAsDeferred;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *btCloseCalibration;
    QSpacerItem *horizontalSpacer_13;
    QLabel *label;
    QGroupBox *groupBoxTrackingMode;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *tManual;
    QRadioButton *tStandard;
    QRadioButton *tSpeed;
    QRadioButton *tGuider;
    tlinsWObservationError *errors;
    QCheckBox *chbOverriteErrors;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btSetReference;
    QTableView *referenceObjects;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btSave;
    QPushButton *btLoad;
    QPushButton *btSearchObject;
    QPushButton *btRemoveObject;
    QGroupBox *axiesDirectionGroup;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_12;
    QCheckBox *chbXReverse;
    QCheckBox *chbYReverse;
    QSpacerItem *horizontalSpacer_11;

    void setupUi(QWidget *tlinsUICalibrationWidget)
    {
        if (tlinsUICalibrationWidget->objectName().isEmpty())
            tlinsUICalibrationWidget->setObjectName(QString::fromUtf8("tlinsUICalibrationWidget"));
        tlinsUICalibrationWidget->resize(1205, 1003);
        verticalLayout_3 = new QVBoxLayout(tlinsUICalibrationWidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        scrollArea = new QScrollArea(tlinsUICalibrationWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1185, 983));
        verticalLayout_5 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBoxMatrix = new QGroupBox(groupBox);
        groupBoxMatrix->setObjectName(QString::fromUtf8("groupBoxMatrix"));
        groupBoxMatrix->setCheckable(false);
        groupBoxMatrix->setChecked(false);
        horizontalLayout_2 = new QHBoxLayout(groupBoxMatrix);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gamma = new tlinsWCoordinateDegris(groupBoxMatrix);
        gamma->setObjectName(QString::fromUtf8("gamma"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gamma->sizePolicy().hasHeightForWidth());
        gamma->setSizePolicy(sizePolicy);
        gamma->setMinimumSize(QSize(0, 32));

        gridLayout_6->addWidget(gamma, 2, 1, 1, 1);

        label_10 = new QLabel(groupBoxMatrix);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);
        label_10->setMinimumSize(QSize(0, 32));

        gridLayout_6->addWidget(label_10, 2, 0, 1, 1);

        beta = new tlinsWCoordinateDegris(groupBoxMatrix);
        beta->setObjectName(QString::fromUtf8("beta"));
        sizePolicy.setHeightForWidth(beta->sizePolicy().hasHeightForWidth());
        beta->setSizePolicy(sizePolicy);
        beta->setMinimumSize(QSize(0, 32));

        gridLayout_6->addWidget(beta, 1, 1, 1, 1);

        label_9 = new QLabel(groupBoxMatrix);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);
        label_9->setMinimumSize(QSize(0, 32));

        gridLayout_6->addWidget(label_9, 1, 0, 1, 1);

        label_8 = new QLabel(groupBoxMatrix);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);
        label_8->setMinimumSize(QSize(0, 32));

        gridLayout_6->addWidget(label_8, 0, 0, 1, 1);

        alfa = new tlinsWCoordinateDegris(groupBoxMatrix);
        alfa->setObjectName(QString::fromUtf8("alfa"));
        sizePolicy.setHeightForWidth(alfa->sizePolicy().hasHeightForWidth());
        alfa->setSizePolicy(sizePolicy);
        alfa->setMinimumSize(QSize(0, 32));

        gridLayout_6->addWidget(alfa, 0, 1, 1, 1);


        verticalLayout_7->addLayout(gridLayout_6);


        horizontalLayout_2->addLayout(verticalLayout_7);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        pbGenerateMatrix = new QPushButton(groupBoxMatrix);
        pbGenerateMatrix->setObjectName(QString::fromUtf8("pbGenerateMatrix"));
        pbGenerateMatrix->setMinimumSize(QSize(0, 60));

        horizontalLayout_2->addWidget(pbGenerateMatrix);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        groupBox_6 = new QGroupBox(groupBoxMatrix);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setFlat(true);
        gridLayout = new QGridLayout(groupBox_6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, 0, -1, -1);
        a33 = new QDoubleSpinBox(groupBox_6);
        a33->setObjectName(QString::fromUtf8("a33"));
        a33->setEnabled(true);
        a33->setMinimumSize(QSize(0, 30));
        QFont font;
        font.setPointSize(11);
        a33->setFont(font);
        a33->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        a33->setReadOnly(false);
        a33->setButtonSymbols(QAbstractSpinBox::NoButtons);
        a33->setDecimals(12);
        a33->setMinimum(-10000.000000000000000);
        a33->setMaximum(10000.000000000000000);

        gridLayout->addWidget(a33, 7, 2, 1, 1);

        a22 = new QDoubleSpinBox(groupBox_6);
        a22->setObjectName(QString::fromUtf8("a22"));
        a22->setEnabled(true);
        a22->setMinimumSize(QSize(0, 30));
        a22->setFont(font);
        a22->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        a22->setReadOnly(false);
        a22->setButtonSymbols(QAbstractSpinBox::NoButtons);
        a22->setDecimals(12);
        a22->setMinimum(-10000.000000000000000);
        a22->setMaximum(10000.000000000000000);

        gridLayout->addWidget(a22, 6, 1, 1, 1);

        a11 = new QDoubleSpinBox(groupBox_6);
        a11->setObjectName(QString::fromUtf8("a11"));
        a11->setEnabled(true);
        a11->setMinimumSize(QSize(0, 30));
        a11->setFont(font);
        a11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        a11->setReadOnly(false);
        a11->setButtonSymbols(QAbstractSpinBox::NoButtons);
        a11->setKeyboardTracking(true);
        a11->setDecimals(12);
        a11->setMinimum(-10000.000000000000000);
        a11->setMaximum(10000.000000000000000);

        gridLayout->addWidget(a11, 5, 0, 1, 1);

        a13 = new QDoubleSpinBox(groupBox_6);
        a13->setObjectName(QString::fromUtf8("a13"));
        a13->setEnabled(true);
        a13->setMinimumSize(QSize(0, 30));
        a13->setFont(font);
        a13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        a13->setReadOnly(false);
        a13->setButtonSymbols(QAbstractSpinBox::NoButtons);
        a13->setDecimals(12);
        a13->setMinimum(-10000.000000000000000);
        a13->setMaximum(10000.000000000000000);

        gridLayout->addWidget(a13, 5, 2, 1, 1);

        a23 = new QDoubleSpinBox(groupBox_6);
        a23->setObjectName(QString::fromUtf8("a23"));
        a23->setEnabled(true);
        a23->setMinimumSize(QSize(0, 30));
        a23->setFont(font);
        a23->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        a23->setReadOnly(false);
        a23->setButtonSymbols(QAbstractSpinBox::NoButtons);
        a23->setDecimals(12);
        a23->setMinimum(-10000.000000000000000);
        a23->setMaximum(10000.000000000000000);

        gridLayout->addWidget(a23, 6, 2, 1, 1);

        a31 = new QDoubleSpinBox(groupBox_6);
        a31->setObjectName(QString::fromUtf8("a31"));
        a31->setEnabled(true);
        a31->setMinimumSize(QSize(0, 30));
        a31->setFont(font);
        a31->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        a31->setReadOnly(false);
        a31->setButtonSymbols(QAbstractSpinBox::NoButtons);
        a31->setDecimals(12);
        a31->setMinimum(-10000.000000000000000);
        a31->setMaximum(10000.000000000000000);

        gridLayout->addWidget(a31, 7, 0, 1, 1);

        a32 = new QDoubleSpinBox(groupBox_6);
        a32->setObjectName(QString::fromUtf8("a32"));
        a32->setEnabled(true);
        a32->setMinimumSize(QSize(0, 30));
        a32->setFont(font);
        a32->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        a32->setReadOnly(false);
        a32->setButtonSymbols(QAbstractSpinBox::NoButtons);
        a32->setDecimals(12);
        a32->setMinimum(-10000.000000000000000);
        a32->setMaximum(10000.000000000000000);

        gridLayout->addWidget(a32, 7, 1, 1, 1);

        a12 = new QDoubleSpinBox(groupBox_6);
        a12->setObjectName(QString::fromUtf8("a12"));
        a12->setEnabled(true);
        a12->setMinimumSize(QSize(0, 30));
        a12->setFont(font);
        a12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        a12->setReadOnly(false);
        a12->setButtonSymbols(QAbstractSpinBox::NoButtons);
        a12->setDecimals(12);
        a12->setMinimum(-10000.000000000000000);
        a12->setMaximum(10000.000000000000000);

        gridLayout->addWidget(a12, 5, 1, 1, 1);

        a21 = new QDoubleSpinBox(groupBox_6);
        a21->setObjectName(QString::fromUtf8("a21"));
        a21->setEnabled(true);
        a21->setMinimumSize(QSize(0, 30));
        a21->setFont(font);
        a21->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        a21->setReadOnly(false);
        a21->setButtonSymbols(QAbstractSpinBox::NoButtons);
        a21->setDecimals(12);
        a21->setMinimum(-10000.000000000000000);
        a21->setMaximum(10000.000000000000000);

        gridLayout->addWidget(a21, 6, 0, 1, 1);


        horizontalLayout_2->addWidget(groupBox_6);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_10);


        gridLayout_3->addWidget(groupBoxMatrix, 3, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, 5, -1, 5);
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_8);

        btStartCalibration = new QPushButton(groupBox);
        btStartCalibration->setObjectName(QString::fromUtf8("btStartCalibration"));
        btStartCalibration->setMinimumSize(QSize(160, 60));

        horizontalLayout_5->addWidget(btStartCalibration);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_9);


        gridLayout_3->addLayout(horizontalLayout_5, 5, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        btMoveUp = new QPushButton(groupBox);
        btMoveUp->setObjectName(QString::fromUtf8("btMoveUp"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btMoveUp->sizePolicy().hasHeightForWidth());
        btMoveUp->setSizePolicy(sizePolicy1);
        btMoveUp->setMinimumSize(QSize(90, 60));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/ic_keyboard_arrow_up_black_24px.svg"), QSize(), QIcon::Normal, QIcon::Off);
        btMoveUp->setIcon(icon);
        btMoveUp->setIconSize(QSize(20, 20));
        btMoveUp->setAutoDefault(true);
        btMoveUp->setFlat(false);

        verticalLayout->addWidget(btMoveUp);

        btMoveDown = new QPushButton(groupBox);
        btMoveDown->setObjectName(QString::fromUtf8("btMoveDown"));
        sizePolicy1.setHeightForWidth(btMoveDown->sizePolicy().hasHeightForWidth());
        btMoveDown->setSizePolicy(sizePolicy1);
        btMoveDown->setMinimumSize(QSize(90, 60));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/ic_keyboard_arrow_down_black_24px.svg"), QSize(), QIcon::Normal, QIcon::Off);
        btMoveDown->setIcon(icon1);
        btMoveDown->setIconSize(QSize(18, 18));

        verticalLayout->addWidget(btMoveDown);

        verticalSpacer = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout_3->addLayout(verticalLayout, 0, 1, 1, 1);

        checkBoxEnableDebug = new QCheckBox(groupBox);
        checkBoxEnableDebug->setObjectName(QString::fromUtf8("checkBoxEnableDebug"));

        gridLayout_3->addWidget(checkBoxEnableDebug, 2, 0, 1, 1);

        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy2);
        gridLayout_2 = new QGridLayout(groupBox_4);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        singleObjectMeasurments = new QSpinBox(groupBox_4);
        singleObjectMeasurments->setObjectName(QString::fromUtf8("singleObjectMeasurments"));
        singleObjectMeasurments->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        singleObjectMeasurments->setReadOnly(false);
        singleObjectMeasurments->setButtonSymbols(QAbstractSpinBox::NoButtons);

        horizontalLayout->addWidget(singleObjectMeasurments);


        gridLayout_2->addLayout(horizontalLayout, 1, 5, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 3, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 2, 8, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 2, 0, 1, 1);

        confirmDeferred = new QPushButton(groupBox_4);
        confirmDeferred->setObjectName(QString::fromUtf8("confirmDeferred"));
        confirmDeferred->setMinimumSize(QSize(180, 60));

        gridLayout_2->addWidget(confirmDeferred, 2, 5, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 2, 6, 1, 1);

        checkAsDeferred = new QCheckBox(groupBox_4);
        checkAsDeferred->setObjectName(QString::fromUtf8("checkAsDeferred"));

        gridLayout_2->addWidget(checkAsDeferred, 1, 1, 1, 1);

        groupBox_2 = new QGroupBox(groupBox_4);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_6 = new QHBoxLayout(groupBox_2);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        btCloseCalibration = new QPushButton(groupBox_2);
        btCloseCalibration->setObjectName(QString::fromUtf8("btCloseCalibration"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(btCloseCalibration->sizePolicy().hasHeightForWidth());
        btCloseCalibration->setSizePolicy(sizePolicy3);
        btCloseCalibration->setMinimumSize(QSize(180, 60));
        btCloseCalibration->setMaximumSize(QSize(16777215, 60));
        QFont font1;
        font1.setItalic(true);
        btCloseCalibration->setFont(font1);

        horizontalLayout_6->addWidget(btCloseCalibration);

        horizontalSpacer_13 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_13);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_6->addWidget(label);

        groupBoxTrackingMode = new QGroupBox(groupBox_2);
        groupBoxTrackingMode->setObjectName(QString::fromUtf8("groupBoxTrackingMode"));
        verticalLayout_4 = new QVBoxLayout(groupBoxTrackingMode);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        tManual = new QRadioButton(groupBoxTrackingMode);
        tManual->setObjectName(QString::fromUtf8("tManual"));

        verticalLayout_4->addWidget(tManual);

        tStandard = new QRadioButton(groupBoxTrackingMode);
        tStandard->setObjectName(QString::fromUtf8("tStandard"));

        verticalLayout_4->addWidget(tStandard);

        tSpeed = new QRadioButton(groupBoxTrackingMode);
        tSpeed->setObjectName(QString::fromUtf8("tSpeed"));

        verticalLayout_4->addWidget(tSpeed);

        tGuider = new QRadioButton(groupBoxTrackingMode);
        tGuider->setObjectName(QString::fromUtf8("tGuider"));

        verticalLayout_4->addWidget(tGuider);


        horizontalLayout_6->addWidget(groupBoxTrackingMode);


        gridLayout_2->addWidget(groupBox_2, 2, 7, 1, 1);

        errors = new tlinsWObservationError(groupBox_4);
        errors->setObjectName(QString::fromUtf8("errors"));

        gridLayout_2->addWidget(errors, 3, 5, 1, 1);

        chbOverriteErrors = new QCheckBox(groupBox_4);
        chbOverriteErrors->setObjectName(QString::fromUtf8("chbOverriteErrors"));

        gridLayout_2->addWidget(chbOverriteErrors, 3, 1, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        btSetReference = new QPushButton(groupBox_4);
        btSetReference->setObjectName(QString::fromUtf8("btSetReference"));
        sizePolicy3.setHeightForWidth(btSetReference->sizePolicy().hasHeightForWidth());
        btSetReference->setSizePolicy(sizePolicy3);
        btSetReference->setMinimumSize(QSize(180, 60));
        btSetReference->setMaximumSize(QSize(16777215, 60));
        btSetReference->setFont(font1);
        btSetReference->setCheckable(true);

        verticalLayout_2->addWidget(btSetReference);


        gridLayout_2->addLayout(verticalLayout_2, 2, 1, 1, 2);


        gridLayout_3->addWidget(groupBox_4, 4, 0, 1, 1);

        referenceObjects = new QTableView(groupBox);
        referenceObjects->setObjectName(QString::fromUtf8("referenceObjects"));
        referenceObjects->setMinimumSize(QSize(0, 200));

        gridLayout_3->addWidget(referenceObjects, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        btSave = new QPushButton(groupBox);
        btSave->setObjectName(QString::fromUtf8("btSave"));
        sizePolicy1.setHeightForWidth(btSave->sizePolicy().hasHeightForWidth());
        btSave->setSizePolicy(sizePolicy1);
        btSave->setMinimumSize(QSize(0, 60));

        horizontalLayout_4->addWidget(btSave);

        btLoad = new QPushButton(groupBox);
        btLoad->setObjectName(QString::fromUtf8("btLoad"));
        sizePolicy1.setHeightForWidth(btLoad->sizePolicy().hasHeightForWidth());
        btLoad->setSizePolicy(sizePolicy1);
        btLoad->setMinimumSize(QSize(0, 60));

        horizontalLayout_4->addWidget(btLoad);

        btSearchObject = new QPushButton(groupBox);
        btSearchObject->setObjectName(QString::fromUtf8("btSearchObject"));
        sizePolicy1.setHeightForWidth(btSearchObject->sizePolicy().hasHeightForWidth());
        btSearchObject->setSizePolicy(sizePolicy1);
        btSearchObject->setMinimumSize(QSize(0, 60));

        horizontalLayout_4->addWidget(btSearchObject);

        btRemoveObject = new QPushButton(groupBox);
        btRemoveObject->setObjectName(QString::fromUtf8("btRemoveObject"));
        sizePolicy1.setHeightForWidth(btRemoveObject->sizePolicy().hasHeightForWidth());
        btRemoveObject->setSizePolicy(sizePolicy1);
        btRemoveObject->setMinimumSize(QSize(0, 60));

        horizontalLayout_4->addWidget(btRemoveObject);


        gridLayout_3->addLayout(horizontalLayout_4, 1, 0, 1, 1);

        axiesDirectionGroup = new QGroupBox(groupBox);
        axiesDirectionGroup->setObjectName(QString::fromUtf8("axiesDirectionGroup"));
        axiesDirectionGroup->setCheckable(true);
        axiesDirectionGroup->setChecked(false);
        horizontalLayout_3 = new QHBoxLayout(axiesDirectionGroup);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_12);

        chbXReverse = new QCheckBox(axiesDirectionGroup);
        chbXReverse->setObjectName(QString::fromUtf8("chbXReverse"));

        horizontalLayout_3->addWidget(chbXReverse);

        chbYReverse = new QCheckBox(axiesDirectionGroup);
        chbYReverse->setObjectName(QString::fromUtf8("chbYReverse"));

        horizontalLayout_3->addWidget(chbYReverse);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_11);


        gridLayout_3->addWidget(axiesDirectionGroup, 6, 0, 1, 1);


        verticalLayout_5->addWidget(groupBox);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_3->addWidget(scrollArea);


        retranslateUi(tlinsUICalibrationWidget);
        QObject::connect(checkBoxEnableDebug, SIGNAL(clicked()), tlinsUICalibrationWidget, SLOT(checkBoxEnableDebugSlot()));

        QMetaObject::connectSlotsByName(tlinsUICalibrationWidget);
    } // setupUi

    void retranslateUi(QWidget *tlinsUICalibrationWidget)
    {
        tlinsUICalibrationWidget->setWindowTitle(QApplication::translate("tlinsUICalibrationWidget", "Form", nullptr));
        groupBox->setTitle(QApplication::translate("tlinsUICalibrationWidget", "Reference objects ", nullptr));
        groupBoxMatrix->setTitle(QString());
        label_10->setText(QApplication::translate("tlinsUICalibrationWidget", "Gamma", nullptr));
        label_9->setText(QApplication::translate("tlinsUICalibrationWidget", "Beta", nullptr));
        label_8->setText(QApplication::translate("tlinsUICalibrationWidget", "Alfa", nullptr));
        pbGenerateMatrix->setText(QApplication::translate("tlinsUICalibrationWidget", "Generate", nullptr));
        groupBox_6->setTitle(QApplication::translate("tlinsUICalibrationWidget", "Matrix", nullptr));
        btStartCalibration->setText(QApplication::translate("tlinsUICalibrationWidget", "Start/reset calibration", nullptr));
        btMoveUp->setText(QString());
        btMoveDown->setText(QString());
        checkBoxEnableDebug->setText(QApplication::translate("tlinsUICalibrationWidget", "Debug - euler angles", nullptr));
        groupBox_4->setTitle(QString());
        label_2->setText(QApplication::translate("tlinsUICalibrationWidget", "Count", nullptr));
        confirmDeferred->setText(QApplication::translate("tlinsUICalibrationWidget", "Confirm deferred", nullptr));
        checkAsDeferred->setText(QApplication::translate("tlinsUICalibrationWidget", "As deferred", nullptr));
        groupBox_2->setTitle(QString());
        btCloseCalibration->setText(QApplication::translate("tlinsUICalibrationWidget", "Close calibration", nullptr));
        label->setText(QApplication::translate("tlinsUICalibrationWidget", "Tracking:", nullptr));
        groupBoxTrackingMode->setTitle(QString());
        tManual->setText(QApplication::translate("tlinsUICalibrationWidget", "Manual", nullptr));
        tStandard->setText(QApplication::translate("tlinsUICalibrationWidget", "Standard", nullptr));
        tSpeed->setText(QApplication::translate("tlinsUICalibrationWidget", "Speed", nullptr));
        tGuider->setText(QApplication::translate("tlinsUICalibrationWidget", "Guider", nullptr));
        chbOverriteErrors->setText(QApplication::translate("tlinsUICalibrationWidget", "Overwrite errors", nullptr));
        btSetReference->setText(QApplication::translate("tlinsUICalibrationWidget", "Set reference object", nullptr));
        btSave->setText(QApplication::translate("tlinsUICalibrationWidget", "Save", nullptr));
        btLoad->setText(QApplication::translate("tlinsUICalibrationWidget", "Load", nullptr));
        btSearchObject->setText(QApplication::translate("tlinsUICalibrationWidget", "Search", nullptr));
        btRemoveObject->setText(QApplication::translate("tlinsUICalibrationWidget", "Remove", nullptr));
        axiesDirectionGroup->setTitle(QApplication::translate("tlinsUICalibrationWidget", "Overwrite axises direction:", nullptr));
        chbXReverse->setText(QApplication::translate("tlinsUICalibrationWidget", "X reverse", nullptr));
        chbYReverse->setText(QApplication::translate("tlinsUICalibrationWidget", "Y reverse", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsUICalibrationWidget: public Ui_tlinsUICalibrationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSUICALIBRATIONWIDGET_H
