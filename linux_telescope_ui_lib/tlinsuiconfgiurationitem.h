#ifndef TLINSUICONFGIURATIONITEM_H
#define TLINSUICONFGIURATIONITEM_H

#include "tlinsuiexception.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

#define __MAX_NUMBER_VALUES__ 15

namespace TlinsAstroBase {

class tlinsUiConfgiurationItem {
public:
    struct itemValues {
    private:
        std::string values[__MAX_NUMBER_VALUES__];
        bool hasValue[__MAX_NUMBER_VALUES__];

    public:
        unsigned size() const
        {
            return __MAX_NUMBER_VALUES__;
        }

        bool setValue(const int idx, const std::string& v)
        {
            if ((unsigned)idx >= size())
                return false;
            values[idx] = v;
            hasValue[idx] = true;
            return true;
        }

        bool getValue(const int idx, std::string& v) const
        {
            if ((unsigned)idx >= size() || !hasValue[idx])
                return false;
            v = values[idx];
            return true;
        }

        itemValues& operator=(const itemValues& v)
        {
            for (int i = 0; (unsigned)i < size(); i++) {
                values[i] = v.values[i];
                hasValue[i] = v.hasValue[i];
            }
            return *this;
        }

        itemValues(const itemValues& v)
        {
            *this = v;
        }

        itemValues()
        {
            for (int i = 0; (unsigned)i < size(); i++) {
                values[i] = "";
                hasValue[i] = false;
            }
        }

        itemValues(const std::string& v)
        {
            for (int i = 0; (unsigned)i < size(); i++) {
                values[i] = "";
                hasValue[i] = false;
            }
            setValue(0, v);
        }

        virtual ~itemValues()
        {
        }
    };

private:
    // Grupa
    std::string groupName;

    // Parametr
    std::string parameter;

    // Wartosci parameteru
    itemValues value;

public:
    const std::string& getGroupName() const;
    const std::string& getParameter() const;
    bool getItemValue(int idx, std::string& v) const;

    int getMaxValuesCount() const
    {
        return __MAX_NUMBER_VALUES__;
    }

    void setGroupName(const std::string& name);
    void setParameter(const std::string name);

    void addItem(const itemValues& v);
    void setValues(const int idx, const std::string& v);
    void setValues(const itemValues& v);

public:
    tlinsUiConfgiurationItem();
    virtual ~tlinsUiConfgiurationItem();
};

class tlinsUiConfgiurationItemsCollection {
private:
    static std::map<std::string, std::shared_ptr<tlinsUiConfgiurationItem>> collection;

public:
    static bool addItem(std::shared_ptr<tlinsUiConfgiurationItem>& item);
    static bool getItem(const std::string& group, const std::string& paraName, std::shared_ptr<tlinsUiConfgiurationItem>& v);

    tlinsUiConfgiurationItemsCollection();
    virtual ~tlinsUiConfgiurationItemsCollection();
};

}

#endif // TLINSUICONFGIURATIONITEM_H
