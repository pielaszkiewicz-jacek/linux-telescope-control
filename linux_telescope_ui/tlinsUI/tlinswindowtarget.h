#ifndef TLINSWINDOWTARGET_H
#define TLINSWINDOWTARGET_H

#include <QDialog>

namespace Ui {
class tlinsWindowTarget;
}

class tlinsWindowTarget : public QDialog {
    Q_OBJECT

public:
    explicit tlinsWindowTarget(QWidget* parent = 0);
    ~tlinsWindowTarget();

private:
    Ui::tlinsWindowTarget* ui;
};

#endif // TLINSWINDOWTARGET_H
