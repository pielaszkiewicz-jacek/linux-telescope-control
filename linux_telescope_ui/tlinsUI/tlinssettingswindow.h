#ifndef TLINSSETTINGSWINDOW_H
#define TLINSSETTINGSWINDOW_H

#include "tlinswsettingsupdateinterface.h"
#include <QAbstractButton>
#include <QDialog>
#include <QPushButton>
#include <map>
#include <string>

namespace Ui {
class tlinsSettingsWindow;
}

class tlinsSettingsWindow : public QDialog {
    Q_OBJECT

public:
    explicit tlinsSettingsWindow(QWidget* parent = 0);
    ~tlinsSettingsWindow();

    Ui::tlinsSettingsWindow* ui;
};

#endif // TLINSSETTINGSWINDOW_H
