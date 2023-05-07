#include "tlinsinfowidget.h"
#include "ui_tlinsinfowidget.h"

#include "tlinsuimainwindow.h"
#include <QDebug>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QThread>
#include <errno.h>
#include <stdio.h>
#include <tlinspluginsstate.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <tlinsuimainwindow.h>

std::thread updateThread;
std::atomic<bool> isPendingUpdate { false };

QString getAddress(QString address_)
{
    return address_.left(address_.indexOf(':'));
}

void tlinsInfoWidget::downloadLogsCb()
{
    if (downloadInProgress.load()) {
        QMessageBox msgBox;
        msgBox.setText("Log files download in progress.");
        msgBox.exec();
        return;
    }

    if (ui->directoryEdit->text().length() == 0) {
        QMessageBox msgBox;
        msgBox.setText("No destynation directory");
        msgBox.exec();
        return;
    }

    struct stat statbuf;
    if (stat(ui->directoryEdit->text().toStdString().c_str(), &statbuf)) {
        QMessageBox msgBox;
        msgBox.setText("Destynation directory is invalid");
        msgBox.exec();
        return;
    }

    if (!S_ISDIR(statbuf.st_mode)) {
        QMessageBox msgBox;
        msgBox.setText("Path dosesn't point directory");
        msgBox.exec();
        return;
    }

    downloadInProgress.store(true);
    auto threadLambda = [this]() {
        do {
            auto removeAfterDelete = this->ui->removeAfterDownload->isChecked();
            auto destDir = this->ui->directoryEdit->text();

            // Get adres of the device
            auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();
            std::string address_ = inst.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
                TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE);

            std::string address = getAddress(QString::fromStdString(address_)).toStdString();
            {
                // Tworzenie polecenia
                std::string cmd { "/usr/bin/scp root@" };
                cmd.append(address);
                cmd.append(":/home/tlins/logs/* ");
                cmd.append(destDir.toStdString());
                cmd.append("/.");

                if (removeAfterDelete) {
                    cmd.append("; /usr/bin/ssh root@");
                    cmd.append(address);
                    cmd.append(" \"rm -f /home/tlins/logs/*\"");
                }

                // Create ssh command to transfer file
                emit getMainWindowInstance()->logEvent(QString { cmd.c_str() });

                if (this->cmdCall(cmd, "Download logs files")) {
                    emit getMainWindowInstance()->popupStatus("Download logs files - error");
                }
            }
            break;
        } while (0);
        emit getMainWindowInstance()->logEvent("Logs file download done");
        emit getMainWindowInstance()->popupStatus("Logs file download done");
    };

    updateThread = std::thread { threadLambda };
    updateThread.detach();
    downloadInProgress.store(false);
}

void tlinsInfoWidget::removeLogsCb()
{
    auto threadLambda = [this]() {
        do {
            // Get adres of the device
            auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();
            std::string address_ = inst.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
                TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE);

            std::string address = getAddress(QString::fromStdString(address_)).toStdString();
            {
                int number = static_cast<int>(this->ui->numberFilesToLeave->getValue());

                // Tworzenie polecenia
                std::string cmd { "" };

                cmd.append("/usr/bin/ssh root@");
                cmd.append(address);
                cmd.append(" \" /usr/bin/find /home/tlins/logs -name \'tlins*log\' -a -cmin +" + std::to_string(number) + " -exec rm -f {} \\; \"");

                // Create ssh command to transfer file
                emit getMainWindowInstance()->logEvent(QString { cmd.c_str() });

                if (this->cmdCall(cmd, "Remove logs files")) {
                    emit getMainWindowInstance()->popupStatus("Remove logs files - error");
                    break;
                }
            }
            emit getMainWindowInstance()->logEvent("Logs files removed");
            emit getMainWindowInstance()->popupStatus("Logs files removed");

        } while (0);
    };

    updateThread = std::thread { threadLambda };
    updateThread.detach();
}

void tlinsInfoWidget::selectOutputDirForLogsCb()
{
    QFileDialog diag { this };

    diag.setAcceptMode(QFileDialog::AcceptMode::AcceptOpen);
    diag.setModal(true);
    diag.setFileMode(QFileDialog::FileMode::DirectoryOnly);
    ui->directoryEdit->setText(diag.getExistingDirectory());
}

