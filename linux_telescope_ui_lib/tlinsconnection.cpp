#include "tlinsconnection.h"
#include "tlinsconfiguration.h"
#include "tlinsuiexception.h"
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>
#include <grpc/grpc.h>
#include <tlinsAstroEngineInterface.hpp>
#include <tlinsBacktrace.hpp>
#include <tlinsLogger.hpp>
#include <tlinsMoveServerInterface.hpp>

#include <memory>

//
// ------------------------------------------------
//

namespace TlinsAstroBase {

std::string tlinsChannelsManager::DEFAULT_CHANNEL_ASTRO = "____DEFAULT_CHANNEL_ASTRO____";
std::string tlinsChannelsManager::DEFAULT_CHANNEL_DEVICE = "____DEFAULT_CHANNEL_DEVICE____";
std::string tlinsChannelsManager::DEFAULT_CHANNEL_DEVICE_ASYNC = "____DEFAULT_CHANNEL_DEVICE_ASYNC____";

tlinsChannelsManager::tlinsChannelsManager()
{
    addDefault();
}

bool tlinsChannelsManager::addChannel(const std::string& name,
    const std::string& url)
{
    std::unique_lock<std::mutex> lock(mtx);

    std::shared_ptr<grpc::Channel> channel { nullptr };
    std::shared_ptr<grpc::ChannelCredentials> channelCred;
    auto res = tlinsConnectionsManager::createChannel(url, channel, channelCred);

    if (!res)
        return res;

    channels[name] = channel;
    channelsCred[name] = channelCred;
    return true;
}

void tlinsChannelsManager::addDefault()
{
    auto& cfgInst = TlinsAstroBase::tlinsConfiguration::getInstance();

    std::string urlAstro { "localhost:20000" };
    if (cfgInst.hasKey(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE))
        urlAstro = cfgInst.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_ASTRO_ENGINE);

    std::string urlDevice { "localhost:20001" };
    if (cfgInst.hasKey(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE))
        urlDevice = cfgInst.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE);

    std::string urlDeviceAsync { "localhost:20003" };
    if (cfgInst.hasKey(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH))
        urlDeviceAsync = cfgInst.getString(TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_GROUP,
            TlinsAstroBase::tlinsConfiguration::CONNECTION_PARAMETER_URL_DEVICE_ENGINE_ASYNCH);

    auto credAstro = grpc::InsecureChannelCredentials();
    auto credDevice = grpc::InsecureChannelCredentials();
    auto credDeviceAsync = grpc::InsecureChannelCredentials();

    auto channelAstro = grpc::CreateChannel(urlAstro.c_str(), credAstro);
    auto channelDevice = grpc::CreateChannel(urlDevice.c_str(), credDevice);
    auto channelDeviceAsync = grpc::CreateChannel(urlDeviceAsync.c_str(), credDeviceAsync);

    {
        std::unique_lock<std::mutex> lock(mtx);

        channels[tlinsChannelsManager::DEFAULT_CHANNEL_ASTRO] = channelAstro;
        channels[tlinsChannelsManager::DEFAULT_CHANNEL_DEVICE] = channelDevice;
        channels[tlinsChannelsManager::DEFAULT_CHANNEL_DEVICE_ASYNC] = channelDeviceAsync;

        channelsCred[tlinsChannelsManager::DEFAULT_CHANNEL_ASTRO] = credAstro;
        channelsCred[tlinsChannelsManager::DEFAULT_CHANNEL_DEVICE] = credDevice;
        channelsCred[tlinsChannelsManager::DEFAULT_CHANNEL_DEVICE_ASYNC] = credDeviceAsync;
    }
}

void tlinsChannelsManager::remove(std::string& name)
{
    std::unique_lock<std::mutex> lock(mtx);
    channels.erase(name);
    channelsCred.erase(name);
}

void tlinsChannelsManager::removeAll()
{
    std::unique_lock<std::mutex> lock(mtx);
    channels.clear();
    channelsCred.clear();
}

void tlinsChannelsManager::removeDefault()
{
    remove(tlinsChannelsManager::DEFAULT_CHANNEL_ASTRO);
    remove(tlinsChannelsManager::DEFAULT_CHANNEL_DEVICE);
    remove(tlinsChannelsManager::DEFAULT_CHANNEL_DEVICE_ASYNC);
}

tlinsChannelsManager::~tlinsChannelsManager()
{
    removeAll();
}

//
// -------------------------------
//
tlinsConnectionsSet& tlinsConnectionsSet::getCurrentInstance()
{
    static tlinsConnectionsSet instance { tlinsChannelsManager::DEFAULT_CHANNEL_DEVICE,
        tlinsChannelsManager::DEFAULT_CHANNEL_DEVICE_ASYNC,
        tlinsChannelsManager::DEFAULT_CHANNEL_ASTRO };
    return instance;
}

void tlinsConnectionsSet::updateChannels(std::string move_,
    std::string moveAsync_,
    std::string astro_)
{
    std::unique_lock<std::mutex> lock(mtx);

    moveEngineConnection = move_;
    moveAsyncEngineConnection = moveAsync_;
    astroEngineConnection = astro_;
}

