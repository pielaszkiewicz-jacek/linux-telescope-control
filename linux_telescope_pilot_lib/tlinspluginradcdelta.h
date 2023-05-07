#ifndef TLINSPLUGINRADCDELTA_H
#define TLINSPLUGINRADCDELTA_H

#include "tlinsshortcutsmanager.h"

namespace tlinsAstroPilot
{

class tlinsPluginRaDcDelta : public tlinsShortCutInterface
{
private:
	enum class Axis
	{
		RA = 1,
		DC = 2
	};

	std :: string name;
	std :: vector<int> keys;
	std :: string cfg;

	double raValue;
	double dcValue;

	Axis axis;

private:
    void set();

public:
    // Joistick
    virtual void callback(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &);
    virtual void callbackRel(const std::list<TlinsAstroBase :: tlinsJoystick :: keyStatusInfo> &, const TlinsAstroBase :: tlinsJoystick :: keyStatusInfo &);

    virtual void callback();
	virtual void release();

	virtual std :: string getName()
	{
		return name;
	}

	virtual const std :: vector<int> &getKeys()
	{
		return keys;
	}

	tlinsPluginRaDcDelta( const std :: string &name_,
	                      const std :: vector<int> &keys_,
	                      const std :: string &cfg );

	tlinsPluginRaDcDelta &operator=( const tlinsPluginRaDcDelta &v ) = default;
	tlinsPluginRaDcDelta() = delete;

	virtual ~tlinsPluginRaDcDelta();
};

class tlinsPluginRaDcDeltaFactory : public tlinsShortCutFactoryInterface
{
public:
    virtual std :: shared_ptr<tlinsShortCutInterface> createInstance( const TlinsAstroBase ::tlinsKeysSortcutType type,
                                                                      const TlinsAstroBase :: tlinsKeysSortcutSubType subType,
                                                                      const std :: string name,
	                                                                  const std :: string &cfg,
	                                                                  const TlinsAstroBase :: tlinsPilotShortcutsDefinitionValidMode mode,
	                                                                  const std :: vector<int> &keys_ ) noexcept;

	tlinsPluginRaDcDeltaFactory() = default;
	virtual ~tlinsPluginRaDcDeltaFactory();
};

};

#endif // TLINSPLUGINRADCDELTA_H
