#ifndef TLINSUIASTRODATABASEMANAGEMENT_H
#define TLINSUIASTRODATABASEMANAGEMENT_H

#include "tlinseditdatabaseobject.h"
#include "tlinswdatabasesearchmain.h"
#include <QDialog>
#include <QVBoxLayout>

namespace Ui {
class tlinsUiAstroDatabaseManagement;
}

class tlinsUiAstroDatabaseManagement : public QDialog {
    Q_OBJECT

public:
    explicit tlinsUiAstroDatabaseManagement(QWidget* parent = nullptr);
    ~tlinsUiAstroDatabaseManagement();

private:
    Ui::tlinsUiAstroDatabaseManagement* ui;
};

#endif // TLINSUIASTRODATABASEMANAGEMENT_H
