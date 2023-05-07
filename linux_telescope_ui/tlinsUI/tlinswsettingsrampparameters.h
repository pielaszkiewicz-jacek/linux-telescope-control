#ifndef TLINSWSETTINGSRAMPPARAMETERS_H
#define TLINSWSETTINGSRAMPPARAMETERS_H

#include <QWidget>

#include "tlinswsettingsupdateinterface.h"

namespace Ui {
class tlinsWSettingsRampParameters;
}

class tlinsWSettingsRampParameters : public QWidget,
                                     public tlinsWSettingsUpdateInterface {
    Q_OBJECT

public:
    virtual void save();
    virtual void saveDefault();
    virtual void restore();

public:
    explicit tlinsWSettingsRampParameters(QWidget* parent = 0);
    ~tlinsWSettingsRampParameters();

private:
    Ui::tlinsWSettingsRampParameters* ui;
};

#endif // TLINSWSETTINGSRAMPPARAMETERS_H
