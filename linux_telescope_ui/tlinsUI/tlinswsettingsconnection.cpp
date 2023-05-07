#include "tlinswsettingsconnection.h"
#include "tlinsconfiguration.h"
#include "ui_tlinswsettingsconnection.h"

void tlinsWSettingsConnection::addItem(QComboBox* widget, const QString& label, const int data)
{
    QVariant var(data);
    widget->addItem(label);
    widget->setItemData(ui->astroEngineAsyncAuthType->count(), var);
}

tlinsWSettingsConnection::tlinsWSettingsConnection(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWSettingsConnection)
{
    ui->setupUi(this);

    addItem(ui->astroEngineAsyncAuthType, "Insecure", 0);
    addItem(ui->astroEngineAsyncAuthType, "SSL/TLS", 1);
    addItem(ui->astroEngineAsyncAuthType, "Token", 2);

    addItem(ui->astroEngineAuthType, "Insecure", 0);
    addItem(ui->astroEngineAuthType, "SSL/TLS", 1);
    addItem(ui->astroEngineAuthType, "Token", 2);

    addItem(ui->deviceEngineAuthType, "Insecure", 0);
    addItem(ui->deviceEngineAuthType, "SSL/TLS", 1);
    addItem(ui->deviceEngineAuthType, "Token", 2);

    addItem(ui->deviceEngineAsyncAuthType, "Insecure", 0);
    addItem(ui->deviceEngineAsyncAuthType, "SSL/TLS", 1);
    addItem(ui->deviceEngineAsyncAuthType, "Token", 2);

    addItem(ui->systemServiceAuthType, "Insecure", 0);
    addItem(ui->systemServiceAuthType, "SSL/TLS", 1);
    addItem(ui->systemServiceAuthType, "Token", 2);

    ui->astroEngineAsyncAuthType->setVisible(false);
    ui->astroEngineAuthType->setVisible(false);
    ui->deviceEngineAuthType->setVisible(false);
    ui->deviceEngineAsyncAuthType->setVisible(false);
    ui->systemServiceAuthType->setVisible(false);

    ui->useCommonAddressIp->setChecked(false);
    ui->commonAddressIp->setText("127.0.0.1");
    ui->astroEnginePort->setValue(20000);
    ui->astroEnginePort->setDecimal(0);
    ui->astroEngineAsyncPort->setValue(20002);
    ui->astroEngineAsyncPort->setDecimal(0);
    ui->deviceEnginePort->setValue(20001);
    ui->deviceEnginePort->setDecimal(0);
    ui->deviceEngineAsyncPort->setValue(20003);
    ui->deviceEngineAsyncPort->setDecimal(0);
    ui->systemServicePort->setValue(20100);
    ui->systemServicePort->setDecimal(0);
    ui->commonAddress->setVisible(false);
    ui->groupBoxAddresses->setVisible(true);

    ui->sysMonitorAutoConnectDisconnect->setChecked(true);

    tlinsWSettingsConnection::restore();
}

tlinsWSettingsConnection::~tlinsWSettingsConnection()
{
    delete ui;
}

