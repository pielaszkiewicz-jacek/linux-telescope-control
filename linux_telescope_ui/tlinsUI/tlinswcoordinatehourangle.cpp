#include "tlinswcoordinatehourangle.h"
#include "QDebug"
#include "tlinsuistrutils.h"
#include "tlinsuistylesmanager.h"
#include "ui_tlinswcoordinatehourangle.h"

void HourAngleValidator::getValue_(const QString& ss,
    int& h,
    unsigned int& m,
    double& s) const
{
    QString s1;
    QString s2;
    QString s3;

    tlinsUiStrUtils::get3Strings(ss, s1, s2, s3);

    h = s1.toInt();
    m = s2.toUInt();
    s = s3.toDouble();
}

HourAngleValidator::HourAngleValidator(QObject* parent)
    : QValidator(parent)
{
}

QValidator::State HourAngleValidator::validate(QString& input,
    int&) const
{
    qDebug() << "void tlinsWCoordinateHourAngle:: update()";

    QString s1, s2, s3;
    tlinsUiStrUtils::get3Strings(input, s1, s2, s3);

    int h;
    unsigned int m;
    double s;

    getValue_(input, h, m, s);

    if (h >= 24) {
        return State::Invalid;
    }

    if (m > 59) {
        return State::Invalid;
    }

    if (s >= 60.0) {
        return State::Invalid;
    }

    return State::Acceptable;
}
void HourAngleValidator::fixup(QString& input) const
{
    qDebug() << "void tlinsWCoordinateHourAngle:: update()";

    QString s1, s2, s3;
    tlinsUiStrUtils::get3Strings(input, s1, s2, s3);
    bool update = false;

    int h;
    unsigned int m;
    double s;

    getValue_(input, h, m, s);

    if (h >= 24) {
        s1 = "23";
        update = true;
    }

    if (m > 59) {
        s2 = "59";
        update = true;
    }

    if (s >= 60.0) {
        s3 = "59.9999";
        update = true;
    }

    if (update) {
        input = (s1 + QString(":") + s2 + QString(":") + s3);
    }
}

//
// ---
// ---
// ---
//
tlinsWCoordinateHourAngle::tlinsWCoordinateHourAngle(QWidget* parent)
    : QWidget(parent)
    , validator(this)
    , ui(new Ui::tlinsWCoordinateHourAngle)
{
    ui->setupUi(this);

    // Control styles
    //    std:: string style;
    //    bool res = tlinsUiStylesManager:: getStyle( tlinsUiStylesManager:: HOUR_ANGLE,
    //                                                 tlinsUiStylesManager:: FieldType:: GROUP_BOX,
    //                                                 style );
    //    if( res )
    //        ui ->groupBox->setStyleSheet( QString( style.c_str() ) );

    //    res = tlinsUiStylesManager:: getStyle( tlinsUiStylesManager:: HOUR_ANGLE,
    //                                            tlinsUiStylesManager:: FieldType:: EDIT,
    //                                            style );
    //    if( res )
    //        ui ->ra->setStyleSheet( QString( style.c_str() ) );

    ui->ra->setValidator(&validator);
    ui->label->setVisible(false);
}

std::string tlinsWCoordinateHourAngle::toString() const
{
    //    QString str = tlinsUiStrUtils:: setValueHour( this -> getValue() );
    //    return str.toStdString();
    return std::string();
}

void tlinsWCoordinateHourAngle::setValue(const double v)
{
    ui->ra->setText(tlinsUiStrUtils::setValueHour(v));
}

double tlinsWCoordinateHourAngle::getValue() const
{
    int h;
    unsigned int m;
    double s;

    getValue(h, m, s);

    return (double)h + (double)m / 60.0 + s / 3600.00;
}

void tlinsWCoordinateHourAngle::getValue(int& h,
    unsigned int& m,
    double& s) const
{
    QString text(ui->ra->text());
    QString s1;
    QString s2;
    QString s3;

    tlinsUiStrUtils::get3Strings(text, s1, s2, s3);

    h = s1.toInt();
    m = s2.toUInt();
    s = s3.toDouble();
}

tlinsWCoordinateHourAngle::~tlinsWCoordinateHourAngle()
{
    delete ui;
}
