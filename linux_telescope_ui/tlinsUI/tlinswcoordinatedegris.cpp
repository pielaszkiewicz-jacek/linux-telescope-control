#include "tlinswcoordinatedegris.h"
#include "tlinsuistrutils.h"
#include "tlinsuistylesmanager.h"
#include "ui_tlinswcoordinatedegris.h"
#include <QChar>
#include <QDebug>
#include <QString>
#include <QValidator>
#include <math.h>
#include <string>

DegrisValidator::DegrisValidator(int min_,
    int max_,
    QObject* parent)
    : QValidator(parent)
{
    min = min_;
    max = max_;
}

void DegrisValidator::getValue_(const QString& ss,
    int& d,
    unsigned int& m,
    double& s) const
{
    QString s1;
    QString s2;
    QString s3;

    tlinsUiStrUtils::get3Strings(ss, s1, s2, s3);

    d = s1.toInt();
    m = s2.toUInt();
    s = s3.toDouble();
}

QValidator::State DegrisValidator::validate(QString& input, int&) const
{
    QString s1;
    QString s2;
    QString s3;
    tlinsUiStrUtils::get3Strings(input, s1, s2, s3);

    int d;
    unsigned int m;
    double s;
    getValue_(input, d, m, s);

    if (d >= max) {
        return QValidator::Invalid;
    }
    if (d <= min) {
        return QValidator::Invalid;
    }

    if (m > 59) {
        return QValidator::Invalid;
    }

    if (s > 59.0) {
        return QValidator::Invalid;
    }

    return QValidator::Acceptable;
}

void DegrisValidator::fixup(QString& input) const
{
    QString s1;
    QString s2;
    QString s3;
    tlinsUiStrUtils::get3Strings(input, s1, s2, s3);

    int d;
    unsigned int m;
    double s;

    getValue_(input, d, m, s);

    bool update = false;

    if (d >= max) {
        s1 = std::to_string(max).c_str();
        s2 = "00";
        m = 0;
        s3 = "00.0000";
        s = 0.0;
        update = true;
    }
    if (d <= min) {
        s1 = std::to_string(min).c_str();
        s2 = "00";
        m = 0.0;
        s3 = "00.0000";
        s = 0.0;
        update = true;
    }

    if (m > 59) {
        s2 = "59";
        update = true;
    }
    if (m < 10) {
        QString s2_ = "0" + s2;
        s2 = s2_;
    }
    if (s2.length() < 2) {
        QString s2_ = "0" + s2;
        s2 = s2_;
    }

    if (s >= 60.0) {
        s3 = "59.9999";
        update = true;
    }

    if (update) {
        input = (s1 + QString(":") + s2 + QString(":") + s3);
    }
}

tlinsWCoordinateDegris::tlinsWCoordinateDegris(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWCoordinateDegris)
{
    ui->setupUi(this);

    ui->coordinateName->setVisible(false);

    // Control stylessetSectionResizeMode
    //    std:: string style;
    //    bool res = tlinsUiStylesManager:: getStyle( tlinsUiStylesManager:: DEGRIS,
    //                                                 tlinsUiStylesManager:: FieldType:: GROUP_BOX,
    //                                                 style );
    //    if( res )
    //        ui ->coordinateName->setStyleSheet( QString( style.c_str() ) );

    //    res = tlinsUiStylesManager:: getStyle( tlinsUiStylesManager:: DEGRIS,
    //                                            tlinsUiStylesManager:: FieldType:: EDIT,
    //                                            style );
    //    if( res )
    //        ui ->degris->setStyleSheet( QString( style.c_str() ) );

    // Set validator
    validator = new DegrisValidator(-360, 360, this);
    ui->degris->setValidator(validator);
}

void tlinsWCoordinateDegris::setValue(const double v)
{
    ui->degris->setText(tlinsUiStrUtils::setValueDegris(v));
}

double tlinsWCoordinateDegris::getValue() const
{
    int d;
    unsigned int m;
    double s;

    getValue(d, m, s);
    double ret = fabs((double)d) + (double)m / 60.0 + s / 3600.0;
    if (d < 0)
        return -1.0 * ret;

    return ret;
}

void tlinsWCoordinateDegris::getValue(int& d, unsigned int& m, double& s) const
{
    QString text(ui->degris->text());
    QString s1;
    QString s2;
    QString s3;

    tlinsUiStrUtils::get3Strings(text, s1, s2, s3);

    d = s1.toInt();
    m = s2.toUInt();
    s = s3.toDouble();
}

void tlinsWCoordinateDegris::setMinMax(const int min_, const int max_)
{
    DegrisValidator* newvalidator = new DegrisValidator(min_, max_, this);
    ui->degris->setValidator(newvalidator);

    delete validator;
    validator = newvalidator;
}

void tlinsWCoordinateDegris::setLabel(const std::string& label)
{
    ui->coordinateName->setText(QString(label.c_str()));
    ui->coordinateName->setVisible(true);
}

tlinsWCoordinateDegris::~tlinsWCoordinateDegris()
{
    delete ui;
    delete validator;
}
