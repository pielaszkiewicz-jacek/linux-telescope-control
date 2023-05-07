/********************************************************************************
** Form generated from reading UI file 'tlinsmainbuttons.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSMAINBUTTONS_H
#define UI_TLINSMAINBUTTONS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_buttonPilot
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QPushButton *pushButton_5;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_4;
    QSpacerItem *verticalSpacer;
    QPushButton *databaseButton;
    QPushButton *pilotButton;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *exitButton;
    QPushButton *settingsButton;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_2;

    void setupUi(QWidget *buttonPilot)
    {
        if (buttonPilot->objectName().isEmpty())
            buttonPilot->setObjectName(QString::fromUtf8("buttonPilot"));
        buttonPilot->resize(946, 551);
        gridLayout_2 = new QGridLayout(buttonPilot);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton_5 = new QPushButton(buttonPilot);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/telescope.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_5->setIcon(icon);
        pushButton_5->setIconSize(QSize(95, 95));
        pushButton_5->setFlat(false);

        gridLayout->addWidget(pushButton_5, 2, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(5, 5, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 3, 1, 1);

        pushButton_4 = new QPushButton(buttonPilot);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        sizePolicy.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/connect.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_4->setIcon(icon1);
        pushButton_4->setIconSize(QSize(100, 100));
        pushButton_4->setFlat(false);

        gridLayout->addWidget(pushButton_4, 0, 6, 1, 1);

        verticalSpacer = new QSpacerItem(5, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 1, 2, 1, 1);

        databaseButton = new QPushButton(buttonPilot);
        databaseButton->setObjectName(QString::fromUtf8("databaseButton"));
        sizePolicy.setHeightForWidth(databaseButton->sizePolicy().hasHeightForWidth());
        databaseButton->setSizePolicy(sizePolicy);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/database.svg"), QSize(), QIcon::Normal, QIcon::Off);
        databaseButton->setIcon(icon2);
        databaseButton->setIconSize(QSize(95, 95));
        databaseButton->setFlat(false);

        gridLayout->addWidget(databaseButton, 0, 2, 1, 1);

        pilotButton = new QPushButton(buttonPilot);
        pilotButton->setObjectName(QString::fromUtf8("pilotButton"));
        sizePolicy.setHeightForWidth(pilotButton->sizePolicy().hasHeightForWidth());
        pilotButton->setSizePolicy(sizePolicy);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/remote-control.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pilotButton->setIcon(icon3);
        pilotButton->setIconSize(QSize(100, 100));
        pilotButton->setFlat(false);

        gridLayout->addWidget(pilotButton, 0, 0, 1, 1);

        pushButton = new QPushButton(buttonPilot);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/info.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon4);
        pushButton->setIconSize(QSize(90, 90));
        pushButton->setFlat(false);

        gridLayout->addWidget(pushButton, 2, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(5, 5, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        exitButton = new QPushButton(buttonPilot);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        sizePolicy.setHeightForWidth(exitButton->sizePolicy().hasHeightForWidth());
        exitButton->setSizePolicy(sizePolicy);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/exit.svg"), QSize(), QIcon::Normal, QIcon::Off);
        exitButton->setIcon(icon5);
        exitButton->setIconSize(QSize(90, 90));
        exitButton->setFlat(false);

        gridLayout->addWidget(exitButton, 2, 6, 1, 1);

        settingsButton = new QPushButton(buttonPilot);
        settingsButton->setObjectName(QString::fromUtf8("settingsButton"));
        sizePolicy.setHeightForWidth(settingsButton->sizePolicy().hasHeightForWidth());
        settingsButton->setSizePolicy(sizePolicy);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/settings.svg"), QSize(), QIcon::Normal, QIcon::Off);
        settingsButton->setIcon(icon6);
        settingsButton->setIconSize(QSize(100, 100));
        settingsButton->setFlat(false);

        gridLayout->addWidget(settingsButton, 0, 4, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(5, 5, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 7, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(5, 5, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 5, 1, 1);

        pushButton_2 = new QPushButton(buttonPilot);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/return.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon7);
        pushButton_2->setIconSize(QSize(90, 90));
        pushButton_2->setFlat(false);

        gridLayout->addWidget(pushButton_2, 2, 4, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 1, 1, 1);


        retranslateUi(buttonPilot);

        QMetaObject::connectSlotsByName(buttonPilot);
    } // setupUi

    void retranslateUi(QWidget *buttonPilot)
    {
        buttonPilot->setWindowTitle(QApplication::translate("buttonPilot", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class buttonPilot: public Ui_buttonPilot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSMAINBUTTONS_H
