#ifndef TLINSWRAMPSETTINGS_H
#define TLINSWRAMPSETTINGS_H

#include <QWidget>

namespace Ui {
class tlinsWRampSettings;
}

class tlinsWRampSettings : public QWidget {
    Q_OBJECT

public:
    explicit tlinsWRampSettings(QWidget* parent = 0);
    ~tlinsWRampSettings();

private:
    Ui::tlinsWRampSettings* ui;
};

#endif // TLINSWRAMPSETTINGS_H
