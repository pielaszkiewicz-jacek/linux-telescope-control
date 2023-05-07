#include "tlinswapplayastroconfigurationwidget.h"
#include "ui_tlinswapplayastroconfigurationwidget.h"

#include "logevent.hpp"
#include "tlinscommunicationthread.h"
#include "tlinsconnection.h"
#include "tlinsenvironment.h"
#include "tlinsplace.h"
#include "tlinsuidatabasedefinition.h"
#include "tlinswapplayastroconfigurationwindow.h"

#include <QMessageBox>
#include <chrono>
#include <ctime>
#include <sofa.h>
#include <sofam.h>

tlinsWApplayAstroConfigurationWidget::tlinsWApplayAstroConfigurationWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWApplayAstroConfigurationWidget)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accepted()));
    connect(this, SIGNAL(applayingStatus(std::string)),
        this, SLOT(applayingStatusSlot(std::string)), Qt::BlockingQueuedConnection);
}

tlinsWApplayAstroConfigurationWidget::~tlinsWApplayAstroConfigurationWidget()
{
    delete ui;
}

void tlinsWApplayAstroConfigurationWidget::applayingStatusSlot(std::string str)
{
    QMessageBox msgBox;
    msgBox.setText(QString::fromStdString(str));
    msgBox.exec();
}

class tlinsApplayAstroCfgEnvironment : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;
    tlinsWApplayAstroConfigurationWidget* parent;

public:
    virtual void operator()() noexcept
    {
        auto& ins = tlinsEnvironment::getInstance();
        tlinsAstroEngineInterface::tlinsEnvironment request;
        request.set_ambientPressure(ins.getAmbientPressure());
        request.set_effectiveColor(ins.getEffectiveColor());
        request.set_realHumidity(ins.getRealHumidity());
        request.set_temperature(ins.getTemperature());

        try {
            // Ustawienie warunkow srodowiskowych
            connection->getAstro()->setEnvironment(request);
            parent->updateSuccessCount();
        } catch (tlinsInterfaceException& exc) {
            std::string msg { "Error applay environment configuration. Error: " };
            msg += exc.getErrorMessage();
            PRINT_LOG(QString::fromStdString(msg));
            parent->updateFailedCount();
        }
    }
    virtual bool isAsynchronuus()
    {
        return false;
    }

    virtual std::string name()
    {
        return "tlinsApplayAstroCfgEnvironment";
    }

    tlinsApplayAstroCfgEnvironment(tlinsWApplayAstroConfigurationWidget* parent_)
        : parent { parent_ }
    {
        // Pobranie polaczenia
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT })) {
            std::string msg { "No active connection: " };
            msg += TLINS_CONNECTION_DEFAULT;
            PRINT_LOG(QString::fromStdString(msg));
            __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));
        }

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
    }

    virtual ~tlinsApplayAstroCfgEnvironment()
    {
    }
};

class tlinsApplayAstroCfgObservationPlace : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;
    tlinsWApplayAstroConfigurationWidget* parent;
    TlinsAstroBase::tlinsPlace data;

