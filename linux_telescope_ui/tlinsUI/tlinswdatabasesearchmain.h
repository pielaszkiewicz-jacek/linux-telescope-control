#ifndef TLINSWDATABASESEARCHMAIN_H
#define TLINSWDATABASESEARCHMAIN_H

#include "tlinsastroobjectsviewmodel.h"
#include "tlinswastrodatabasesearch3.h"
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include <QWidget>
#include <vector>

namespace Ui {
class tlinsWDatabaseSearchMain;
}

class tlinsWDatabaseSearchMain : public QWidget {
    Q_OBJECT

public:
    explicit tlinsWDatabaseSearchMain(QWidget* parent = nullptr);
    ~tlinsWDatabaseSearchMain();

private:
    QSortFilterProxyModel proxyModel;
    tlinsAstroObjectsViewModel dataModel;
    long currentOffset;
    long previousOffset;

    long totalRowsCount;

private:
    enum offsetOperation {
        OFFSET_NON,
        OFFSET_INCREASE,
        OFFSET_DECRASE
    };

    void fetchData(offsetOperation increaseOffset);

public:
    void getSelectedRows(std::vector<int>& records, TlinsAstroBase::tlinsAstroCatalogCollection& result);
    bool updateRecord(int id, TlinsAstroBase::tlinsAstroCatalogItem& v);
    void insertRecord(TlinsAstroBase::tlinsAstroCatalogItem& v);
    void removeRecords(TlinsAstroBase::tlinsAstroCatalogCollection& result);
    void activateRemoveButton();
    void hideSelectAllButton();
    void setSingleLineSelection();

private slots:
    void buttonSearchPresed();
    void next();
    void previous();
    void on_selectButton_clicked();
    void on_deselectButton_clicked();
    void on_actualOffset_valueChanged(int arg1);

    void on_removeButton_clicked();

private:
    tlinsWAstroDatabaseSearch3 searchWidget;

private:
    Ui::tlinsWDatabaseSearchMain* ui;
};

#endif // TLINSWDATABASESEARCHMAIN_H
