#ifndef TLINSOBSERVATIONSPLACESWINDOW_H
#define TLINSOBSERVATIONSPLACESWINDOW_H

#include <QDialog>

namespace Ui {
class tlinsObservationsPlacesWindow;
}

class tlinsObservationsPlacesWindow : public QDialog {
    Q_OBJECT

public:
    explicit tlinsObservationsPlacesWindow(QWidget* parent = 0);
    ~tlinsObservationsPlacesWindow();

private:
    Ui::tlinsObservationsPlacesWindow* ui;
};

#endif // TLINSOBSERVATIONSPLACESWINDOW_H