void tlinsWSettingsConnection::save()
{
    // Instancja konfiguracji
    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();

    //
    // -- Wspolny adres IP
    //
    bool useSingleAddress { false };
    auto CONNECTION_PARAMETER_URL_ASTRO_ENGINE_PORT_ { 0 };
    auto CONNECTION_PARAMETER_URL_DEVICE_ENGINE_PORT_ { 0 };
    auto CONNECTION_PARAMETER_URL_ASTRO_ENGINE_ASYNCH_PORT_ { 0 };
    auto CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH_PORT_ { 0 };
    auto CONNECTION_PARAMETER_URL_SYSTEM_SERVICE_PORT_ { 0 };
    auto CONNECTION_PARAMETER_URL_COMMON_ADDRESS_IP_ { std::string { "" } };

    {
        useSingleAddress = ui->useCommonAddressIp->isChecked();

        auto value = useSingleAddress ? std::string { "true" } : std::string { "false" };
        inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_USE_COMMON_ADDRESS, value);
    }
    {
        CONNECTION_PARAMETER_URL_ASTRO_ENGINE_PORT_ = static_cast<int>((ui->astroEnginePort->getValue()));
        CONNECTION_PARAMETER_URL_DEVICE_ENGINE_PORT_ = static_cast<int>((ui->deviceEnginePort->getValue()));
        CONNECTION_PARAMETER_URL_ASTRO_ENGINE_ASYNCH_PORT_ = static_cast<int>(ui->astroEngineAsyncPort->getValue());
        CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH_PORT_ = static_cast<int>(ui->deviceEngineAsyncPort->getValue());
        CONNECTION_PARAMETER_URL_SYSTEM_SERVICE_PORT_ = static_cast<int>(ui->systemServicePort->getValue());
        CONNECTION_PARAMETER_URL_COMMON_ADDRESS_IP_ = ui->commonAddressIp->text().toStdString();

        inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE_PORT, CONNECTION_PARAMETER_URL_ASTRO_ENGINE_PORT_);
        inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_PORT, CONNECTION_PARAMETER_URL_DEVICE_ENGINE_PORT_);
        inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE_ASYNCH_PORT, CONNECTION_PARAMETER_URL_ASTRO_ENGINE_ASYNCH_PORT_);
        inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH_PORT, CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH_PORT_);
        inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_SYSTEM_SERVICE_PORT, CONNECTION_PARAMETER_URL_SYSTEM_SERVICE_PORT_);
        inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_COMMON_ADDRESS_IP, CONNECTION_PARAMETER_URL_COMMON_ADDRESS_IP_);
    }

    if (ui->sysMonitorAutoConnectDisconnect->isChecked()) {
        inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_CONNECT_SYSTEM_EVENT_MONITOR, "true");
    } else {
        inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_CONNECT_SYSTEM_EVENT_MONITOR, "false");
    }

    if (!useSingleAddress) {
        inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE, ui->urlAstroEngine->text().toStdString());
        inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE_AUTH, ui->astroEngineAuthType->currentIndex());

        inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE, ui->urlDeviceEngine->text().toStdString());
        inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_AUTH, ui->deviceEngineAuthType->currentIndex());

        inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE_ASYNCH, ui->urlAstroEngineAsynch->text().toStdString());
        inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE_ASYNCH_AUTH, ui->astroEngineAsyncAuthType->currentIndex());

        inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH, ui->urlDeviceEngineAsynch->text().toStdString());
        inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH_AUTH, ui->deviceEngineAsyncAuthType->currentIndex());

        inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_SYSTEM_SERVICE, ui->urlSystemService->text().toStdString());
        inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_SYSTEM_SERVICE_AUTH, ui->systemServiceAuthType->currentIndex());
    } else {
        {
            std::string value { CONNECTION_PARAMETER_URL_COMMON_ADDRESS_IP_ + ":" + std::to_string(CONNECTION_PARAMETER_URL_ASTRO_ENGINE_PORT_) };

            inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE, value);
            ui->urlAstroEngine->setText(QString::fromStdString(value));
        }

        {
            std::string value { CONNECTION_PARAMETER_URL_COMMON_ADDRESS_IP_ + ":" + std::to_string(CONNECTION_PARAMETER_URL_DEVICE_ENGINE_PORT_) };

            inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE, value);
            ui->urlDeviceEngine->setText(QString::fromStdString(value));
        }

        {
            std::string value { CONNECTION_PARAMETER_URL_COMMON_ADDRESS_IP_ + ":" + std::to_string(CONNECTION_PARAMETER_URL_ASTRO_ENGINE_ASYNCH_PORT_) };

            inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE_ASYNCH, value);
            ui->urlAstroEngineAsynch->setText(QString::fromStdString(value));
        }

        {
            std::string value { CONNECTION_PARAMETER_URL_COMMON_ADDRESS_IP_ + ":" + std::to_string(CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH_PORT_) };

            inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH, value);
            ui->urlDeviceEngineAsynch->setText(QString::fromStdString(value));
        }

        {
            std::string value { CONNECTION_PARAMETER_URL_COMMON_ADDRESS_IP_ + ":" + std::to_string(CONNECTION_PARAMETER_URL_SYSTEM_SERVICE_PORT_) };

            inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_SYSTEM_SERVICE, value);
            ui->urlSystemService->setText(QString::fromStdString(value));
        }
    }
}

void tlinsWSettingsConnection::useCommonIp(bool set)
{
    if (set) {
        ui->commonAddress->setVisible(true);
        ui->groupBoxAddresses->setVisible(false);
    } else {
        ui->commonAddress->setVisible(false);
        ui->groupBoxAddresses->setVisible(true);
    }
}

