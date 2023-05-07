#ifndef TLINSWCOORDINATEHOURANGLE_H
#define TLINSWCOORDINATEHOURANGLE_H

#include <QValidator>
#include <QWidget>
#include <string>

#include "tlinsvalueabstract.h"

namespace Ui {
class tlinsWCoordinateHourAngle;
}

class HourAngleValidator : public QValidator {
    Q_OBJECT
private:
    void getValue_(const QString& ss, int& d, unsigned int& m, double& s) const;

public:
    explicit HourAngleValidator(QObject* parent);

    virtual QValidator::State validate(QString& input, int&) const;
    virtual void fixup(QString& input) const;
};

class tlinsWCoordinateHourAngle : public QWidget, public tlinsValueAbstract {
    Q_OBJECT

signals:
    void valueChanged(std::string newValue);

public:
    double getValue() const;
    std::string toString() const;
    void getValue(int& h, unsigned int& m, double& s) const;
    void setValue(const double v);

public:
    explicit tlinsWCoordinateHourAngle(QWidget* parent = nullptr);
    ~tlinsWCoordinateHourAngle();

private:
    HourAngleValidator validator;
    Ui::tlinsWCoordinateHourAngle* ui;
};

#endif // TLINSWCOORDINATEHOURANGLE_H
