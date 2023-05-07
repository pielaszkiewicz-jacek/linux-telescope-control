#ifndef TLINSWCOORDINATEDECLINATION_H
#define TLINSWCOORDINATEDECLINATION_H

#include <QValidator>
#include <QWidget>

#include "tlinsvalueabstract.h"

namespace Ui {
class tlinsWCoordinateDeclination;
}

class DeclinationValidator : public QValidator {
    Q_OBJECT
private:
    void getValue_(const QString& ss, int& d, unsigned int& m, double& s) const;

public:
    explicit DeclinationValidator(QObject* parent);

    virtual QValidator::State validate(QString& input, int&) const;
    virtual void fixup(QString& input) const;
};

class tlinsWCoordinateDeclination : public QWidget, public tlinsValueAbstract {
    Q_OBJECT

signals:
    void valueChanged(std::string newValue);

public:
    void setValue(const double v);
    double getValue() const;
    void getValue(int& d, unsigned int& m, double& s, bool& sign) const;

public:
    explicit tlinsWCoordinateDeclination(QWidget* parent = 0);
    ~tlinsWCoordinateDeclination();

private:
    DeclinationValidator validator;
    Ui::tlinsWCoordinateDeclination* ui;
};

#endif // TLINSWCOORDINATEDECLINATION_H
