#ifndef TLINSSETTINGSWIDGET_H
#define TLINSSETTINGSWIDGET_H

#include "tlinswsettingsupdateinterface.h"
#include <QAbstractButton>
#include <QDialog>
#include <QPushButton>
#include <QWidget>
#include <map>
#include <string>

namespace Ui {
class tlinsSettingsWidget;
}

class tlinsSettingsWidget : public QWidget {
    Q_OBJECT

public slots:
    void saveSlot();
    void saveAllSlot();
    void defaultsSlot();
    void discardSlot();

private:
    std::map<std::string, tlinsWSettingsUpdateInterface*> objMap;

private:
    QPushButton* saveAll;
    QPushButton* save;
    QPushButton* defaults;
    QPushButton* reject;

public:
    explicit tlinsSettingsWidget(QWidget* parent = nullptr);
    ~tlinsSettingsWidget();

private:
    Ui::tlinsSettingsWidget* ui;
};

#endif // TLINSSETTINGSWIDGET_H
