#include "tlinsjoystickeventhandler.h"
#include <tlinsuidatabasedefinition.h>
#include <tlinsBacktrace.hpp>
#include <monitors/tlinsKeysDefinition.hpp>

#include "tlinsshortcutsmanager.h"

#include <memory>
#include <functional>
#include <QDebug>

namespace tlinsAstroPilot
{

static std :: map<std :: string, int> kmap{
    {std::string{"Joy_Up"},         tlinsKeysDefinition::JOY_PAD_UP    },
    {std::string{"Joy_Left"},       tlinsKeysDefinition::JOY_PAD_LEFT  },
    {std::string{"Joy_Right"},      tlinsKeysDefinition::JOY_PAD_RIGHT },
    {std::string{"Joy_Down"},       tlinsKeysDefinition::JOY_PAD_DOWN  },
    {std::string{"Joy_Select"},     tlinsKeysDefinition::JOY_KEY_SELECT},
    {std::string{"Joy_Start"},      tlinsKeysDefinition::JOY_KEY_START },
    {std::string{"Joy_L11"},        tlinsKeysDefinition::JOY_KEY_L1    },
    {std::string{"Joy_L12"},        tlinsKeysDefinition::JOY_KEY_L2    },
    {std::string{"Joy_R11"},        tlinsKeysDefinition::JOY_KEY_R1    },
    {std::string{"Joy_R12"},        tlinsKeysDefinition::JOY_KEY_R2    },
    {std::string{"Joy_1"},          tlinsKeysDefinition::JOY_KEY_1     },
    {std::string{"Joy_2"},          tlinsKeysDefinition::JOY_KEY_2     },
    {std::string{"Joy_3"},          tlinsKeysDefinition::JOY_KEY_3     },
    {std::string{"Joy_4"},          tlinsKeysDefinition::JOY_KEY_4     },
    {std::string{"Joy_Main_Left"},  tlinsKeysDefinition::JOY_LPAD      },
    {std::string{"Joy_Left_Pad"},   tlinsKeysDefinition::JOY_LPAD      },
    {std::string{"Joy_Main_Right"}, tlinsKeysDefinition::JOY_RPAD      },
    {std::string{"Joy_Right_Pad"},  tlinsKeysDefinition::JOY_RPAD      }
};

static void convertIntoNumbers( const std :: vector<std :: string> in, std :: vector<int> &out )
{
    for( auto &inIter: in )
    {
        qDebug() << "KEY = " << inIter.c_str();
        if( kmap.count( inIter ) != 0 ) {
            qDebug() << "KEY TRANS = " << kmap[inIter];
            out.push_back( kmap[inIter] );
        }
    }
}

void tlinsJoystickEventHandler :: applayConfiguration()
{
    TlinsAstroBase :: tlinsUIDatabase db;
    TlinsAstroBase :: tlinsUIDatabaseDefinition dbDef(db);

    //
    // Domyslny handler obslugi jostika. Jako domyslny "horisontal-vertical-move-increment"
    //
    auto &factoryInstance = tlinsShortcutsFactoriesManager :: getInstance();
    auto factory = factoryInstance.getFactory( "horisontal-vertical-move" );
    if( factory )
    {
        // Tworzenie instancji przez fabryke
        auto shortCutInstance = factory -> createInstance(TlinsAstroBase ::tlinsKeysSortcutType::JOYSTICK,
                                                          TlinsAstroBase :: tlinsKeysSortcutSubType::JOYSTICK_GAMEPAD,
                                                          "Default",
                                                          "{ \"axis\": \"vertical\", \"direction\": \"right\" }",  // Parametery nie sa istotne
                                                          TlinsAstroBase :: tlinsPilotShortcutsDefinitionValidMode :: BOTH,
                                                          std :: vector<int>{});   // Pusta lista skrutow

        std :: function<void (const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &)> defaultEnter = [shortCutInstance](const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &stat) {
            shortCutInstance -> defaultEnter(stat);
        };

        std :: function<void (const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &)> defaultRelease = [shortCutInstance](const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &stat) {
            shortCutInstance -> defaultRelease(stat);
        };

        // Rejestracja domyslnych funkcji obslugi
        joystickMapper.setDefaultHandlers(defaultEnter, defaultRelease);
    }

    std :: vector<TlinsAstroBase :: tlinsKeysSortcut> data;
    dbDef.selectShortcuts( data, TlinsAstroBase :: tlinsKeysSortcutType :: JOYSTICK );

    for( auto &item: data )
    {
        // Sekwencja klawiszy
        std :: vector<std :: string> keys;
        item.getActionKeys( keys );

        // Konfiguracja
        std :: string cfgJson{ item.getActionSettingsJson() };

        // Nazwa skrotu klawiszowego
        std :: string shortcutName{ item.getShortcutName() };

        TlinsAstroBase :: tlinsKeysSortcutType    type    = item.getType();
        TlinsAstroBase :: tlinsKeysSortcutSubType subType = item.getSubType();

        // Nazwa akcji
        std :: string actionName{ item.getActionName() };

        qDebug() << "Joystick Configuration : " <<  QString :: fromStdString( cfgJson );
        qDebug() << "Joystick Name          : " <<  QString :: fromStdString( shortcutName );
        qDebug() << "Joystick Action        : " <<  QString :: fromStdString( actionName );

        TlinsAstroBase :: tlinsPilotShortcutsDefinitionValidMode mode = item.getActionMode();

        auto &factoryInstance = tlinsShortcutsFactoriesManager :: getInstance();
        auto factory = factoryInstance.getFactory( actionName );
        if( !factory )
        {
            // Brak fabryki
            TLINS_LOG_ERROR( "No factory for " + actionName );
            continue;
        }

        // Rejestracja nowego callbacka
        std :: vector<int> numKeys;
        convertIntoNumbers( keys, numKeys );

        // Tworzenie instancji przez fabryke
        auto shortCutInstance = factory -> createInstance(type,
                                                          subType,
                                                          shortcutName,
                                                          cfgJson,
                                                          mode,
                                                          numKeys);
        if( !shortCutInstance )
        {
            TLINS_LOG_ERROR( "Error create shortcut instance for " + actionName );
            continue;
        }

        // Rejestracja w managerze
        tlinsShortcutsManager :: getInstance().addShortcut( shortCutInstance );

        std::function<void()> fun = [shortCutInstance]
            {
                shortCutInstance -> callback();
            };
        std::function<void()> funRelease = [shortCutInstance]
            {
                shortCutInstance -> release();
            };

        std :: function<void (const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &)> joyFun = [shortCutInstance](const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &a, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &b)
            {
                shortCutInstance -> callback(a,b);
            };
        std :: function<void (const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &)> joyFunRel = [shortCutInstance](const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &a, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &b)
            {
                shortCutInstance -> callbackRel(a,b);
            };

        switch(subType)
        {
        case TlinsAstroBase :: tlinsKeysSortcutSubType ::JOYSTICK_KEYS:
            joystickMapper.addKeyboardCallback( shortCutInstance -> getKeys(),
                                                fun,
                                                funRelease);
            break;

        case TlinsAstroBase :: tlinsKeysSortcutSubType ::JOYSTICK_GAMEPAD:
            joystickMapper.addEventHandler( shortCutInstance -> getKeys(), joyFun, joyFunRel );
            break;

        case TlinsAstroBase :: tlinsKeysSortcutSubType ::ANY:
            break;
        }

        if(item.getDefaultHandler() == TlinsAstroBase :: tlinsDefaultHandler :: YES)
        {
            std :: function<void (const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &)> defaultEnter = [shortCutInstance](const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &stat)
            {
                shortCutInstance -> defaultEnter(stat);
            };

            std :: function<void (const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &)> defaultRelease = [shortCutInstance](const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &stat)
            {
                shortCutInstance -> defaultRelease(stat);
            };

            // Rejkestracja domyslnych funkcji obslugi
            joystickMapper.setDefaultHandlers(defaultEnter, defaultRelease);
        }
    }
}

void tlinsJoystickEventHandler :: operator()( const tlinsSystemServiceClient :: Event &ev )
{
    // Przetwarzanie zdarzenia
    joystickMapper.event(ev.type, ev.value, ev.number);
}

tlinsJoystickEventHandler :: tlinsJoystickEventHandler( std ::shared_ptr<grpc ::Channel> &channel )
{
    using namespace std::placeholders;

    // Rejestracja obiektu nasluchujacego na zdarzenia z klawiatury
    std :: vector<tlinsSystemServiceClient :: EventType> evs{ tlinsSystemServiceClient :: EventType :: JOYSTICK };
    tlinsSystemServiceClient *ptr = new tlinsSystemServiceClient( channel, evs, std::bind(&tlinsJoystickEventHandler::operator(), this, _1) );
    eventsReader = std :: move( std :: unique_ptr<tlinsSystemServiceClient>{ ptr } );

    // Rejestracja zdefiniowanych skrotow klawiszowych
    applayConfiguration();
}

tlinsJoystickEventHandler :: ~tlinsJoystickEventHandler()
{
}

};
