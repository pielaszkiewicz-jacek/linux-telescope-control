#ifndef TLINSWHARDWERCONFIGURATION_H
#define TLINSWHARDWERCONFIGURATION_H

#include <QWidget>

namespace Ui {
class tlinsWHardwerConfiguration;
}

class tlinsWHardwerConfiguration : public QWidget {
    Q_OBJECT

public:
    explicit tlinsWHardwerConfiguration(QWidget* parent = 0);
    ~tlinsWHardwerConfiguration();

private:
    Ui::tlinsWHardwerConfiguration* ui;
};

#endif // TLINSWHARDWERCONFIGURATION_H
