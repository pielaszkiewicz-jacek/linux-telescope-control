/********************************************************************************
** Form generated from reading UI file 'tlinswastrodatabasesearch3.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWASTRODATABASESEARCH3_H
#define UI_TLINSWASTRODATABASESEARCH3_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <tlinswastrocatalog.h>
#include <tlinswdecimalvalue.h>
#include "tlinswastroobjecttype.h"
#include "tlinswcatalogobjecttype.h"
#include "tlinswconstelation.h"
#include "tlinswcoordinatedeclination.h"
#include "tlinswcoordinatedegris.h"
#include "tlinswcoordinatehourangle.h"
#include "tlinswobjectname.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsWAstroDatabaseSearch3
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *gbBasic;
    QFormLayout *formLayout;
    QGroupBox *gbCoordinate;
    QGridLayout *gridLayout;
    QCheckBox *useDc;
    tlinsWCoordinateDeclination *dc;
    tlinsWCoordinateHourAngle *ra;
    QLabel *label_3;
    tlinsWCoordinateDegris *deg;
    QLabel *label_2;
    QCheckBox *useRadius;
    QLabel *label_10;
    QCheckBox *useRa;
    QGroupBox *gbGeneral;
    QGridLayout *gridLayout_3;
    QCheckBox *useObjectName;
    QLabel *label;
    QLabel *label_7;
    tlinsWCatalogObjectType *objCatalogObjectId;
    tlinsWObjectName *objName;
    QCheckBox *useObjectConstelation;
    QLabel *label_4;
    QCheckBox *useObjectIdInCatalog;
    tlinsWAstroCatalog *objCatalog;
    QLabel *label_5;
    tlinsWConstelation *objConstelation;
    QCheckBox *useObjectCatalog;
    QLabel *label_6;
    tlinsWAstroObjectType *objType;
    QCheckBox *useObjectType;
    QGroupBox *gbMagnitude;
    QGridLayout *gridLayout_2;
    QCheckBox *useMagnitudeFrom;
    tlinsWDecimalValue *magnitudeTo;
    QLabel *label_11;
    tlinsWDecimalValue *magnitudeFrom;
    QCheckBox *useMagnitudeTo;
    QLabel *label_12;
    QGroupBox *sqlAdanced;
    QGridLayout *gridLayout_9;
    QTextEdit *sqlText;

    void setupUi(QWidget *tlinsWAstroDatabaseSearch3)
    {
        if (tlinsWAstroDatabaseSearch3->objectName().isEmpty())
            tlinsWAstroDatabaseSearch3->setObjectName(QString::fromUtf8("tlinsWAstroDatabaseSearch3"));
        tlinsWAstroDatabaseSearch3->resize(1460, 1000);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tlinsWAstroDatabaseSearch3->sizePolicy().hasHeightForWidth());
        tlinsWAstroDatabaseSearch3->setSizePolicy(sizePolicy);
        tlinsWAstroDatabaseSearch3->setMinimumSize(QSize(0, 1000));
        tlinsWAstroDatabaseSearch3->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout = new QVBoxLayout(tlinsWAstroDatabaseSearch3);
        verticalLayout->setSpacing(32);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 5, 16);
        gbBasic = new QGroupBox(tlinsWAstroDatabaseSearch3);
        gbBasic->setObjectName(QString::fromUtf8("gbBasic"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(gbBasic->sizePolicy().hasHeightForWidth());
        gbBasic->setSizePolicy(sizePolicy1);
        gbBasic->setMinimumSize(QSize(200, 200));
        gbBasic->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        gbBasic->setFont(font);
        gbBasic->setCheckable(true);
        formLayout = new QFormLayout(gbBasic);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(5, 5, 5, 5);
        gbCoordinate = new QGroupBox(gbBasic);
        gbCoordinate->setObjectName(QString::fromUtf8("gbCoordinate"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(240);
        sizePolicy2.setHeightForWidth(gbCoordinate->sizePolicy().hasHeightForWidth());
        gbCoordinate->setSizePolicy(sizePolicy2);
        gbCoordinate->setMinimumSize(QSize(0, 0));
        gbCoordinate->setMaximumSize(QSize(16777215, 16777215));
        gbCoordinate->setCheckable(true);
        gridLayout = new QGridLayout(gbCoordinate);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(5, 5, 5, 5);
        useDc = new QCheckBox(gbCoordinate);
        useDc->setObjectName(QString::fromUtf8("useDc"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(useDc->sizePolicy().hasHeightForWidth());
        useDc->setSizePolicy(sizePolicy3);
        useDc->setMinimumSize(QSize(0, 40));
        useDc->setMaximumSize(QSize(25, 16777215));
        useDc->setInputMethodHints(Qt::ImhDate);
        useDc->setChecked(true);

        gridLayout->addWidget(useDc, 0, 6, 1, 1);

        dc = new tlinsWCoordinateDeclination(gbCoordinate);
        dc->setObjectName(QString::fromUtf8("dc"));
        sizePolicy3.setHeightForWidth(dc->sizePolicy().hasHeightForWidth());
        dc->setSizePolicy(sizePolicy3);
        dc->setMinimumSize(QSize(0, 40));
        dc->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(dc, 0, 5, 1, 1);

        ra = new tlinsWCoordinateHourAngle(gbCoordinate);
        ra->setObjectName(QString::fromUtf8("ra"));
        sizePolicy3.setHeightForWidth(ra->sizePolicy().hasHeightForWidth());
        ra->setSizePolicy(sizePolicy3);
        ra->setMinimumSize(QSize(0, 40));
        ra->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(ra, 0, 1, 1, 1);

        label_3 = new QLabel(gbCoordinate);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy4);
        label_3->setMinimumSize(QSize(0, 40));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        deg = new tlinsWCoordinateDegris(gbCoordinate);
        deg->setObjectName(QString::fromUtf8("deg"));
        sizePolicy3.setHeightForWidth(deg->sizePolicy().hasHeightForWidth());
        deg->setSizePolicy(sizePolicy3);
        deg->setMinimumSize(QSize(0, 40));
        deg->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(deg, 2, 1, 1, 1);

        label_2 = new QLabel(gbCoordinate);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy4.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy4);
        label_2->setMinimumSize(QSize(0, 40));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        useRadius = new QCheckBox(gbCoordinate);
        useRadius->setObjectName(QString::fromUtf8("useRadius"));
        sizePolicy3.setHeightForWidth(useRadius->sizePolicy().hasHeightForWidth());
        useRadius->setSizePolicy(sizePolicy3);
        useRadius->setMinimumSize(QSize(0, 35));
        useRadius->setMaximumSize(QSize(25, 35));
        useRadius->setChecked(true);

        gridLayout->addWidget(useRadius, 2, 3, 1, 1);

        label_10 = new QLabel(gbCoordinate);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy4.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy4);
        label_10->setMinimumSize(QSize(0, 40));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_10, 0, 4, 1, 1);

        useRa = new QCheckBox(gbCoordinate);
        useRa->setObjectName(QString::fromUtf8("useRa"));
        sizePolicy3.setHeightForWidth(useRa->sizePolicy().hasHeightForWidth());
        useRa->setSizePolicy(sizePolicy3);
        useRa->setMinimumSize(QSize(0, 40));
        useRa->setMaximumSize(QSize(25, 16777215));
        useRa->setChecked(true);

        gridLayout->addWidget(useRa, 0, 3, 1, 1);


        formLayout->setWidget(0, QFormLayout::SpanningRole, gbCoordinate);

        gbGeneral = new QGroupBox(gbBasic);
        gbGeneral->setObjectName(QString::fromUtf8("gbGeneral"));
        sizePolicy.setHeightForWidth(gbGeneral->sizePolicy().hasHeightForWidth());
        gbGeneral->setSizePolicy(sizePolicy);
        gbGeneral->setMinimumSize(QSize(0, 0));
        gbGeneral->setMaximumSize(QSize(16777215, 16777215));
        gbGeneral->setCheckable(true);
        gridLayout_3 = new QGridLayout(gbGeneral);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(5, 5, 5, 8);
        useObjectName = new QCheckBox(gbGeneral);
        useObjectName->setObjectName(QString::fromUtf8("useObjectName"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(useObjectName->sizePolicy().hasHeightForWidth());
        useObjectName->setSizePolicy(sizePolicy5);
        useObjectName->setMinimumSize(QSize(25, 25));
        useObjectName->setMaximumSize(QSize(25, 25));
        useObjectName->setChecked(true);

        gridLayout_3->addWidget(useObjectName, 0, 2, 1, 1);

        label = new QLabel(gbGeneral);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(0, 40));
        label->setMaximumSize(QSize(16777215, 40));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label, 8, 0, 1, 1);

        label_7 = new QLabel(gbGeneral);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_7, 6, 0, 1, 1);

        objCatalogObjectId = new tlinsWCatalogObjectType(gbGeneral);
        objCatalogObjectId->setObjectName(QString::fromUtf8("objCatalogObjectId"));
        sizePolicy1.setHeightForWidth(objCatalogObjectId->sizePolicy().hasHeightForWidth());
        objCatalogObjectId->setSizePolicy(sizePolicy1);
        objCatalogObjectId->setMinimumSize(QSize(0, 40));
        objCatalogObjectId->setMaximumSize(QSize(16777215, 40));

        gridLayout_3->addWidget(objCatalogObjectId, 8, 1, 1, 1);

        objName = new tlinsWObjectName(gbGeneral);
        objName->setObjectName(QString::fromUtf8("objName"));
        sizePolicy4.setHeightForWidth(objName->sizePolicy().hasHeightForWidth());
        objName->setSizePolicy(sizePolicy4);
        objName->setMinimumSize(QSize(0, 40));
        objName->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_3->addWidget(objName, 0, 1, 1, 1);

        useObjectConstelation = new QCheckBox(gbGeneral);
        useObjectConstelation->setObjectName(QString::fromUtf8("useObjectConstelation"));
        sizePolicy5.setHeightForWidth(useObjectConstelation->sizePolicy().hasHeightForWidth());
        useObjectConstelation->setSizePolicy(sizePolicy5);
        useObjectConstelation->setMinimumSize(QSize(25, 25));
        useObjectConstelation->setMaximumSize(QSize(25, 25));
        useObjectConstelation->setChecked(true);

        gridLayout_3->addWidget(useObjectConstelation, 2, 2, 1, 1);

        label_4 = new QLabel(gbGeneral);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_4, 0, 0, 1, 1);

        useObjectIdInCatalog = new QCheckBox(gbGeneral);
        useObjectIdInCatalog->setObjectName(QString::fromUtf8("useObjectIdInCatalog"));
        sizePolicy5.setHeightForWidth(useObjectIdInCatalog->sizePolicy().hasHeightForWidth());
        useObjectIdInCatalog->setSizePolicy(sizePolicy5);
        useObjectIdInCatalog->setMinimumSize(QSize(25, 25));
        useObjectIdInCatalog->setMaximumSize(QSize(25, 25));
        useObjectIdInCatalog->setChecked(true);

        gridLayout_3->addWidget(useObjectIdInCatalog, 8, 2, 1, 1);

        objCatalog = new tlinsWAstroCatalog(gbGeneral);
        objCatalog->setObjectName(QString::fromUtf8("objCatalog"));
        sizePolicy1.setHeightForWidth(objCatalog->sizePolicy().hasHeightForWidth());
        objCatalog->setSizePolicy(sizePolicy1);
        objCatalog->setMinimumSize(QSize(0, 40));
        objCatalog->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_3->addWidget(objCatalog, 6, 1, 1, 1);

        label_5 = new QLabel(gbGeneral);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_5, 2, 0, 1, 1);

        objConstelation = new tlinsWConstelation(gbGeneral);
        objConstelation->setObjectName(QString::fromUtf8("objConstelation"));
        sizePolicy4.setHeightForWidth(objConstelation->sizePolicy().hasHeightForWidth());
        objConstelation->setSizePolicy(sizePolicy4);
        objConstelation->setMinimumSize(QSize(0, 40));
        objConstelation->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_3->addWidget(objConstelation, 2, 1, 1, 1);

        useObjectCatalog = new QCheckBox(gbGeneral);
        useObjectCatalog->setObjectName(QString::fromUtf8("useObjectCatalog"));
        sizePolicy5.setHeightForWidth(useObjectCatalog->sizePolicy().hasHeightForWidth());
        useObjectCatalog->setSizePolicy(sizePolicy5);
        useObjectCatalog->setMinimumSize(QSize(25, 25));
        useObjectCatalog->setMaximumSize(QSize(25, 25));
        useObjectCatalog->setChecked(true);

        gridLayout_3->addWidget(useObjectCatalog, 6, 2, 1, 1);

        label_6 = new QLabel(gbGeneral);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_6, 7, 0, 1, 1);

        objType = new tlinsWAstroObjectType(gbGeneral);
        objType->setObjectName(QString::fromUtf8("objType"));
        sizePolicy1.setHeightForWidth(objType->sizePolicy().hasHeightForWidth());
        objType->setSizePolicy(sizePolicy1);
        objType->setMinimumSize(QSize(0, 40));
        objType->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_3->addWidget(objType, 7, 1, 1, 1);

        useObjectType = new QCheckBox(gbGeneral);
        useObjectType->setObjectName(QString::fromUtf8("useObjectType"));
        sizePolicy5.setHeightForWidth(useObjectType->sizePolicy().hasHeightForWidth());
        useObjectType->setSizePolicy(sizePolicy5);
        useObjectType->setMinimumSize(QSize(25, 25));
        useObjectType->setMaximumSize(QSize(25, 25));
        useObjectType->setChecked(true);

        gridLayout_3->addWidget(useObjectType, 7, 2, 1, 1);


        formLayout->setWidget(1, QFormLayout::SpanningRole, gbGeneral);

        gbMagnitude = new QGroupBox(gbBasic);
        gbMagnitude->setObjectName(QString::fromUtf8("gbMagnitude"));
        sizePolicy.setHeightForWidth(gbMagnitude->sizePolicy().hasHeightForWidth());
        gbMagnitude->setSizePolicy(sizePolicy);
        gbMagnitude->setMinimumSize(QSize(0, 0));
        gbMagnitude->setMaximumSize(QSize(16777215, 16777215));
        gbMagnitude->setFont(font);
        gbMagnitude->setCheckable(true);
        gridLayout_2 = new QGridLayout(gbMagnitude);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(5, 5, 5, 3);
        useMagnitudeFrom = new QCheckBox(gbMagnitude);
        useMagnitudeFrom->setObjectName(QString::fromUtf8("useMagnitudeFrom"));
        sizePolicy5.setHeightForWidth(useMagnitudeFrom->sizePolicy().hasHeightForWidth());
        useMagnitudeFrom->setSizePolicy(sizePolicy5);
        useMagnitudeFrom->setMinimumSize(QSize(25, 25));
        useMagnitudeFrom->setMaximumSize(QSize(25, 25));
        useMagnitudeFrom->setChecked(true);

        gridLayout_2->addWidget(useMagnitudeFrom, 0, 2, 1, 1);

        magnitudeTo = new tlinsWDecimalValue(gbMagnitude);
        magnitudeTo->setObjectName(QString::fromUtf8("magnitudeTo"));
        sizePolicy3.setHeightForWidth(magnitudeTo->sizePolicy().hasHeightForWidth());
        magnitudeTo->setSizePolicy(sizePolicy3);
        magnitudeTo->setMinimumSize(QSize(0, 40));
        magnitudeTo->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_2->addWidget(magnitudeTo, 0, 4, 1, 1);

        label_11 = new QLabel(gbMagnitude);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_11, 0, 0, 1, 1);

        magnitudeFrom = new tlinsWDecimalValue(gbMagnitude);
        magnitudeFrom->setObjectName(QString::fromUtf8("magnitudeFrom"));
        sizePolicy3.setHeightForWidth(magnitudeFrom->sizePolicy().hasHeightForWidth());
        magnitudeFrom->setSizePolicy(sizePolicy3);
        magnitudeFrom->setMinimumSize(QSize(0, 40));
        magnitudeFrom->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_2->addWidget(magnitudeFrom, 0, 1, 1, 1);

        useMagnitudeTo = new QCheckBox(gbMagnitude);
        useMagnitudeTo->setObjectName(QString::fromUtf8("useMagnitudeTo"));
        sizePolicy5.setHeightForWidth(useMagnitudeTo->sizePolicy().hasHeightForWidth());
        useMagnitudeTo->setSizePolicy(sizePolicy5);
        useMagnitudeTo->setMinimumSize(QSize(25, 25));
        useMagnitudeTo->setMaximumSize(QSize(25, 25));
        useMagnitudeTo->setChecked(true);

        gridLayout_2->addWidget(useMagnitudeTo, 0, 5, 1, 1);

        label_12 = new QLabel(gbMagnitude);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_12, 0, 3, 1, 1);


        formLayout->setWidget(2, QFormLayout::SpanningRole, gbMagnitude);


        verticalLayout->addWidget(gbBasic);

        sqlAdanced = new QGroupBox(tlinsWAstroDatabaseSearch3);
        sqlAdanced->setObjectName(QString::fromUtf8("sqlAdanced"));
        sizePolicy3.setHeightForWidth(sqlAdanced->sizePolicy().hasHeightForWidth());
        sqlAdanced->setSizePolicy(sizePolicy3);
        sqlAdanced->setMinimumSize(QSize(0, 120));
        sqlAdanced->setMaximumSize(QSize(16777215, 16777215));
        sqlAdanced->setCheckable(true);
        gridLayout_9 = new QGridLayout(sqlAdanced);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        gridLayout_9->setContentsMargins(5, 5, 5, 5);
        sqlText = new QTextEdit(sqlAdanced);
        sqlText->setObjectName(QString::fromUtf8("sqlText"));
        sizePolicy3.setHeightForWidth(sqlText->sizePolicy().hasHeightForWidth());
        sqlText->setSizePolicy(sizePolicy3);

        gridLayout_9->addWidget(sqlText, 0, 0, 1, 1);


        verticalLayout->addWidget(sqlAdanced);


        retranslateUi(tlinsWAstroDatabaseSearch3);

        QMetaObject::connectSlotsByName(tlinsWAstroDatabaseSearch3);
    } // setupUi

    void retranslateUi(QWidget *tlinsWAstroDatabaseSearch3)
    {
        tlinsWAstroDatabaseSearch3->setWindowTitle(QApplication::translate("tlinsWAstroDatabaseSearch3", "Form", nullptr));
        gbBasic->setTitle(QApplication::translate("tlinsWAstroDatabaseSearch3", "Besic creteria", nullptr));
        gbCoordinate->setTitle(QApplication::translate("tlinsWAstroDatabaseSearch3", "Coordinates", nullptr));
        useDc->setText(QString());
        label_3->setText(QApplication::translate("tlinsWAstroDatabaseSearch3", "Radius", nullptr));
        label_2->setText(QApplication::translate("tlinsWAstroDatabaseSearch3", "Hour angle", nullptr));
        useRadius->setText(QString());
        label_10->setText(QApplication::translate("tlinsWAstroDatabaseSearch3", "Declination", nullptr));
        useRa->setText(QString());
        gbGeneral->setTitle(QApplication::translate("tlinsWAstroDatabaseSearch3", "General", nullptr));
        useObjectName->setText(QString());
        label->setText(QApplication::translate("tlinsWAstroDatabaseSearch3", "Object id in catalog", nullptr));
        label_7->setText(QApplication::translate("tlinsWAstroDatabaseSearch3", "Catalog", nullptr));
        useObjectConstelation->setText(QString());
        label_4->setText(QApplication::translate("tlinsWAstroDatabaseSearch3", "Object name", nullptr));
        useObjectIdInCatalog->setText(QString());
        label_5->setText(QApplication::translate("tlinsWAstroDatabaseSearch3", "Constelation", nullptr));
        useObjectCatalog->setText(QString());
        label_6->setText(QApplication::translate("tlinsWAstroDatabaseSearch3", "Object type", nullptr));
        useObjectType->setText(QString());
        gbMagnitude->setTitle(QApplication::translate("tlinsWAstroDatabaseSearch3", "Magnitude", nullptr));
        useMagnitudeFrom->setText(QString());
        label_11->setText(QApplication::translate("tlinsWAstroDatabaseSearch3", "Magnitude from", nullptr));
        useMagnitudeTo->setText(QString());
        label_12->setText(QApplication::translate("tlinsWAstroDatabaseSearch3", "Magnitude to", nullptr));
        sqlAdanced->setTitle(QApplication::translate("tlinsWAstroDatabaseSearch3", "Adanced search", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWAstroDatabaseSearch3: public Ui_tlinsWAstroDatabaseSearch3 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWASTRODATABASESEARCH3_H
