#include "tlinsastrocatalogitem.h"
#include <tlinsuiexception.h>

namespace TlinsAstroBase {

std::vector<Constelations::ConstelationInfo> Constelations::constelationsList;
std::map<std::string, int> Constelations::byConstelationType;

void Constelations::initFromDb()
{
}

#define __CONS__(label, id, name)                                                                                                   \
    do {                                                                                                                            \
        Constelations::constelationsList.push_back(Constelations::ConstelationInfo(std::string(label), std::string(name), id)); \
        Constelations::byConstelationType[std::string(label)] = id;                                                               \
    } while (false)

void Constelations::init()
{
    __CONS__("", 0, "<No set>");
    __CONS__("And", 1, "[And] Andromeda (Andromeda)");
    __CONS__("Ant", 2, "[Ant] Antlia (Pompa - wodna)");
    __CONS__("Aps", 3, "[Aps] Apus (Ptak Rajski)");
    __CONS__("Aqr", 4, "[Aqr] Aquarius (Wodnik)");
    __CONS__("Aql", 5, "[Aql] Aquila (Orzeł)");
    __CONS__("Ara", 6, "[Ara] Ara (Ołtarz)");
    __CONS__("Ari", 7, "[Ari] Aries (Baran)");
    __CONS__("Aur", 8, "[Aur] Auriga (Woźnica)");
    __CONS__("Boo", 9, "[Boo] Bootes (Wolarz)");
    __CONS__("Cae", 10, "[Cae] Caelum (Rylec)");
    __CONS__("Cam", 11, "[Cam] Camelopardalis (Żyrafa)");
    __CONS__("Cnc", 12, "[Cnc] Cancer (ak)");
    __CONS__("CVn", 13, "[CVn] Canes Venatici (Psy Gończe)");
    __CONS__("CMa", 14, "[CMa] Canis Maior (Wielki Pies)");
    __CONS__("CMi", 15, "[CMi] Canis Minor (Mały Pies)");
    __CONS__("Cap", 16, "[Cap] Capricornus (Koziorożec)");
    __CONS__("Car", 17, "[Car] Carina (Kil)");
    __CONS__("Cas", 18, "[Cas] Cassiopeia (Kasjopea)");
    __CONS__("Cen", 19, "[Cen] Centaurus (Centaur)");
    __CONS__("Cep", 20, "[Cep] Cepheus (Cefeusz)");
    __CONS__("Cet", 21, "[Cet] Cetus (Wieloryb)");
    __CONS__("Cha", 22, "[Cha] Chamaeleon (Kameleon)");
    __CONS__("Cir", 23, "[Cir] Circinus (Cyrkiel)");
    __CONS__("Col", 24, "[Col] Columba (Gołąb)");
    __CONS__("Com", 25, "[Com] Coma Berenices (Warkocz Bereniki)");
    __CONS__("CrA", 26, "[CrA] Corona Australis (Korona Południowa)");
    __CONS__("CrB", 27, "[CrB] Corona Borealis (Korona Północna)");
    __CONS__("Crv", 28, "[Crv] Corvus (Kruk)");
    __CONS__("Crt", 29, "[Crt] Crater (Puchar)");
    __CONS__("Cru", 30, "[Cru] Crux (Krzyż)");
    __CONS__("Cyg", 31, "[Cyg] Cygnus (Łabędź)");
    __CONS__("Del", 32, "[Del] Delphinus (Delfin)");
    __CONS__("Dor", 33, "[Dor] Dorado (Złota)");
    __CONS__("Dra", 34, "[Dra] Draco (Smok)");
    __CONS__("Equ", 35, "[Equ] Equuleus (Źrebię)");
    __CONS__("Eri", 36, "[Eri] Eridanus (Erydan)");
    __CONS__("For", 37, "[For] Fornax (Piec)");
    __CONS__("Gem", 38, "[Gem] Gemini (Bliźnięta)");
    __CONS__("Gru", 39, "[Gru] Grus (Żuraw)");
    __CONS__("Her", 40, "[Her] Hercules (Herkules)");
    __CONS__("Hor", 41, "[Hor] Horologium (Zegar)");
    __CONS__("Hya", 42, "[Hya] Hydra (Hydra)");
    __CONS__("Hyi", 43, "[Hyi] Hydrus (Wąż)");
    __CONS__("Ind", 44, "[Ind] Indus (Indianin)");
    __CONS__("Lac", 45, "[Lac] Lacerta (Jaszczurka)");
    __CONS__("Leo", 46, "[Leo] Leo (Lew)");
    __CONS__("LMi", 47, "[LMi] Leo Minor (Mały lew)");
    __CONS__("Lep", 48, "[Lep] Lepus (Zając)");
    __CONS__("Lib", 49, "[Lib] Libra (Waga)");
    __CONS__("Lup", 50, "[Lup] Lupus (Wilk)");
    __CONS__("Lyn", 51, "[Lyn] Lynx (Ryś)");
    __CONS__("Lyr", 52, "[Lyr] Lyra (Lutnia)");
    __CONS__("Men", 53, "[Men] Mensa (Góra)");
    __CONS__("Mic", 54, "[Mic] Microscopium (Mikroskop)");
    __CONS__("Mon", 55, "[Mon] Monoceros (Jednorożec)");
    __CONS__("Mus", 56, "[Mus] Musca (Mucha)");
    __CONS__("Nor", 57, "[Nor] Norma (Węgielnica)");
    __CONS__("Oct", 58, "[Oct] Octans (Oktant)");
    __CONS__("Oph", 59, "[Oph] Ophiuchus (Wężownik)");
    __CONS__("Ori", 60, "[Ori] Orion (Orion)");
    __CONS__("Pav", 61, "[Pav] Pavo (Paw)");
    __CONS__("Peg", 62, "[Peg] Pegasus (Pegaz)");
    __CONS__("Per", 63, "[Per] Perseus (Perseusz)");
    __CONS__("Phe", 64, "[Phe] Phoenix (Feniks)");
    __CONS__("Pic", 65, "[Pic] Pictor (Malarz)");
    __CONS__("Psc", 66, "[Psc] Pisces (Ryby)");
    __CONS__("PsA", 67, "[Psa] Piscis Austrinus (Ryba Południowa)");
    __CONS__("Pup", 68, "[Pup] Puppis (Rufa)");
    __CONS__("Pyx", 69, "[Pyx] Pyxis (Kompas)");
    __CONS__("Ret", 70, "[Ret] Reticulum (Sieć)");
    __CONS__("Sge", 71, "[Sge] Sagitta (Strzała)");
    __CONS__("Sgr", 72, "[Sgr] Sagittarius (Strzelec)");
    __CONS__("Sco", 73, "[Sco] Scorpius (Skorpion)");
    __CONS__("Scl", 74, "[Scl] Sculptor (Rzeźbiarz)");
    __CONS__("Sct", 75, "[Sct] Scutum (Tarcza)");
    __CONS__("Ser", 76, "[Ser] Serpens (Wąż)");
    __CONS__("Sex", 77, "[Sex] Sextans (Sekstant)");
    __CONS__("Tau", 78, "[Tau] Taurus (Byk)");
    __CONS__("Tel", 79, "[Tel] Telescopium (Luneta)");
    __CONS__("Tri", 80, "[Tri] Triangulum (Trójkąt)");
    __CONS__("TrA", 81, "[Tra] Triangulum Australe (Trójkąt Południowy)");
    __CONS__("Tuc", 82, "[Tuc] Tucana (Tukan)");
    __CONS__("UMa", 83, "[UMa] Ursa Maior (Wielka Niedźwiedzica)");
    __CONS__("UMi", 84, "[UMi] Ursa Minor (Mała Niedźwiedzica)");
    __CONS__("Vel", 85, "[Vel] Vela (Żagiel)");
    __CONS__("Vir", 86, "[Vir] Virgo (Panna)");
    __CONS__("Vol", 87, "[Vol] Volans (Ryba)");
    __CONS__("Vul", 88, "[Vul] Vulpecula (Lis)");
}

int Constelations::count()
{
    return static_cast<int>(constelationsList.size());
}

bool Constelations::getByTypeName(const std::string& name, std::string& output)
{
    auto i = Constelations::byConstelationType.find(name);
    if (i == Constelations::byConstelationType.end())
        return false;
    output = Constelations::constelationsList[i->second].name;

    return true;
}

bool Constelations::get(const int idx, int& id, std::string& label, std::string& name)
{
    if (idx >= Constelations::count())
        return false;

    Constelations::ConstelationInfo value = constelationsList[idx];
    id = value.id;
    label = value.label;
    name = value.name;

    return true;
}

bool Constelations::get(const int idx, ConstelationInfo& res)
{
    if (idx >= Constelations::count())
        return false;

    res = constelationsList[idx];
    return true;
}

bool Constelations::get(const std::string& name, ConstelationInfo& res)
{
    if (byConstelationType.count(name) == 0)
        return false;
    return get(byConstelationType[name], res);
}

// ###################################################
// ###################################################
// ###################################################

std::vector<CatalogType::CatalogTypeInfo> CatalogType::catalogTypeList;
std::map<std::string, int> CatalogType::byCatalogType;

void CatalogType::initFromDb()
{
}

void CatalogType::init()
{
    CatalogType::catalogTypeList.push_back(CatalogType::CatalogTypeInfo(std::string("CATALOG_MODIFIED_YELLOW_SKAY"), std::string("Modified yellow sky"), 0));
    CatalogType::byCatalogType[std::string("CATALOG_MODIFIED_YELLOW_SKAY")] = 0;

    CatalogType::catalogTypeList.push_back(CatalogType::CatalogTypeInfo(std::string("CATALOG_AC2000_2"), std::string("AC2000.2"), 1));
    CatalogType::byCatalogType[std::string("CATALOG_AC2000_2")] = 1;

    CatalogType::catalogTypeList.push_back(CatalogType::CatalogTypeInfo(std::string("CATALOG_TYCHO_2"), std::string("TYCHO-2"), 2));
    CatalogType::byCatalogType[std::string("CATALOG_TYCHO_2")] = 2;

    CatalogType::catalogTypeList.push_back(CatalogType::CatalogTypeInfo(std::string("CATALOG_USNO"), std::string("USNO"), 3));
    CatalogType::byCatalogType[std::string("CATALOG_USNO")] = 3;

    CatalogType::catalogTypeList.push_back(CatalogType::CatalogTypeInfo(std::string("CATALOG_HIPPATCOS"), std::string("HIPPATCOS"), 4));
    CatalogType::byCatalogType[std::string("CATALOG_HIPPATCOS")] = 4;

    CatalogType::catalogTypeList.push_back(CatalogType::CatalogTypeInfo(std::string("CATALOG_LUTEN_TWO_TENTHS"), std::string("Luten two tenths"), 5));
    CatalogType::byCatalogType[std::string("CATALOG_LUTEN_TWO_TENTHS")] = 5;

    CatalogType::catalogTypeList.push_back(CatalogType::CatalogTypeInfo(std::string("CATALOG_USNO_A2"), std::string("USNO A2"), 6));
    CatalogType::byCatalogType[std::string("CATALOG_USNO_A2")] = 6;
}

int CatalogType::count()
{
    return static_cast<int>(catalogTypeList.size());
}

bool CatalogType::getByTypeName(const std::string& name, std::string& output)
{
    auto i = CatalogType::byCatalogType.find(name);
    if (i == CatalogType::byCatalogType.end())
        return false;
    output = CatalogType::catalogTypeList[i->second].name;

    return true;
}

bool CatalogType::get(const int idx, int& id, std::string& label, std::string& name)
{
    if (idx >= CatalogType::count())
        return false;

    CatalogType::CatalogTypeInfo value = catalogTypeList[idx];
    id = value.id;
    label = value.label;
    name = value.name;

    return true;
}

bool CatalogType::get(const int idx, CatalogTypeInfo& res)
{
    if (idx >= CatalogType::count())
        return false;
    res = catalogTypeList[idx];
    return true;
}

bool CatalogType::get(const std::string& name, CatalogTypeInfo& res)
{
    if (byCatalogType.count(name) == 0)
        return false;

    return get(byCatalogType[name], res);
}

// ###################################################
// ###################################################
// ###################################################

std::vector<ObjectType::ObjectTypeInfo> ObjectType::objectTypeList;
std::map<std::string, int> ObjectType::byObjectType;

void ObjectType::initFromDb()
{
}

void ObjectType::init()
{
    ObjectType::objectTypeList.push_back(ObjectType::ObjectTypeInfo(std::string("OBJECT_TYPE_STAR"), std::string("Gwiazda"), 0));
    ObjectType::byObjectType[std::string("OBJECT_TYPE_STAR")] = 0;
    ObjectType::objectTypeList.push_back(ObjectType::ObjectTypeInfo(std::string("OBJECT_TYPE_BINARY_STARS"), std::string("Gwiazda podwojna"), 1));
    ObjectType::byObjectType[std::string("OBJECT_TYPE_BINARY_STARS")] = 1;
    ObjectType::objectTypeList.push_back(ObjectType::ObjectTypeInfo(std::string("OBJECT_TYPE_MULTIPLE_STARS"), std::string("Gwiazda wielokrotna"), 2));
    ObjectType::byObjectType[std::string("OBJECT_TYPE_MULTIPLE_STARS")] = 2;
    ObjectType::objectTypeList.push_back(ObjectType::ObjectTypeInfo(std::string("OBJECT_TYPE_VARIABLE_STAR"), std::string("Gwiazda zmenna"), 3));
    ObjectType::byObjectType[std::string("OBJECT_TYPE_VARIABLE_STAR")] = 3;
    ObjectType::objectTypeList.push_back(ObjectType::ObjectTypeInfo(std::string("OBJECT_TYPE_NOVAE_STAR"), std::string("Gwiazda nowa"), 4));
    ObjectType::byObjectType[std::string("OBJECT_TYPE_NOVAE_STAR")] = 4;
    ObjectType::objectTypeList.push_back(ObjectType::ObjectTypeInfo(std::string("OBJECT_TYPE_SUPERNOVAE_STAR"), std::string("Sueprnowa"), 5));
    ObjectType::byObjectType[std::string("OBJECT_TYPE_SUPERNOVAE_STAR")] = 5;
    ObjectType::objectTypeList.push_back(ObjectType::ObjectTypeInfo(std::string("OBJECT_TYPE_STARS_CLUSTER"), std::string("Gromada gwiazd"), 6));
    ObjectType::byObjectType[std::string("OBJECT_TYPE_STARS_CLUSTER")] = 6;
    ObjectType::objectTypeList.push_back(ObjectType::ObjectTypeInfo(std::string("OBJECT_TYPE_STARS_GLOBUAR_CLUSTER"), std::string("Gromada gwiazd globular"), 7));
    ObjectType::byObjectType[std::string("OBJECT_TYPE_STARS_GLOBUAR_CLUSTER")] = 7;
    ObjectType::objectTypeList.push_back(ObjectType::ObjectTypeInfo(std::string("OBJECT_TYPE_STARS_OPEN_CLUSTER"), std::string("Otwarta gromada gwiazd"), 8));
    ObjectType::byObjectType[std::string("OBJECT_TYPE_STARS_OPEN_CLUSTER")] = 8;

    ObjectType::objectTypeList.push_back(ObjectType::ObjectTypeInfo(std::string("OBJECT_TYPE_NEBULEA"), std::string("Mgławica"), 9));
    ObjectType::byObjectType[std::string("OBJECT_TYPE_NEBULEA")] = 9;
    ObjectType::objectTypeList.push_back(ObjectType::ObjectTypeInfo(std::string("OBJECT_TYPE_DIFFUSE_NEBULAE"), std::string("Mgławica dyfuzyjn"), 10));
    ObjectType::byObjectType[std::string("OBJECT_TYPE_DIFFUSE_NEBULAE")] = 10;
    ObjectType::objectTypeList.push_back(ObjectType::ObjectTypeInfo(std::string("OBJECT_TYPE_PLANETARY_NEBULAE"), std::string("Mgławica planetarna"), 11));
    ObjectType::byObjectType[std::string("OBJECT_TYPE_PLANETARY_NEBULAE")] = 11;
    ObjectType::objectTypeList.push_back(ObjectType::ObjectTypeInfo(std::string("OBJECT_TYPE_DARK_NEBULAE"), std::string("Ciemna mgławica"), 12));
    ObjectType::byObjectType[std::string("OBJECT_TYPE_PLANETARY_NEBULAE")] = 12;

    ObjectType::objectTypeList.push_back(ObjectType::ObjectTypeInfo(std::string("OBJECT_TYPE_GALAXY"), std::string("Galaktyka"), 13));
    ObjectType::byObjectType[std::string("OBJECT_TYPE_GALAXY")] = 13;
    ObjectType::objectTypeList.push_back(ObjectType::ObjectTypeInfo(std::string("OBJECT_TYPE_SPIRAL_GALAXY"), std::string("Galaktyka spiralna"), 14));
    ObjectType::byObjectType[std::string("OBJECT_TYPE_SPIRAL_GALAXY")] = 14;
    ObjectType::objectTypeList.push_back(ObjectType::ObjectTypeInfo(std::string("OBJECT_TYPE_QUASAR"), std::string("Galaktyka eliptyczna"), 15));
    ObjectType::byObjectType[std::string("OBJECT_TYPE_QUASAR")] = 15;
    ObjectType::objectTypeList.push_back(ObjectType::ObjectTypeInfo(std::string("OBJECT_TYPE_IRREGULAR_GALAXY"), std::string("Galaktyka nieregularna"), 16));
    ObjectType::byObjectType[std::string("OBJECT_TYPE_IRREGULAR_GALAXY")] = 16;

    ObjectType::objectTypeList.push_back(ObjectType::ObjectTypeInfo(std::string("OBJECT_TYPE_QUASAR"), std::string("Kwazar"), 17));
    ObjectType::byObjectType[std::string("OBJECT_TYPE_QUASAR")] = 17;
}

bool ObjectType::getByType(const std::string& in, std::string& out)
{
    auto i = ObjectType::byObjectType.find(in);
    if (i == ObjectType::byObjectType.end())
        return false;

    out = ObjectType::objectTypeList[i->second].name;
    return true;
}

int ObjectType::count()
{
    return objectTypeList.size();
}

bool ObjectType::get(const int idx, int& id, std::string& label, std::string& name)
{
    if (idx >= ObjectType::count())
        return false;

    ObjectType::ObjectTypeInfo value = objectTypeList[idx];
    id = value.id;
    label = value.label;
    name = value.name;

    return true;
}

bool ObjectType::get(const int idx, ObjectTypeInfo& res)
{
    if (idx >= ObjectType::count())
        return false;

    res = objectTypeList[idx];
    return true;
}

bool ObjectType::get(const std::string& name, ObjectTypeInfo& res)
{
    if (byObjectType.count(name) == 0)
        return false;

    return get(byObjectType[name], res);
}

// ###################################################
// ###################################################
// ###################################################

const std::string& tlinsAstroCatalogItem::getName() const
{
    return name;
}

const std::string& tlinsAstroCatalogItem::getDescription() const
{
    return description;
}

const ObjectType::ObjectTypeInfo& tlinsAstroCatalogItem::getType() const
{
    return type;
}

const std::string& tlinsAstroCatalogItem::getTypeDetails1() const
{
    return typeDetails1;
}

const std::string& tlinsAstroCatalogItem::getTypeDetails2() const
{
    return typeDetails2;
}

const std::string& tlinsAstroCatalogItem::getTypeDetails3() const
{
    return typeDetails3;
}

const Constelations::ConstelationInfo& tlinsAstroCatalogItem::getConstelation() const
{
    return constelation;
}

double tlinsAstroCatalogItem::getRA() const
{
    return RA;
}

double tlinsAstroCatalogItem::getDC() const
{
    return DC;
}

double tlinsAstroCatalogItem::getPmRA() const
{
    return pmRA;
}

double tlinsAstroCatalogItem::getPmDC() const
{
    return pmDC;
}

double tlinsAstroCatalogItem::getEpRA() const
{
    return epRA;
}

double tlinsAstroCatalogItem::getEpDC() const
{
    return epDC;
}

double tlinsAstroCatalogItem::getMinErrRA() const
{
    return minErrRa;
}

double tlinsAstroCatalogItem::getMinErrDC() const
{
    return minErrDc;
}

double tlinsAstroCatalogItem::getErrMeanRA() const
{
    return errMeanRA;
}

double tlinsAstroCatalogItem::getErrMeanDC() const
{
    return errMeanDC;
}

double tlinsAstroCatalogItem::getErrMeanPmRA() const
{
    return errMeanPmRA;
}

double tlinsAstroCatalogItem::getErrMeanPmDC() const
{
    return errMeanPmDC;
}

double tlinsAstroCatalogItem::getMagnitude() const
{
    return magnitude;
}

double tlinsAstroCatalogItem::getErrMagnitude() const
{
    return errMagnitude;
}

const CatalogType::CatalogTypeInfo& tlinsAstroCatalogItem::getCatalogType() const
{
    return catalogType;
}

const std::string& tlinsAstroCatalogItem::getObjectIdInCatalog() const
{
    return objectIdInCatalog;
}

const std::string& tlinsAstroCatalogItem::getObjectDescription() const
{
    return objectDescription;
}

unsigned int tlinsAstroCatalogItem::getRecordID() const
{
    return static_cast<unsigned int>(recordID);
}

// -----------------------------------------------------

void tlinsAstroCatalogItem::setName(const std::string& v)
{
    name = v;
}

void tlinsAstroCatalogItem::setDescription(const std::string& v)
{
    description = v;
}

void tlinsAstroCatalogItem::setType(const ObjectType::ObjectTypeInfo& v)
{
    type = v;
}

void tlinsAstroCatalogItem::setTypeDetails1(const std::string& v)
{
    typeDetails1 = v;
}

void tlinsAstroCatalogItem::setTypeDetails2(const std::string& v)
{
    typeDetails2 = v;
}

void tlinsAstroCatalogItem::setTypeDetails3(const std::string& v)
{
    typeDetails3 = v;
}

void tlinsAstroCatalogItem::setConstelation(const Constelations::ConstelationInfo& v)
{
    constelation = v;
}

void tlinsAstroCatalogItem::setRA(const double v)
{
    RA = v;
}

void tlinsAstroCatalogItem::setDC(const double v)
{
    DC = v;
}

void tlinsAstroCatalogItem::setPmRA(const double v)
{
    pmRA = v;
}

void tlinsAstroCatalogItem::setPmDC(const double v)
{
    pmDC = v;
}

void tlinsAstroCatalogItem::setEpRA(const double v)
{
    epRA = v;
}

void tlinsAstroCatalogItem::setEpDC(const double v)
{
    epDC = v;
}

void tlinsAstroCatalogItem::setMinErrRA(const double v)
{
    minErrRa = v;
}

void tlinsAstroCatalogItem::setMinErrDC(const double v)
{
    minErrDc = v;
}

void tlinsAstroCatalogItem::setErrMeanRA(const double v)
{
    errMeanRA = v;
}

void tlinsAstroCatalogItem::setErrMeanDC(const double v)
{
    errMeanDC = v;
}

void tlinsAstroCatalogItem::setErrMeanPmRA(const double v)
{
    errMeanPmRA = v;
}

void tlinsAstroCatalogItem::setErrMeanPmDC(const double v)
{
    errMeanPmDC = v;
}

void tlinsAstroCatalogItem::setMagnitude(const double v)
{
    magnitude = v;
}

void tlinsAstroCatalogItem::setErrMagnitude(const double v)
{
    errMagnitude = v;
}

void tlinsAstroCatalogItem::setCatalogType(const CatalogType::CatalogTypeInfo& v)
{
    catalogType = v;
}

void tlinsAstroCatalogItem::setObjectIdInCatalog(const std::string& v)
{
    objectIdInCatalog = v;
}

void tlinsAstroCatalogItem::setObjectDescription(const std::string& v)
{
    objectDescription = v;
}

void tlinsAstroCatalogItem::setRecordID(const unsigned int v)
{
    recordID = v;
}

tlinsAstroCatalogItem& tlinsAstroCatalogItem::operator=(const tlinsAstroCatalogItem& v)
{
    recordID = v.recordID;
    name = v.name;
    description = v.description;
    type = v.type;
    typeDetails1 = v.typeDetails1;
    typeDetails2 = v.typeDetails2;
    typeDetails3 = v.typeDetails3;
    constelation = v.constelation;
    RA = v.RA;
    DC = v.DC;
    pmRA = v.pmRA;
    pmDC = v.pmDC;
    epRA = v.epRA;
    epDC = v.epDC;
    minErrRa = v.minErrRa;
    minErrDc = v.minErrDc;
    errMeanRA = v.errMeanRA;
    errMeanDC = v.errMeanDC;
    errMeanPmRA = v.errMeanPmRA;
    errMeanPmDC = v.errMeanPmDC;
    magnitude = v.magnitude;
    errMagnitude = v.errMagnitude;
    catalogType = v.catalogType;
    objectIdInCatalog = v.objectIdInCatalog;
    objectDescription = v.objectDescription;
    radialVelocity = v.radialVelocity;
    parallex = v.parallex;

    return *this;
}

tlinsAstroCatalogItem::tlinsAstroCatalogItem(const tlinsAstroCatalogItem& v)
{
    *this = v;
}

tlinsAstroCatalogItem::tlinsAstroCatalogItem()
{
}

tlinsAstroCatalogItem::~tlinsAstroCatalogItem()
{
}

}
