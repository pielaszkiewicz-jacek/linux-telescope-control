#ifndef TLINSPLUGINCLOSEVELOCITYMEASURMENT_H
#define TLINSPLUGINCLOSEVELOCITYMEASURMENT_H

#include "tlinsshortcutsmanager.h"

class tlinsPluginCloseVelocityMeasurment : public tlinsShortCutInterface
{
private:
	std :: string name;
	std :: vector<int> keys;
	std :: string cfg;

public:
    virtual void callback(int, int, int);
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

    tlinsPluginCloseVelocityMeasurment( const std :: string &name_,
                                        const std :: vector<int> &keys_,
                                        const std :: string &cfg );

	tlinsPluginCloseVelocityMeasurment &operator=( const tlinsPluginCloseVelocityMeasurment &v ) = default;
	tlinsPluginCloseVelocityMeasurment() = delete;

	virtual ~tlinsPluginCloseVelocityMeasurment();
};

class tlinsPluginCloseVelocityMeasurmentFactory : public tlinsShortCutFactoryInterface
{
public:
    virtual std :: shared_ptr<tlinsShortCutInterface> createInstance( const TlinsAstroBase ::tlinsKeysSortcutType type,
                                                                      const TlinsAstroBase :: tlinsKeysSortcutSubType subType,
                                                                      const std :: string name,
	                                                                  const std :: string &cfg,
	                                                                  const TlinsAstroBase :: tlinsPilotShortcutsDefinitionValidMode mode,
	                                                                  const std :: vector<int> &keys_ ) noexcept;

	tlinsPluginCloseVelocityMeasurmentFactory() = default;
	virtual ~tlinsPluginCloseVelocityMeasurmentFactory();
};

#endif // TLINSPLUGINCLOSEVELOCITYMEASURMENT_H
