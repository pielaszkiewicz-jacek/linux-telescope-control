/********************************************************************************
** Form generated from reading UI file 'tlinswdatabasesearchmain.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWDATABASESEARCHMAIN_H
#define UI_TLINSWDATABASESEARCHMAIN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsWDatabaseSearchMain
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QPushButton *searchButton;
    QPushButton *selectButton;
    QPushButton *deselectButton;
    QPushButton *removeButton;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_4;
    QLabel *label;
    QSpinBox *actualOffset;
    QGridLayout *gridLayout_5;
    QPushButton *previous;
    QComboBox *winSize;
    QPushButton *next;
    QSpacerItem *horizontalSpacer;
    QTableView *data;
    QScrollArea *search;
    QWidget *searchWidget;

    void setupUi(QWidget *tlinsWDatabaseSearchMain)
    {
        if (tlinsWDatabaseSearchMain->objectName().isEmpty())
            tlinsWDatabaseSearchMain->setObjectName(QString::fromUtf8("tlinsWDatabaseSearchMain"));
        tlinsWDatabaseSearchMain->resize(738, 562);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tlinsWDatabaseSearchMain->sizePolicy().hasHeightForWidth());
        tlinsWDatabaseSearchMain->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(tlinsWDatabaseSearchMain);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(25);
        gridLayout_2->setContentsMargins(25, 10, 25, 10);
        searchButton = new QPushButton(tlinsWDatabaseSearchMain);
        searchButton->setObjectName(QString::fromUtf8("searchButton"));
        searchButton->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(searchButton, 0, 0, 1, 1);

        selectButton = new QPushButton(tlinsWDatabaseSearchMain);
        selectButton->setObjectName(QString::fromUtf8("selectButton"));
        selectButton->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(selectButton, 0, 1, 1, 1);

        deselectButton = new QPushButton(tlinsWDatabaseSearchMain);
        deselectButton->setObjectName(QString::fromUtf8("deselectButton"));
        deselectButton->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(deselectButton, 0, 2, 1, 1);

        removeButton = new QPushButton(tlinsWDatabaseSearchMain);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        removeButton->setMinimumSize(QSize(0, 40));

        gridLayout_2->addWidget(removeButton, 0, 3, 1, 1);


        gridLayout->addLayout(gridLayout_2, 1, 0, 1, 1);

        groupBox = new QGroupBox(tlinsWDatabaseSearchMain);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("Roboto Condensed"));
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        gridLayout_4->addWidget(label, 0, 0, 1, 1);

        actualOffset = new QSpinBox(groupBox);
        actualOffset->setObjectName(QString::fromUtf8("actualOffset"));
        actualOffset->setMinimumSize(QSize(65, 25));
        actualOffset->setMaximumSize(QSize(65, 25));

        gridLayout_4->addWidget(actualOffset, 0, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_4, 0, 1, 1, 1);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        previous = new QPushButton(groupBox);
        previous->setObjectName(QString::fromUtf8("previous"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/ic_keyboard_arrow_left_black_24px.svg"), QSize(), QIcon::Normal, QIcon::Off);
        previous->setIcon(icon);
        previous->setFlat(true);

        gridLayout_5->addWidget(previous, 0, 0, 1, 1);

        winSize = new QComboBox(groupBox);
        winSize->addItem(QString());
        winSize->addItem(QString());
        winSize->addItem(QString());
        winSize->addItem(QString());
        winSize->addItem(QString());
        winSize->addItem(QString());
        winSize->setObjectName(QString::fromUtf8("winSize"));
        winSize->setMinimumSize(QSize(60, 25));
        winSize->setMaximumSize(QSize(60, 25));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Roboto Condensed"));
        winSize->setFont(font1);
        winSize->setEditable(true);
        winSize->setModelColumn(0);

        gridLayout_5->addWidget(winSize, 0, 1, 1, 1);

        next = new QPushButton(groupBox);
        next->setObjectName(QString::fromUtf8("next"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/ic_keyboard_arrow_right_black_24px.svg"), QSize(), QIcon::Normal, QIcon::Off);
        next->setIcon(icon1);
        next->setFlat(true);

        gridLayout_5->addWidget(next, 0, 2, 1, 1);


        gridLayout_3->addLayout(gridLayout_5, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(189, 26, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_3);

        data = new QTableView(groupBox);
        data->setObjectName(QString::fromUtf8("data"));
        sizePolicy.setHeightForWidth(data->sizePolicy().hasHeightForWidth());
        data->setSizePolicy(sizePolicy);
        data->setSelectionMode(QAbstractItemView::MultiSelection);
        data->setSelectionBehavior(QAbstractItemView::SelectRows);
        data->setSortingEnabled(true);
        data->verticalHeader()->setMinimumSectionSize(29);

        verticalLayout->addWidget(data);


        gridLayout->addWidget(groupBox, 4, 0, 1, 1);

        search = new QScrollArea(tlinsWDatabaseSearchMain);
        search->setObjectName(QString::fromUtf8("search"));
        search->setMinimumSize(QSize(0, 0));
        search->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        search->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        search->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        search->setWidgetResizable(true);
        search->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        searchWidget = new QWidget();
        searchWidget->setObjectName(QString::fromUtf8("searchWidget"));
        searchWidget->setGeometry(QRect(0, 0, 718, 198));
        sizePolicy.setHeightForWidth(searchWidget->sizePolicy().hasHeightForWidth());
        searchWidget->setSizePolicy(sizePolicy);
        search->setWidget(searchWidget);

        gridLayout->addWidget(search, 0, 0, 1, 1);


        retranslateUi(tlinsWDatabaseSearchMain);

        QMetaObject::connectSlotsByName(tlinsWDatabaseSearchMain);
    } // setupUi

    void retranslateUi(QWidget *tlinsWDatabaseSearchMain)
    {
        tlinsWDatabaseSearchMain->setWindowTitle(QApplication::translate("tlinsWDatabaseSearchMain", "Form", nullptr));
        searchButton->setText(QApplication::translate("tlinsWDatabaseSearchMain", "Search", nullptr));
        selectButton->setText(QApplication::translate("tlinsWDatabaseSearchMain", "Select all", nullptr));
        deselectButton->setText(QApplication::translate("tlinsWDatabaseSearchMain", "Deselect", nullptr));
        removeButton->setText(QApplication::translate("tlinsWDatabaseSearchMain", "Remove", nullptr));
        groupBox->setTitle(QApplication::translate("tlinsWDatabaseSearchMain", "Search result", nullptr));
        label->setText(QApplication::translate("tlinsWDatabaseSearchMain", "Result set ", nullptr));
#ifndef QT_NO_TOOLTIP
        previous->setToolTip(QApplication::translate("tlinsWDatabaseSearchMain", "Previous", nullptr));
#endif // QT_NO_TOOLTIP
        previous->setText(QString());
        winSize->setItemText(0, QApplication::translate("tlinsWDatabaseSearchMain", "100", nullptr));
        winSize->setItemText(1, QApplication::translate("tlinsWDatabaseSearchMain", "50", nullptr));
        winSize->setItemText(2, QApplication::translate("tlinsWDatabaseSearchMain", "25", nullptr));
        winSize->setItemText(3, QApplication::translate("tlinsWDatabaseSearchMain", "20", nullptr));
        winSize->setItemText(4, QApplication::translate("tlinsWDatabaseSearchMain", "10", nullptr));
        winSize->setItemText(5, QApplication::translate("tlinsWDatabaseSearchMain", "1", nullptr));

#ifndef QT_NO_TOOLTIP
        winSize->setToolTip(QApplication::translate("tlinsWDatabaseSearchMain", "Records set size", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        next->setToolTip(QApplication::translate("tlinsWDatabaseSearchMain", "Next", nullptr));
#endif // QT_NO_TOOLTIP
        next->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class tlinsWDatabaseSearchMain: public Ui_tlinsWDatabaseSearchMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWDATABASESEARCHMAIN_H
