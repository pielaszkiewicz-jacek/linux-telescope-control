#ifndef TLINSSHORTCUTSMANAGER_H
#define TLINSSHORTCUTSMANAGER_H

#include <tlinskeyboard.h>
#include <tlinspilotshortcutsdefinitionvalidmode.h>
#include <tlinskeyssortcut.h>
#include <tlinsjoystick.h>

#include <memory>
#include <mutex>
#include <map>

//
// Interfejs do obiektow realizujacych akcje
//

namespace tlinsAstroPilot
{

class tlinsShortCutInterface
{
private:
	std :: string action;
	std :: string name;
	std :: vector<int> keys;

public:
    virtual void callback(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &) = 0;
    virtual void callbackRel(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &) = 0;

    virtual void defaultEnter(const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &)
    {
    }

    virtual void defaultRelease(const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &)
    {
    }

    virtual void callback() = 0;
	virtual void release() = 0;
	virtual std :: string getName()  = 0;
	virtual const std :: vector<int> &getKeys()  = 0;

	virtual ~tlinsShortCutInterface();
};

//
// Menadrzer instancji obiektow skrutow
//
class tlinsShortcutsManager
{
private:
	std :: map<std :: string, std :: shared_ptr<tlinsShortCutInterface>> shortcuts;
	std :: mutex mtx;

public:
	std :: map<std :: string, std :: shared_ptr<tlinsShortCutInterface>> :: iterator begin();
	std :: map<std :: string, std :: shared_ptr<tlinsShortCutInterface>> :: iterator end();

	bool addShortcut( std :: shared_ptr<tlinsShortCutInterface> &obj );
	std :: shared_ptr<tlinsShortCutInterface> getShortcut( const std :: string &name );
	void clear();

	static tlinsShortcutsManager &getInstance();

	tlinsShortcutsManager( const tlinsShortcutsManager &v ) = delete;
	virtual ~tlinsShortcutsManager();

private:
	tlinsShortcutsManager();
};

//
// Menadzer obiektow bedacych fabrykami skrutow
//
class tlinsShortCutFactoryInterface
{
public:
    virtual std :: shared_ptr<tlinsShortCutInterface> createInstance( const TlinsAstroBase ::tlinsKeysSortcutType type,
                                                                      const TlinsAstroBase :: tlinsKeysSortcutSubType subType,
                                                                      const std :: string name,
                                                                      const std :: string &cfg,
                                                                      const TlinsAstroBase :: tlinsPilotShortcutsDefinitionValidMode mode,
                                                                      const std :: vector<int> &keys_ ) noexcept = 0;

    virtual ~tlinsShortCutFactoryInterface();
};

class tlinsShortcutsFactoriesManager
{
private:
	std :: map<std :: string, std :: shared_ptr<tlinsShortCutFactoryInterface>> factories;
	std :: mutex mtx;

public:
	bool addFactory( const std :: string &fName, std :: shared_ptr<tlinsShortCutFactoryInterface> &obj );
	std :: shared_ptr<tlinsShortCutFactoryInterface> getFactory( const std :: string &name );

	static tlinsShortcutsFactoriesManager &getInstance();

	tlinsShortcutsFactoriesManager( const tlinsShortcutsFactoriesManager &v ) = delete;
	virtual ~tlinsShortcutsFactoriesManager() = default;

private:
	tlinsShortcutsFactoriesManager() = default;
};

template<typename T>
struct tlinsShortcutsFactoryCreator
{
	tlinsShortcutsFactoryCreator( const std :: string &name )
	{
		std :: shared_ptr<tlinsShortCutFactoryInterface> ptr{ new T{} };
		tlinsShortcutsFactoriesManager :: getInstance().addFactory( name, ptr);
	}
};

};

#endif // TLINSSHORTCUTSMANAGER_H
