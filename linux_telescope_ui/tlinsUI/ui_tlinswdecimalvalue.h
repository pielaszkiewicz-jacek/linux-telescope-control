/********************************************************************************
** Form generated from reading UI file 'tlinswdecimalvalue.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWDECIMALVALUE_H
#define UI_TLINSWDECIMALVALUE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsWDecimalValue
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *valueName;
    QDoubleSpinBox *value;

    void setupUi(QWidget *tlinsWDecimalValue)
    {
        if (tlinsWDecimalValue->objectName().isEmpty())
            tlinsWDecimalValue->setObjectName(QString::fromUtf8("tlinsWDecimalValue"));
        tlinsWDecimalValue->resize(172, 130);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tlinsWDecimalValue->sizePolicy().hasHeightForWidth());
        tlinsWDecimalValue->setSizePolicy(sizePolicy);
        tlinsWDecimalValue->setMinimumSize(QSize(165, 48));
        tlinsWDecimalValue->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setPointSize(11);
        tlinsWDecimalValue->setFont(font);
        horizontalLayout = new QHBoxLayout(tlinsWDecimalValue);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        valueName = new QLabel(tlinsWDecimalValue);
        valueName->setObjectName(QString::fromUtf8("valueName"));
        valueName->setMinimumSize(QSize(0, 25));
        valueName->setMaximumSize(QSize(16777215, 25));

        horizontalLayout->addWidget(valueName);

        value = new QDoubleSpinBox(tlinsWDecimalValue);
        value->setObjectName(QString::fromUtf8("value"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(value->sizePolicy().hasHeightForWidth());
        value->setSizePolicy(sizePolicy1);
        value->setMinimumSize(QSize(0, 40));
        value->setMaximumSize(QSize(16777215, 40));
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(false);
        font1.setWeight(50);
        value->setFont(font1);
        value->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        value->setDecimals(4);
        value->setMinimum(-1000000000.000000000000000);
        value->setMaximum(1000000000.000000000000000);

        horizontalLayout->addWidget(value);


        retranslateUi(tlinsWDecimalValue);
        QObject::connect(value, SIGNAL(valueChanged(double)), tlinsWDecimalValue, SLOT(valueChanged(double)));

        QMetaObject::connectSlotsByName(tlinsWDecimalValue);
    } // setupUi

    void retranslateUi(QWidget *tlinsWDecimalValue)
    {
        tlinsWDecimalValue->setWindowTitle(QApplication::translate("tlinsWDecimalValue", "Form", nullptr));
        valueName->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class tlinsWDecimalValue: public Ui_tlinsWDecimalValue {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWDECIMALVALUE_H
