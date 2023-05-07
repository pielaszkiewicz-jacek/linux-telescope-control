#ifndef TLINSPLUGINHORISONTALVERTICALSPEEDDELTA_H
#define TLINSPLUGINHORISONTALVERTICALSPEEDDELTA_H

#include "tlinsshortcutsmanager.h"

namespace tlinsAstroPilot
{

class tlinsPluginHorisontalVerticalSpeedDelta : public tlinsShortCutInterface
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

	tlinsPluginHorisontalVerticalSpeedDelta( const std :: string &name_,
	                                    const std :: vector<int> &keys_,
	                                    const std :: string &cfg );

	tlinsPluginHorisontalVerticalSpeedDelta &operator=( const tlinsPluginHorisontalVerticalSpeedDelta &v ) = default;
	tlinsPluginHorisontalVerticalSpeedDelta() = delete;

	virtual ~tlinsPluginHorisontalVerticalSpeedDelta();
};

class tlinsPluginHorisontalVerticalSpeedDeltaFactory : public tlinsShortCutFactoryInterface
{
public:
    virtual std :: shared_ptr<tlinsShortCutInterface> createInstance( const TlinsAstroBase ::tlinsKeysSortcutType type,
                                                                      const TlinsAstroBase :: tlinsKeysSortcutSubType subType,
                                                                      const std :: string name,
	                                                                  const std :: string &cfg,
	                                                                  const TlinsAstroBase :: tlinsPilotShortcutsDefinitionValidMode mode,
	                                                                  const std :: vector<int> &keys_ ) noexcept;

	tlinsPluginHorisontalVerticalSpeedDeltaFactory() = default;
	virtual ~tlinsPluginHorisontalVerticalSpeedDeltaFactory();
};

};

#endif // TLINSPLUGINHORISONTALVERTICALSPEEDDELTA_H
