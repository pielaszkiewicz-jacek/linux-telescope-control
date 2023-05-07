#ifndef TLINSWTIMEDATEIERSSETTINGS_H
#define TLINSWTIMEDATEIERSSETTINGS_H

#include "tlinsiersmodel.h"
#include <QFileDialog>
#include <QItemSelection>
#include <QWidget>

namespace Ui {
class tlinsWTimeDateIERSSettings;
}

class tlinsWTimeDateIERSSettings : public QWidget {
    Q_OBJECT

public:
    explicit tlinsWTimeDateIERSSettings(QWidget* parent = 0);
    ~tlinsWTimeDateIERSSettings();

public slots:
    void on_newItem_clicked();
    void on_addItem_clicked();
    void on_removeItem_clicked();
    void on_updateItem_clicked();
    void on_storeItems_clicked();
    void on_reload_clicked();

    void on_pushButtonSelectFile_clicked();
    void on_loadFile_clicked();

private slots:

    void on_selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

private:
    bool loadFromFile(const QString& file);

    bool getSelected(std::vector<int>& rows);
    void loadData();

    tlinsIERSModel dataModel;
    Ui::tlinsWTimeDateIERSSettings* ui;
};

#endif // TLINSWTIMEDATEIERSSETTINGS_H
