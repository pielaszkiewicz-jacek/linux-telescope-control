#ifndef TLINSPILOTSHORTCUTSDEFINITIONSWINDOW_H
#define TLINSPILOTSHORTCUTSDEFINITIONSWINDOW_H

#include <QDialog>

namespace Ui {
class tlinsPilotShortcutsDefinitionsWindow;
}

class tlinsPilotShortcutsDefinitionsWindow : public QDialog {
    Q_OBJECT

public:
    explicit tlinsPilotShortcutsDefinitionsWindow(QWidget* parent = 0);
    ~tlinsPilotShortcutsDefinitionsWindow();

private:
    Ui::tlinsPilotShortcutsDefinitionsWindow* ui;
};

#endif // TLINSPILOTSHORTCUTSDEFINITIONSWINDOW_H
