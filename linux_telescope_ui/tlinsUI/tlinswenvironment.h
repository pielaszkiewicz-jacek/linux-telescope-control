#ifndef TLINSWENVIRONMENT_H
#define TLINSWENVIRONMENT_H

#include <QWidget>

namespace Ui {
class tlinsWEnvironment;
}

class tlinsWEnvironment : public QWidget {
    Q_OBJECT

public:
    double getAmbientPressure() const;
    double getEffectiveColor() const;
    double getRealHumidity() const;
    double getTemperature() const;

public:
    explicit tlinsWEnvironment(QWidget* parent = 0);
    ~tlinsWEnvironment();

private:
    Ui::tlinsWEnvironment* ui;
};

#endif // TLINSWENVIRONMENT_H
