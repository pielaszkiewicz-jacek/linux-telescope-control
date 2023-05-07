#ifndef TLINSPLUGINVERITCALSTEPSDELTA_H
#define TLINSPLUGINVERITCALSTEPSDELTA_H

#include "tlinsshortcutsmanager.h"
#include <string>
#include <vector>
#include <memory>

//
// Klasy implementuja wtyczke ktora pozwala modyfkowac krok przemieszczenia.
//
// --------------
//
// Os:
//   Os pionowa
// Tryb:
//   Normal
// Parametery:
//   vertical-steps - krokm przemieszczenia
//

class tlinsPluginVeritcalStepsDelta : public tlinsShortCutInterface
{
private:
	std :: string name;
	std :: vector<int> keys;
	std :: string cfg;
	long deltaValue;

public:
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

	tlinsPluginVeritcalStepsDelta( const std :: string &name_,
	                            const std :: vector<int> &keys_,
	                            const std :: string &cfg );

	tlinsPluginVeritcalStepsDelta &operator=( const tlinsPluginVeritcalStepsDelta &v ) = default;
	tlinsPluginVeritcalStepsDelta() = delete;

	virtual ~tlinsPluginVeritcalStepsDelta();
};

class tlinsPluginVeritcalStepsDeltaFactory : public tlinsShortCutFactoryInterface
{
public:
	virtual std :: shared_ptr<tlinsShortCutInterface> createInstance( const std :: string name,
	                                                                  const std :: string &cfg,
	                                                                  const TlinsAstroBase :: tlinsPilotShortcutsDefinitionValidMode mode,
	                                                                  const std :: vector<int> &keys_ ) noexcept;

	tlinsPluginVeritcalStepsDeltaFactory() = default;
	virtual ~tlinsPluginVeritcalStepsDeltaFactory();

};

#endif // TLINSPLUGINVERITCALSTEPSDELTA_H
