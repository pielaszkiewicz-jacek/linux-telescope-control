/********************************************************************************
** Form generated from reading UI file 'tlinswobservationplace.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWOBSERVATIONPLACE_H
#define UI_TLINSWOBSERVATIONPLACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
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

class Ui_tlinsWObservationPlace
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *places;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *newItem;
    QPushButton *addItem;
    QPushButton *updateItem;
    QPushButton *deleteItem;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *saveItems;
    QPushButton *reloadItems;
    QGridLayout *gridLayout;
    tlinsWCoordinateDegris *longitude;
    QLabel *label;
    QLineEdit *name;
    QLabel *label_2;
    QLabel *label_4;
    tlinsWDecimalValue *hm;
    QLabel *label_3;
    QLabel *label_5;
    QComboBox *elipsoideType;
    tlinsWCoordinateDegris *latitude;
    QLabel *label_6;
    QCheckBox *isDefault;

    void setupUi(QWidget *tlinsWObservationPlace)
    {
        if (tlinsWObservationPlace->objectName().isEmpty())
            tlinsWObservationPlace->setObjectName(QString::fromUtf8("tlinsWObservationPlace"));
        tlinsWObservationPlace->resize(867, 483);
        verticalLayout = new QVBoxLayout(tlinsWObservationPlace);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        places = new QTableView(tlinsWObservationPlace);
        places->setObjectName(QString::fromUtf8("places"));

        verticalLayout->addWidget(places);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        newItem = new QPushButton(tlinsWObservationPlace);
        newItem->setObjectName(QString::fromUtf8("newItem"));

        horizontalLayout->addWidget(newItem);

        addItem = new QPushButton(tlinsWObservationPlace);
        addItem->setObjectName(QString::fromUtf8("addItem"));

        horizontalLayout->addWidget(addItem);

        updateItem = new QPushButton(tlinsWObservationPlace);
        updateItem->setObjectName(QString::fromUtf8("updateItem"));

        horizontalLayout->addWidget(updateItem);

        deleteItem = new QPushButton(tlinsWObservationPlace);
        deleteItem->setObjectName(QString::fromUtf8("deleteItem"));

        horizontalLayout->addWidget(deleteItem);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        saveItems = new QPushButton(tlinsWObservationPlace);
        saveItems->setObjectName(QString::fromUtf8("saveItems"));

        horizontalLayout->addWidget(saveItems);

        reloadItems = new QPushButton(tlinsWObservationPlace);
        reloadItems->setObjectName(QString::fromUtf8("reloadItems"));

        horizontalLayout->addWidget(reloadItems);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        longitude = new tlinsWCoordinateDegris(tlinsWObservationPlace);
        longitude->setObjectName(QString::fromUtf8("longitude"));

        gridLayout->addWidget(longitude, 1, 1, 1, 1);

        label = new QLabel(tlinsWObservationPlace);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        name = new QLineEdit(tlinsWObservationPlace);
        name->setObjectName(QString::fromUtf8("name"));

        gridLayout->addWidget(name, 0, 1, 1, 1);

        label_2 = new QLabel(tlinsWObservationPlace);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label_4 = new QLabel(tlinsWObservationPlace);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 5, 0, 1, 1);

        hm = new tlinsWDecimalValue(tlinsWObservationPlace);
        hm->setObjectName(QString::fromUtf8("hm"));

        gridLayout->addWidget(hm, 4, 1, 1, 1);

        label_3 = new QLabel(tlinsWObservationPlace);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        label_5 = new QLabel(tlinsWObservationPlace);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

        elipsoideType = new QComboBox(tlinsWObservationPlace);
        elipsoideType->addItem(QString());
        elipsoideType->addItem(QString());
        elipsoideType->addItem(QString());
        elipsoideType->setObjectName(QString::fromUtf8("elipsoideType"));

        gridLayout->addWidget(elipsoideType, 5, 1, 1, 1);

        latitude = new tlinsWCoordinateDegris(tlinsWObservationPlace);
        latitude->setObjectName(QString::fromUtf8("latitude"));

        gridLayout->addWidget(latitude, 2, 1, 1, 1);

        label_6 = new QLabel(tlinsWObservationPlace);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 6, 0, 1, 1);

        isDefault = new QCheckBox(tlinsWObservationPlace);
        isDefault->setObjectName(QString::fromUtf8("isDefault"));

        gridLayout->addWidget(isDefault, 6, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(tlinsWObservationPlace);

        QMetaObject::connectSlotsByName(tlinsWObservationPlace);
    } // setupUi

    void retranslateUi(QWidget *tlinsWObservationPlace)
    {
        tlinsWObservationPlace->setWindowTitle(QApplication::translate("tlinsWObservationPlace", "Form", nullptr));
        newItem->setText(QApplication::translate("tlinsWObservationPlace", "New", nullptr));
        addItem->setText(QApplication::translate("tlinsWObservationPlace", "Add", nullptr));
        updateItem->setText(QApplication::translate("tlinsWObservationPlace", "Update", nullptr));
        deleteItem->setText(QApplication::translate("tlinsWObservationPlace", "Delete", nullptr));
        saveItems->setText(QApplication::translate("tlinsWObservationPlace", "Save", nullptr));
        reloadItems->setText(QApplication::translate("tlinsWObservationPlace", "Reload", nullptr));
        label->setText(QApplication::translate("tlinsWObservationPlace", "Longitude", nullptr));
        label_2->setText(QApplication::translate("tlinsWObservationPlace", "Latitude", nullptr));
        label_4->setText(QApplication::translate("tlinsWObservationPlace", "Elipsoide type", nullptr));
        label_3->setText(QApplication::translate("tlinsWObservationPlace", "Height above the geoid", nullptr));
        label_5->setText(QApplication::translate("tlinsWObservationPlace", "Name", nullptr));
        elipsoideType->setItemText(0, QApplication::translate("tlinsWObservationPlace", "WGS_84", nullptr));
        elipsoideType->setItemText(1, QApplication::translate("tlinsWObservationPlace", "GRS_80", nullptr));
        elipsoideType->setItemText(2, QApplication::translate("tlinsWObservationPlace", "WGS_72", nullptr));

        label_6->setText(QApplication::translate("tlinsWObservationPlace", "Default", nullptr));
        isDefault->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class tlinsWObservationPlace: public Ui_tlinsWObservationPlace {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWOBSERVATIONPLACE_H
