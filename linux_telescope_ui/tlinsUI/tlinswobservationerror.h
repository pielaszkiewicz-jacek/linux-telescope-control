#ifndef TLINSWOBSERVATIONERROR_H
#define TLINSWOBSERVATIONERROR_H

#include <QWidget>

namespace Ui {
class tlinsWObservationError;
}

class tlinsWObservationError : public QWidget {
    Q_OBJECT

public:
    void setLongitudeError(const double v);
    void setLatitudeError(const double v);
    void setWeight(const double v);

    double getLongitudeError();
    double getLatitudeError();
    double getWeight();

public:
    explicit tlinsWObservationError(QWidget* parent = 0);
    ~tlinsWObservationError();

private:
    Ui::tlinsWObservationError* ui;
};

#endif // TLINSWOBSERVATIONERROR_H
