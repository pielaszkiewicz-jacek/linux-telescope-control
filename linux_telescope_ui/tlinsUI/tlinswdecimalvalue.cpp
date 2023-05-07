#include "tlinswdecimalvalue.h"
#include "tlinsuistylesmanager.h"
#include "ui_tlinswdecimalvalue.h"
#include <QAbstractSpinBox>
#include <math.h>

tlinsWDecimalValue::tlinsWDecimalValue(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWDecimalValue)
{
    ui->setupUi(this);
    ui->valueName->setVisible(false);
    minMaxLimitActive = false;
}

void tlinsWDecimalValue::setMinMaxValue(const double min, const double max)
{
    minMaxLimitActive = true;
    minValue = min;
    maxValue = max;
}

void tlinsWDecimalValue::setCenter()
{
    ui->value->setAlignment(Qt::Alignment { Qt::AlignmentFlag::AlignHCenter });
}

void tlinsWDecimalValue::disableButtons()
{
    ui->value->setButtonSymbols(QAbstractSpinBox::NoButtons);
}

void tlinsWDecimalValue::setDecimal(const int v)
{
    ui->value->setDecimals(v);
}

void tlinsWDecimalValue::setCallback(std::function<void(double)> fun)
{
    callback = fun;
}

void tlinsWDecimalValue::valueChanged(double)
{
    if (callback) {
        callback(getValue());
    }

    if (minMaxLimitActive) {
        double val = getValue();

        if (val < minValue)
            setValue(minValue);

        if (val > maxValue)
            setValue(maxValue);
    }
}

void tlinsWDecimalValue::setMinMax(const double min, const double max)
{
    ui->value->setMinimum(min);
    ui->value->setMaximum(max);
}

void tlinsWDecimalValue::setValue(const double v)
{
    ui->value->setValue(v);
    //    callback(v);
}

double tlinsWDecimalValue::getValue() const
{
    return ui->value->value();
}

void tlinsWDecimalValue::setLabel(const std::string& label)
{
    ui->valueName->setText(QString(label.c_str()));
    ui->valueName->setVisible(true);
}

tlinsWDecimalValue::~tlinsWDecimalValue()
{
    delete ui;
}
