#ifndef TLINSWASTROENGINECONFIGURATION_H
#define TLINSWASTROENGINECONFIGURATION_H

#include <QWidget>

namespace Ui {
class tlinsWAstroEngineConfiguration;
}

class tlinsWAstroEngineConfiguration : public QWidget {
    Q_OBJECT

public:
    explicit tlinsWAstroEngineConfiguration(QWidget* parent = 0);
    ~tlinsWAstroEngineConfiguration();

private:
    Ui::tlinsWAstroEngineConfiguration* ui;
};

#endif // TLINSWASTROENGINECONFIGURATION_H