void tlinsWSettingsConnection::saveDefault()
{
    // Instancja konfiguracji
    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();

    inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_CONNECT_SYSTEM_EVENT_MONITOR, "true");
    inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_SYSTEM_SERVICE, "localhost:20100");
    inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE, "localhost:20000");
    inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE, "localhost:20001");
    inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE_ASYNCH, "localhost:20002");
    inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH, "localhost:20003");
    inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_SYSTEM_SERVICE_AUTH, 0);
    inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE_AUTH, 0);
    inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_AUTH, 0);
    inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE_ASYNCH_AUTH, 0);
    inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH_AUTH, 0);
    inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_USE_COMMON_ADDRESS, std::string { "false" });
    inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE_PORT, 20000);
    inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_PORT, 20001);
    inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE_ASYNCH_PORT, 20002);
    inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH_PORT, 20003);
    inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_SYSTEM_SERVICE_PORT, 20100);
    inst.setValue(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_COMMON_ADDRESS_IP, std::string { "127.0.0.1" });
}

void tlinsWSettingsConnection::restore()
{
    // Instancja konfiguracji
    auto& inst = TlinsAstroBase::tlinsConfiguration::getInstance();

    QString bValue = QString::fromStdString(inst.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
        TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_CONNECT_SYSTEM_EVENT_MONITOR));
    if (bValue.toLower() == "true") {
        ui->sysMonitorAutoConnectDisconnect->setChecked(true);
    } else {
        ui->sysMonitorAutoConnectDisconnect->setChecked(false);
    }

    ui->urlSystemService->clear();
    ui->urlAstroEngine->clear();
    ui->urlDeviceEngine->clear();
    ui->urlAstroEngine->insert(QString::fromStdString(inst.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE)));
    ui->urlDeviceEngine->insert(QString::fromStdString(inst.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE)));
    ui->urlSystemService->insert(QString::fromStdString(inst.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_SYSTEM_SERVICE)));

    ui->urlAstroEngineAsynch->clear();
    ui->urlDeviceEngineAsynch->clear();
    ui->urlAstroEngineAsynch->insert(QString::fromStdString(inst.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE_ASYNCH)));
    ui->urlDeviceEngineAsynch->insert(QString::fromStdString(inst.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH)));

    ui->astroEngineAuthType->setCurrentIndex(inst.getInt(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_SYSTEM_SERVICE_AUTH));
    ui->astroEngineAuthType->setCurrentIndex(inst.getInt(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE_AUTH));
    ui->deviceEngineAuthType->setCurrentIndex(inst.getInt(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_AUTH));
    ui->astroEngineAsyncAuthType->setCurrentIndex(inst.getInt(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE_ASYNCH_AUTH));
    ui->deviceEngineAsyncAuthType->setCurrentIndex(inst.getInt(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH_AUTH));

    //
    // -- Wspolny adres IP
    //
    if (inst.hasKey(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_USE_COMMON_ADDRESS)) {
        auto useCommon = inst.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_USE_COMMON_ADDRESS);

        // Uzywany jest wspolny address IP
        auto str = QString::fromStdString(useCommon);
        if (str.toLower() == "true") {
            ui->commonAddress->setVisible(true);
            ui->groupBoxAddresses->setVisible(false);
            ui->useCommonAddressIp->setChecked(true);
        } else {
            ui->commonAddress->setVisible(false);
            ui->groupBoxAddresses->setVisible(true);
            ui->useCommonAddressIp->setChecked(false);
        }
    }

    if (inst.hasKey(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE_PORT)) {
        auto value = inst.getInt(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE_PORT);
        ui->astroEnginePort->setValue(static_cast<double>(value));
    }

    if (inst.hasKey(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_PORT)) {
        auto value = inst.getInt(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_PORT);
        ui->deviceEnginePort->setValue(static_cast<double>(value));
    }

    if (inst.hasKey(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE_ASYNCH_PORT)) {
        auto value = inst.getInt(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE_ASYNCH_PORT);
        ui->astroEngineAsyncPort->setValue(static_cast<double>(value));
    }

    if (inst.hasKey(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH_PORT)) {
        auto value = inst.getInt(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH_PORT);
        ui->deviceEngineAsyncPort->setValue(static_cast<double>(value));
    }

    if (inst.hasKey(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_SYSTEM_SERVICE_PORT)) {
        auto value = inst.getInt(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_SYSTEM_SERVICE_PORT);
        ui->systemServicePort->setValue(static_cast<double>(value));
    }

    if (inst.hasKey(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_COMMON_ADDRESS_IP)) {
        auto value = inst.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP, TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_COMMON_ADDRESS_IP);
        ui->commonAddressIp->setText(QString::fromStdString(value));
    }
}
