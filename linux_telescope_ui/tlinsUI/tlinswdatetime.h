#ifndef TLINSWDATETIME_H
#define TLINSWDATETIME_H

#include <QWidget>
#include <atomic>
#include <thread>

namespace Ui {
class tlinsWDateTime;
}

class tlinsWDateTime : public QWidget {
    Q_OBJECT

public:
    void get(int& year, int& month, int& day, int& hour, int& minute, int& second);

    explicit tlinsWDateTime(QWidget* parent = nullptr);
    ~tlinsWDateTime();

private slots:
    void stateChangedSlot(int state);
    void updateTimerSlot(const int& year, const int& month, const int& day, const int& hour, const int& minute, const int& second);

signals:
    void updateTimer(const int& year, const int& month, const int& day, const int& hour, const int& minute, const int& second);

private:
    std::thread th;
    std::atomic<bool> end;
    Ui::tlinsWDateTime* ui;
};

#endif // TLINSWDATETIME_H
