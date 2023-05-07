#ifndef TLINSWPILOTSETTINGS_H
#define TLINSWPILOTSETTINGS_H

#include "tlinswsettingsupdateinterface.h"

#include <QWidget>

namespace Ui {
class tlinsWPilotSettings;
}

class tlinsWPilotSettings : public QWidget, public tlinsWSettingsUpdateInterface {
    Q_OBJECT

public:
    void save();
    void saveDefault();
    void restore();

public:
    explicit tlinsWPilotSettings(QWidget* parent = 0);
    ~tlinsWPilotSettings();

private:
    Ui::tlinsWPilotSettings* ui;
};

#endif // TLINSWPILOTSETTINGS_H