bool tlinsInfoWidget::cmdCall(const std::string& _cmd_, const std::string& operation)
{
    FILE* fPtr = ::popen(_cmd_.c_str(), "r");
    bool isError { false };

    if (fPtr != nullptr) {
        while (!feof(fPtr)) {
            char buf[2048];
            auto items = ::fread((void*)buf, sizeof(char), sizeof(buf), fPtr);
            if (items == 0) {
                qDebug() << "CMD end of stream";
                break;
            } else if (items < 0) {
                std::string msg { "Operation: " + operation + ". Error read operation progress. Upgrade will be interupted." };
                if (this->ui->sendUpdateLogsIntoAppLog->isChecked()) {
                    emit getMainWindowInstance()->logEvent(QString { msg.c_str() });
                }
                isError = true;
                break;
            }
            // Write debug info
            emit getMainWindowInstance()->logInstallEvent(QString { buf });
            if (this->ui->sendUpdateLogsIntoAppLog->isChecked()) {
                emit getMainWindowInstance()->logEvent(QString { buf });
            }
        }
        auto status = ::pclose(fPtr);
        if (status != 0) {
            std::string msg { "ERROR! Operation: " + operation + ". Operation status code: " + std::to_string(status).c_str() };
            emit getMainWindowInstance()->logInstallEvent(QString { msg.c_str() });
            isError = true;
        }

    } else {
        std::string msg { "ERROR! Operation: " + operation + ". Error create cxhilde process" };
        emit getMainWindowInstance()->logInstallEvent(QString { msg.c_str() });
        isError = true;
    }
    return isError;
}

bool tlinsInfoWidget::cmdCallStr(const std::string& _cmd_, std::string& result)
{
    FILE* fPtr = ::popen(_cmd_.c_str(), "r");
    bool isError { false };

    result = "";

    if (fPtr != nullptr) {
        while (!feof(fPtr)) {
            char buf[2048];
            auto items = ::fread((void*)buf, sizeof(char), sizeof(buf), fPtr);
            if (items == 0) {
                qDebug() << "CMD end of stream";
                break;
            } else if (items < 0) {
                std::string msg { "Error read operation progress. Upgrade will be interupted." };
                if (this->ui->sendUpdateLogsIntoAppLog->isChecked()) {
                    emit getMainWindowInstance()->logEvent(QString { msg.c_str() });
                }
                isError = true;
                break;
            }
            // Write debug info
            buf[items] = '\0';
            result.append(buf);
        }
        auto status = ::pclose(fPtr);
        if (status != 0) {
            std::string msg { std::string { "ERROR! Operation status code: " } + std::to_string(status).c_str() };
            emit getMainWindowInstance()->logInstallEvent(QString { msg.c_str() });
            isError = true;
        }

    } else {
        std::string msg { "ERROR! Error create childe process" };
        emit getMainWindowInstance()->logInstallEvent(QString { msg.c_str() });
        isError = true;
    }
    return isError;
}

void tlinsInfoWidget::downloadCfg()
{
    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();
    std::string address_ = inst.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE);

    std::string address = getAddress(QString::fromStdString(address_)).toStdString();
    {
        // Tworzenie polecenia
        std::string cmd { "" };

        cmd.append("/usr/bin/ssh root@");
        cmd.append(address);
        cmd.append(" cat /home/tlins/cfg/configuration.xml");

        // Create ssh command to transfer file
        emit getMainWindowInstance()->logEvent(QString { cmd.c_str() });

        std::string result;
        if (this->cmdCallStr(cmd, result)) {
            emit getMainWindowInstance()->popupStatus("Error read configuration");
        } else {
            ui->textEdit_4->setPlainText(QString { result.c_str() });
        }
    }
}

