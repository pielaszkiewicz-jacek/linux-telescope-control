#ifndef TLINSIERSWINDOW_H
#define TLINSIERSWINDOW_H

#include <QDialog>

namespace Ui {
class tlinsIERSWindow;
}

class tlinsIERSWindow : public QDialog {
    Q_OBJECT

public:
    explicit tlinsIERSWindow(QWidget* parent = 0);
    ~tlinsIERSWindow();

private:
    Ui::tlinsIERSWindow* ui;
};

#endif // TLINSIERSWINDOW_H