std::tuple<std::shared_ptr<grpc::Channel>, std::shared_ptr<grpc::Channel>, std::shared_ptr<grpc::Channel>> tlinsConnectionsSet::getChannels()
{
    std::shared_ptr<grpc::Channel> move_;
    std::shared_ptr<grpc::Channel> moveAsync_;
    std::shared_ptr<grpc::Channel> astro_;

    auto& mgr = tlinsChannelsManager::instance();

    if (!mgr.getChannel(move_, moveEngineConnection))
        throw tlinsUIException(tlinsUIException::ERROR_INVALID_PARAMETER, "No " + moveEngineConnection + " channel");

    if (!mgr.getChannel(moveAsync_, moveAsyncEngineConnection))
        throw tlinsUIException(tlinsUIException::ERROR_INVALID_PARAMETER, "No " + moveAsyncEngineConnection + " channel");

    if (!mgr.getChannel(astro_, astroEngineConnection))
        throw tlinsUIException(tlinsUIException::ERROR_INVALID_PARAMETER, "No " + astroEngineConnection + " channel");

    return std::tuple<std::shared_ptr<grpc::Channel>, std::shared_ptr<grpc::Channel>, std::shared_ptr<grpc::Channel>> { move_, moveAsync_, astro_ };
}

tlinsConnectionsSet& tlinsConnectionsSet::operator=(const tlinsConnectionsSet& v)
{
    moveEngineConnection = v.moveEngineConnection;
    moveAsyncEngineConnection = v.moveAsyncEngineConnection;
    astroEngineConnection = v.astroEngineConnection;
    return *this;
}

tlinsConnectionsSet::tlinsConnectionsSet(const tlinsConnectionsSet& v)
{
    moveEngineConnection = v.moveEngineConnection;
    moveAsyncEngineConnection = v.moveAsyncEngineConnection;
    astroEngineConnection = v.astroEngineConnection;
}

tlinsConnectionsSet::tlinsConnectionsSet(std::string move_,
    std::string moveAsync_,
    std::string astro_)
    : moveEngineConnection { move_ }
    , moveAsyncEngineConnection { moveAsync_ }
    , astroEngineConnection { astro_ }
{
}

//
// ---------------------
//

tlinsConnectionContext::tlinsConnectionContext(const std::string& urlDevice, const std::string& urlDeviceAsync, const std::string& urlAstro)
{
    // Kanaly
    std::shared_ptr<grpc::Channel> channelAstro = grpc::CreateChannel(urlAstro.c_str(), grpc::InsecureChannelCredentials());
    std::shared_ptr<grpc::Channel> channelDevice = grpc::CreateChannel(urlDevice.c_str(), grpc::InsecureChannelCredentials());
    std::shared_ptr<grpc::Channel> channelDeviceAsync = grpc::CreateChannel(urlDeviceAsync.c_str(), grpc::InsecureChannelCredentials());

    device = std::unique_ptr<tlinsMoveServerInterface>(new tlinsMoveServerInterface { channelDevice, channelDeviceAsync });
    astro = std::unique_ptr<tlinsAstroEngineInterface>(new tlinsAstroEngineInterface { channelAstro });
}

tlinsConnectionContext::~tlinsConnectionContext()
{
}

bool tlinsConnectionsManager::createChannel(const std::string& url,
    std::shared_ptr<grpc::Channel>& channel,
    std::shared_ptr<grpc::ChannelCredentials>& cred)
{
    cred = grpc::InsecureChannelCredentials();
    if (!cred)
        return false;

    channel = grpc::CreateChannel(url, cred);
    if (!channel) {
        cred.reset();
        return false;
    }
    return true;
}

void tlinsConnectionsManager::setConnection(const std::string& key, const std::string& urlDevice, const std::string& urlDeviceAsync, const std::string& urlAstro)
{
    std::unique_lock<std::mutex> lock(mtx);

    try {
        auto ptr = std::make_shared<tlinsConnectionContext>(urlDevice, urlDeviceAsync, urlAstro);
        connections[key.c_str()].reset();
        connections[key.c_str()] = ptr;
    } catch (...) {
        throw;
    }
}

std::shared_ptr<tlinsConnectionContext> tlinsConnectionsManager::getConnection(const std::string& key)
{
    std::unique_lock<std::mutex> lock(mtx);

    if (connections.find(key.c_str()) == connections.end())
        return std::shared_ptr<tlinsConnectionContext>(nullptr);
    return connections[key.c_str()];
}

bool tlinsConnectionsManager::hasConnection(const std::string& key) const
{
    return connections.find(key.c_str()) != connections.end();
}

void tlinsConnectionsManager::removeConnection(const std::string& key)
{
    std::unique_lock<std::mutex> lock(mtx);
    connections.erase(key.c_str());
}

tlinsConnectionsManager::tlinsConnectionsManager()
{
}

tlinsConnectionsManager& tlinsConnectionsManager::getInstance()
{
    static tlinsConnectionsManager instance {};
    return instance;
}

tlinsConnectionsManager::~tlinsConnectionsManager()
{
}

}
