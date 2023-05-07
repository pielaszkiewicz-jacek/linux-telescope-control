#ifndef TLINSASTROSEARCHWINDOW_H
#define TLINSASTROSEARCHWINDOW_H

#include "tlinswdatabasesearchmain.h"
#include <QDialog>
#include <QVBoxLayout>
#include <tlinsastrocatalogcollection.h>
#include <vector>

namespace Ui {
class tlinsAstroSearchWindow;
}

class tlinsAstroSearchWindow : public QDialog {
    Q_OBJECT

public:
    explicit tlinsAstroSearchWindow(QWidget* parent, bool remove_bt = true);
    ~tlinsAstroSearchWindow();

public:
    void getSelectedRows(std::vector<int>& records, TlinsAstroBase::tlinsAstroCatalogCollection& result);
    void singleRowSelectionMode();
    void hideSelectAllButton();

private slots:
    void on_buttonBox_accepted();

signals:
    void selectionAccepted();

private:
    tlinsWDatabaseSearchMain searchWidget;
    QVBoxLayout lsearchWidget;

    Ui::tlinsAstroSearchWindow* ui;
};

#endif // TLINSASTROSEARCHWINDOW_H