void tlinsInfoWidget::downloadCfgAstro()
{
    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();
    std::string address_ = inst.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE);

    std::string address = getAddress(QString::fromStdString(address_)).toStdString();
    {
        // Tworzenie polecenia
        std::string cmd { "" };

        cmd.append("/usr/bin/ssh root@");
        cmd.append(address);
        cmd.append(" cat /home/tlins/cfg/configuration-astro.xml");

        // Create ssh command to transfer file
        emit getMainWindowInstance()->logEvent(QString { cmd.c_str() });

        std::string result;
        if (this->cmdCallStr(cmd, result)) {
            emit getMainWindowInstance()->popupStatus("Error read configuration");
        } else {
            ui->textEdit_3->setText(QString { result.c_str() });
        }
    }
}

void tlinsInfoWidget::downloadCfgAstroService()
{
    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();
    std::string address_ = inst.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE);

    std::string address = getAddress(QString::fromStdString(address_)).toStdString();
    {
        // Tworzenie polecenia
        std::string cmd { "" };

        cmd.append("/usr/bin/ssh root@");
        cmd.append(address);
        cmd.append(" cat /home/tlins/cfg/configuration-system-service.xml");

        // Create ssh command to transfer file
        emit getMainWindowInstance()->logEvent(QString { cmd.c_str() });

        std::string result;
        if (this->cmdCallStr(cmd, result)) {
            emit getMainWindowInstance()->popupStatus("Error read configuration");
        } else {
            ui->textEdit_2->setText(QString { result.c_str() });
        }
    }
}

void tlinsInfoWidget::uploadCfg()
{
    string text = ui->textEdit_4->toPlainText().toStdString();

    if (text.length() == 0) {
        QMessageBox msgBox;
        msgBox.setText("Empty configuration");
        msgBox.exec();
        return;
    }

    FILE* fptr = fopen("/tmp/_cfg_", "w");
    if (fptr != nullptr) {
        fwrite(text.c_str(), text.length(), 1, fptr);
        fclose(fptr);
    }

    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();
    std::string address_ = inst.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE);

    std::string address = getAddress(QString::fromStdString(address_)).toStdString();
    {
        // Tworzenie polecenia
        std::string cmd { "" };

        cmd.append("/usr/bin/scp /tmp/_cfg_ root@");
        cmd.append(address);
        cmd.append(":/home/tlins/cfg/configuration.xml");

        // Create ssh command to transfer file
        emit getMainWindowInstance()->logEvent(QString { cmd.c_str() });

        std::string result;
        if (this->cmdCallStr(cmd, result)) {
            emit getMainWindowInstance()->popupStatus("Error read configuration");
        }
    }

    QMessageBox msgBox;
    msgBox.setText("Done");
    msgBox.exec();
}

void tlinsInfoWidget::uploadCfgAstro()
{
    string text = ui->textEdit_3->toPlainText().toStdString();

    if (text.length() == 0) {
        QMessageBox msgBox;
        msgBox.setText("Empty configuration");
        msgBox.exec();
        return;
    }

    FILE* fptr = fopen("/tmp/_cfg_astro_", "w");
    if (fptr != nullptr) {
        fwrite(text.c_str(), text.length(), 1, fptr);
        fclose(fptr);
    }

    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();
    std::string address_ = inst.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE);

    std::string address = getAddress(QString::fromStdString(address_)).toStdString();
    {
        // Tworzenie polecenia
        std::string cmd { "" };

        cmd.append("/usr/bin/scp /tmp/_cfg_astro_ root@");
        cmd.append(address);
        cmd.append(":/home/tlins/cfg/configuration-astro.xml");

        // Create ssh command to transfer file
        emit getMainWindowInstance()->logEvent(QString { cmd.c_str() });

        std::string result;
        if (this->cmdCallStr(cmd, result)) {
            emit getMainWindowInstance()->popupStatus("Error read configuration");
        }
    }

    QMessageBox msgBox;
    msgBox.setText("Done");
    msgBox.exec();
}

