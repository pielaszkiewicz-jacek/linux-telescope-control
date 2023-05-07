#ifndef TLINSUISTRUTILS_H
#define TLINSUISTRUTILS_H

#include <QString>

class tlinsUiStrUtils {
public:
    static bool get3Strings(const QString& in, QString& s1, QString& s2, QString& s3);
    static QString setValueDegris(const double v);
    static QString setValueHour(const double v);
    tlinsUiStrUtils();
};

#endif // TLINSUISTRUTILS_H
