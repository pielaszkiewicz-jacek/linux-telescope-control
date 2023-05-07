#include "tlinswdatetime.h"
#include "ui_tlinswdatetime.h"
#include <chrono>
#include <time.h>

tlinsWDateTime::tlinsWDateTime(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWDateTime)
{
    ui->setupUi(this);

    // Miejsca zerowe
    ui->year->setDecimal(0);
    ui->month->setDecimal(0);
    ui->day->setDecimal(0);
    ui->hour->setDecimal(0);
    ui->minute->setDecimal(0);
    ui->second->setDecimal(0);

    // Usuniecie przycikow
    ui->year->disableButtons();
    ui->month->disableButtons();
    ui->day->disableButtons();
    ui->hour->disableButtons();
    ui->minute->disableButtons();
    ui->second->disableButtons();

    // Wysrodkowanie tekstu w kontrolkach
    ui->year->setCenter();
    ui->month->setCenter();
    ui->day->setCenter();
    ui->hour->setCenter();
    ui->minute->setCenter();
    ui->second->setCenter();

    ui->useLocalTime->setChecked(false);
    ui->year->setEnabled(true);
    ui->month->setEnabled(true);
    ui->day->setEnabled(true);
    ui->hour->setEnabled(true);
    ui->minute->setEnabled(true);
    ui->second->setEnabled(true);

    // Inicalny czas
    auto tt =::time(reinterpret_cast<time_t*>(NULL));
    struct tm* tmTime =::localtime(&tt);
    ui->year->setValue(tmTime->tm_year + 1900);
    ui->month->setValue(tmTime->tm_mon + 1);
    ui->day->setValue(tmTime->tm_mday);
    ui->hour->setValue(tmTime->tm_hour);
    ui->minute->setValue(tmTime->tm_min);
    ui->second->setValue(tmTime->tm_sec);

    connect(ui->useLocalTime, SIGNAL(stateChanged(int)),
        this, SLOT(stateChangedSlot(int)));

    connect(this, SIGNAL(updateTimer(const int&, const int&, const int&, const int&, const int&, const int&)),
        this, SLOT(updateTimerSlot(const int&, const int&, const int&, const int&, const int&, const int&)));

    end = false;
    auto fun = [this]() {
        while (!end) {
            if (this->ui->useLocalTime->isChecked()) {
                auto tt =::time(reinterpret_cast<time_t*>(NULL));
                struct tm* tmTime =::localtime(&tt);

                emit this->updateTimer(tmTime->tm_year + 1900,
                    tmTime->tm_mon + 1,
                    tmTime->tm_mday,
                    tmTime->tm_hour,
                    tmTime->tm_min,
                    tmTime->tm_sec);
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    };

    th = std::move(std::thread { fun });
}

void tlinsWDateTime::updateTimerSlot(const int& year,
    const int& month,
    const int& day,
    const int& hour,
    const int& minute,
    const int& second)
{
    ui->year->setValue(year);
    ui->month->setValue(month);
    ui->day->setValue(day);
    ui->hour->setValue(hour);
    ui->minute->setValue(minute);
    ui->second->setValue(second);
}

void tlinsWDateTime::get(int& year, int& month, int& day, int& hour, int& minute, int& second)
{
    if (ui->useLocalTime->isChecked()) {
        auto tt =::time(reinterpret_cast<time_t*>(NULL));
        struct tm* tmTime =::localtime(&tt);

        year = tmTime->tm_year + 1900;
        month = tmTime->tm_mon + 1;
        day = tmTime->tm_mday;
        hour = tmTime->tm_hour;
        minute = tmTime->tm_min;
        second = tmTime->tm_sec;
    } else {
        year = static_cast<int>(ui->year->getValue());
        month = static_cast<int>(ui->month->getValue());
        day = static_cast<int>(ui->day->getValue());
        hour = static_cast<int>(ui->hour->getValue());
        minute = static_cast<int>(ui->minute->getValue());
        second = static_cast<int>(ui->second->getValue());
    }
}

void tlinsWDateTime::stateChangedSlot(int state)
{
    if (state == Qt::CheckState::Checked) {
        ui->year->setDisabled(true);
        ui->month->setDisabled(true);
        ui->day->setDisabled(true);
        ui->hour->setDisabled(true);
        ui->minute->setDisabled(true);
        ui->second->setDisabled(true);
    } else {
        ui->year->setEnabled(true);
        ui->month->setEnabled(true);
        ui->day->setEnabled(true);
        ui->hour->setEnabled(true);
        ui->minute->setEnabled(true);
        ui->second->setEnabled(true);
    }
}

tlinsWDateTime::~tlinsWDateTime()
{
    end = true;
    if (th.joinable())
        th.join();

    delete ui;
}
