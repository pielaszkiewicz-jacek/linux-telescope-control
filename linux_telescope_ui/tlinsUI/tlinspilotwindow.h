#ifndef TLINSPILOTWINDOW_H
#define TLINSPILOTWINDOW_H

#include "tlinsuipolit4.h"

#include <QDialog>

namespace Ui {
class tlinsPilotWindow;
}

class tlinsPilotWindow : public QDialog {
    Q_OBJECT

public:
    explicit tlinsPilotWindow(QWidget* parent = 0);
    ~tlinsPilotWindow();

protected:
    void resizeEvent(QResizeEvent* event) override;
    void moveEvent(QMoveEvent* event) override;
    void fullWindow(int state);

public slots:

private:
    Ui::tlinsPilotWindow* ui;
    int xPos;
    int yPos;
    int xSize;
    int ySize;
};

#endif // TLINSPILOTWINDOW_H
