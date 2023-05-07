#ifndef TLINSWSETTINGSCONNECTION_H
#define TLINSWSETTINGSCONNECTION_H

#include "tlinswsettingsupdateinterface.h"
#include <QComboBox>
#include <QWidget>

namespace Ui {
class tlinsWSettingsConnection;
}

class tlinsWSettingsConnection : public QWidget,
                                 public tlinsWSettingsUpdateInterface {
    Q_OBJECT
public:
    void save();
    void saveDefault();
    void restore();

public slots:
    void useCommonIp(bool set);

public:
    explicit tlinsWSettingsConnection(QWidget* parent = 0);
    ~tlinsWSettingsConnection();

private:
    void addItem(QComboBox* widget, const QString& label, const int data);

    Ui::tlinsWSettingsConnection* ui;
};

#endif // TLINSWSETTINGSCONNECTION_H
