#ifndef TLINSCONNECTION_H
#define TLINSCONNECTION_H

#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>
#include <memory>
#include <mutex>
#include <tlinsAstroEngineInterface.hpp>
#include <tlinsInterfaceException.hpp>
#include <tlinsMoveServerInterface.hpp>
#include <tuple>

#define TLINS_CONNECTION_DEFAULT "__DEFAULT_CONNECTION__"

//
// -----------------------------------------------------------------------------
// Manager kanalow
// -----------------------------------------------------------------------------
//

namespace TlinsAstroBase {

class tlinsChannelsManager {
public:
    static std::string DEFAULT_CHANNEL_ASTRO;
    static std::string DEFAULT_CHANNEL_DEVICE;
    static std::string DEFAULT_CHANNEL_DEVICE_ASYNC;

private:
    std::mutex mtx;
    std::map<std::string, std::shared_ptr<grpc::Channel>> channels;
    std::map<std::string, std::shared_ptr<grpc::ChannelCredentials>> channelsCred;

public:
    bool getChannel(std::shared_ptr<grpc::Channel>& ch, const std::string& name)
    {
        std::unique_lock<std::mutex> lock(mtx);

        auto c = channels.find(name);
        if (c == channels.end())
            return false;

        ch = c->second;
        return true;
    }

private:
    tlinsChannelsManager();

public:
    static tlinsChannelsManager& instance()
    {
        static tlinsChannelsManager ins {};
        return ins;
    }

    bool addChannel(const std::string& name,
        const std::string& url);
    void addDefault();

    void remove(std::string& name);
    void removeAll();
    void removeDefault();

    virtual ~tlinsChannelsManager();
};

//
// -----------------------------------------------------------------------------
// Obiekt polaczenia
// -----------------------------------------------------------------------------
//
class tlinsConnectionsSet {
private:
    // Kanaly reprezentujace polczenie z silnikiem przemieszczenia
    std::string moveEngineConnection;
    std::string moveAsyncEngineConnection;
    std::string astroEngineConnection;

    // Mutex kontrolujacy biezacy
    std::mutex mtx;

public:
    // Instancja obiektu
    static tlinsConnectionsSet& getCurrentInstance();

    //
    void updateChannels(std::string move_,
        std::string moveAsync_,
        std::string astro_);

public:
    std::tuple<std::shared_ptr<grpc::Channel>, std::shared_ptr<grpc::Channel>, std::shared_ptr<grpc::Channel>> getChannels();

    tlinsConnectionsSet& operator=(const tlinsConnectionsSet& v);

    // Konstruktor i destuktor klasy
    tlinsConnectionsSet() = delete;
    tlinsConnectionsSet(const tlinsConnectionsSet& v);

    tlinsConnectionsSet(std::string move_,
        std::string moveAsync_,
        std::string astro_);

    virtual ~tlinsConnectionsSet() = default;
};

class tlinsConnectionContext {
public:
    std::unique_ptr<tlinsMoveServerInterface> device;
    std::unique_ptr<tlinsAstroEngineInterface> astro;

    const std::unique_ptr<tlinsMoveServerInterface>& getDevice()
    {
        return device;
    }

    const std::unique_ptr<tlinsAstroEngineInterface>& getAstro()
    {
        return astro;
    }

    tlinsConnectionContext(const std::string& urlDevice, const std::string& urlDeviceAsync, const std::string& urlAstro);
    virtual ~tlinsConnectionContext();
};

class tlinsConnectionsManager {
private:
    std::map<std::string, std::shared_ptr<tlinsConnectionContext>> connections;
    tlinsConnectionsManager();
    std::mutex mtx;

public:
    void setConnection(const std::string& key, const std::string& urlDevice, const std::string& urlDeviceAsync, const std::string& urlAstro);
    std::shared_ptr<tlinsConnectionContext> getConnection(const std::string& key);
    bool hasConnection(const std::string& key) const;
    void removeConnection(const std::string& key);

    static tlinsConnectionsManager& getInstance();
    static bool createChannel(const std::string& url,
        std::shared_ptr<grpc::Channel>& channel,
        std::shared_ptr<grpc::ChannelCredentials>& cred);
    virtual ~tlinsConnectionsManager();
};

}

#endif // TLINSCONNECTION_H
