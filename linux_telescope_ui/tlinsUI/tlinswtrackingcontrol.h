#ifndef TLINSWTRACKINGCONTROL_H
#define TLINSWTRACKINGCONTROL_H

#include <QWidget>

namespace Ui {
class tlinsWTrackingControl;
}

class tlinsWTrackingControl : public QWidget {
    Q_OBJECT

public slots:
    void start();
    void stop();

public:
    explicit tlinsWTrackingControl(QWidget* parent = nullptr);
    ~tlinsWTrackingControl();

private:
    Ui::tlinsWTrackingControl* ui;
};

#endif // TLINSWTRACKINGCONTROL_H
