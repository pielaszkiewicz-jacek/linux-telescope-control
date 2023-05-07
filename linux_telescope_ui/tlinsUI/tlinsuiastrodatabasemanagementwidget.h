#ifndef TLINSUIASTRODATABASEMANAGEMENTWIDGET_H
#define TLINSUIASTRODATABASEMANAGEMENTWIDGET_H

#include "tlinseditdatabaseobject.h"
#include "tlinswdatabasesearchmain.h"
#include <QVBoxLayout>
#include <QWidget>

namespace Ui {
class tlinsUiAstroDatabaseManagementWidget;
}

class tlinsUiAstroDatabaseManagementWidget : public QWidget {
    Q_OBJECT

public:
    explicit tlinsUiAstroDatabaseManagementWidget(QWidget* parent = nullptr);
    ~tlinsUiAstroDatabaseManagementWidget();

private slots:
    void on_addButton_clicked();
    void on_editButton_clicked();
    void on_deleteButton_clicked();
    void on_importButton_clicked();

    void objectChanged(TlinsAstroBase::tlinsAstroCatalogItem v, int id);
    void objectCreated(TlinsAstroBase::tlinsAstroCatalogItem v);

private:
    tlinsEditDatabaseObject editObject;

    Ui::tlinsUiAstroDatabaseManagementWidget* ui;
};

#endif // TLINSUIASTRODATABASEMANAGEMENTWIDGET_H
