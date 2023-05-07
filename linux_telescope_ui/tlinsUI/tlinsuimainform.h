#ifndef TLINSUIMAINFORM_H
#define TLINSUIMAINFORM_H

#include <QWidget>

namespace Ui {
class tlinsUiMainForm;
}

class tlinsUiMainForm : public QWidget {
    Q_OBJECT

public:
    explicit tlinsUiMainForm(QWidget* parent = 0);
    ~tlinsUiMainForm();

private:
    Ui::tlinsUiMainForm* ui;
};

#endif // TLINSUIMAINFORM_H
