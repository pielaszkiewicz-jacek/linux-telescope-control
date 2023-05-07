#ifndef TLINSPLUGINCLOSECALIBRATION_H
#define TLINSPLUGINCLOSECALIBRATION_H

#include "tlinsshortcutsmanager.h"

namespace tlinsAstroPilot
{

class tlinsPluginCloseCalibration : public tlinsShortCutInterface
{
private:
	std :: string name;
	std :: vector<int> keys;
	std :: string cfg;

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

    tlinsPluginCloseCalibration( const std :: string &name_,
                                 const std :: vector<int> &keys_,
                                 const std :: string &cfg );

	tlinsPluginCloseCalibration &operator=( const tlinsPluginCloseCalibration &v ) = default;
	tlinsPluginCloseCalibration() = delete;

	virtual ~tlinsPluginCloseCalibration();
};

class tlinsPluginCloseCalibrationFactory : public tlinsShortCutFactoryInterface
{
public:
    virtual std :: shared_ptr<tlinsShortCutInterface> createInstance( const TlinsAstroBase ::tlinsKeysSortcutType type,
                                                                      const TlinsAstroBase :: tlinsKeysSortcutSubType subType,
                                                                      const std :: string name,
	                                                                  const std :: string &cfg,
	                                                                  const TlinsAstroBase :: tlinsPilotShortcutsDefinitionValidMode mode,
	                                                                  const std :: vector<int> &keys_ ) noexcept;

	tlinsPluginCloseCalibrationFactory() = default;
	virtual ~tlinsPluginCloseCalibrationFactory();
};

};

#endif // TLINSPLUGINCLOSECALIBRATION_H
