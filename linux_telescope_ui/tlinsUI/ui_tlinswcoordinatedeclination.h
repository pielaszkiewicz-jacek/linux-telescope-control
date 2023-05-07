/********************************************************************************
** Form generated from reading UI file 'tlinswcoordinatedeclination.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWCOORDINATEDECLINATION_H
#define UI_TLINSWCOORDINATEDECLINATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsWCoordinateDeclination
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *dc;

    void setupUi(QWidget *tlinsWCoordinateDeclination)
    {
        if (tlinsWCoordinateDeclination->objectName().isEmpty())
            tlinsWCoordinateDeclination->setObjectName(QString::fromUtf8("tlinsWCoordinateDeclination"));
        tlinsWCoordinateDeclination->resize(197, 78);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tlinsWCoordinateDeclination->sizePolicy().hasHeightForWidth());
        tlinsWCoordinateDeclination->setSizePolicy(sizePolicy);
        tlinsWCoordinateDeclination->setMinimumSize(QSize(165, 40));
        tlinsWCoordinateDeclination->setMaximumSize(QSize(16777215, 16777215));
        horizontalLayout = new QHBoxLayout(tlinsWCoordinateDeclination);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(tlinsWCoordinateDeclination);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        dc = new QLineEdit(tlinsWCoordinateDeclination);
        dc->setObjectName(QString::fromUtf8("dc"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dc->sizePolicy().hasHeightForWidth());
        dc->setSizePolicy(sizePolicy1);
        dc->setMinimumSize(QSize(0, 40));
        dc->setMaximumSize(QSize(16777215, 40));
        QFont font;
        font.setPointSize(11);
        font.setBold(false);
        font.setWeight(50);
        dc->setFont(font);
        dc->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(dc);


        retranslateUi(tlinsWCoordinateDeclination);

        QMetaObject::connectSlotsByName(tlinsWCoordinateDeclination);
    } // setupUi

    void retranslateUi(QWidget *tlinsWCoordinateDeclination)
    {
        tlinsWCoordinateDeclination->setWindowTitle(QApplication::translate("tlinsWCoordinateDeclination", "Form", nullptr));
        label->setText(QString());
        dc->setInputMask(QApplication::translate("tlinsWCoordinateDeclination", "#09:09:09.0000", nullptr));
        dc->setText(QApplication::translate("tlinsWCoordinateDeclination", "00:00:00.0000", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWCoordinateDeclination: public Ui_tlinsWCoordinateDeclination {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWCOORDINATEDECLINATION_H
