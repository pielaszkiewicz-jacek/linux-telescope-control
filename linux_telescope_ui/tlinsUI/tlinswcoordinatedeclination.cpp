#include "tlinswcoordinatedeclination.h"
#include "QDebug"
#include "tlinsuistrutils.h"
#include "tlinsuistylesmanager.h"
#include "ui_tlinswcoordinatedeclination.h"
#include <math.h>

void DeclinationValidator::getValue_(const QString& ss, int& d, unsigned int& m, double& s) const
{
    QString s1;
    QString s2;
    QString s3;

    tlinsUiStrUtils::get3Strings(ss, s1, s2, s3);

    d = s1.toInt();
    m = s2.toUInt();
    s = s3.toDouble();
}

DeclinationValidator::DeclinationValidator(QObject* parent)
    : QValidator(parent)
{
}

QValidator::State DeclinationValidator::validate(QString& input, int&) const
{
    qDebug() << "void tlinsWCoordinateDeclination:: update() >> ";

    QString s1;
    QString s2;
    QString s3;
    tlinsUiStrUtils::get3Strings(input, s1, s2, s3);

    int d;
    unsigned int m;
    double s;
    getValue_(input, d, m, s);

    if (d > 90) {
        return State::Invalid;
    }
    if (d < -90) {
        return State::Invalid;
    }

    if (m > 59) {
        return State::Invalid;
    }

    if (s > 59.00) {
        return State::Invalid;
    }

    if (abs(d) == 90 && (m != 0 || s != 0.0)) {
        return State::Invalid;
    }
    return State::Acceptable;
}

void DeclinationValidator::fixup(QString& input) const
{
    QString s1;
    QString s2;
    QString s3;
    tlinsUiStrUtils::get3Strings(input, s1, s2, s3);

    bool update = false;
    int d;
    unsigned int m;
    double s;
    getValue_(input, d, m, s);

    if (d > 90) {
        s1 = "90";
        update = true;
    }
    if (d < -90) {
        s1 = "-90";
        update = true;
    }

    if (m > 59) {
        s2 = "59";
        update = true;
    }

    if (s > 60.00) {
        s3 = "59.9999";
        update = true;
    }

    if (abs(d) == 90 && (m != 0 || s != 0.0)) {
        s2 = "00";
        s3 = "00.0000";
        update = true;
    }

    if (update) {
        input = s1 + QString(":") + s2 + QString(":") + s3;
    }
}

//
// ---
// ---
//
tlinsWCoordinateDeclination::tlinsWCoordinateDeclination(QWidget* parent)
    : QWidget(parent)
    , validator(this)
    , ui(new Ui::tlinsWCoordinateDeclination)
{
    ui->setupUi(this);

    // Control styles
    //    std:: string style;
    //    bool res = tlinsUiStylesManager:: getStyle( tlinsUiStylesManager:: DECLINATION,
    //                                                 tlinsUiStylesManager:: FieldType:: GROUP_BOX,
    //                                                 style );
    //    if( res )
    //        ui -> groupBox -> setStyleSheet( QString( style.c_str() ) );

    //    res = tlinsUiStylesManager:: getStyle( tlinsUiStylesManager:: DECLINATION,
    //                                            tlinsUiStylesManager:: FieldType:: EDIT,
    //                                            style );
    //    if( res )
    //        ui -> dc -> setStyleSheet( QString( style.c_str() ) );
    ui->label->setVisible(false);
    ui->dc->setValidator(&validator);
}

void tlinsWCoordinateDeclination::setValue(const double v)
{
    ui->dc->setText(tlinsUiStrUtils::setValueDegris(v));
}

double tlinsWCoordinateDeclination::getValue() const
{
    int h;
    unsigned int m;
    double s;
    bool sign;

    getValue(h, m, s, sign);

    double ret = fabs((double)h) + (double)m / 60.0 + s / 3600.00;
    if (h < 0 || sign)
        return -1.0 * ret;

    return ret;
}

void tlinsWCoordinateDeclination::getValue(int& d, unsigned int& m, double& s, bool& sign) const
{
    QString text(ui->dc->text());
    QString s1;
    QString s2;
    QString s3;

    tlinsUiStrUtils::get3Strings(text, s1, s2, s3);

    QString s1Trimmed = s1.trimmed();

    sign = false;
    if (s1Trimmed.size() != 0) {
        auto c = s1Trimmed[0];
        if (c.cell() == '-')
            sign = true;
    }

    d = s1.toInt();
    m = s2.toUInt();
    s = s3.toDouble();
}

tlinsWCoordinateDeclination::~tlinsWCoordinateDeclination()
{
    delete ui;
}
