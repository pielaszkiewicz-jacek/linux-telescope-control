/********************************************************************************
** Form generated from reading UI file 'tlinswastrodatabaseobject.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWASTRODATABASEOBJECT_H
#define UI_TLINSWASTRODATABASEOBJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <tlinswastrocatalog.h>
#include <tlinswdecimalvalue.h>
#include "tlinswastroobjecttype.h"
#include "tlinswcatalogobjecttype.h"
#include "tlinswconstelation.h"
#include "tlinswcoordinatedeclination.h"
#include "tlinswcoordinatehourangle.h"
#include "tlinswobjectname.h"

QT_BEGIN_NAMESPACE

class Ui_tlinsWAstroDatabaseObject
{
public:
    QFormLayout *formLayout_4;
    QTabWidget *tabWidget;
    QWidget *tabGeneralInfo;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_12;
    QGridLayout *gridLayout_11;
    QLabel *label_18;
    tlinsWConstelation *objConstelation;
    QLabel *label_20;
    tlinsWObjectName *objName;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_7;
    QGridLayout *gridLayout_13;
    QLabel *label_21;
    QLabel *label_19;
    tlinsWDecimalValue *magnitude;
    tlinsWDecimalValue *magnitudeError;
    QGroupBox *gbDescription;
    QGridLayout *gridLayout_14;
    QTextEdit *description;
    QGroupBox *gbObjectType;
    QFormLayout *formLayout_5;
    QFormLayout *formLayout_6;
    QLabel *label_23;
    tlinsWAstroObjectType *objType;
    QGridLayout *gridLayout_17;
    QLabel *label;
    QTextEdit *objectTypeDetails1;
    QGridLayout *gridLayout_18;
    QTextEdit *objectTypeDetails2;
    QLabel *label_2;
    QGridLayout *gridLayout_19;
    QLabel *label_3;
    QTextEdit *objectTypeDetails3;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QWidget *tabCatalog;
    QGridLayout *gridLayout_10;
    QGridLayout *gridLayout_3;
    QLabel *label_16;
    tlinsWAstroCatalog *catalogID;
    tlinsWCatalogObjectType *objCatalogObjectId;
    QLabel *label_17;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QTextEdit *catalogDescription;
    QWidget *tabCoordinate;
    QFormLayout *formLayout_3;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QGridLayout *gridLayout_9;
    QLabel *label_13;
    QLabel *label_12;
    tlinsWCoordinateHourAngle *ra;
    tlinsWCoordinateDeclination *dc;
    QGroupBox *groupBox_5;
    QFormLayout *formLayout_2;
    QGridLayout *gridLayout_6;
    QLabel *label_9;
    QLabel *label_8;
    QLabel *label_11;
    QLabel *label_10;
    tlinsWDecimalValue *raMinErr;
    tlinsWDecimalValue *dcMinErr;
    tlinsWDecimalValue *raMeanErr;
    tlinsWDecimalValue *dcMeanErr;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_8;
    tlinsWDecimalValue *centralEpochRa;
    QLabel *label_6;
    QLabel *label_7;
    tlinsWDecimalValue *centralEpochDc;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QLabel *label_25;
    tlinsWDecimalValue *pmDc;
    tlinsWDecimalValue *pmRa;
    QLabel *label_15;
    QLabel *label_14;
    QLabel *label_4;
    QLabel *label_5;
    tlinsWDecimalValue *pmRaErr;
    tlinsWDecimalValue *pmDcErr;
    QLabel *label_26;
    QGroupBox *groupBox_8;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout_15;
    tlinsWDecimalValue *radialVelocity;
    QLabel *label_22;
    QLabel *label_24;
    tlinsWDecimalValue *parallex;

    void setupUi(QWidget *tlinsWAstroDatabaseObject)
    {
        if (tlinsWAstroDatabaseObject->objectName().isEmpty())
            tlinsWAstroDatabaseObject->setObjectName(QString::fromUtf8("tlinsWAstroDatabaseObject"));
        tlinsWAstroDatabaseObject->resize(1326, 957);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tlinsWAstroDatabaseObject->sizePolicy().hasHeightForWidth());
        tlinsWAstroDatabaseObject->setSizePolicy(sizePolicy);
        tlinsWAstroDatabaseObject->setMinimumSize(QSize(655, 530));
        tlinsWAstroDatabaseObject->setMaximumSize(QSize(16777215, 16777215));
        formLayout_4 = new QFormLayout(tlinsWAstroDatabaseObject);
        formLayout_4->setObjectName(QString::fromUtf8("formLayout_4"));
        tabWidget = new QTabWidget(tlinsWAstroDatabaseObject);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMinimumSize(QSize(655, 530));
        tabWidget->setMaximumSize(QSize(16777215, 16777215));
        tabWidget->setSizeIncrement(QSize(0, 0));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setUsesScrollButtons(true);
        tabGeneralInfo = new QWidget();
        tabGeneralInfo->setObjectName(QString::fromUtf8("tabGeneralInfo"));
        verticalLayout = new QVBoxLayout(tabGeneralInfo);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_3 = new QGroupBox(tabGeneralInfo);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        QFont font;
        font.setBold(false);
        font.setItalic(true);
        font.setWeight(50);
        groupBox_3->setFont(font);
        gridLayout_12 = new QGridLayout(groupBox_3);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        gridLayout_11 = new QGridLayout();
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        label_18 = new QLabel(groupBox_3);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        QFont font1;
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        label_18->setFont(font1);

        gridLayout_11->addWidget(label_18, 0, 0, 1, 1);

        objConstelation = new tlinsWConstelation(groupBox_3);
        objConstelation->setObjectName(QString::fromUtf8("objConstelation"));
        objConstelation->setMinimumSize(QSize(0, 48));

        gridLayout_11->addWidget(objConstelation, 0, 1, 1, 1);

        label_20 = new QLabel(groupBox_3);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setFont(font1);

        gridLayout_11->addWidget(label_20, 0, 2, 1, 1);

        objName = new tlinsWObjectName(groupBox_3);
        objName->setObjectName(QString::fromUtf8("objName"));
        objName->setMinimumSize(QSize(0, 48));

        gridLayout_11->addWidget(objName, 0, 3, 1, 1);


        gridLayout_12->addLayout(gridLayout_11, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(tabGeneralInfo);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        QFont font2;
        font2.setItalic(true);
        groupBox_4->setFont(font2);
        gridLayout_7 = new QGridLayout(groupBox_4);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_13 = new QGridLayout();
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        label_21 = new QLabel(groupBox_4);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setFont(font1);

        gridLayout_13->addWidget(label_21, 0, 2, 1, 1);

        label_19 = new QLabel(groupBox_4);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        QFont font3;
        font3.setItalic(false);
        label_19->setFont(font3);

        gridLayout_13->addWidget(label_19, 0, 0, 1, 1);

        magnitude = new tlinsWDecimalValue(groupBox_4);
        magnitude->setObjectName(QString::fromUtf8("magnitude"));
        magnitude->setMinimumSize(QSize(0, 48));

        gridLayout_13->addWidget(magnitude, 0, 1, 1, 1);

        magnitudeError = new tlinsWDecimalValue(groupBox_4);
        magnitudeError->setObjectName(QString::fromUtf8("magnitudeError"));
        magnitudeError->setMinimumSize(QSize(0, 48));

        gridLayout_13->addWidget(magnitudeError, 0, 3, 1, 1);


        gridLayout_7->addLayout(gridLayout_13, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_4);

        gbDescription = new QGroupBox(tabGeneralInfo);
        gbDescription->setObjectName(QString::fromUtf8("gbDescription"));
        gbDescription->setFont(font2);
        gridLayout_14 = new QGridLayout(gbDescription);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        description = new QTextEdit(gbDescription);
        description->setObjectName(QString::fromUtf8("description"));

        gridLayout_14->addWidget(description, 0, 0, 1, 1);


        verticalLayout->addWidget(gbDescription);

        gbObjectType = new QGroupBox(tabGeneralInfo);
        gbObjectType->setObjectName(QString::fromUtf8("gbObjectType"));
        gbObjectType->setMinimumSize(QSize(0, 95));
        gbObjectType->setFont(font2);
        formLayout_5 = new QFormLayout(gbObjectType);
        formLayout_5->setObjectName(QString::fromUtf8("formLayout_5"));
        formLayout_6 = new QFormLayout();
        formLayout_6->setObjectName(QString::fromUtf8("formLayout_6"));
        label_23 = new QLabel(gbObjectType);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setFont(font3);

        formLayout_6->setWidget(0, QFormLayout::LabelRole, label_23);

        objType = new tlinsWAstroObjectType(gbObjectType);
        objType->setObjectName(QString::fromUtf8("objType"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(objType->sizePolicy().hasHeightForWidth());
        objType->setSizePolicy(sizePolicy1);
        objType->setMinimumSize(QSize(310, 48));
        objType->setMaximumSize(QSize(16777215, 35));

        formLayout_6->setWidget(0, QFormLayout::FieldRole, objType);


        formLayout_5->setLayout(0, QFormLayout::SpanningRole, formLayout_6);

        gridLayout_17 = new QGridLayout();
        gridLayout_17->setObjectName(QString::fromUtf8("gridLayout_17"));
        label = new QLabel(gbObjectType);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(45, 45));
        label->setMaximumSize(QSize(45, 45));
        label->setFont(font3);

        gridLayout_17->addWidget(label, 0, 0, 1, 1);

        objectTypeDetails1 = new QTextEdit(gbObjectType);
        objectTypeDetails1->setObjectName(QString::fromUtf8("objectTypeDetails1"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(objectTypeDetails1->sizePolicy().hasHeightForWidth());
        objectTypeDetails1->setSizePolicy(sizePolicy2);
        objectTypeDetails1->setMinimumSize(QSize(0, 48));
        objectTypeDetails1->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_17->addWidget(objectTypeDetails1, 0, 1, 1, 1);


        formLayout_5->setLayout(1, QFormLayout::SpanningRole, gridLayout_17);

        gridLayout_18 = new QGridLayout();
        gridLayout_18->setObjectName(QString::fromUtf8("gridLayout_18"));
        objectTypeDetails2 = new QTextEdit(gbObjectType);
        objectTypeDetails2->setObjectName(QString::fromUtf8("objectTypeDetails2"));
        sizePolicy2.setHeightForWidth(objectTypeDetails2->sizePolicy().hasHeightForWidth());
        objectTypeDetails2->setSizePolicy(sizePolicy2);
        objectTypeDetails2->setMinimumSize(QSize(0, 48));
        objectTypeDetails2->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_18->addWidget(objectTypeDetails2, 0, 1, 1, 1);

        label_2 = new QLabel(gbObjectType);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(45, 45));
        label_2->setMaximumSize(QSize(45, 45));
        label_2->setFont(font3);

        gridLayout_18->addWidget(label_2, 0, 0, 1, 1);


        formLayout_5->setLayout(3, QFormLayout::SpanningRole, gridLayout_18);

        gridLayout_19 = new QGridLayout();
        gridLayout_19->setObjectName(QString::fromUtf8("gridLayout_19"));
        label_3 = new QLabel(gbObjectType);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(45, 45));
        label_3->setMaximumSize(QSize(45, 45));
        label_3->setFont(font3);

        gridLayout_19->addWidget(label_3, 0, 0, 1, 1);

        objectTypeDetails3 = new QTextEdit(gbObjectType);
        objectTypeDetails3->setObjectName(QString::fromUtf8("objectTypeDetails3"));
        sizePolicy2.setHeightForWidth(objectTypeDetails3->sizePolicy().hasHeightForWidth());
        objectTypeDetails3->setSizePolicy(sizePolicy2);
        objectTypeDetails3->setMinimumSize(QSize(0, 48));
        objectTypeDetails3->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_19->addWidget(objectTypeDetails3, 0, 1, 1, 1);


        formLayout_5->setLayout(5, QFormLayout::SpanningRole, gridLayout_19);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout_5->setItem(2, QFormLayout::LabelRole, verticalSpacer);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout_5->setItem(4, QFormLayout::LabelRole, verticalSpacer_2);


        verticalLayout->addWidget(gbObjectType);

        tabWidget->addTab(tabGeneralInfo, QString());
        tabCatalog = new QWidget();
        tabCatalog->setObjectName(QString::fromUtf8("tabCatalog"));
        gridLayout_10 = new QGridLayout(tabCatalog);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_10->setContentsMargins(5, 5, 5, 20);
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setHorizontalSpacing(6);
        gridLayout_3->setVerticalSpacing(0);
        gridLayout_3->setContentsMargins(-1, 6, 8, 6);
        label_16 = new QLabel(tabCatalog);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_3->addWidget(label_16, 0, 0, 1, 1);

        catalogID = new tlinsWAstroCatalog(tabCatalog);
        catalogID->setObjectName(QString::fromUtf8("catalogID"));
        catalogID->setMinimumSize(QSize(310, 48));
        catalogID->setMaximumSize(QSize(310, 16777215));

        gridLayout_3->addWidget(catalogID, 0, 1, 1, 1);

        objCatalogObjectId = new tlinsWCatalogObjectType(tabCatalog);
        objCatalogObjectId->setObjectName(QString::fromUtf8("objCatalogObjectId"));
        objCatalogObjectId->setMinimumSize(QSize(0, 48));
        objCatalogObjectId->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_3->addWidget(objCatalogObjectId, 1, 1, 1, 1);

        label_17 = new QLabel(tabCatalog);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_3->addWidget(label_17, 1, 0, 1, 1);


        gridLayout_10->addLayout(gridLayout_3, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(tabCatalog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy3);
        groupBox_2->setFont(font2);
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(5, 5, 5, 5);
        catalogDescription = new QTextEdit(groupBox_2);
        catalogDescription->setObjectName(QString::fromUtf8("catalogDescription"));
        catalogDescription->setMinimumSize(QSize(0, 0));
        catalogDescription->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_4->addWidget(catalogDescription, 0, 0, 1, 1);


        gridLayout_10->addWidget(groupBox_2, 1, 0, 1, 1);

        tabWidget->addTab(tabCatalog, QString());
        tabCoordinate = new QWidget();
        tabCoordinate->setObjectName(QString::fromUtf8("tabCoordinate"));
        formLayout_3 = new QFormLayout(tabCoordinate);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        groupBox = new QGroupBox(tabCoordinate);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setFont(font2);
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        gridLayout_9 = new QGridLayout();
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_9->addWidget(label_13, 0, 2, 1, 1);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_9->addWidget(label_12, 0, 0, 1, 1);

        ra = new tlinsWCoordinateHourAngle(groupBox);
        ra->setObjectName(QString::fromUtf8("ra"));
        ra->setMinimumSize(QSize(0, 48));

        gridLayout_9->addWidget(ra, 0, 1, 1, 1);

        dc = new tlinsWCoordinateDeclination(groupBox);
        dc->setObjectName(QString::fromUtf8("dc"));
        dc->setMinimumSize(QSize(0, 48));

        gridLayout_9->addWidget(dc, 0, 3, 1, 1);


        formLayout->setLayout(0, QFormLayout::SpanningRole, gridLayout_9);


        formLayout_3->setWidget(0, QFormLayout::SpanningRole, groupBox);

        groupBox_5 = new QGroupBox(tabCoordinate);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setFont(font2);
        formLayout_2 = new QFormLayout(groupBox_5);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_9 = new QLabel(groupBox_5);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_6->addWidget(label_9, 0, 2, 1, 1);

        label_8 = new QLabel(groupBox_5);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_6->addWidget(label_8, 0, 0, 1, 1);

        label_11 = new QLabel(groupBox_5);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_6->addWidget(label_11, 1, 2, 1, 1);

        label_10 = new QLabel(groupBox_5);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_6->addWidget(label_10, 1, 0, 1, 1);

        raMinErr = new tlinsWDecimalValue(groupBox_5);
        raMinErr->setObjectName(QString::fromUtf8("raMinErr"));
        raMinErr->setMinimumSize(QSize(0, 48));

        gridLayout_6->addWidget(raMinErr, 0, 1, 1, 1);

        dcMinErr = new tlinsWDecimalValue(groupBox_5);
        dcMinErr->setObjectName(QString::fromUtf8("dcMinErr"));
        dcMinErr->setMinimumSize(QSize(0, 48));

        gridLayout_6->addWidget(dcMinErr, 0, 3, 1, 1);

        raMeanErr = new tlinsWDecimalValue(groupBox_5);
        raMeanErr->setObjectName(QString::fromUtf8("raMeanErr"));
        raMeanErr->setMinimumSize(QSize(0, 48));

        gridLayout_6->addWidget(raMeanErr, 1, 1, 1, 1);

        dcMeanErr = new tlinsWDecimalValue(groupBox_5);
        dcMeanErr->setObjectName(QString::fromUtf8("dcMeanErr"));
        dcMeanErr->setMinimumSize(QSize(0, 48));

        gridLayout_6->addWidget(dcMeanErr, 1, 3, 1, 1);


        formLayout_2->setLayout(0, QFormLayout::SpanningRole, gridLayout_6);


        formLayout_3->setWidget(1, QFormLayout::SpanningRole, groupBox_5);

        groupBox_7 = new QGroupBox(tabCoordinate);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setFont(font2);
        gridLayout_5 = new QGridLayout(groupBox_7);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_8 = new QGridLayout();
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        centralEpochRa = new tlinsWDecimalValue(groupBox_7);
        centralEpochRa->setObjectName(QString::fromUtf8("centralEpochRa"));
        centralEpochRa->setMinimumSize(QSize(0, 48));

        gridLayout_8->addWidget(centralEpochRa, 0, 1, 1, 1);

        label_6 = new QLabel(groupBox_7);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_8->addWidget(label_6, 0, 0, 1, 1);

        label_7 = new QLabel(groupBox_7);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_8->addWidget(label_7, 0, 2, 1, 1);

        centralEpochDc = new tlinsWDecimalValue(groupBox_7);
        centralEpochDc->setObjectName(QString::fromUtf8("centralEpochDc"));
        centralEpochDc->setMinimumSize(QSize(0, 48));

        gridLayout_8->addWidget(centralEpochDc, 0, 3, 1, 1);


        gridLayout_5->addLayout(gridLayout_8, 0, 0, 1, 1);


        formLayout_3->setWidget(2, QFormLayout::SpanningRole, groupBox_7);

        groupBox_6 = new QGroupBox(tabCoordinate);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setFont(font2);
        gridLayout = new QGridLayout(groupBox_6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_25 = new QLabel(groupBox_6);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_25, 0, 2, 1, 1);

        pmDc = new tlinsWDecimalValue(groupBox_6);
        pmDc->setObjectName(QString::fromUtf8("pmDc"));
        pmDc->setMinimumSize(QSize(0, 48));

        gridLayout_2->addWidget(pmDc, 0, 4, 1, 1);

        pmRa = new tlinsWDecimalValue(groupBox_6);
        pmRa->setObjectName(QString::fromUtf8("pmRa"));
        pmRa->setMinimumSize(QSize(0, 48));

        gridLayout_2->addWidget(pmRa, 0, 1, 1, 1);

        label_15 = new QLabel(groupBox_6);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_2->addWidget(label_15, 1, 3, 1, 1);

        label_14 = new QLabel(groupBox_6);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_2->addWidget(label_14, 1, 0, 1, 1);

        label_4 = new QLabel(groupBox_6);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        label_5 = new QLabel(groupBox_6);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 0, 3, 1, 1);

        pmRaErr = new tlinsWDecimalValue(groupBox_6);
        pmRaErr->setObjectName(QString::fromUtf8("pmRaErr"));
        pmRaErr->setMinimumSize(QSize(0, 48));

        gridLayout_2->addWidget(pmRaErr, 1, 1, 1, 1);

        pmDcErr = new tlinsWDecimalValue(groupBox_6);
        pmDcErr->setObjectName(QString::fromUtf8("pmDcErr"));
        pmDcErr->setMinimumSize(QSize(0, 48));

        gridLayout_2->addWidget(pmDcErr, 1, 4, 1, 1);

        label_26 = new QLabel(groupBox_6);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_26, 0, 5, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 1);


        formLayout_3->setWidget(3, QFormLayout::SpanningRole, groupBox_6);

        groupBox_8 = new QGroupBox(tabCoordinate);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setFont(font2);
        horizontalLayout = new QHBoxLayout(groupBox_8);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout_15 = new QGridLayout();
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        radialVelocity = new tlinsWDecimalValue(groupBox_8);
        radialVelocity->setObjectName(QString::fromUtf8("radialVelocity"));
        radialVelocity->setMinimumSize(QSize(0, 48));

        gridLayout_15->addWidget(radialVelocity, 0, 1, 1, 1);

        label_22 = new QLabel(groupBox_8);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout_15->addWidget(label_22, 0, 0, 1, 1);

        label_24 = new QLabel(groupBox_8);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        gridLayout_15->addWidget(label_24, 1, 0, 1, 1);

        parallex = new tlinsWDecimalValue(groupBox_8);
        parallex->setObjectName(QString::fromUtf8("parallex"));
        parallex->setMinimumSize(QSize(0, 48));

        gridLayout_15->addWidget(parallex, 1, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout_15);


        formLayout_3->setWidget(4, QFormLayout::SpanningRole, groupBox_8);

        tabWidget->addTab(tabCoordinate, QString());

        formLayout_4->setWidget(0, QFormLayout::SpanningRole, tabWidget);


        retranslateUi(tlinsWAstroDatabaseObject);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(tlinsWAstroDatabaseObject);
    } // setupUi

    void retranslateUi(QWidget *tlinsWAstroDatabaseObject)
    {
        tlinsWAstroDatabaseObject->setWindowTitle(QApplication::translate("tlinsWAstroDatabaseObject", "Form", nullptr));
        groupBox_3->setTitle(QApplication::translate("tlinsWAstroDatabaseObject", "Constelation and object name", nullptr));
        label_18->setText(QApplication::translate("tlinsWAstroDatabaseObject", "Constelation", nullptr));
        label_20->setText(QApplication::translate("tlinsWAstroDatabaseObject", "Object name", nullptr));
        groupBox_4->setTitle(QApplication::translate("tlinsWAstroDatabaseObject", "Magnitude", nullptr));
        label_21->setText(QApplication::translate("tlinsWAstroDatabaseObject", "Magnitude error", nullptr));
        label_19->setText(QApplication::translate("tlinsWAstroDatabaseObject", "Magnitude", nullptr));
        gbDescription->setTitle(QApplication::translate("tlinsWAstroDatabaseObject", "Description", nullptr));
        gbObjectType->setTitle(QApplication::translate("tlinsWAstroDatabaseObject", "Object type details", nullptr));
        label_23->setText(QApplication::translate("tlinsWAstroDatabaseObject", "Object type", nullptr));
        label->setText(QApplication::translate("tlinsWAstroDatabaseObject", "Detail 1", nullptr));
        label_2->setText(QApplication::translate("tlinsWAstroDatabaseObject", "Detail 2 ", nullptr));
        label_3->setText(QApplication::translate("tlinsWAstroDatabaseObject", "Detail 3", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabGeneralInfo), QApplication::translate("tlinsWAstroDatabaseObject", "General info", nullptr));
        label_16->setText(QApplication::translate("tlinsWAstroDatabaseObject", "Catalog", nullptr));
        label_17->setText(QApplication::translate("tlinsWAstroDatabaseObject", "Object catalog ID", nullptr));
        groupBox_2->setTitle(QApplication::translate("tlinsWAstroDatabaseObject", "Catalog Description", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabCatalog), QApplication::translate("tlinsWAstroDatabaseObject", "Catalog", nullptr));
        groupBox->setTitle(QApplication::translate("tlinsWAstroDatabaseObject", "Coordinates", nullptr));
        label_13->setText(QApplication::translate("tlinsWAstroDatabaseObject", "DC", nullptr));
        label_12->setText(QApplication::translate("tlinsWAstroDatabaseObject", "RA", nullptr));
        groupBox_5->setTitle(QApplication::translate("tlinsWAstroDatabaseObject", "Coordinate errors", nullptr));
        label_9->setText(QApplication::translate("tlinsWAstroDatabaseObject", "Min Error (DC)", nullptr));
        label_8->setText(QApplication::translate("tlinsWAstroDatabaseObject", "Min Error (RA)", nullptr));
        label_11->setText(QApplication::translate("tlinsWAstroDatabaseObject", "Mean Error (DC)", nullptr));
        label_10->setText(QApplication::translate("tlinsWAstroDatabaseObject", "Mean Error (RA)", nullptr));
        groupBox_7->setTitle(QApplication::translate("tlinsWAstroDatabaseObject", "Central epoch", nullptr));
        label_6->setText(QApplication::translate("tlinsWAstroDatabaseObject", "Central epoch (RA)", nullptr));
        label_7->setText(QApplication::translate("tlinsWAstroDatabaseObject", "Central epoch (DC)", nullptr));
        groupBox_6->setTitle(QApplication::translate("tlinsWAstroDatabaseObject", "Proper motion", nullptr));
        label_25->setText(QApplication::translate("tlinsWAstroDatabaseObject", "[mas/year]", nullptr));
        label_15->setText(QApplication::translate("tlinsWAstroDatabaseObject", "Error (DC)", nullptr));
        label_14->setText(QApplication::translate("tlinsWAstroDatabaseObject", "Error (RA)", nullptr));
        label_4->setText(QApplication::translate("tlinsWAstroDatabaseObject", "Proper motion (RA)", nullptr));
        label_5->setText(QApplication::translate("tlinsWAstroDatabaseObject", "Proper motion (DC)", nullptr));
        label_26->setText(QApplication::translate("tlinsWAstroDatabaseObject", "[mas/year]", nullptr));
        groupBox_8->setTitle(QApplication::translate("tlinsWAstroDatabaseObject", "Other", nullptr));
        label_22->setText(QApplication::translate("tlinsWAstroDatabaseObject", "Radial velocity", nullptr));
        label_24->setText(QApplication::translate("tlinsWAstroDatabaseObject", "Parallex", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabCoordinate), QApplication::translate("tlinsWAstroDatabaseObject", "Coordinates and Proper motion", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tlinsWAstroDatabaseObject: public Ui_tlinsWAstroDatabaseObject {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWASTRODATABASEOBJECT_H
