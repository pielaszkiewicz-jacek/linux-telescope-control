#ifndef TLINSWAPPLAYASTROCONFIGURATION_H
#define TLINSWAPPLAYASTROCONFIGURATION_H

#include <QWidget>
#include <map>

namespace Ui {
class tlinsWApplayAstroConfiguration;
}

class tlinsWApplayAstroConfiguration : public QWidget {
    Q_OBJECT

public:
    explicit tlinsWApplayAstroConfiguration(QWidget* parent = 0);
    ~tlinsWApplayAstroConfiguration();

public:
    enum class CFG_TYPE {
        ENVIRONMENT = 1,
        OBSERVATION_PLACE = 2,
        IERS = 3,
        IERS_STORE_LOCALY = 4,
        IERS_OVERWRITE = 5
    };
    std::map<CFG_TYPE, bool> getCfgToBeApplyed() const;

private:
    Ui::tlinsWApplayAstroConfiguration* ui;
};

#endif // TLINSWAPPLAYASTROCONFIGURATION_H
