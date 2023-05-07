#ifndef TLINSWTARGET_H
#define TLINSWTARGET_H

#include "tlinsastrosearchwindow.h"
#include "tlinstarget.h"
#include <QWidget>

namespace Ui {
class tlinsWTarget;
}

class tlinsWTarget : public QWidget {
    Q_OBJECT

private:
    void setControls();
    void setObject();

signals:
    void notiStatus(std::string);

public slots:
    void notiStatusSlot(std::string str);

    void on_btClear_clicked();
    void on_btSetTarget_clicked();
    void on_btFind_clicked();
    void dataSelected();

public:
    explicit tlinsWTarget(QWidget* parent = nullptr);
    ~tlinsWTarget();

private:
    tlinsAstroSearchWindow searchWindow;
    Ui::tlinsWTarget* ui;

    tlinsTarget target;
    bool isSet;
};

#endif // TLINSWTARGET_H
