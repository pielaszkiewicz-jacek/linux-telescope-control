#ifndef TLINSWCALIBRATIONSETTINGS_H
#define TLINSWCALIBRATIONSETTINGS_H

#include "tlinswsettingsupdateinterface.h"

#include <QWidget>

namespace Ui {
class tlinsWCalibrationSettings;
}

class tlinsWCalibrationSettings : public QWidget, public tlinsWSettingsUpdateInterface {
    Q_OBJECT

public:
    virtual void save();
    virtual void saveDefault();
    virtual void restore();

public:
    explicit tlinsWCalibrationSettings(QWidget* parent = 0);
    ~tlinsWCalibrationSettings();

private:
    Ui::tlinsWCalibrationSettings* ui;
};

#endif // TLINSWCALIBRATIONSETTINGS_H
