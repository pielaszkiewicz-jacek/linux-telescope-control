#ifndef TLINSWOBSERVATIONERRORSETTINGS_H
#define TLINSWOBSERVATIONERRORSETTINGS_H

#include "tlinswsettingsupdateinterface.h"

#include <QWidget>

namespace Ui {
class tlinsWObservationErrorSettings;
}

class tlinsWObservationErrorSettings : public QWidget, public tlinsWSettingsUpdateInterface {
    Q_OBJECT

public:
    virtual void save();
    virtual void saveDefault();
    virtual void restore();

public:
    explicit tlinsWObservationErrorSettings(QWidget* parent = 0);
    ~tlinsWObservationErrorSettings();

private:
    Ui::tlinsWObservationErrorSettings* ui;
};

#endif // TLINSWOBSERVATIONERRORSETTINGS_H
