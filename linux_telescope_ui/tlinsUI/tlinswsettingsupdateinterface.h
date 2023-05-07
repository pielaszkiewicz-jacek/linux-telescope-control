#ifndef TLINSWSETTINGSUPDATEINTERFACE_H
#define TLINSWSETTINGSUPDATEINTERFACE_H

class tlinsWSettingsUpdateInterface {
public:
    tlinsWSettingsUpdateInterface();

    virtual void saveDefault() = 0;
    virtual void restore() = 0;
    virtual void save() = 0;

    virtual ~tlinsWSettingsUpdateInterface() {};
};

#endif // TLINSWSETTINGSUPDATEINTERFACE_H
