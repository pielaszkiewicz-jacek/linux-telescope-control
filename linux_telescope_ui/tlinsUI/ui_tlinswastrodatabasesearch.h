/********************************************************************************
** Form generated from reading UI file 'tlinswastrodatabasesearch.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TLINSWASTRODATABASESEARCH_H
#define UI_TLINSWASTRODATABASESEARCH_H
#define QT_NO_PRINTER
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tlinsWAstroDatabaseSearch
{
public:
    QGroupBox *mainSearch;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *coordinates;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QWidget *ra;
    QWidget *dc;
    QWidget *radius;
    QGroupBox *groupBox_6;
    QDoubleSpinBox *magnitudeFrom;
    QDoubleSpinBox *magnitudeTo;
    QLabel *label;
    QWidget *widget1;
    QGridLayout *gridLayout;
    QWidget *wObjectType;
    QWidget *wCatalog;
    QWidget *wObjectName;
    QWidget *wConstelation;
    QGroupBox *advancedSearch;
    QTextEdit *sqlText;

    void setupUi(QWidget *tlinsWAstroDatabaseSearch)
    {
	if (tlinsWAstroDatabaseSearch->objectName().isEmpty())
	    tlinsWAstroDatabaseSearch->setObjectName(QString::fromUtf8("tlinsWAstroDatabaseSearch"));
	tlinsWAstroDatabaseSearch->resize(793, 666);
	mainSearch = new QGroupBox(tlinsWAstroDatabaseSearch);
	mainSearch->setObjectName(QString::fromUtf8("mainSearch"));
	mainSearch->setGeometry(QRect(1, 0, 800, 450));
	mainSearch->setMinimumSize(QSize(800, 450));
	mainSearch->setMaximumSize(QSize(800, 450));
	mainSearch->setSizeIncrement(QSize(0, 290));
	QFont font;
	font.setItalic(true);
	mainSearch->setFont(font);
	mainSearch->setCheckable(true);
	widget = new QWidget(mainSearch);
	widget->setObjectName(QString::fromUtf8("widget"));
	widget->setGeometry(QRect(11, 220, 701, 261));
	horizontalLayout_3 = new QHBoxLayout(widget);
	horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
	horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
	coordinates = new QGroupBox(widget);
	coordinates->setObjectName(QString::fromUtf8("coordinates"));
	coordinates->setMinimumSize(QSize(450, 200));
	coordinates->setMaximumSize(QSize(475, 200));
	coordinates->setCheckable(true);
	layoutWidget = new QWidget(coordinates);
	layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
	layoutWidget->setGeometry(QRect(10, 30, 450, 161));
	verticalLayout_2 = new QVBoxLayout(layoutWidget);
	verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
	verticalLayout_2->setContentsMargins(0, 0, 0, 0);
	horizontalLayout_2 = new QHBoxLayout();
	horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
	ra = new QWidget(layoutWidget);
	ra->setObjectName(QString::fromUtf8("ra"));
	ra->setMinimumSize(QSize(220, 70));
	ra->setMaximumSize(QSize(220, 70));

	horizontalLayout_2->addWidget(ra);

	dc = new QWidget(layoutWidget);
	dc->setObjectName(QString::fromUtf8("dc"));
	dc->setMinimumSize(QSize(220, 70));
	dc->setMaximumSize(QSize(220, 70));

	horizontalLayout_2->addWidget(dc);


	verticalLayout_2->addLayout(horizontalLayout_2);

	radius = new QWidget(layoutWidget);
	radius->setObjectName(QString::fromUtf8("radius"));
	radius->setMinimumSize(QSize(220, 70));
	radius->setMaximumSize(QSize(220, 70));

	verticalLayout_2->addWidget(radius);


	horizontalLayout_3->addWidget(coordinates);

	groupBox_6 = new QGroupBox(widget);
	groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
	groupBox_6->setMinimumSize(QSize(220, 65));
	groupBox_6->setMaximumSize(QSize(220, 65));
	groupBox_6->setCheckable(true);
	magnitudeFrom = new QDoubleSpinBox(groupBox_6);
	magnitudeFrom->setObjectName(QString::fromUtf8("magnitudeFrom"));
	magnitudeFrom->setGeometry(QRect(11, 31, 80, 25));
	magnitudeFrom->setMinimumSize(QSize(80, 25));
	magnitudeFrom->setMaximumSize(QSize(80, 25));
	magnitudeFrom->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
	magnitudeFrom->setDecimals(4);
	magnitudeTo = new QDoubleSpinBox(groupBox_6);
	magnitudeTo->setObjectName(QString::fromUtf8("magnitudeTo"));
	magnitudeTo->setGeometry(QRect(126, 31, 80, 25));
	magnitudeTo->setMinimumSize(QSize(80, 25));
	magnitudeTo->setMaximumSize(QSize(80, 25));
	magnitudeTo->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
	magnitudeTo->setDecimals(4);
	label = new QLabel(groupBox_6);
	label->setObjectName(QString::fromUtf8("label"));
	label->setGeometry(QRect(106, 31, 16, 16));
	label->setAlignment(Qt::AlignCenter);

	horizontalLayout_3->addWidget(groupBox_6);

	widget1 = new QWidget(mainSearch);
	widget1->setObjectName(QString::fromUtf8("widget1"));
	widget1->setGeometry(QRect(13, 32, 734, 148));
	gridLayout = new QGridLayout(widget1);
	gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
	gridLayout->setContentsMargins(0, 0, 0, 0);
	wObjectType = new QWidget(widget1);
	wObjectType->setObjectName(QString::fromUtf8("wObjectType"));
	wObjectType->setMinimumSize(QSize(240, 70));
	wObjectType->setMaximumSize(QSize(240, 70));

	gridLayout->addWidget(wObjectType, 0, 0, 1, 1);

	wCatalog = new QWidget(widget1);
	wCatalog->setObjectName(QString::fromUtf8("wCatalog"));
	wCatalog->setMinimumSize(QSize(240, 70));
	wCatalog->setMaximumSize(QSize(240, 70));

	gridLayout->addWidget(wCatalog, 0, 1, 1, 1);

	wObjectName = new QWidget(widget1);
	wObjectName->setObjectName(QString::fromUtf8("wObjectName"));
	wObjectName->setMinimumSize(QSize(240, 70));
	wObjectName->setMaximumSize(QSize(240, 70));

	gridLayout->addWidget(wObjectName, 0, 2, 1, 1);

	wConstelation = new QWidget(widget1);
	wConstelation->setObjectName(QString::fromUtf8("wConstelation"));
	wConstelation->setMinimumSize(QSize(240, 70));
	wConstelation->setMaximumSize(QSize(240, 70));

	gridLayout->addWidget(wConstelation, 1, 0, 1, 1);

	advancedSearch = new QGroupBox(tlinsWAstroDatabaseSearch);
	advancedSearch->setObjectName(QString::fromUtf8("advancedSearch"));
	advancedSearch->setGeometry(QRect(1, 530, 725, 95));
	advancedSearch->setMinimumSize(QSize(725, 95));
	advancedSearch->setMaximumSize(QSize(725, 95));
	advancedSearch->setFont(font);
	advancedSearch->setCheckable(true);
	advancedSearch->setChecked(false);
	sqlText = new QTextEdit(advancedSearch);
	sqlText->setObjectName(QString::fromUtf8("sqlText"));
	sqlText->setGeometry(QRect(10, 30, 700, 55));
	sqlText->setMinimumSize(QSize(700, 25));
	sqlText->setMaximumSize(QSize(700, 16777215));
	QWidget::setTabOrder(advancedSearch, coordinates);
	QWidget::setTabOrder(coordinates, groupBox_6);
	QWidget::setTabOrder(groupBox_6, magnitudeFrom);
	QWidget::setTabOrder(magnitudeFrom, magnitudeTo);
	QWidget::setTabOrder(magnitudeTo, sqlText);
	QWidget::setTabOrder(sqlText, mainSearch);

	retranslateUi(tlinsWAstroDatabaseSearch);

	QMetaObject::connectSlotsByName(tlinsWAstroDatabaseSearch);
    } // setupUi

    void retranslateUi(QWidget *tlinsWAstroDatabaseSearch)
    {
	tlinsWAstroDatabaseSearch->setWindowTitle(QApplication::translate("tlinsWAstroDatabaseSearch", "Form", 0));
	mainSearch->setTitle(QApplication::translate("tlinsWAstroDatabaseSearch", "Search creteria", 0));
	coordinates->setTitle(QApplication::translate("tlinsWAstroDatabaseSearch", "Coordinates", 0));
	groupBox_6->setTitle(QApplication::translate("tlinsWAstroDatabaseSearch", "Magnitude", 0));
	label->setText(QApplication::translate("tlinsWAstroDatabaseSearch", "-", 0));
	advancedSearch->setTitle(QApplication::translate("tlinsWAstroDatabaseSearch", "Advanced search", 0));
    } // retranslateUi

};

namespace Ui {
    class tlinsWAstroDatabaseSearch: public Ui_tlinsWAstroDatabaseSearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TLINSWASTRODATABASESEARCH_H