void tlinsInfoWidget::uploadCfgAstroService()
{
    string text = ui->textEdit_2->toPlainText().toStdString();

    if (text.length() == 0) {
        QMessageBox msgBox;
        msgBox.setText("Empty configuration");
        msgBox.exec();
        return;
    }

    FILE* fptr = fopen("/tmp/_cfg_service_", "w");
    if (fptr != nullptr) {
        fwrite(text.c_str(), text.length(), 1, fptr);
        fclose(fptr);
    }

    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();
    std::string address_ = inst.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE);

    std::string address = getAddress(QString::fromStdString(address_)).toStdString();
    {
        // Tworzenie polecenia
        std::string cmd { "" };

        cmd.append("/usr/bin/scp /tmp/_cfg_service_ root@");
        cmd.append(address);
        cmd.append(":/home/tlins/cfg/configuration-system-service.xml");

        // Create ssh command to transfer file
        emit getMainWindowInstance()->logEvent(QString { cmd.c_str() });

        std::string result;
        if (this->cmdCallStr(cmd, result)) {
            emit getMainWindowInstance()->popupStatus("Error read configuration");
        }
    }

    QMessageBox msgBox;
    msgBox.setText("Done");
    msgBox.exec();
}

void tlinsInfoWidget::sofUpdatePerfomeCb()
{
    if (isPendingUpdate) {
        QMessageBox msgBox;
        msgBox.setText("Update is in progress plase wait.");
        msgBox.exec();
        return;
    }

    if (ui->updateInputFile->text().length() == 0) {
        QMessageBox msgBox;
        msgBox.setText("Please select file.");
        msgBox.exec();
        return;
    }

    bool yesClicked { false };
    {
        QMessageBox msgBox;
        QAbstractButton* yes = msgBox.addButton(QMessageBox::StandardButton::Yes);
        msgBox.addButton(QMessageBox::StandardButton::No);
        msgBox.setText("\nDo you whant to start firmware update?\n");
        msgBox.setDetailedText("Firware updated details.\nFile : " + ui->updateInputFile->text());
        msgBox.exec();

        QAbstractButton* clicked = msgBox.clickedButton();
        if (clicked == yes) {
            yesClicked = true;
        }
    }

    if (!yesClicked) {
        QMessageBox msgBox;
        std::string msg { "Update has been dissmised." };
        msgBox.setText(msg.c_str());
        msgBox.exec();

        return;
    } else {
    }

    ui->updateDetails->clear();

    // 1. Transfer installation package over ssh
    auto threadLambda = [this]() {
        isPendingUpdate.store(true);
        do {
            // Get adres of the device
            auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();
            std::string address_ = inst.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
                TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE);

            std::string address = getAddress(QString::fromStdString(address_)).toStdString();

            // Remove old files
            {
                std::string cmd { "/usr/bin/ssh " };

                // Create ssh command to transfer file
                cmd.append(" root@");
                cmd.append(address);
                cmd.append(" \"touch /tmp/tlins-pkg; rm -rf /tmp/install /tmp/tlins-pkg*\" ");
                emit getMainWindowInstance()->logInstallEvent(QString { cmd.c_str() });
                if (this->ui->sendUpdateLogsIntoAppLog->isChecked()) {
                    emit getMainWindowInstance()->logEvent(QString { cmd.c_str() });
                }
                qDebug() << cmd.c_str();
                this->cmdCall(cmd, "Remove old files");
            }

            {
                std::string cmd { "/usr/bin/scp " };
                cmd.append(this->ui->updateInputFile->text().toStdString());

                // Create SCP command to transfer file
                cmd.append(" root@");
                cmd.append(address);
                cmd.append(":/tmp/. 2>&1 ");
                emit getMainWindowInstance()->logInstallEvent(QString { cmd.c_str() });
                if (this->ui->sendUpdateLogsIntoAppLog->isChecked()) {
                    emit getMainWindowInstance()->logEvent(QString { cmd.c_str() });
                }
                if (this->cmdCall(cmd, "Installation package upload")) {
                    emit getMainWindowInstance()->popupStatus("Installation package upload - error");
                    break;
                }
            }

            // Extract archive
            {
                std::string cmd { "/usr/bin/ssh " };

                // Create ssh command to transfer file
                cmd.append(" root@");
                cmd.append(address);
                cmd.append(" \"cd /tmp/; tar -xvf tlins-pkg-*.tar; cd /tmp/install; ./tlins-pkg-*.sh\" ");
                emit getMainWindowInstance()->logInstallEvent(QString { cmd.c_str() });
                if (this->ui->sendUpdateLogsIntoAppLog->isChecked()) {
                    emit getMainWindowInstance()->logEvent(QString { cmd.c_str() });
                }
                qDebug() << cmd.c_str();
                if (this->cmdCall(cmd, "Extract input file and perform update")) {
                    emit getMainWindowInstance()->popupStatus("Extract input file and perform update - error");
                    break;
                }
            }
        } while (0);
        emit getMainWindowInstance()->popupStatus("Upgrade done");
        emit getMainWindowInstance()->logInstallEvent("Upgrade done");
        isPendingUpdate.store(false);
    };

    updateThread = std::thread { threadLambda };
    updateThread.detach();
}

