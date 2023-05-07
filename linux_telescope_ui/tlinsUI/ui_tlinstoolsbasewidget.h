/********************************************************************************
** Form generated from reading UI file 'tlinstoolsbasewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSTOOLSBASEWIDGET_H
#define UI_TLINSTOOLSBASEWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsToolsBaseWidget
{
public:
    QGridLayout *gridLayout;
    QFrame *line;
    QWidget *widget;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *icon;
    QLabel *title;

    void setupUi(QWidget *tlinsToolsBaseWidget)
    {
        if (tlinsToolsBaseWidget->objectName().isEmpty())
            tlinsToolsBaseWidget->setObjectName(QString::fromUtf8("tlinsToolsBaseWidget"));
        tlinsToolsBaseWidget->resize(811, 442);
        gridLayout = new QGridLayout(tlinsToolsBaseWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setVerticalSpacing(25);
        line = new QFrame(tlinsToolsBaseWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 1, 1, 1, 1);

        widget = new QWidget(tlinsToolsBaseWidget);
        widget->setObjectName(QString::fromUtf8("widget"));

        gridLayout->addWidget(widget, 2, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(120, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(120, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout->addItem(verticalSpacer, 3, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        icon = new QToolButton(tlinsToolsBaseWidget);
        icon->setObjectName(QString::fromUtf8("icon"));
        icon->setEnabled(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/add.svg"), QSize(), QIcon::Normal, QIcon::Off);
        icon->setIcon(icon1);
        icon->setIconSize(QSize(48, 48));
        icon->setAutoRaise(true);

        horizontalLayout_2->addWidget(icon);

        title = new QLabel(tlinsToolsBaseWidget);
        title->setObjectName(QString::fromUtf8("title"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(title->sizePolicy().hasHeightForWidth());
        title->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(26);
        font.setItalic(true);
        font.setUnderline(false);
        title->setFont(font);
        title->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(title);


        gridLayout->addLayout(horizontalLayout_2, 0, 1, 1, 1);


        retranslateUi(tlinsToolsBaseWidget);

        QMetaObject::connectSlotsByName(tlinsToolsBaseWidget);
    } // setupUi

    void retranslateUi(QWidget *tlinsToolsBaseWidget)
    {
        tlinsToolsBaseWidget->setWindowTitle(QApplication::translate("tlinsToolsBaseWidget", "Form", nullptr));
        icon->setText(QString());
        title->setText(QApplication::translate("tlinsToolsBaseWidget", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsToolsBaseWidget: public Ui_tlinsToolsBaseWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSTOOLSBASEWIDGET_H
