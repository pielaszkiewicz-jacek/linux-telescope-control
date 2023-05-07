#ifndef TLINSPLUGINHORISONTALVERTICALDELTA_H
#define TLINSPLUGINHORISONTALVERTICALDELTA_H

#include "tlinsshortcutsmanager.h"

namespace tlinsAstroPilot
{

class tlinsPluginHorisontalVerticalDelta : public tlinsShortCutInterface
{
private:
	enum class Axis
	{
		H = 1,
		V = 2
	};

	enum class Type
	{
		STEPS = 1,
		DEGRIS = 2
	};

	std :: string name;
	std :: vector<int> keys;
	std :: string cfg;

	long valueSteps;
	double valueDegris;

	Type type;
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

	tlinsPluginHorisontalVerticalDelta( const std :: string &name_,
	                                    const std :: vector<int> &keys_,
	                                    const std :: string &cfg );

	tlinsPluginHorisontalVerticalDelta &operator=( const tlinsPluginHorisontalVerticalDelta &v ) = default;
	tlinsPluginHorisontalVerticalDelta() = delete;

	virtual ~tlinsPluginHorisontalVerticalDelta();
};

class tlinsPluginHorisontalVerticalDeltaFactory : public tlinsShortCutFactoryInterface
{
public:
    virtual std :: shared_ptr<tlinsShortCutInterface> createInstance( const TlinsAstroBase ::tlinsKeysSortcutType type,
                                                                      const TlinsAstroBase :: tlinsKeysSortcutSubType subType,
                                                                      const std :: string name,
	                                                                  const std :: string &cfg,
	                                                                  const TlinsAstroBase :: tlinsPilotShortcutsDefinitionValidMode mode,
	                                                                  const std :: vector<int> &keys_ ) noexcept;

	tlinsPluginHorisontalVerticalDeltaFactory() = default;
	virtual ~tlinsPluginHorisontalVerticalDeltaFactory();
};

};

#endif // TLINSPLUGINHORISONTALVERTICALDELTA_H
