#ifndef TLINSPLUGINSETREFERENCEOBJECT_H
#define TLINSPLUGINSETREFERENCEOBJECT_H

#include "tlinsshortcutsmanager.h"

namespace tlinsAstroPilot
{

class tlinsPluginSetReferenceObject : public tlinsShortCutInterface
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

	tlinsPluginSetReferenceObject( const std :: string &name_,
	                               const std :: vector<int> &keys_,
	                               const std :: string &cfg );

	tlinsPluginSetReferenceObject &operator=( const tlinsPluginSetReferenceObject &v ) = default;
	tlinsPluginSetReferenceObject() = delete;

	virtual ~tlinsPluginSetReferenceObject();
};

class tlinsPluginSetReferenceObjectFactory : public tlinsShortCutFactoryInterface
{
public:
    virtual std :: shared_ptr<tlinsShortCutInterface> createInstance( const TlinsAstroBase ::tlinsKeysSortcutType type,
                                                                      const TlinsAstroBase :: tlinsKeysSortcutSubType subType,
                                                                      const std :: string name,
	                                                                  const std :: string &cfg,
	                                                                  const TlinsAstroBase :: tlinsPilotShortcutsDefinitionValidMode mode,
	                                                                  const std :: vector<int> &keys_ ) noexcept;

	tlinsPluginSetReferenceObjectFactory() = default;
	virtual ~tlinsPluginSetReferenceObjectFactory();
};

};

#endif // TLINSPLUGINSETREFERENCEOBJECT_H
