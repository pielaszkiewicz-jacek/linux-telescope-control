#ifndef TLINSWDECIMALVALUE_H
#define TLINSWDECIMALVALUE_H

#include "tlinsvalueabstract.h"
#include <QWidget>
#include <functional>

namespace Ui {
class tlinsWDecimalValue;
}

class tlinsWDecimalValue : public QWidget, public tlinsValueAbstract {
    Q_OBJECT

private:
    std::function<void(double)> callback;

    double maxValue;
    double minValue;

    bool minMaxLimitActive;

public:
    void setLabel(const std::string& label);
    void setValue(const double v);
    void setDecimal(const int v);
    double getValue() const;
    void setMinMax(const double min, const double max);
    void disableButtons();
    void setCenter();

    void setCallback(std::function<void(double)> fun);

    void setMinMaxValue(const double min, const double max);

public slots:
    void valueChanged(double v);

public:
    explicit tlinsWDecimalValue(QWidget* parent = 0);
    ~tlinsWDecimalValue();

private:
    Ui::tlinsWDecimalValue* ui;
};

#endif // TLINSWDECIMALVALUE_H
