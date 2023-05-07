#ifndef TLINSPLUGINUTILSMOVEREQUEST_H
#define TLINSPLUGINUTILSMOVEREQUEST_H

#include <tlinscommunicationthread.h>
#include <tlinsastrouibase.h>

namespace tlinsAstroPilot
{

class tlinsPluginUtilsMoveRequest : public TlinsAstroBase :: tlinsCommunicationThreadRequest
{
private:
    class moveCb : public tlinsMoveServerInterface :: tlinsMoveRequestConfirmation
    {
    private:
        tlinsPluginUtilsMoveRequest &parent;

    public:
        void process(const tlins :: tlinsRpcConfirmationStatus &status);
        bool release();
        moveCb( tlinsPluginUtilsMoveRequest &parent_ ) : parent{ parent_ }
        {
        }
        virtual ~moveCb() = default;
    };

    std :: shared_ptr<tlinsMoveServerInterface :: tlinsMoveRequestConfirmation> callback;
    std :: shared_ptr<TlinsAstroBase :: tlinsConnectionContext> connection;

private:
    std :: unique_ptr<tlinsMoveServerInterface :: MoveRequestDevice> request;

public:
    void confirm();

    virtual void operator()() noexcept;
    virtual bool isAsynchronuus();
    virtual std :: string name()
    {
        // TODO
        return "";
    }

    tlinsPluginUtilsMoveRequest( std :: unique_ptr<tlinsMoveServerInterface :: MoveRequestDevice> &ptr );
    virtual ~tlinsPluginUtilsMoveRequest();
};

//
// --------------------------------------------
// --------------------------------------------
//

class tlinsPluginUtilsStopTracking : public TlinsAstroBase :: tlinsCommunicationThreadRequest
{
private:
    std :: shared_ptr<TlinsAstroBase :: tlinsConnectionContext> connection;

public:
    void confirm();

    virtual void operator()() noexcept;
    virtual bool isAsynchronuus();

    virtual std :: string name()
    {
        // TODO
        return "";
    }

    tlinsPluginUtilsStopTracking();
    virtual ~tlinsPluginUtilsStopTracking();
};

};

#endif // TLINSPLUGINUTILSMOVEREQUEST_H
