#ifndef TLINSDATETIMEWINDOW_H
#define TLINSDATETIMEWINDOW_H

#include <QDialog>

namespace Ui {
class tlinsDateTimeWindow;
}

class tlinsDateTimeWindow : public QDialog {
    Q_OBJECT

private slots:
    void acceptedSlot();

public slots:
    void setStatusSlot(std::string str);

signals:
    void setStatus(std::string);

public:
    explicit tlinsDateTimeWindow(QWidget* parent = nullptr);
    ~tlinsDateTimeWindow();

private:
    Ui::tlinsDateTimeWindow* ui;
};

#endif // TLINSDATETIMEWINDOW_H