void tlinsInfoWidget::sofUpdateSelectFileCb()
{
    QFileDialog diag { this };

    diag.setAcceptMode(QFileDialog::AcceptMode::AcceptOpen);
    diag.setModal(true);
    diag.setFileMode(QFileDialog::FileMode::ExistingFile);
    ui->updateInputFile->setText(diag.getOpenFileName());
}

void tlinsInfoWidget::setInstallText(const QString& v)
{
    ui->updateDetails->append(v);
}

void tlinsInfoWidget::setText(const QString& v)
{
    ui->textEdit->append(v);
}

void tlinsInfoWidget::restore()
{
    auto& stateInst = tlinsAstroPilot::tlinsPluginsState::getInstance();

    ui->raDelta->setValue(stateInst.getRaDelta());
    ui->raSpeed->setValue(stateInst.getRaSpeed());

    ui->decDelta->setValue(stateInst.getDcDelta());
    ui->decSpeed->setValue(stateInst.getDcDelta());

    ui->xDegrisDelta->setValue(stateInst.getXDegrisDelta());
    ui->yDegrisDelta->setValue(stateInst.getYDegrisDelta());

    ui->xDegrisSpeed->setValue(stateInst.getXDegrisSpeed());
    ui->yDegrisSpeed->setValue(stateInst.getYDegrisSpeed());

    ui->xStepsDelta->setValue(stateInst.getXStepsDelta());
    ui->yStepsDelta->setValue(stateInst.getYStepsDelta());

    ui->xStepsSpeed->setValue(stateInst.getXStepsSpeed());
    ui->yStepsSpeed->setValue(stateInst.getYStepsSpeed());

    ui->scaleX->setValue(stateInst.getXScale());
    ui->scaleY->setValue(stateInst.getYScale());
}

void tlinsInfoWidget::update()
{
    auto& stateInst = tlinsAstroPilot::tlinsPluginsState::getInstance();

    stateInst.updateRaDelta(ui->raDelta->getValue());
    stateInst.updateRaSpeed(ui->raSpeed->getValue());
    stateInst.updateDcDelta(ui->decDelta->getValue());
    stateInst.updateDcDelta(ui->decSpeed->getValue());
    stateInst.updateXDegrisDelta(ui->xDegrisDelta->getValue());
    stateInst.updateYDegrisDelta(ui->yDegrisDelta->getValue());
    stateInst.updateXDegrisSpeed(ui->xDegrisSpeed->getValue());
    stateInst.updateYDegrisSpeed(ui->yDegrisSpeed->getValue());
    stateInst.updateXStepsDelta(ui->xStepsDelta->getValue());
    stateInst.updateYStepsDelta(ui->yStepsDelta->getValue());
    stateInst.updateXStepsSpeed(ui->xStepsSpeed->getValue());
    stateInst.updateYStepsSpeed(ui->yStepsSpeed->getValue());

    stateInst.updateXScale(ui->scaleX->getValue());
    stateInst.updateYScale(ui->scaleY->getValue());
}

void tlinsInfoWidget::updateCb()
{
    update();
    QMessageBox msgBox;
    msgBox.setText("Configuration has been updated in memeory - do not forget store.");
    msgBox.exec();
}

void tlinsInfoWidget::reloadCb()
{
    restore();

    QMessageBox msgBox;
    msgBox.setText("Changes has been reloaded.");
    msgBox.exec();
}

