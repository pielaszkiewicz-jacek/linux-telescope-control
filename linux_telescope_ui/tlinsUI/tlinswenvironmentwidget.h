#ifndef TLINSWENVIRONMENTWIDGET_H
#define TLINSWENVIRONMENTWIDGET_H

#include <QWidget>

namespace Ui {
class tlinsWEnvironmentWidget;
}

class tlinsWEnvironmentWidget : public QWidget {
    Q_OBJECT

public:
    explicit tlinsWEnvironmentWidget(QWidget* parent = nullptr);
    ~tlinsWEnvironmentWidget();

private slots:
    void accepted();

private:
    Ui::tlinsWEnvironmentWidget* ui;
};

#endif // TLINSWENVIRONMENTWIDGET_H
