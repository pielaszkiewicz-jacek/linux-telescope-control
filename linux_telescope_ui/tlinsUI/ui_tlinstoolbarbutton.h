/********************************************************************************
** Form generated from reading UI file 'tlinstoolbarbutton.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSTOOLBARBUTTON_H
#define UI_TLINSTOOLBARBUTTON_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsToolBarButton
{
public:
    QGridLayout *gridLayout;
    QToolButton *toolButton;

    void setupUi(QWidget *tlinsToolBarButton)
    {
        if (tlinsToolBarButton->objectName().isEmpty())
            tlinsToolBarButton->setObjectName(QString::fromUtf8("tlinsToolBarButton"));
        tlinsToolBarButton->resize(130, 71);
        gridLayout = new QGridLayout(tlinsToolBarButton);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        toolButton = new QToolButton(tlinsToolBarButton);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setEnabled(true);
        toolButton->setMinimumSize(QSize(130, 0));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/add.svg"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon);
        toolButton->setIconSize(QSize(42, 42));
        toolButton->setCheckable(true);
        toolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        toolButton->setAutoRaise(true);

        gridLayout->addWidget(toolButton, 0, 0, 1, 1);


        retranslateUi(tlinsToolBarButton);
        QObject::connect(toolButton, SIGNAL(pressed()), tlinsToolBarButton, SLOT(buttonPressed()));

        QMetaObject::connectSlotsByName(tlinsToolBarButton);
    } // setupUi

    void retranslateUi(QWidget *tlinsToolBarButton)
    {
        tlinsToolBarButton->setWindowTitle(QApplication::translate("tlinsToolBarButton", "Form", nullptr));
        toolButton->setText(QApplication::translate("tlinsToolBarButton", "Tejst", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsToolBarButton: public Ui_tlinsToolBarButton {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSTOOLBARBUTTON_H
