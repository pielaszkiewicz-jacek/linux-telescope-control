/********************************************************************************
** Form generated from reading UI file 'tlinswtimedateierssettings.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWTIMEDATEIERSSETTINGS_H
#define UI_TLINSWTIMEDATEIERSSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <tlinswdecimalvalue.h>
#include "tlinswcoordinatedegris.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsWTimeDateIERSSettings
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButtonSelectFile;
    QLineEdit *inputFle;
    QPushButton *loadFile;
    QCheckBox *replaceByFile;
    QTableView *iersTableView;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *newItem;
    QPushButton *addItem;
    QPushButton *removeItem;
    QPushButton *updateItem;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *storeItems;
    QPushButton *reload;
    QFrame *line;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLabel *label;
    tlinsWDecimalValue *month;
    tlinsWDecimalValue *day;
    QLabel *label_3;
    tlinsWDecimalValue *year;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    tlinsWCoordinateDegris *pmy;
    QLabel *label_4;
    tlinsWCoordinateDegris *pmx;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_5;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout;
    tlinsWDecimalValue *ut1_utc;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    QLabel *label_6;
    QLabel *label_9;
    QLabel *label_8;
    tlinsWCoordinateDegris *dy;
    tlinsWCoordinateDegris *dx;
    tlinsWDecimalValue *dPsi;
    tlinsWDecimalValue *dEpsilon;
    QLabel *label_10;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *tlinsWTimeDateIERSSettings)
    {
        if (tlinsWTimeDateIERSSettings->objectName().isEmpty())
            tlinsWTimeDateIERSSettings->setObjectName(QString::fromUtf8("tlinsWTimeDateIERSSettings"));
        tlinsWTimeDateIERSSettings->resize(795, 536);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tlinsWTimeDateIERSSettings->sizePolicy().hasHeightForWidth());
        tlinsWTimeDateIERSSettings->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(tlinsWTimeDateIERSSettings);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_5 = new QGroupBox(tlinsWTimeDateIERSSettings);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        QFont font;
        font.setItalic(true);
        groupBox_5->setFont(font);
        verticalLayout_2 = new QVBoxLayout(groupBox_5);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pushButtonSelectFile = new QPushButton(groupBox_5);
        pushButtonSelectFile->setObjectName(QString::fromUtf8("pushButtonSelectFile"));
        QFont font1;
        font1.setItalic(false);
        pushButtonSelectFile->setFont(font1);

        horizontalLayout_4->addWidget(pushButtonSelectFile);

        inputFle = new QLineEdit(groupBox_5);
        inputFle->setObjectName(QString::fromUtf8("inputFle"));
        inputFle->setFont(font1);

        horizontalLayout_4->addWidget(inputFle);

        loadFile = new QPushButton(groupBox_5);
        loadFile->setObjectName(QString::fromUtf8("loadFile"));
        loadFile->setMinimumSize(QSize(0, 30));
        loadFile->setFont(font1);

        horizontalLayout_4->addWidget(loadFile);

        replaceByFile = new QCheckBox(groupBox_5);
        replaceByFile->setObjectName(QString::fromUtf8("replaceByFile"));
        replaceByFile->setFont(font1);

        horizontalLayout_4->addWidget(replaceByFile);


        verticalLayout_2->addLayout(horizontalLayout_4);

        iersTableView = new QTableView(groupBox_5);
        iersTableView->setObjectName(QString::fromUtf8("iersTableView"));
        iersTableView->setFont(font1);

        verticalLayout_2->addWidget(iersTableView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        newItem = new QPushButton(groupBox_5);
        newItem->setObjectName(QString::fromUtf8("newItem"));
        newItem->setMinimumSize(QSize(0, 30));
        newItem->setFont(font1);

        horizontalLayout_2->addWidget(newItem);

        addItem = new QPushButton(groupBox_5);
        addItem->setObjectName(QString::fromUtf8("addItem"));
        addItem->setMinimumSize(QSize(0, 30));
        addItem->setFont(font1);

        horizontalLayout_2->addWidget(addItem);

        removeItem = new QPushButton(groupBox_5);
        removeItem->setObjectName(QString::fromUtf8("removeItem"));
        removeItem->setMinimumSize(QSize(0, 30));
        removeItem->setFont(font1);

        horizontalLayout_2->addWidget(removeItem);

        updateItem = new QPushButton(groupBox_5);
        updateItem->setObjectName(QString::fromUtf8("updateItem"));
        updateItem->setMinimumSize(QSize(0, 30));
        updateItem->setFont(font1);

        horizontalLayout_2->addWidget(updateItem);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        storeItems = new QPushButton(groupBox_5);
        storeItems->setObjectName(QString::fromUtf8("storeItems"));
        storeItems->setMinimumSize(QSize(0, 30));
        storeItems->setFont(font1);

        horizontalLayout_2->addWidget(storeItems);

        reload = new QPushButton(groupBox_5);
        reload->setObjectName(QString::fromUtf8("reload"));
        reload->setMinimumSize(QSize(0, 30));
        reload->setFont(font1);

        horizontalLayout_2->addWidget(reload);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(groupBox_5);

        line = new QFrame(tlinsWTimeDateIERSSettings);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        groupBox = new QGroupBox(tlinsWTimeDateIERSSettings);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setFont(font);
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 4, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        month = new tlinsWDecimalValue(groupBox);
        month->setObjectName(QString::fromUtf8("month"));

        gridLayout_2->addWidget(month, 0, 3, 1, 1);

        day = new tlinsWDecimalValue(groupBox);
        day->setObjectName(QString::fromUtf8("day"));

        gridLayout_2->addWidget(day, 0, 5, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 0, 2, 1, 1);

        year = new tlinsWDecimalValue(groupBox);
        year->setObjectName(QString::fromUtf8("year"));

        gridLayout_2->addWidget(year, 0, 1, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(tlinsWTimeDateIERSSettings);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setFont(font);
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pmy = new tlinsWCoordinateDegris(groupBox_2);
        pmy->setObjectName(QString::fromUtf8("pmy"));

        gridLayout->addWidget(pmy, 0, 4, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        pmx = new tlinsWCoordinateDegris(groupBox_2);
        pmx->setObjectName(QString::fromUtf8("pmx"));

        gridLayout->addWidget(pmx, 0, 1, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 0, 3, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 0, 2, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(tlinsWTimeDateIERSSettings);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setFont(font);
        horizontalLayout = new QHBoxLayout(groupBox_3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        ut1_utc = new tlinsWDecimalValue(groupBox_3);
        ut1_utc->setObjectName(QString::fromUtf8("ut1_utc"));

        horizontalLayout->addWidget(ut1_utc);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(tlinsWTimeDateIERSSettings);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setFont(font);
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_4->addWidget(label_6, 0, 0, 1, 1);

        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_4->addWidget(label_9, 2, 0, 1, 1);

        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_4->addWidget(label_8, 0, 3, 1, 1);

        dy = new tlinsWCoordinateDegris(groupBox_4);
        dy->setObjectName(QString::fromUtf8("dy"));

        gridLayout_4->addWidget(dy, 2, 4, 1, 1);

        dx = new tlinsWCoordinateDegris(groupBox_4);
        dx->setObjectName(QString::fromUtf8("dx"));

        gridLayout_4->addWidget(dx, 2, 1, 1, 1);

        dPsi = new tlinsWDecimalValue(groupBox_4);
        dPsi->setObjectName(QString::fromUtf8("dPsi"));

        gridLayout_4->addWidget(dPsi, 0, 1, 1, 1);

        dEpsilon = new tlinsWDecimalValue(groupBox_4);
        dEpsilon->setObjectName(QString::fromUtf8("dEpsilon"));

        gridLayout_4->addWidget(dEpsilon, 0, 4, 1, 1);

        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_4->addWidget(label_10, 2, 3, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_4, 0, 2, 1, 1);


        verticalLayout->addWidget(groupBox_4);


        retranslateUi(tlinsWTimeDateIERSSettings);

        QMetaObject::connectSlotsByName(tlinsWTimeDateIERSSettings);
    } // setupUi

    void retranslateUi(QWidget *tlinsWTimeDateIERSSettings)
    {
        tlinsWTimeDateIERSSettings->setWindowTitle(QApplication::translate("tlinsWTimeDateIERSSettings", "Form", nullptr));
        groupBox_5->setTitle(QApplication::translate("tlinsWTimeDateIERSSettings", "IERS data", nullptr));
        pushButtonSelectFile->setText(QApplication::translate("tlinsWTimeDateIERSSettings", "Select file", nullptr));
        loadFile->setText(QApplication::translate("tlinsWTimeDateIERSSettings", "Load from file", nullptr));
        replaceByFile->setText(QApplication::translate("tlinsWTimeDateIERSSettings", "Replace", nullptr));
        newItem->setText(QApplication::translate("tlinsWTimeDateIERSSettings", "New", nullptr));
        addItem->setText(QApplication::translate("tlinsWTimeDateIERSSettings", "Add", nullptr));
        removeItem->setText(QApplication::translate("tlinsWTimeDateIERSSettings", "Remove", nullptr));
        updateItem->setText(QApplication::translate("tlinsWTimeDateIERSSettings", "Update", nullptr));
        storeItems->setText(QApplication::translate("tlinsWTimeDateIERSSettings", "Store", nullptr));
        reload->setText(QApplication::translate("tlinsWTimeDateIERSSettings", "Reload", nullptr));
        groupBox->setTitle(QApplication::translate("tlinsWTimeDateIERSSettings", "Date:", nullptr));
        label_2->setText(QApplication::translate("tlinsWTimeDateIERSSettings", "Day", nullptr));
        label->setText(QApplication::translate("tlinsWTimeDateIERSSettings", "Year", nullptr));
        label_3->setText(QApplication::translate("tlinsWTimeDateIERSSettings", "Month", nullptr));
        groupBox_2->setTitle(QApplication::translate("tlinsWTimeDateIERSSettings", "Polar motion:", nullptr));
        label_4->setText(QApplication::translate("tlinsWTimeDateIERSSettings", "Pm X", nullptr));
        label_5->setText(QApplication::translate("tlinsWTimeDateIERSSettings", "Pm Y", nullptr));
        groupBox_3->setTitle(QApplication::translate("tlinsWTimeDateIERSSettings", "UT1-UTC:", nullptr));
        groupBox_4->setTitle(QApplication::translate("tlinsWTimeDateIERSSettings", "Nutation:", nullptr));
        label_6->setText(QApplication::translate("tlinsWTimeDateIERSSettings", "dPsi", nullptr));
        label_9->setText(QApplication::translate("tlinsWTimeDateIERSSettings", "dX", nullptr));
        label_8->setText(QApplication::translate("tlinsWTimeDateIERSSettings", "dEpsilon", nullptr));
        label_10->setText(QApplication::translate("tlinsWTimeDateIERSSettings", "dY", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWTimeDateIERSSettings: public Ui_tlinsWTimeDateIERSSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWTIMEDATEIERSSETTINGS_H
