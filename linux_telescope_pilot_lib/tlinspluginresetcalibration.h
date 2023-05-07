#ifndef TLINSPLUGINRESETCALIBRATION_H
#define TLINSPLUGINRESETCALIBRATION_H

#include "tlinsshortcutsmanager.h"

namespace tlinsAstroPilot
{

class tlinsPluginResetCalibration : public tlinsShortCutInterface
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

	tlinsPluginResetCalibration( const std :: string &name_,
	                      const std :: vector<int> &keys_,
	                      const std :: string &cfg );

	tlinsPluginResetCalibration &operator=( const tlinsPluginResetCalibration &v ) = default;
	tlinsPluginResetCalibration() = delete;

	virtual ~tlinsPluginResetCalibration();
};

class tlinsPluginResetCalibrationFactory : public tlinsShortCutFactoryInterface
{
public:
    virtual std :: shared_ptr<tlinsShortCutInterface> createInstance( const TlinsAstroBase ::tlinsKeysSortcutType type,
                                                                      const TlinsAstroBase :: tlinsKeysSortcutSubType subType,
                                                                      const std :: string name,
	                                                                  const std :: string &cfg,
	                                                                  const TlinsAstroBase :: tlinsPilotShortcutsDefinitionValidMode mode,
	                                                                  const std :: vector<int> &keys_ ) noexcept;

	tlinsPluginResetCalibrationFactory() = default;
	virtual ~tlinsPluginResetCalibrationFactory();
};

};

#endif // TLINSPLUGINRESETCALIBRATION_H
