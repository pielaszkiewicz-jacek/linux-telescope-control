#ifndef TLINSINFOWIDGET_H
#define TLINSINFOWIDGET_H

#include <QWidget>

#include <thread>
#include <tlinscommunicationthread.h>
#include <tlinsconfiguration.h>

namespace Ui {
class tlinsInfoWidget;
}

class tlinsInfoWidget : public QWidget {
    Q_OBJECT

private:
    void restore();

private:
    void load();
    void update();
    bool cmdCall(const std::string& _cmd_, const std::string& operation);
    bool cmdCallStr(const std::string& _cmd_, std::string& result);

    std::atomic<bool> downloadInProgress;

public slots:
    void updateCb();
    void reloadCb();
    void storeCb();
    void loadCb();

    void downloadCfg();
    void downloadCfgAstro();
    void downloadCfgAstroService();

    void uploadCfg();
    void uploadCfgAstro();
    void uploadCfgAstroService();

    void downloadLogsCb();
    void removeLogsCb();
    void selectOutputDirForLogsCb();

    void sofUpdatePerfomeCb();
    void sofUpdateSelectFileCb();

    void clearLog();

public:
    Ui::tlinsInfoWidget* getUi()
    {
        return ui;
    };

    void setText(const QString& v);
    void setInstallText(const QString& v);

    explicit tlinsInfoWidget(QWidget* parent = nullptr);
    ~tlinsInfoWidget();

private:
    Ui::tlinsInfoWidget* ui;
};

#endif // TLINSINFOWIDGET_H
