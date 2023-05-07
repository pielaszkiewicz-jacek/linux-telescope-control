#ifndef TLINSASTROCATALOGCOLLECTION_H
#define TLINSASTROCATALOGCOLLECTION_H

#include "tlinsastrocatalogitem.h"
#include "tlinsuiexception.h"
#include <map>
#include <memory>
#include <vector>

namespace TlinsAstroBase {

class tlinsAstroCatalogCollection {
private:
    std::map<std::string, int> collection;
    std::vector<tlinsAstroCatalogItem> collectionVector;

private:
    std::string itemKey(const tlinsAstroCatalogItem& item) const;

public:
    tlinsAstroCatalogItem& operator[](int idx);
    tlinsAstroCatalogCollection& operator=(const tlinsAstroCatalogCollection& v);
    tlinsAstroCatalogItem getItem(const int idx) const;
    int count() const;

    // Dodaje kopie pozycji do kolekcji
    bool addItem(tlinsAstroCatalogItem& item);
    void removeItem(tlinsAstroCatalogItem& item);

    tlinsAstroCatalogCollection();
    virtual ~tlinsAstroCatalogCollection();
};

}

#endif // TLINSASTROCATALOGCOLLECTION_H
