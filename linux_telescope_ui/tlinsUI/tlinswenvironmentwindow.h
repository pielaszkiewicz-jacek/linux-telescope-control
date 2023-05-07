#ifndef TLINSWENVIRONMENTWINDOW_H
#define TLINSWENVIRONMENTWINDOW_H

#include <QDialog>

namespace Ui {
class tlinsWEnvironmentWindow;
}

class tlinsWEnvironmentWindow : public QDialog {
    Q_OBJECT

public:
    explicit tlinsWEnvironmentWindow(QWidget* parent = 0);
    ~tlinsWEnvironmentWindow();

private slots:
    void accepted();

private:
    Ui::tlinsWEnvironmentWindow* ui;
};

#endif // TLINSWENVIRONMENTWINDOW_H
