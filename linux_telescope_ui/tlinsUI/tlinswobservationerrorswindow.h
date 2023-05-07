#ifndef TLINSWOBSERVATIONERRORSWINDOW_H
#define TLINSWOBSERVATIONERRORSWINDOW_H

#include "tlinswobservationerror.h"
#include <QDialog>

namespace Ui {
class tlinsWObservationErrorsWindow;
}

class tlinsWObservationErrorsWindow : public QDialog {
    Q_OBJECT

public:
    const tlinsWObservationError& getWErrors();

public:
    explicit tlinsWObservationErrorsWindow(QWidget* parent = 0);
    ~tlinsWObservationErrorsWindow();

private:
    Ui::tlinsWObservationErrorsWindow* ui;
};

#endif // TLINSWOBSERVATIONERRORSWINDOW_H
