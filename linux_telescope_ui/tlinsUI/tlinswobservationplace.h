#ifndef TLINSWOBSERVATIONPLACE_H
#define TLINSWOBSERVATIONPLACE_H

#include <QItemSelection>

#include "tlinsobservationplacenodel.h"

#include <QWidget>

namespace Ui {
class tlinsWObservationPlace;
}

class tlinsWObservationPlace : public QWidget {
    Q_OBJECT

public slots:
    void on_addItem_clicked();
    void on_updateItem_clicked();
    void on_deleteItem_clicked();
    void on_newItem_clicked();
    void on_saveItems_clicked();
    void on_reloadItems_clicked();

private slots:
    void on_selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

public:
    explicit tlinsWObservationPlace(QWidget* parent = 0);
    ~tlinsWObservationPlace();

private:
    bool getSelected(std::vector<int>& rows);

    Ui::tlinsWObservationPlace* ui;
    tlinsObservationPlaceNodel dataModel;
};

#endif // TLINSWOBSERVATIONPLACE_H
