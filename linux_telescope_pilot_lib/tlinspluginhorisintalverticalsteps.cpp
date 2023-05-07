#include "tlinspluginhorisintalverticalsteps.h"
#include <tlinsserverstatusinfo.h>
#include <tlinsconfiguration.h>
#include <tlinsastrouibase.h>
#include "tlinspluginsstate.h"
#include <tlinsuiexception.h>
#include <QJsonDocument>

#include <QDebug>

namespace tlinsAstroPilot
{

class tlinsPluginHorisintalVerticalStepsMoveRequest : public TlinsAstroBase :: tlinsCommunicationThreadRequest
{
private:
    class moveCb : public tlinsMoveServerInterface :: tlinsMoveRequestConfirmation
    {
    private:
        tlinsPluginHorisintalVerticalStepsMoveRequest &parent;

    public:
        void process(const tlins :: tlinsRpcConfirmationStatus &status);
        bool release();
        moveCb( tlinsPluginHorisintalVerticalStepsMoveRequest &parent_ ) : parent{ parent_ }
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

    tlinsPluginHorisintalVerticalStepsMoveRequest( std :: unique_ptr<tlinsMoveServerInterface :: MoveRequestDevice> &ptr );
    virtual ~tlinsPluginHorisintalVerticalStepsMoveRequest();
};

//
// ---------------------------------------------
// ---------------------------------------------
// ---------------------------------------------
//
void tlinsPluginHorisintalVerticalSteps :: callback(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &)
{
    //
    // Weryfikacja stanu w ktorym znajduje sie kontroler
    //
    bool isAstro = false;
    bool isTrackingEnabled = false;

    // Odczyt konfiguracji oi aktualnego stanu
    auto &stateInfo = tlinsPluginsState :: getInstance();

    // Okreslenie stanu kontrolera
    TlinsAstroBase ::tlinsAstroBase::getAstroStaetInfo(isAstro, isTrackingEnabled);

    double vX = 0.0;
    double vY = 0.0;
    double distanceX = 0.0;
    double distanceY = 0.0;

    if(!isAstro)
    {
        //
        // 1. Predkosci
        //
        if(mode == TlinsAstroBase :: tlinsAstroBase :: Mode ::STEPS )
        {
            vX = stateInfo.getXStepsSpeed();
            vY = stateInfo.getYStepsSpeed();

            distanceX = stateInfo.getXStepsDelta();
            distanceX = stateInfo.getYStepsDelta();
        }
        else
        {
            vX = stateInfo.getXDegrisSpeed();
            vY = stateInfo.getYDegrisSpeed();

            distanceX = stateInfo.getXDegrisDelta();
            distanceY = stateInfo.getYDegrisDelta();
        }
    }
    else
    {
        // Predkosc w trybie astro
        vX = stateInfo.getRaSpeed();
        vY = stateInfo.getDcSpeed();

        distanceX = stateInfo.getRaDelta();
        distanceY = stateInfo.getDcDelta();

        qDebug() << "RA DIS = " << distanceX;
        qDebug() << "RD DIS = " << distanceY;
    }

    TlinsAstroBase :: tlinsAstroBase :: distanceRequestMove( aX, aY,
                                isAstro,
                                leftX ? distanceX * -1.0 : distanceX,
                                leftY ? distanceY * -1.0 : distanceY, vX, vY, mode );
}

void tlinsPluginHorisintalVerticalSteps :: callbackRel(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &)
{
}

void tlinsPluginHorisintalVerticalSteps :: defaultEnter(const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &)
{
}

void tlinsPluginHorisintalVerticalSteps :: defaultRelease(const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &)
{
}

void tlinsPluginHorisintalVerticalSteps :: callback()
{
    std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> l;
    callback(std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo>{},
             TlinsAstroBase :: tlinsJoystick :: keyStatusInfo{});
}

void tlinsPluginHorisintalVerticalSteps :: release()
{
}

//
// Konfiguracja
//

/*

  {
     "axis":"X",
     "mode":"steps"|"degris"|"astro"
     "direction":"left"|"right"
  }

 */

tlinsPluginHorisintalVerticalSteps :: tlinsPluginHorisintalVerticalSteps( const std :: string &name_,
                                                                          const std :: vector<int> &keys_,
                                                                          const std :: string &cfg ) :
    name{name_},
    keys{keys_}
{
    QJsonDocument doc = QJsonDocument :: fromJson( QString :: fromStdString( cfg ).toUtf8() );

    // Os
    {
        QJsonValue v = doc[QString("axis")];
        if( !v.isString() )
        {
            // Przekazana wartosc nie jest typu double
            __THROW__( TlinsAstroBase :: tlinsUIException( TlinsAstroBase :: tlinsUIException :: ERROR_INVALID_PARAMETER, "Parameter value is not a string" ) );
        }

        aX = false;
        aY = false;
        if(v.toString().toUpper() == "X")
            aX = true;
        else if(v.toString().toUpper() == "Y")
            aY = true;
        else
        {
            // Niezanan nazwa osi
            __THROW__( TlinsAstroBase :: tlinsUIException( TlinsAstroBase :: tlinsUIException :: ERROR_INVALID_PARAMETER, "Unknown Axis" ) );
        }
    }

    // Tryb
    {
        QJsonValue v = doc[QString("mode")];
        if( !v.isString() )
        {
            // Przekazana wartosc nie jest typu double
            __THROW__( TlinsAstroBase :: tlinsUIException( TlinsAstroBase :: tlinsUIException :: ERROR_INVALID_PARAMETER, "Parameter value is not a string" ) );
        }

        if(v.toString().toUpper() == "STEPS")
            mode = TlinsAstroBase :: tlinsAstroBase :: Mode :: STEPS;
        else if(v.toString().toUpper() == "DEGRIS")
            mode = TlinsAstroBase :: tlinsAstroBase :: Mode :: DEGRIS;
        else if(v.toString().toUpper() == "ASTRO")
            mode = TlinsAstroBase :: tlinsAstroBase :: Mode :: ASTRO;
        else
        {
            // Niezanan nazwa osi
            __THROW__( TlinsAstroBase :: tlinsUIException( TlinsAstroBase :: tlinsUIException :: ERROR_INVALID_PARAMETER, "Unknown mode" ) );
        }
    }

    // Kierunek
    {
        leftX = false;
        leftY = false;

        bool isLeft = false;
        QJsonValue v = doc[QString("direction")];
        if( !v.isString() )
        {
            // Przekazana wartosc nie jest typu double
            __THROW__( TlinsAstroBase :: tlinsUIException( TlinsAstroBase :: tlinsUIException :: ERROR_INVALID_PARAMETER, "Parameter value is not a string" ) );
        }

        if(v.toString().toUpper() == "LEFT")
            isLeft = true;
        else if(v.toString().toUpper() == "RIGHT")
            isLeft = false;
        else
        {
            // Niezanan nazwa osi
            __THROW__( TlinsAstroBase :: tlinsUIException( TlinsAstroBase :: tlinsUIException :: ERROR_INVALID_PARAMETER, "Unknown direction" ) );
        }

        if(aX) {
            leftX = isLeft;
        }

        if(aY) {
            leftY = isLeft;
        }
    }
}

//
// -----------------------------------------------
//
std :: shared_ptr<tlinsShortCutInterface> tlinsPluginHorisintalVerticalStepsFactory :: createInstance( const TlinsAstroBase ::tlinsKeysSortcutType,
                                                                                                       const TlinsAstroBase :: tlinsKeysSortcutSubType,
                                                                                                       const std :: string name,
                                                                                                       const std :: string &cfg,
                                                                                                       const TlinsAstroBase :: tlinsPilotShortcutsDefinitionValidMode,
                                                                                                       const std :: vector<int> &keys_ ) noexcept
{
    return std :: shared_ptr<tlinsShortCutInterface>{ new tlinsPluginHorisintalVerticalSteps{ name, keys_, cfg } };
}

tlinsPluginHorisintalVerticalStepsFactory :: ~tlinsPluginHorisintalVerticalStepsFactory()
{
}

static tlinsShortcutsFactoryCreator<tlinsPluginHorisintalVerticalStepsFactory> __creator__{"horisintal-vertical-steps"};

};
