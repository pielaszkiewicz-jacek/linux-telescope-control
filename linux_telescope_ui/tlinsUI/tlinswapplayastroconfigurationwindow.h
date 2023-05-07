#ifndef TLINSWAPPLAYASTROCONFIGURATIONWINDOW_H
#define TLINSWAPPLAYASTROCONFIGURATIONWINDOW_H

#include <QDialog>
#include <atomic>
#include <condition_variable>
#include <mutex>

namespace Ui {
class tlinsWApplayAstroConfigurationWindow;
}

class tlinsWApplayAstroConfigurationWindow : public QDialog {
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
    explicit tlinsWApplayAstroConfigurationWindow(QWidget* parent = 0);
    ~tlinsWApplayAstroConfigurationWindow();

signals:
    void applayingStatus(std::string);

public slots:
    void applayingStatusSlot(std::string str);
    void accepted();

private:
    Ui::tlinsWApplayAstroConfigurationWindow* ui;
};

#endif // TLINSWAPPLAYASTROCONFIGURATIONWINDOW_H
