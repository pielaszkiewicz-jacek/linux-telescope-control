/********************************************************************************
** Form generated from reading UI file 'tlinsuipolit4.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSUIPOLIT4_H
#define UI_TLINSUIPOLIT4_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <tlinswdecimalvalue.h>
#include "tlinswcoordinatedeclination.h"
#include "tlinswcoordinatedegris.h"
#include "tlinswcoordinatehourangle.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsUiPolit4
{
public:
    QHBoxLayout *horizontalLayout_4;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_8;
    QCheckBox *speedMode;
    QCheckBox *inSteps;
    QSpacerItem *horizontalSpacer_7;
    QGridLayout *gridLayout_2;
    QPushButton *bRight;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;
    QPushButton *bStop;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *bLeft;
    QPushButton *bUp;
    QPushButton *bAbort;
    QPushButton *bDown;
    QSpacerItem *verticalSpacer_2;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_5;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_6;
    QLabel *ltddy;
    QLabel *ltdax;
    tlinsWDecimalValue *Sy;
    QLabel *ldsy;
    QLabel *ltday;
    QLabel *ltddx;
    tlinsWCoordinateHourAngle *RaX;
    QLabel *lday;
    tlinsWDecimalValue *VSy;
    tlinsWCoordinateDegris *VDy;
    QLabel *lvdy;
    QLabel *ltvdy;
    tlinsWCoordinateDeclination *VDc;
    QLabel *ldsx;
    tlinsWCoordinateDegris *VDx;
    QLabel *ldax;
    QLabel *lddx;
    QLabel *ltvsy;
    QLabel *lvsy;
    tlinsWCoordinateHourAngle *VRa;
    QLabel *ltvax;
    QLabel *lvsx;
    QLabel *ltvdx;
    tlinsWCoordinateDeclination *DcY;
    QLabel *lvdx;
    tlinsWCoordinateDegris *Dy;
    QLabel *ltvay;
    QLabel *ltvsx;
    QLabel *lvay;
    tlinsWDecimalValue *Sx;
    QLabel *ltdsx;
    tlinsWDecimalValue *VSx;
    tlinsWCoordinateDegris *Dx;
    QLabel *lddy;
    QLabel *ltdsy;
    QLabel *lvax;
    QFrame *line_3;

    void setupUi(QWidget *tlinsUiPolit4)
    {
        if (tlinsUiPolit4->objectName().isEmpty())
            tlinsUiPolit4->setObjectName(QString::fromUtf8("tlinsUiPolit4"));
        tlinsUiPolit4->resize(739, 988);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tlinsUiPolit4->sizePolicy().hasHeightForWidth());
        tlinsUiPolit4->setSizePolicy(sizePolicy);
        horizontalLayout_4 = new QHBoxLayout(tlinsUiPolit4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, -1, 0, -1);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_8);

        speedMode = new QCheckBox(tlinsUiPolit4);
        speedMode->setObjectName(QString::fromUtf8("speedMode"));
        QFont font;
        font.setPointSize(11);
        font.setItalic(true);
        speedMode->setFont(font);

        horizontalLayout_2->addWidget(speedMode);

        inSteps = new QCheckBox(tlinsUiPolit4);
        inSteps->setObjectName(QString::fromUtf8("inSteps"));
        inSteps->setFont(font);

        horizontalLayout_2->addWidget(inSteps);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_7);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(15);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(-1, 15, -1, 15);
        bRight = new QPushButton(tlinsUiPolit4);
        bRight->setObjectName(QString::fromUtf8("bRight"));
        sizePolicy.setHeightForWidth(bRight->sizePolicy().hasHeightForWidth());
        bRight->setSizePolicy(sizePolicy);
        bRight->setMinimumSize(QSize(170, 150));
        bRight->setMaximumSize(QSize(170, 150));
        bRight->setSizeIncrement(QSize(1, 1));
        bRight->setBaseSize(QSize(20, 20));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/ic_keyboard_arrow_right_black_24px.svg"), QSize(), QIcon::Normal, QIcon::Off);
        bRight->setIcon(icon);
        bRight->setIconSize(QSize(70, 70));
        bRight->setAutoRepeat(false);
        bRight->setAutoExclusive(false);
        bRight->setFlat(false);

        gridLayout_2->addWidget(bRight, 2, 4, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 3, 1, 1);

        bStop = new QPushButton(tlinsUiPolit4);
        bStop->setObjectName(QString::fromUtf8("bStop"));
        sizePolicy.setHeightForWidth(bStop->sizePolicy().hasHeightForWidth());
        bStop->setSizePolicy(sizePolicy);
        bStop->setMinimumSize(QSize(170, 120));
        bStop->setMaximumSize(QSize(170, 120));
        bStop->setSizeIncrement(QSize(1, 1));
        bStop->setBaseSize(QSize(20, 20));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/pause.svg"), QSize(), QIcon::Normal, QIcon::Off);
        bStop->setIcon(icon1);
        bStop->setIconSize(QSize(50, 50));
        bStop->setFlat(false);

        gridLayout_2->addWidget(bStop, 5, 4, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 2, 5, 1, 1);

        bLeft = new QPushButton(tlinsUiPolit4);
        bLeft->setObjectName(QString::fromUtf8("bLeft"));
        sizePolicy.setHeightForWidth(bLeft->sizePolicy().hasHeightForWidth());
        bLeft->setSizePolicy(sizePolicy);
        bLeft->setMinimumSize(QSize(170, 150));
        bLeft->setMaximumSize(QSize(170, 150));
        bLeft->setSizeIncrement(QSize(1, 1));
        bLeft->setBaseSize(QSize(20, 20));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/ic_keyboard_arrow_left_black_24px.svg"), QSize(), QIcon::Normal, QIcon::Off);
        bLeft->setIcon(icon2);
        bLeft->setIconSize(QSize(70, 70));
        bLeft->setAutoRepeat(false);
        bLeft->setAutoExclusive(false);
        bLeft->setFlat(false);

        gridLayout_2->addWidget(bLeft, 2, 2, 1, 1);

        bUp = new QPushButton(tlinsUiPolit4);
        bUp->setObjectName(QString::fromUtf8("bUp"));
        sizePolicy.setHeightForWidth(bUp->sizePolicy().hasHeightForWidth());
        bUp->setSizePolicy(sizePolicy);
        bUp->setMinimumSize(QSize(170, 150));
        bUp->setMaximumSize(QSize(170, 150));
        bUp->setSizeIncrement(QSize(1, 1));
        bUp->setBaseSize(QSize(20, 20));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/ic_keyboard_arrow_up_black_24px.svg"), QSize(), QIcon::Normal, QIcon::Off);
        bUp->setIcon(icon3);
        bUp->setIconSize(QSize(70, 70));
        bUp->setAutoRepeat(false);
        bUp->setAutoExclusive(false);
        bUp->setFlat(false);

        gridLayout_2->addWidget(bUp, 1, 3, 1, 1);

        bAbort = new QPushButton(tlinsUiPolit4);
        bAbort->setObjectName(QString::fromUtf8("bAbort"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(bAbort->sizePolicy().hasHeightForWidth());
        bAbort->setSizePolicy(sizePolicy1);
        bAbort->setMinimumSize(QSize(170, 120));
        bAbort->setMaximumSize(QSize(170, 120));
        bAbort->setSizeIncrement(QSize(1, 1));
        bAbort->setBaseSize(QSize(20, 20));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/cancel-button.svg"), QSize(), QIcon::Normal, QIcon::Off);
        bAbort->setIcon(icon4);
        bAbort->setIconSize(QSize(50, 50));
        bAbort->setFlat(false);

        gridLayout_2->addWidget(bAbort, 5, 2, 1, 1);

        bDown = new QPushButton(tlinsUiPolit4);
        bDown->setObjectName(QString::fromUtf8("bDown"));
        sizePolicy.setHeightForWidth(bDown->sizePolicy().hasHeightForWidth());
        bDown->setSizePolicy(sizePolicy);
        bDown->setMinimumSize(QSize(170, 150));
        bDown->setMaximumSize(QSize(170, 150));
        bDown->setSizeIncrement(QSize(1, 1));
        bDown->setBaseSize(QSize(20, 20));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/ic_keyboard_arrow_down_black_24px.svg"), QSize(), QIcon::Normal, QIcon::Off);
        bDown->setIcon(icon5);
        bDown->setIconSize(QSize(70, 70));
        bDown->setAutoRepeat(false);
        bDown->setAutoExclusive(false);
        bDown->setFlat(false);

        gridLayout_2->addWidget(bDown, 3, 3, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 4, 3, 1, 1);


        gridLayout->addLayout(gridLayout_2, 4, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalSpacer_9 = new QSpacerItem(160, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_9, 0, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(160, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_5, 0, 2, 1, 1);

        groupBox = new QGroupBox(tlinsUiPolit4);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy2);
        groupBox->setFont(font);
        groupBox->setFlat(true);
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setHorizontalSpacing(10);
        ltddy = new QLabel(groupBox);
        ltddy->setObjectName(QString::fromUtf8("ltddy"));
        QFont font1;
        font1.setPointSize(10);
        font1.setItalic(false);
        ltddy->setFont(font1);
        ltddy->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(ltddy, 1, 5, 1, 1);

        ltdax = new QLabel(groupBox);
        ltdax->setObjectName(QString::fromUtf8("ltdax"));
        ltdax->setFont(font1);
        ltdax->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(ltdax, 2, 2, 1, 1);

        Sy = new tlinsWDecimalValue(groupBox);
        Sy->setObjectName(QString::fromUtf8("Sy"));
        Sy->setFont(font1);

        gridLayout_6->addWidget(Sy, 0, 4, 1, 1);

        ldsy = new QLabel(groupBox);
        ldsy->setObjectName(QString::fromUtf8("ldsy"));
        ldsy->setFont(font1);
        ldsy->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(ldsy, 0, 3, 1, 1);

        ltday = new QLabel(groupBox);
        ltday->setObjectName(QString::fromUtf8("ltday"));
        ltday->setFont(font1);
        ltday->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(ltday, 2, 5, 1, 1);

        ltddx = new QLabel(groupBox);
        ltddx->setObjectName(QString::fromUtf8("ltddx"));
        ltddx->setFont(font1);
        ltddx->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(ltddx, 1, 2, 1, 1);

        RaX = new tlinsWCoordinateHourAngle(groupBox);
        RaX->setObjectName(QString::fromUtf8("RaX"));
        RaX->setFont(font1);

        gridLayout_6->addWidget(RaX, 2, 1, 1, 1);

        lday = new QLabel(groupBox);
        lday->setObjectName(QString::fromUtf8("lday"));
        lday->setFont(font1);
        lday->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(lday, 2, 3, 1, 1);

        VSy = new tlinsWDecimalValue(groupBox);
        VSy->setObjectName(QString::fromUtf8("VSy"));
        VSy->setFont(font1);

        gridLayout_6->addWidget(VSy, 3, 4, 1, 1);

        VDy = new tlinsWCoordinateDegris(groupBox);
        VDy->setObjectName(QString::fromUtf8("VDy"));
        VDy->setFont(font1);

        gridLayout_6->addWidget(VDy, 4, 4, 1, 1);

        lvdy = new QLabel(groupBox);
        lvdy->setObjectName(QString::fromUtf8("lvdy"));
        lvdy->setFont(font1);
        lvdy->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(lvdy, 4, 3, 1, 1);

        ltvdy = new QLabel(groupBox);
        ltvdy->setObjectName(QString::fromUtf8("ltvdy"));
        ltvdy->setFont(font1);
        ltvdy->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(ltvdy, 4, 5, 1, 1);

        VDc = new tlinsWCoordinateDeclination(groupBox);
        VDc->setObjectName(QString::fromUtf8("VDc"));
        VDc->setFont(font1);

        gridLayout_6->addWidget(VDc, 5, 4, 1, 1);

        ldsx = new QLabel(groupBox);
        ldsx->setObjectName(QString::fromUtf8("ldsx"));
        ldsx->setFont(font1);
        ldsx->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(ldsx, 0, 0, 1, 1);

        VDx = new tlinsWCoordinateDegris(groupBox);
        VDx->setObjectName(QString::fromUtf8("VDx"));
        VDx->setFont(font1);

        gridLayout_6->addWidget(VDx, 4, 1, 1, 1);

        ldax = new QLabel(groupBox);
        ldax->setObjectName(QString::fromUtf8("ldax"));
        ldax->setFont(font1);
        ldax->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(ldax, 2, 0, 1, 1);

        lddx = new QLabel(groupBox);
        lddx->setObjectName(QString::fromUtf8("lddx"));
        lddx->setFont(font1);
        lddx->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(lddx, 1, 0, 1, 1);

        ltvsy = new QLabel(groupBox);
        ltvsy->setObjectName(QString::fromUtf8("ltvsy"));
        ltvsy->setFont(font1);
        ltvsy->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(ltvsy, 3, 5, 1, 1);

        lvsy = new QLabel(groupBox);
        lvsy->setObjectName(QString::fromUtf8("lvsy"));
        lvsy->setFont(font1);
        lvsy->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(lvsy, 3, 3, 1, 1);

        VRa = new tlinsWCoordinateHourAngle(groupBox);
        VRa->setObjectName(QString::fromUtf8("VRa"));
        VRa->setFont(font1);

        gridLayout_6->addWidget(VRa, 5, 1, 1, 1);

        ltvax = new QLabel(groupBox);
        ltvax->setObjectName(QString::fromUtf8("ltvax"));
        ltvax->setFont(font1);
        ltvax->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(ltvax, 5, 2, 1, 1);

        lvsx = new QLabel(groupBox);
        lvsx->setObjectName(QString::fromUtf8("lvsx"));
        lvsx->setFont(font1);
        lvsx->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(lvsx, 3, 0, 1, 1);

        ltvdx = new QLabel(groupBox);
        ltvdx->setObjectName(QString::fromUtf8("ltvdx"));
        ltvdx->setFont(font1);
        ltvdx->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(ltvdx, 4, 2, 1, 1);

        DcY = new tlinsWCoordinateDeclination(groupBox);
        DcY->setObjectName(QString::fromUtf8("DcY"));
        DcY->setFont(font1);

        gridLayout_6->addWidget(DcY, 2, 4, 1, 1);

        lvdx = new QLabel(groupBox);
        lvdx->setObjectName(QString::fromUtf8("lvdx"));
        lvdx->setFont(font1);
        lvdx->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(lvdx, 4, 0, 1, 1);

        Dy = new tlinsWCoordinateDegris(groupBox);
        Dy->setObjectName(QString::fromUtf8("Dy"));
        Dy->setFont(font1);

        gridLayout_6->addWidget(Dy, 1, 4, 1, 1);

        ltvay = new QLabel(groupBox);
        ltvay->setObjectName(QString::fromUtf8("ltvay"));
        ltvay->setFont(font1);
        ltvay->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(ltvay, 5, 5, 1, 1);

        ltvsx = new QLabel(groupBox);
        ltvsx->setObjectName(QString::fromUtf8("ltvsx"));
        ltvsx->setFont(font1);
        ltvsx->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(ltvsx, 3, 2, 1, 1);

        lvay = new QLabel(groupBox);
        lvay->setObjectName(QString::fromUtf8("lvay"));
        lvay->setFont(font1);
        lvay->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(lvay, 5, 3, 1, 1);

        Sx = new tlinsWDecimalValue(groupBox);
        Sx->setObjectName(QString::fromUtf8("Sx"));
        Sx->setFont(font1);

        gridLayout_6->addWidget(Sx, 0, 1, 1, 1);

        ltdsx = new QLabel(groupBox);
        ltdsx->setObjectName(QString::fromUtf8("ltdsx"));
        ltdsx->setFont(font1);
        ltdsx->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(ltdsx, 0, 2, 1, 1);

        VSx = new tlinsWDecimalValue(groupBox);
        VSx->setObjectName(QString::fromUtf8("VSx"));
        VSx->setFont(font1);

        gridLayout_6->addWidget(VSx, 3, 1, 1, 1);

        Dx = new tlinsWCoordinateDegris(groupBox);
        Dx->setObjectName(QString::fromUtf8("Dx"));
        Dx->setFont(font1);

        gridLayout_6->addWidget(Dx, 1, 1, 1, 1);

        lddy = new QLabel(groupBox);
        lddy->setObjectName(QString::fromUtf8("lddy"));
        lddy->setFont(font1);
        lddy->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(lddy, 1, 3, 1, 1);

        ltdsy = new QLabel(groupBox);
        ltdsy->setObjectName(QString::fromUtf8("ltdsy"));
        ltdsy->setFont(font1);
        ltdsy->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_6->addWidget(ltdsy, 0, 5, 1, 1);

        lvax = new QLabel(groupBox);
        lvax->setObjectName(QString::fromUtf8("lvax"));
        lvax->setFont(font1);
        lvax->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(lvax, 5, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout_6, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 1, 1, 1);

        line_3 = new QFrame(tlinsUiPolit4);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line_3, 1, 1, 1, 1);


        gridLayout->addLayout(gridLayout_3, 1, 0, 1, 1);


        horizontalLayout_4->addLayout(gridLayout);

        QWidget::setTabOrder(speedMode, inSteps);
        QWidget::setTabOrder(inSteps, bRight);
        QWidget::setTabOrder(bRight, bLeft);
        QWidget::setTabOrder(bLeft, bUp);
        QWidget::setTabOrder(bUp, bStop);
        QWidget::setTabOrder(bStop, bAbort);
        QWidget::setTabOrder(bAbort, bDown);

        retranslateUi(tlinsUiPolit4);

        QMetaObject::connectSlotsByName(tlinsUiPolit4);
    } // setupUi

    void retranslateUi(QWidget *tlinsUiPolit4)
    {
        tlinsUiPolit4->setWindowTitle(QApplication::translate("tlinsUiPolit4", "Form", nullptr));
        speedMode->setText(QApplication::translate("tlinsUiPolit4", "Speed mode", nullptr));
        inSteps->setText(QApplication::translate("tlinsUiPolit4", "In steps", nullptr));
#ifndef QT_NO_SHORTCUT
        bUp->setShortcut(QString());
#endif // QT_NO_SHORTCUT
        groupBox->setTitle(QApplication::translate("tlinsUiPolit4", "Move and speed", nullptr));
        ltddy->setText(QApplication::translate("tlinsUiPolit4", "[degris]", nullptr));
        ltdax->setText(QApplication::translate("tlinsUiPolit4", "[hours]", nullptr));
        ldsy->setText(QApplication::translate("tlinsUiPolit4", "Y", nullptr));
        ltday->setText(QApplication::translate("tlinsUiPolit4", "[degris]", nullptr));
        ltddx->setText(QApplication::translate("tlinsUiPolit4", "[degris]", nullptr));
        lday->setText(QApplication::translate("tlinsUiPolit4", "Dc", nullptr));
        lvdy->setText(QApplication::translate("tlinsUiPolit4", "V (Y)", nullptr));
        ltvdy->setText(QApplication::translate("tlinsUiPolit4", "[degris/s]", nullptr));
        ldsx->setText(QApplication::translate("tlinsUiPolit4", " X", nullptr));
        ldax->setText(QApplication::translate("tlinsUiPolit4", "Ra", nullptr));
        lddx->setText(QApplication::translate("tlinsUiPolit4", "X", nullptr));
        ltvsy->setText(QApplication::translate("tlinsUiPolit4", "[steps/s]", nullptr));
        lvsy->setText(QApplication::translate("tlinsUiPolit4", "V (Y)", nullptr));
        ltvax->setText(QApplication::translate("tlinsUiPolit4", "[hours/s]", nullptr));
        lvsx->setText(QApplication::translate("tlinsUiPolit4", "V (X)", nullptr));
        ltvdx->setText(QApplication::translate("tlinsUiPolit4", "[degris/s]", nullptr));
        lvdx->setText(QApplication::translate("tlinsUiPolit4", "V (X)", nullptr));
        ltvay->setText(QApplication::translate("tlinsUiPolit4", "[degris/s]", nullptr));
        ltvsx->setText(QApplication::translate("tlinsUiPolit4", "[steps/s]", nullptr));
        lvay->setText(QApplication::translate("tlinsUiPolit4", "V (Dc)", nullptr));
        ltdsx->setText(QApplication::translate("tlinsUiPolit4", "[steps]", nullptr));
        lddy->setText(QApplication::translate("tlinsUiPolit4", "Y", nullptr));
        ltdsy->setText(QApplication::translate("tlinsUiPolit4", "[steps]", nullptr));
        lvax->setText(QApplication::translate("tlinsUiPolit4", "V (Ra)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsUiPolit4: public Ui_tlinsUiPolit4 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSUIPOLIT4_H
