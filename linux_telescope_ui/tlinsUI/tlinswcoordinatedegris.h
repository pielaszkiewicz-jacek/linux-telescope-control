#ifndef TLINSWCOORDINATEDEGRIS_H
#define TLINSWCOORDINATEDEGRIS_H

#include <string>

#include <QString>
#include <QValidator>
#include <QWidget>

#include "tlinsvalueabstract.h"

namespace Ui {
class tlinsWCoordinateDegris;
}

class DegrisValidator : public QValidator {
    Q_OBJECT
private:
    int min;
    int max;
    void getValue_(const QString& ss, int& d, unsigned int& m, double& s) const;

public:
    explicit DegrisValidator(int min_, int max_, QObject* parent);

    virtual QValidator::State validate(QString& input, int&) const;
    virtual void fixup(QString& input) const;
};

class tlinsWCoordinateDegris : public QWidget, public tlinsValueAbstract {
    Q_OBJECT

private:
    QValidator* validator;

signals:
    void valueChanged(std::string newValue);

public:
    void setLabel(const std::string& label);
    void setValue(const double v);

    double getValue() const;
    void getValue(int& h, unsigned int& m, double& s) const;

    void setMinMax(const int min, const int max);

public:
    explicit tlinsWCoordinateDegris(QWidget* parent = 0);
    ~tlinsWCoordinateDegris();

private:
    Ui::tlinsWCoordinateDegris* ui;
};

#endif // TLINSWCOORDINATEDEGRIS_H
