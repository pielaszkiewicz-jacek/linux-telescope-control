#ifndef TLINSPLUGINRADCINCREMENT_H
#define TLINSPLUGINRADCINCREMENT_H

#include <tlinscommunicationthread.h>
#include "tlinsshortcutsmanager.h"

namespace tlinsAstroPilot
{

//
// Klasy implementuja wtyczke ktora realizauje przemieszczernie dla osi RA.
//
// --------------
//
// Os:
//   RA
// Tryb:
//   Astro
// Parametery:
//   direction - kierunek przemieszczenia
//   axis
//
class tlinsPluginRaDcIncrement : public tlinsShortCutInterface
{
public:
	enum class DIRECTION { LEFT = 1, RIGHT = 2 };
	enum class AXIS { RA = 1, DC = 2 };

private:
	std :: string name;
	std :: vector<int> keys;
	std :: string cfg;
	DIRECTION  direction;
	AXIS axis;

public:
    // Joistick
    virtual void callback(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &);
    virtual void callbackRel(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &);

	virtual void callback();
	virtual void release();

	virtual std :: string getName();

	virtual const std :: vector<int> &getKeys();

	tlinsPluginRaDcIncrement( const std :: string &name_,
	                    const std :: vector<int> &keys_,
	                    const std :: string &cfg );

	tlinsPluginRaDcIncrement &operator=( const tlinsPluginRaDcIncrement &v ) = default;
	tlinsPluginRaDcIncrement() = delete;

	virtual ~tlinsPluginRaDcIncrement();
};

class tlinsPluginRaDcIncrementFactory : public tlinsShortCutFactoryInterface
{
public:
    virtual std :: shared_ptr<tlinsShortCutInterface> createInstance( const TlinsAstroBase ::tlinsKeysSortcutType type,
                                                                      const TlinsAstroBase :: tlinsKeysSortcutSubType subType,
                                                                      const std :: string name,
	                                                                  const std :: string &cfg,
	                                                                  const TlinsAstroBase :: tlinsPilotShortcutsDefinitionValidMode mode,
	                                                                  const std :: vector<int> &keys_ ) noexcept;

	tlinsPluginRaDcIncrementFactory() = default;
	virtual ~tlinsPluginRaDcIncrementFactory();
};

};

#endif // TLINSPLUGINRAINCREMENT_H
