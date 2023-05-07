#include "tlinsuiconfgiurationitem.h"

namespace TlinsAstroBase {

const std::string& tlinsUiConfgiurationItem::getGroupName() const
{
    return groupName;
}

const std::string& tlinsUiConfgiurationItem::getParameter() const
{
    return parameter;
}

bool tlinsUiConfgiurationItem::getItemValue(const int idx, std::string& v) const
{
    return value.getValue(idx, v);
}

void tlinsUiConfgiurationItem::setGroupName(const std::string& name)
{
    groupName = name;
}

void tlinsUiConfgiurationItem::setParameter(const std::string name)
{
    parameter = name;
}

void tlinsUiConfgiurationItem::addItem(const itemValues& v)
{
    value = v;
}

void tlinsUiConfgiurationItem::setValues(const int idx, const std::string& v)
{
    if ((unsigned)idx >= value.size())
        throw TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_OUT_OF_INDEX_RANGE, std::string("Out of index range"));

    if (!value.setValue(idx, v))
        throw TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_OUT_OF_INDEX_RANGE, std::string("Out of index range"));
}

void tlinsUiConfgiurationItem::setValues(const itemValues& v)
{
    value = v;
}

tlinsUiConfgiurationItem::tlinsUiConfgiurationItem()
{
}

tlinsUiConfgiurationItem::~tlinsUiConfgiurationItem()
{
}

// ---
// --- ------------
// ---

std::map<std::string, std::shared_ptr<tlinsUiConfgiurationItem>> tlinsUiConfgiurationItemsCollection::collection;

bool tlinsUiConfgiurationItemsCollection::addItem(std::shared_ptr<tlinsUiConfgiurationItem>& item)
{
    std::string key = item->getGroupName() + std::string("::") + item->getParameter();
    auto iter = tlinsUiConfgiurationItemsCollection::collection.find(key);
    if (iter != tlinsUiConfgiurationItemsCollection::collection.end())
        return false;

    tlinsUiConfgiurationItemsCollection::collection[key] = item;
    return true;
}

bool tlinsUiConfgiurationItemsCollection::getItem(const std::string& group, const std::string& paraName, std::shared_ptr<tlinsUiConfgiurationItem>& v)
{
    std::string key = group + std::string("::") + paraName;
    auto iter = tlinsUiConfgiurationItemsCollection::collection.find(key);
    if (iter == tlinsUiConfgiurationItemsCollection::collection.end())
        return false;

    v = iter->second;
    return true;
}

tlinsUiConfgiurationItemsCollection::tlinsUiConfgiurationItemsCollection()
{
}

tlinsUiConfgiurationItemsCollection::~tlinsUiConfgiurationItemsCollection() {};

}
