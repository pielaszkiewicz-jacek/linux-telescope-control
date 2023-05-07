#include "tlinsastrocatalogcollection.h"
#include <QDebug>
#include <stdio.h>

namespace TlinsAstroBase {

tlinsAstroCatalogCollection::tlinsAstroCatalogCollection()
{
}

tlinsAstroCatalogItem& tlinsAstroCatalogCollection::operator[](int idx)
{
    return collectionVector.at(idx);
}

tlinsAstroCatalogCollection& tlinsAstroCatalogCollection::operator=(const tlinsAstroCatalogCollection& v)
{
    // Czyssczenie mapy i wektora
    collection.clear();
    collectionVector.clear();

    for (auto iter = v.collectionVector.begin(); iter != v.collectionVector.end(); iter++) {
        collectionVector.push_back(*iter);
    }

    for (auto iter = v.collection.begin(); iter != v.collection.end(); iter++) {
        collection[iter->first] = iter->second;
    }
    return *this;
}

int tlinsAstroCatalogCollection::count() const
{
    return collectionVector.size();
}

tlinsAstroCatalogItem tlinsAstroCatalogCollection::getItem(const int idx) const
{
    if (idx >= count())
        throw TlinsAstroBase::tlinsUIException(TlinsAstroBase::tlinsUIException::ERROR_OUT_OF_INDEX_RANGE, std::string("Out of index range"));

    return collectionVector[idx];
}

std::string tlinsAstroCatalogCollection::itemKey(const tlinsAstroCatalogItem& item) const
{
    char text[1024];

    sprintf(text, "%s:%s:%3.8f:%3.8f", item.getCatalogType().label.c_str(), item.getObjectIdInCatalog().c_str(), item.getRA(), item.getDC());
    return std::string(text);
}

void tlinsAstroCatalogCollection::removeItem(tlinsAstroCatalogItem& item)
{
    std::string key = itemKey(item);

    auto itemRef = collection.find(key);
    if (itemRef == collection.end())
        return;

    int pos = itemRef->second;
    collection.erase(itemRef);

    // Usuniecie pozycji wektora
    collectionVector.erase(collectionVector.begin() + pos);

    // Czyszczenie mapy
    collection.clear();

    for (unsigned int i = 0; i < collectionVector.size(); i++) {
        collectionVector[i].setRecordID(i);
    }

    // Przenumerowanie rekordow w kolekcji
    for (unsigned int i = 0; i < collectionVector.size(); i++) {
        auto it = collectionVector.at(i);
        std::string keyn = itemKey(it);
        collection[keyn] = i;
    }
}

// Dodaje kopie pozycji do kolekcji
bool tlinsAstroCatalogCollection::addItem(tlinsAstroCatalogItem& item)
{
    std::string key = itemKey(item);

    auto itemRef = collection.find(key);
    if (itemRef != collection.end())
        return false;

    collection[key] = count();
    collectionVector.push_back(item);
    collectionVector[count() - 1].setRecordID((unsigned long)(count() - 1));

    return true;
}

tlinsAstroCatalogCollection::~tlinsAstroCatalogCollection()
{
}

}
