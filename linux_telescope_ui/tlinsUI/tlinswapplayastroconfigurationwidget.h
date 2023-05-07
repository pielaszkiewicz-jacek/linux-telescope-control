#ifndef TLINSWAPPLAYASTROCONFIGURATIONWIDGET_H
#define TLINSWAPPLAYASTROCONFIGURATIONWIDGET_H

#include <QDialog>
#include <atomic>
#include <condition_variable>
#include <mutex>

#include <QWidget>

namespace Ui {
class tlinsWApplayAstroConfigurationWidget;
}

class tlinsWApplayAstroConfigurationWidget : public QWidget {
    Q_OBJECT

private:
    std::atomic<int> successCount;
    std::atomic<int> failedCount;
    int totalCount;

public:
    void updateSuccessCount();
    void updateFailedCount();

    void resetCounters()
    {
        successCount = 0;
        failedCount = 0;
    }

public:
    explicit tlinsWApplayAstroConfigurationWidget(QWidget* parent = nullptr);
    ~tlinsWApplayAstroConfigurationWidget();

signals:
    void applayingStatus(std::string);

public slots:
    void applayingStatusSlot(std::string str);
    void accepted();

private:
    Ui::tlinsWApplayAstroConfigurationWidget* ui;
};

#endif // TLINSWAPPLAYASTROCONFIGURATIONWIDGET_H
