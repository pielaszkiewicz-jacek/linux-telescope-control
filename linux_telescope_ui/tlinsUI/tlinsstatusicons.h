#ifndef TLINSSTATUSICONS_H
#define TLINSSTATUSICONS_H

#include <QWidget>

namespace Ui {
class tlinsStatusIcons;
}

class tlinsStatusIcons : public QWidget {
    Q_OBJECT

public:
    enum class CalibrationStatus {
        UNDEFINED = 0,
        UNDER_CALIBRATION = 1,
        REGULAR = 2
    };

public:
    void setConnectionStatus(bool stat);
    void setCalibrationState(const CalibrationStatus v);

    void setPos(const long& X, const long& Y);
    void setPos(const double& RA, const double& DEC);

    explicit tlinsStatusIcons(QWidget* parent = 0);
    ~tlinsStatusIcons();

private:
    Ui::tlinsStatusIcons* ui;
};

#endif // TLINSSTATUSICONS_H
