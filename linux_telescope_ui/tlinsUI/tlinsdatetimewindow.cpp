#include "tlinsdatetimewindow.h"
#include "tlinsBacktrace.hpp"
#include "tlinscommunicationthread.h"
#include "ui_tlinsdatetimewindow.h"

#include "tlinsuimainwindow.h"

#include <QMessageBox>

tlinsDateTimeWindow::tlinsDateTimeWindow(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::tlinsDateTimeWindow)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptedSlot()));
    connect(this, SIGNAL(setStatus(std::string)), this, SLOT(setStatusSlot(std::string)), Qt::BlockingQueuedConnection);
}

void tlinsDateTimeWindow::setStatusSlot(std::string str)
{
    QMessageBox msgBox;
    msgBox.setText(QString::fromStdString(str));
    msgBox.exec();
}

class tlinsDateTimeProc : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;
    tlinsDateTimeWindow* parent;
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

public:
    virtual void operator()() noexcept
    {
        try {
            // Nie przekazujemy wejscia z kontrolera
            connection->getDevice()->setDateTime(year, month, day, hour, minute, second);

            auto msg = std::string { "Date time set" };
            emit getMainWindowInstance()->logEvent(QString::fromStdString(msg));
            emit parent->setStatus(msg);
        } catch (tlinsInterfaceException& exc) {
            auto msg = std::string { "Error set date time: " } + exc.getErrorMessage();
            emit getMainWindowInstance()->logEvent(QString::fromStdString(msg));
            emit parent->setStatus(msg);
            return;
        }
    }

    virtual bool isAsynchronuus()
    {
        return false;
    }

    tlinsDateTimeProc(tlinsDateTimeWindow* parent_,
        const int year_,
        const int month_,
        const int day_,
        const int hour_,
        const int minute_,
        const int second_)
        : parent { parent_ }
        , year { year_ }
        , month { month_ }
        , day { day_ }
        , hour { hour_ }
        , minute { minute_ }
        , second { second_ }
    {
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT })) {
            auto msg { std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT) };
            emit getMainWindowInstance()->logEvent(QString::fromStdString(msg));
            __THROW__(tlinsInterfaceException(msg, -1));
        }

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
    }

    virtual std::string name()
    {
        return "tlinsDateTimeProc";
    }

    virtual ~tlinsDateTimeProc()
    {
        connection.reset();
    }
};

void tlinsDateTimeWindow::acceptedSlot()
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    ui->dateTime->get(year, month, day, hour, minute, second);

    try {
        // Wysalnie rzadania
        std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest> req(new tlinsDateTimeProc { this, year, month, day, hour, minute, second });
        TlinsAstroBase::tlinsCommunicationThread::getInstance().push(req);
    } catch (tlinsInterfaceException& exc) {
        std::string m { "Error set date time. " };
        m += exc.getErrorMessage().c_str();

        emit getMainWindowInstance()->logEvent(QString::fromStdString(m));
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString(m));
        msgBox.exec();
    }
}

tlinsDateTimeWindow::~tlinsDateTimeWindow()
{
    delete ui;
}
