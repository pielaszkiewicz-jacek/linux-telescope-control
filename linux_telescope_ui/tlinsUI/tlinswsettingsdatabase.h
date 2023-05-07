#ifndef TLINSWSETTINGSDATABASE_H
#define TLINSWSETTINGSDATABASE_H

#include <QFileDialog>
#include <QWidget>

#include "tlinswsettingsupdateinterface.h"

namespace Ui {
class tlinsWSettingsDatabase;
}

class tlinsWSettingsDatabase : public QWidget,
                               public tlinsWSettingsUpdateInterface {
    Q_OBJECT

public:
    explicit tlinsWSettingsDatabase(QWidget* parent = 0);
    ~tlinsWSettingsDatabase();

private:
    Ui::tlinsWSettingsDatabase* ui;

public slots:
    void selectFile(bool);

public:
    void save();
    void saveDefault();
    void restore();
};

#endif // TLINSWSETTINGSDATABASE_H