public:
    virtual void operator()() noexcept
    {
        tlinsAstroEngineInterface::tlinsObservationPlace request;

        tlinsAstroEngineInterface::tlinsCoordinate lo;
        {
            char sign;
            int idmsf[4];
            double radians = data.getLongitude() * DD2R;
            ::iauA2af(9, radians, &sign, idmsf);

            int d = idmsf[0];
            int m = idmsf[1];
            double s = static_cast<double>(idmsf[2]) + static_cast<double>(idmsf[3]) / 1000000000.0;

            lo.set_degris(d);
            lo.set_minutes(m);
            lo.set_seconds(s);
            lo.set_sign(sign == '-' ? true : false);
        }

        tlinsAstroEngineInterface::tlinsCoordinate la;
        {
            char sign;
            int idmsf[4];
            double radians = data.getLatitude() * DD2R;
            ::iauA2af(9, radians, &sign, idmsf);

            int d = idmsf[0];
            int m = idmsf[1];
            int s = static_cast<double>(idmsf[2]) + static_cast<double>(idmsf[3]) / 1000000000.0;

            la.set_degris(d);
            la.set_minutes(m);
            la.set_seconds(s);
            la.set_sign(sign == '-' ? true : false);
        }

        request.set_longitude(lo);
        request.set_latitude(la);

        request.set_hm(data.getHm());

        switch (data.getEpType()) {
        case TlinsAstroBase::tlinsPlace::ElipsoideType::GRS_80:
            request.set_epType(tlinsAstroEngineInterface::tlinsElipsoideType::GRS_80);
            break;
        case TlinsAstroBase::tlinsPlace::ElipsoideType::WGS_72:
            request.set_epType(tlinsAstroEngineInterface::tlinsElipsoideType::WGS_72);
            break;
        case TlinsAstroBase::tlinsPlace::ElipsoideType::WGS_84:
            request.set_epType(tlinsAstroEngineInterface::tlinsElipsoideType::WGS_84);
            break;
        }

        try {
            // Ustawienie warunkow srodowiskowych
            connection->getAstro()->setObservationPlace(request);
            parent->updateSuccessCount();
        } catch (tlinsInterfaceException& exc) {
            std::string msg { "Error set observation place. Error: " };
            msg += exc.getErrorMessage();
            PRINT_LOG(QString::fromStdString(msg));
            parent->updateFailedCount();
        }
    }
    virtual bool isAsynchronuus()
    {
        return false;
    }

    virtual std::string name()
    {
        return "tlinsApplayAstroCfgObservationPlace";
    }

    tlinsApplayAstroCfgObservationPlace(tlinsWApplayAstroConfigurationWidget* parent_)
        : parent { parent_ }
    {
        bool result = false;
        try {
            // Odczyt z bazy lokalizacji
            TlinsAstroBase::tlinsUIDatabase db;
            TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db);
            result = dbDef.selectDefaultPlace(data);
        } catch (TlinsAstroBase::tlinsUIException& exc) {
            __THROW__(tlinsException(std::string("Error read database: ") + exc.getErrorDescription(), -1));
        } catch (...) {
            __THROW__(tlinsException(std::string("Error read database"), -1));
        }

        if (!result) {
            __THROW__(tlinsException(std::string("No default observation place."), -1));
        }

        // Polaczenie z kontrolerem astro
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
            __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
    }

    virtual ~tlinsApplayAstroCfgObservationPlace()
    {
    }
};

class tlinsApplayAstroCfgIERS : public TlinsAstroBase::tlinsCommunicationThreadRequest {
private:
    std::shared_ptr<TlinsAstroBase::tlinsConnectionContext> connection;
    tlinsWApplayAstroConfigurationWidget* parent;
    std::vector<TlinsAstroBase::tlinsIERS> data;
    bool store;
    bool overwrite;

public:
    virtual void operator()() noexcept
    {
        tlinsAstroEngineInterface::tlinsIERSListItems request;

        request.set_overwrite(overwrite);
        request.set_localStore(store);
        for (auto& item : data) {
            tlinsAstroEngineInterface::tlinsIERS dataItem;
            dataItem.set_year(item.getYear());
            dataItem.set_month(item.getMonth());
            dataItem.set_day(item.getDay());
            dataItem.set_pmX(item.getPmx());
            dataItem.set_pmY(item.getPmy());
            dataItem.set_deltaUT(item.getDeltaUt());
            dataItem.set_dPsi(item.getDPsi());
            dataItem.set_dEpsilon(item.getDEpsilon());
            dataItem.set_dx(item.getDx());
            dataItem.set_dy(item.getDy());
            request.add(dataItem);
        }
        try {
            // Ustawienie warunkow srodowiskowych
            connection->getAstro()->setIERSInfo(request);
            parent->updateSuccessCount();
        } catch (tlinsInterfaceException& exc) {
            std::string msg { "Error set observation place. Error: " };
            msg += exc.getErrorMessage();
            PRINT_LOG(QString::fromStdString(msg));
            parent->updateFailedCount();
        }
    }

    virtual bool isAsynchronuus()
    {
        return false;
    }

    virtual std::string name()
    {
        return "tlinsApplayAstroCfgIERS";
    }