void tlinsInfoWidget::storeCb()
{
    auto& cfgInst = TlinsAstroBase::tlinsConfiguration::getInstance();
    auto& stateInst = tlinsAstroPilot::tlinsPluginsState::getInstance();

    cfgInst.setValue(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_RADELTA, stateInst.getRaDelta());
    cfgInst.setValue(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_DECDELTA, stateInst.getDcDelta());
    cfgInst.setValue(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_RASPEED, stateInst.getRaSpeed());
    cfgInst.setValue(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_DECSPEED, stateInst.getDcDelta());
    cfgInst.setValue(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_XDEGRISDELTA, stateInst.getXDegrisDelta());
    cfgInst.setValue(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_YDEGRISDELTA, stateInst.getYDegrisDelta());
    cfgInst.setValue(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_XDEGRISSPEED, stateInst.getXDegrisSpeed());
    cfgInst.setValue(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_YDEGRISSPEED, stateInst.getYDegrisSpeed());
    cfgInst.setValue(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_XSTEPSDELTA, stateInst.getXStepsDelta());
    cfgInst.setValue(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_YSTEPSDELTA, stateInst.getYStepsDelta());
    cfgInst.setValue(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_XSTEPSSPEED, stateInst.getXStepsSpeed());
    cfgInst.setValue(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_YSTEPSSPEED, stateInst.getYStepsSpeed());
    cfgInst.setValue(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_XSCALE, stateInst.getXScale());
    cfgInst.setValue(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_YSCALE, stateInst.getYScale());

    cfgInst.setValue(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_SPEEDMODE, stateInst.getSpeedMode());
    cfgInst.setValue(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_INSTEPS, stateInst.getInSteps());

    QMessageBox msgBox;
    msgBox.setText("Configuration has been stored.");
    msgBox.exec();
}

void tlinsInfoWidget::load()
{
    auto& cfgInst = TlinsAstroBase::tlinsConfiguration::getInstance();
    auto& stateInst = tlinsAstroPilot::tlinsPluginsState::getInstance();

    {
        double v = cfgInst.getDouble(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_RADELTA);
        stateInst.updateRaDelta(v);
    }
    {
        double v = cfgInst.getDouble(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_DECDELTA);
        stateInst.updateDcDelta(v);
    }
    {
        double v = cfgInst.getDouble(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_RASPEED);
        stateInst.updateRaSpeed(v);
    }
    {
        double v = cfgInst.getDouble(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_DECSPEED);
        stateInst.updateDcDelta(v);
    }
    {
        double v = cfgInst.getDouble(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_XDEGRISDELTA);
        stateInst.updateXDegrisDelta(v);
    }
    {
        double v = cfgInst.getDouble(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_YDEGRISDELTA);
        stateInst.updateYDegrisDelta(v);
    }
    {
        double v = cfgInst.getDouble(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_XDEGRISSPEED);
        stateInst.updateXDegrisSpeed(v);
    }
    {
        double v = cfgInst.getDouble(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_YDEGRISSPEED);
        stateInst.updateYDegrisSpeed(v);
    }
    {
        long v = cfgInst.getLong(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_XSTEPSDELTA);
        stateInst.updateXStepsDelta(v);
    }
    {
        long v = cfgInst.getLong(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_YSTEPSDELTA);
        stateInst.updateYStepsDelta(v);
    }
    {
        long v = cfgInst.getLong(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_XSTEPSSPEED);
        stateInst.updateXStepsSpeed(v);
    }
    {
        long v = cfgInst.getLong(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_YSTEPSSPEED);
        stateInst.updateYStepsSpeed(v);
    }
    {
        long v = cfgInst.getLong(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_XSCALE);
        stateInst.updateXScale(v);
    }
    {
        long v = cfgInst.getLong(TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::SHORTCUT_PARAMETER_YSCALE);
        stateInst.updateYScale(v);
    }
}
void tlinsInfoWidget::loadCb()
{
    load();
    restore();

    QMessageBox msgBox;
    msgBox.setText("Configuration has been loaded");
    msgBox.exec();
}

void tlinsInfoWidget::clearLog()
{
    ui->textEdit->clear();
}

