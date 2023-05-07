#include "tlinsshortcutsmanager.h"

namespace tlinsAstroPilot
{

tlinsShortCutInterface :: ~tlinsShortCutInterface()
{
}

//
// -------------------------------------
//
std :: map<std :: string, std :: shared_ptr<tlinsShortCutInterface>> :: iterator tlinsShortcutsManager :: begin()
{
	return shortcuts.begin();
}

std :: map<std :: string, std :: shared_ptr<tlinsShortCutInterface>> :: iterator tlinsShortcutsManager :: end()
{
	return shortcuts.end();
}

bool tlinsShortcutsManager :: addShortcut( std :: shared_ptr<tlinsShortCutInterface> &obj )
{
	std::lock_guard<std::mutex> lock( mtx );

	if( shortcuts.count( obj -> getName() ) != 0 )
		return false;

	shortcuts[obj -> getName()] = obj;
	return true;
}

std :: shared_ptr<tlinsShortCutInterface> tlinsShortcutsManager :: getShortcut( const std :: string &name )
{
	std::lock_guard<std::mutex> lock( mtx );

	if( shortcuts.count( name ) != 0 )
		return std :: shared_ptr<tlinsShortCutInterface>{ nullptr };
	return shortcuts[name];
}

void tlinsShortcutsManager :: clear()
{
	std::lock_guard<std::mutex> lock( mtx );
	shortcuts.clear();
}

tlinsShortcutsManager &tlinsShortcutsManager :: getInstance()
{
	static tlinsShortcutsManager instance;
	return instance;
}

tlinsShortcutsManager :: ~tlinsShortcutsManager()
{
}

tlinsShortcutsManager :: tlinsShortcutsManager()
{
}

//addShortcut
// -------------------------------------
//
tlinsShortCutFactoryInterface :: ~tlinsShortCutFactoryInterface()
{
}

bool tlinsShortcutsFactoriesManager :: addFactory( const std :: string &fName,
                                                   std :: shared_ptr<tlinsShortCutFactoryInterface> &obj )
{
	std::lock_guard<std::mutex> lock( mtx );

	if( factories.count( fName ) != 0 )
		return false;

	factories[fName] = obj;
	return true;
}

std :: shared_ptr<tlinsShortCutFactoryInterface> tlinsShortcutsFactoriesManager :: getFactory( const std :: string &name )
{
	std::lock_guard<std::mutex> lock( mtx );

	if( factories.count( name ) == 0 )
		return std :: shared_ptr<tlinsShortCutFactoryInterface>{ nullptr };

	return factories[name];
}

tlinsShortcutsFactoriesManager &tlinsShortcutsFactoriesManager :: getInstance()
{
	static tlinsShortcutsFactoriesManager instance{};
	return instance;
}

};