    tlinsApplayAstroCfgIERS(tlinsWApplayAstroConfigurationWidget* parent_, const bool store_, const bool overwrite_)
        : parent { parent_ }
        , store { store_ }
        , overwrite(overwrite_)
    {
        // Biezaca data
        try {
            // Odczyt z bazy lokalizacji
            TlinsAstroBase::tlinsUIDatabase db;
            TlinsAstroBase::tlinsUIDatabaseDefinition dbDef(db);
            dbDef.selectIERS(data);
        } catch (TlinsAstroBase::tlinsUIException& exc) {
            __THROW__(tlinsException(std::string("Error read database: ") + exc.getErrorDescription(), -1));
        } catch (...) {
            __THROW__(tlinsException(std::string("Error read database"), -1));
        }

        // Pobranie polaczenia
        if (!TlinsAstroBase::tlinsConnectionsManager::getInstance().hasConnection(std::string { TLINS_CONNECTION_DEFAULT }))
            __THROW__(tlinsException(std::string("No active connection: ") + std::string(TLINS_CONNECTION_DEFAULT), -1));

        // Polaczenie
        connection = TlinsAstroBase::tlinsConnectionsManager::getInstance().getConnection(TLINS_CONNECTION_DEFAULT);
    }

    virtual ~tlinsApplayAstroCfgIERS()
    {
    }
};

void tlinsWApplayAstroConfigurationWidget::updateSuccessCount()
{
    successCount++;
    if ((successCount + failedCount) >= totalCount) {
        if (totalCount == successCount)
            emit applayingStatusSlot("Successfully applied configuration.");
        else
            emit applayingStatusSlot("Configuration applied with errors - check log.");
    }
}

void tlinsWApplayAstroConfigurationWidget::updateFailedCount()
{
    failedCount++;
    if ((successCount + failedCount) >= totalCount) {
        emit this->applayingStatusSlot("Configuration applied with errors - check log.");
    }
}

void tlinsWApplayAstroConfigurationWidget::accepted()
{
    auto toApplay = ui->cfg->getCfgToBeApplyed();

    // Inicalizacja licznikow
    resetCounters();

    try {
        std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest> reqEnv(nullptr);
        std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest> reqPos(nullptr);
        std::unique_ptr<TlinsAstroBase::tlinsCommunicationThreadRequest> reqIERS(nullptr);

        totalCount = 0;
        if (toApplay[tlinsWApplayAstroConfiguration::CFG_TYPE::ENVIRONMENT]) {
            reqEnv.reset(new tlinsApplayAstroCfgEnvironment { this });
            totalCount++;
        }

        if (toApplay[tlinsWApplayAstroConfiguration::CFG_TYPE::IERS]) {
            reqIERS.reset(new tlinsApplayAstroCfgIERS(this,
                toApplay[tlinsWApplayAstroConfiguration::CFG_TYPE::IERS_STORE_LOCALY],
                toApplay[tlinsWApplayAstroConfiguration::CFG_TYPE::IERS_OVERWRITE]));
            totalCount++;
        }

        if (toApplay[tlinsWApplayAstroConfiguration::CFG_TYPE::OBSERVATION_PLACE]) {
            reqPos.reset(new tlinsApplayAstroCfgObservationPlace { this });
            totalCount++;
        }

        if (totalCount == 0) {
            emit this->applayingStatusSlot("No configuration selected.");
            return;
        }

        // Ustawienie srodowiska
        if (toApplay[tlinsWApplayAstroConfiguration::CFG_TYPE::ENVIRONMENT]) {
            PRINT_LOG(QString { "Environment configuration will be set." });
            TlinsAstroBase::tlinsCommunicationThread::getInstance().push(reqEnv);
        }

        if (toApplay[tlinsWApplayAstroConfiguration::CFG_TYPE::IERS]) {
            PRINT_LOG(QString { "IERS will be set." });
            TlinsAstroBase::tlinsCommunicationThread::getInstance().push(reqIERS);
        }

        if (toApplay[tlinsWApplayAstroConfiguration::CFG_TYPE::OBSERVATION_PLACE]) {
            PRINT_LOG(QString { "Observation place will be set." });
            TlinsAstroBase::tlinsCommunicationThread::getInstance().push(reqPos);
        }
    } catch (tlinsException& exc) {
        PRINT_LOG(QString { "Error applying astro configuration." });
        emit this->applayingStatusSlot(exc.getErrorMessage());
    }
}
