#include "tlinsuistrutils.h"
#include <QChar>
#include <QDebug>
#include <QRegExp>
#include <QStringList>
#include <cmath>

bool tlinsUiStrUtils::get3Strings(const QString& in, QString& s1, QString& s2, QString& s3)
{
    QString text(in);

    // Remove spaces
    text.remove(QChar(' '));
    QStringList list = text.split(QRegExp(":"));

    if (list.size() != 3)
        return false;
    s1 = list.at(0);
    s2 = list.at(1);
    s3 = list.at(2);
    return true;
}

QString tlinsUiStrUtils::setValueDegris(const double v)
{
    double inputAbs = fabs(v);

    double degrisf = floor(inputAbs);
    int degris = (int)degrisf;

    QString degrisStr;
    if (degris < 10)
        degrisStr = QString("0") + QString::number(degris);
    else
        degrisStr = QString::number(degris);

    double minutes = (inputAbs - degrisf) * 60.0;
    double minutesf = floor(minutes);

    QString minutesStr;
    if (minutesf < 10.0)
        minutesStr = QString("0") + QString::number((unsigned int)minutesf);
    else
        minutesStr = QString::number((unsigned int)minutesf);

    double sec = (minutes - minutesf) * 60.0;
    QString secendsStr;
    if (sec < 10.0)
        secendsStr = QString("0") + QString::number(sec, 'f', 4) + QString("0000");
    else
        secendsStr = QString::number(sec, 'f', 4) + QString("0000");

    return (v < 0.0 ? QString("-") : QString("")) + degrisStr + QString(":") + minutesStr + QString(":") + QString(secendsStr.toStdString().substr(0, 7).c_str());
}

QString tlinsUiStrUtils::setValueHour(const double v)
{
    double hourf = floor(v);
    int hour = (int)hourf;

    QString hourStr;
    if (hour < 10)
        hourStr = QString("0") + QString::number(hour);
    else
        hourStr = QString::number(hour);

    double minutes = (v - hourf) * 60.0;
    double minutesf = floor(minutes);

    QString minutesStr;
    if (minutesf < 10.0)
        minutesStr = QString("0") + QString::number((unsigned int)minutesf);
    else
        minutesStr = QString::number((unsigned int)minutesf);

    double sec = (minutes - minutesf) * 60.0;

    QString secendsStr;
    if (sec < 10.0)
        secendsStr = QString("0") + QString::number(sec, 'f', 4) + QString("0000");
    else
        secendsStr = QString::number(sec, 'f', 4) + QString("0000");

    return hourStr + QString(":") + minutesStr + QString(":") + QString(secendsStr.toStdString().substr(0, 7).c_str());
}

tlinsUiStrUtils::tlinsUiStrUtils()
{
}