tlinsInfoWidget::tlinsInfoWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsInfoWidget)
{
    ui->setupUi(this);
    ui->scaleX->setDecimal(0);
    ui->scaleY->setDecimal(0);
    ui->xStepsDelta->setDecimal(0);
    ui->yStepsDelta->setDecimal(0);
    ui->xStepsSpeed->setDecimal(0);
    ui->yStepsSpeed->setDecimal(0);
    ui->numberFilesToLeave->setDecimal(0);
    ui->baseInterval->setDecimal(0);
    downloadInProgress.store(false);

    ui->groupBox_5->setVisible(false);

    load();
    restore();

    // Rejestrowanie callbacka notyfikujacego zmiany statusuów pilota
    tlinsAstroPilot::tlinsPluginsState::getInstance().addCallback([this](const tlinsAstroPilot::tlinsPluginsState::VALUE_TYPE v) {
        auto& stateInst = tlinsAstroPilot::tlinsPluginsState::getInstance();
        switch (v) {
        case tlinsAstroPilot::tlinsPluginsState::VALUE_TYPE::__raDelta__:
            this->ui->raDelta->setValue(stateInst.getRaDelta());
            break;

        case tlinsAstroPilot::tlinsPluginsState::VALUE_TYPE::__dcDelta__:
            ui->decDelta->setValue(stateInst.getDcDelta());
            break;

        case tlinsAstroPilot::tlinsPluginsState::VALUE_TYPE::__raSpeed__:
            ui->raSpeed->setValue(stateInst.getRaSpeed());
            break;

        case tlinsAstroPilot::tlinsPluginsState::VALUE_TYPE::__dcSpeed__:
            ui->decSpeed->setValue(stateInst.getDcDelta());
            break;

        case tlinsAstroPilot::tlinsPluginsState::VALUE_TYPE::__calibrationObjectId__:
            break;

        case tlinsAstroPilot::tlinsPluginsState::VALUE_TYPE::__xDegrisDelta__:
            ui->xDegrisDelta->setValue(stateInst.getXDegrisDelta());
            break;

        case tlinsAstroPilot::tlinsPluginsState::VALUE_TYPE::__yDegrisDelta__:
            ui->yDegrisDelta->setValue(stateInst.getYDegrisDelta());
            break;

        case tlinsAstroPilot::tlinsPluginsState::VALUE_TYPE::__xDegrisSpeed__:
            ui->xDegrisSpeed->setValue(stateInst.getXDegrisSpeed());
            break;

        case tlinsAstroPilot::tlinsPluginsState::VALUE_TYPE::__yDegrisSpeed__:
            ui->yDegrisSpeed->setValue(stateInst.getYDegrisSpeed());
            break;

        case tlinsAstroPilot::tlinsPluginsState::VALUE_TYPE::__xStepsDelta__:
            ui->xStepsDelta->setValue(stateInst.getXStepsDelta());
            break;

        case tlinsAstroPilot::tlinsPluginsState::VALUE_TYPE::__yStepsDelta__:
            ui->yStepsDelta->setValue(stateInst.getYStepsDelta());
            break;

        case tlinsAstroPilot::tlinsPluginsState::VALUE_TYPE::__xStepsSpeed__:
            ui->xStepsSpeed->setValue(stateInst.getXStepsSpeed());
            break;

        case tlinsAstroPilot::tlinsPluginsState::VALUE_TYPE::__yStepsSpeed__:
            ui->yStepsSpeed->setValue(stateInst.getYStepsSpeed());
            break;

        case tlinsAstroPilot::tlinsPluginsState::VALUE_TYPE::__xScale__:
            ui->scaleX->setValue(stateInst.getXScale());
            break;

        case tlinsAstroPilot::tlinsPluginsState::VALUE_TYPE::__yScale__:
            ui->scaleY->setValue(stateInst.getYScale());
            break;

        case tlinsAstroPilot::tlinsPluginsState::VALUE_TYPE::__speedMode__:
            break;

        case tlinsAstroPilot::tlinsPluginsState::VALUE_TYPE::__inSteps__:
            break;
        }
    });
}

tlinsInfoWidget::~tlinsInfoWidget()
{
    delete ui;
}
