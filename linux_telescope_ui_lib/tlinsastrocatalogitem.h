#ifndef TLINSASTROCATALOGITEM_H
#define TLINSASTROCATALOGITEM_H

#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

/*
 *
   1-  8  I08   ---      2UCAC  [00000001,48330571] UCAC designation (1)
+  10- 20  F11.7 deg      RAdeg  Right ascension (degrees), ICRS, Ep=J2000 (2)
+  21- 31  F11.7 deg      DEdeg  Declination (degrees), ICRS, Ep=J2000 (2)
+  33- 35  I3    mas    e_RAdeg  Minimal mean error on RAdeg (3)
+  37- 39  I3    mas    e_DEdeg  Minimal mean error on DEdeg (3)
   41- 43  I3    mas      ePos   Error of original UCAC observation (4)
   45- 49  F5.2  mag      UCmag  Magnitude in UCAC system (579-642nm) (5)
   51- 52  I2    ---      No     Number of UCAC observations for the star
   54- 55  I2    ---      Nc     Number of catalog positions used for pmRA, pmDE
+  58- 59  I02   ---      cfl    Major catalogs used in pmRA, pmDE (6)
+  61- 68  F8.3  yr       EpRA   Central epoch for mean RA (3)
+  70- 77  F8.3  yr       EpDE   Central epoch for mean Declination (3)
+  79- 86  F8.1  mas/yr   pmRA   Proper motion in RA(*cos(Dec)) (7)
+  88- 95  F8.1  mas/yr   pmDE   Proper motion in Dec
+  97-100  F4.1  mas/yr e_pmRA   Mean error on pmRA (8)
+ 102-105  F4.1  mas/yr e_pmDE   Mean error on pmDE (8)
  107-111  F5.2  ---      qpmRA  Goodness of fit for pmRA (8)
  113-117  F5.2  ---      qpmDE  Goodness of fit for pmDE (8)
  119-128  I10   ---      2Mkey  2MASS (II/246) Unique source identi        case 4: _t->on_pushButton_clicked(); break;fier
  130-135  F6.3  mag      Jmag   ? J magnitude (1.2um) from 2MASS
  137-142  F6.3  mag      Hmag   ? H magnitude (1.6um) from 2MASS
  144-149  F6.3  mag      Kmag   ? K magnitude (2.2um) from 2MASS
  151-153  I03   ---      phf    2MASS photometric quality flag (9)
  155-157  I03   ---      ccf    2MASS confusion flag (10)

Note (1): this star number is not provided in the original files.
	 It represents the running line number over all data, and uses an
	 8-digit after the string "2UCAC"

Note (2): Positions are on the International Celestial Reference System
	(ICRS) as represented by the Hipparcos / Tycho-2 catalogs. The epoch
	for the positions of all stars is J2000.0; the weighted mean catalog
	position was updated using the provided proper motions. The
	observational UCAC position is but one of several going into these
	values and is not given in the UCAC2, thus the original UCAC
	observation cannot be recovered from these data.

Note (3):  Values for e_RAm and e_DEm are internal standard errors in
	position at the central epoch, NOT at the epoch J2000; for any epoch T
	(including "J2000.0" which corresponds to RAdeg and DEdeg columns) the
	error in position can be computed as:

	  e_RAdeg(T) = sqrt(e_RAdeg^2^ + (e_pmRA * (T-EpRA))^2^)

	and similarly for e_DEdeg. Thus for all epochs other than EpRAm or
	EpDEm the positional errors for RA and Dec, respectively, increase
	for both going forward or back in time. Values for EpRAm and EpDEm
	are usually not equal due to different weights assigned to coordinates
	in the individual catalogs used in determining the mean positions and
	proper motions.

Note (4): ePos is the internal, formal, 1-sigma error in position of
	the UCAC astrograph observations, expressed as the mean of the error
	in RA*cos(DE) and DE. This error is derived from the scatter of
	individual positions which form the mean observed position from the
	CCD observations of each star. These values are subject to small
	number statistics; many of the stars have only 2 to 4 observations. On
	average, for stars in the 7.5 to 10 mag range, 30 mas is expected, for
	10 to 14.5 about 15 to 20 mas and increasing up to 70 mas toward 16th
	magnitude.

Note (5): values for UCmag should be considered approximate.
	The UCAC bandpass (579-642nm) is between V and R. Observations were
	often made under non-photometric conditions and UCmag is provided here
	for identification purposes only. Estimated errors are 0.3 magnitude
	absolute, 0.1 magnitude relative.

Note (6): identifier of some major catalogs used in the computation of
	proper motions, which also provides the user with information
	regarding known, high proper motion stars. However, this flag does
	not contain all catalogs going into the proper motions, about 150
	were used in this project. The cfl value is actually a sum of numbers,
	each with the following meaning:

	 1 = modified Yellow Sky (NOFS scans of NPM, SPM; not published)
	 2 = AC2000.2 Catalog (I/275)
	 4 = Tycho-2 Catalogue observed position (I/259)
	 8 = USNO measurement of AGK2 plates (not published)
	16 = Hipparcos Catalogue (I/239)
	32 = Known high proper motion star from the revised New Luyten's
		 Two-Tenths catalog (NLTT, Cat. I/98, match provided by A.Gould,
		 see J/ApJ/582/1011)
	64 = USNO A2 Catalog (I/252)

Note (7): The original proper motion did not contain the cos(DE) factor,
	which was applied here to enable an easy computation of the total
	proper motion.

Note (8): e_pmRA and e_pmDE are the formal standard errors of
	pmRA, pmDE respectively. In addition to these "model" errors,
	"scatter" errors have been calculated for each star having 3 or more
	catalog positions used in the proper motion determination. This
	"scatter" error depends on how well the individual catalog positions
	fit the computed proper motion. The "scatter" errors in position and
	proper motion component for each star are not explicitly given here,
	however the scatter error proper motion values can be recovered using
	the values qpmRA and qpmDE.

	qpmRA and qpmDE are termed "goodness of fit" for the pmRA and pmDE.
	These values give information on how well the computed proper motions
	actually fit the catalog positions used to compute them, termed
	"scatter error". The values qpmRA and qpmDE are actually ratios,
	"scatter error pm"/e_pmRA (or e_pmDE). Thus, when the actual fit of
	the proper motion to the catalog positions is better than the formal,
	model errors (e_pmRA, e_pmDE), the ratio is smaller than 1. In the
	opposite case, the ratio is larger than 1. Stars with qpmRA or qpmDE
	values exceeding 5 should be used with caution. If the ratio is larger
	than 12.5 it is set to 12.5. The ratio of "scatter error" to "model
	error" of the mean positions is highly correlated to those of the
	proper motions.

	Note that the "scatter error" only makes sense for stars with 3
	or more catalog positions; if only 2 catalogs were used for the
	determination of the proper motion, the "fit" is perfect (going
	directly through each of the 2 positions, regardless of weights).
	In these cases, the ratios are set to 1.0.

Note (9): photometric quality flag from the 2MASS catalog (II/246).
	For each color (J, H, K) one digit is given and has the following
	meaning:

	0 = 2MASS quality is A or B, meaning good detections (snr > 7)
	1 = 2MASS quality is C or D, meaning weak detections
	2 = 2MASS quality is something else and the 2MASS documentation
		should be consulted.

Note (10):  artifact contamination and confusion from the 2MASS catalog
	(II/246). For each color (J, H, K) one digit is given and has the
	following meaning:

	0 = 2MASS confusion is 0, no artifacts or contamination seen
	1 = 2MASS confusion is "c", confusion with nearby brighter source
	2 = 2MASS confusion is something else and the 2MASS documentation
		should be consulted.
*/

namespace TlinsAstroBase {

class Constelations {
public:
    struct ConstelationInfo {
        std::string label;
        std::string name;
        int id;

        ConstelationInfo(const std::string& _label,
            const std::string& _name,
            const int _id)
        {
            label = _label;
            name = _name;
            id = _id;
        }

        ConstelationInfo& operator=(const ConstelationInfo& v)
        {
            label = v.label;
            name = v.name;
            id = v.id;
            return *this;
        };

        ConstelationInfo(const ConstelationInfo& v)
        {
            *this = v;
        }

        ConstelationInfo()
            : id { -1 }
        {
        }

        virtual ~ConstelationInfo()
        {
        }
    };

private:
    static std::vector<ConstelationInfo> constelationsList;
    static std::map<std::string, int> byConstelationType;

public:
    static void init();
    static void initFromDb();
    static int count();
    static bool get(const int idx, int& id, std::string& label, std::string& name);
    static bool getByTypeName(const std::string& name, std::string& output);

    static bool get(const int idx, ConstelationInfo& res);
    static bool get(const std::string& name, ConstelationInfo& res);
};

class CatalogType {
public:
    struct CatalogTypeInfo {
        std::string label;
        std::string name;
        int id;

        CatalogTypeInfo(const std::string& _label,
            const std::string& _name,
            const int _id)
        {
            label = _label;
            name = _name;
            id = _id;
        }

        CatalogTypeInfo& operator=(const CatalogTypeInfo& v)
        {
            label = v.label;
            name = v.name;
            id = v.id;
            return *this;
        };

        CatalogTypeInfo(const CatalogTypeInfo& v)
        {
            *this = v;
        }

        CatalogTypeInfo()
            : id { -1 }
        {
        }

        virtual ~CatalogTypeInfo()
        {
        }
    };

private:
    static std::vector<CatalogTypeInfo> catalogTypeList;
    static std::map<std::string, int> byCatalogType;

public:
    static void init();
    static void initFromDb();
    static int count();
    static bool get(const int idx, int& id, std::string& label, std::string& name);
    static bool getByTypeName(const std::string& name, std::string& output);
    static bool get(const int idx, CatalogTypeInfo& res);
    static bool get(const std::string& name, CatalogTypeInfo& res);
};

class ObjectType {
public:
    struct ObjectTypeInfo {
        std::string label;
        std::string name;
        int id;

        ObjectTypeInfo(const std::string& _label,
            const std::string& _name,
            const int _id)
        {
            label = _label;
            name = _name;
            id = _id;
        }

        ObjectTypeInfo& operator=(const ObjectTypeInfo& v)
        {
            label = v.label;
            name = v.name;
            id = v.id;
            return *this;
        };

        ObjectTypeInfo(const ObjectTypeInfo& v)
        {
            *this = v;
        }

        ObjectTypeInfo()
            : id { -1 }
        {
        }

        virtual ~ObjectTypeInfo()
        {
        }
    };

private:
    static std::vector<ObjectTypeInfo> objectTypeList;
    static std::map<std::string, int> byObjectType;

public:
    static void init();
    static void initFromDb();
    static int count();
    static bool get(const int idx, int& id, std::string& label, std::string& name);
    static bool getByType(const std::string& in, std::string& out);

    static bool get(const int idx, ObjectTypeInfo& res);
    static bool get(const std::string& name, ObjectTypeInfo& res);
};

class tlinsAstroCatalogItem {
private:
    unsigned long recordID;

    // Informacje na temat typu obiektu
    std::string name; // Astro object name
    std::string description; // Astro object description
    ObjectType::ObjectTypeInfo type; // Astro object type
    std::string typeDetails1; // Astro object type details 1
    std::string typeDetails2; // Astro object type details 2
    std::string typeDetails3; // Astro object type details 3
    Constelations::ConstelationInfo constelation; // Constelation

    // Dane dotyczace polozenia ruchu wlasnego, bledow, jasnosci, ...
    double RA; // + Right Ascension
    double DC; // + Declination
    double pmRA; // + Proper Motion in RA
    double pmDC; // + Proper Motion in DC
    double epRA; // + Central epoch for mean (RA)
    double epDC; // + Central epoch for mean (DC)
    double minErrRa; // + Minimal mean error on RAdeg
    double minErrDc; // + Minimal mean error on Dcdeg
    double errMeanRA; // + Mean error in RA
    double errMeanDC; // + Mean error in DC
    double errMeanPmRA; // + Mean error in Mean error in Proper Motion RA
    double errMeanPmDC; // + Mean error in Mean error in Proper Motion DC
    double magnitude; // + Magnitude
    double errMagnitude; // + Magnitude error
    double radialVelocity; // + Radial velocity
    double parallex; // + Parallex

    CatalogType::CatalogTypeInfo catalogType; // + Katalog type  - nowy
    std::string objectIdInCatalog; // Identyfikator obiektu w katalogu
    std::string objectDescription; // Dodatkowe opisy komentarze dotyczace obiektu

public:
    unsigned int getRecordID() const;
    const std::string& getName() const;
    const std::string& getDescription() const;
    const ObjectType::ObjectTypeInfo& getType() const;
    const std::string& getTypeDetails1() const;
    const std::string& getTypeDetails2() const;
    const std::string& getTypeDetails3() const;
    const Constelations::ConstelationInfo& getConstelation() const;

    double getRA() const; // Right Ascension
    double getDC() const; // Right Ascension
    double getPmRA() const; // Proper Motion in RA
    double getPmDC() const; // Proper Motion in DC
    double getEpRA() const; // Mean Epoch (RA)
    double getEpDC() const; // Mean Epoch (DC)
    double getMinErrRA() const; // Mean error in RA
    double getMinErrDC() const; // Mean error in DC
    double getErrMeanRA() const; // Mean error in RA
    double getErrMeanDC() const; // Mean error in DC
    double getErrMeanPmRA() const; // Mean error in Mean error in Proper Motion RA
    double getErrMeanPmDC() const; // Mean error in Mean error in Proper Motion DC
    double getMagnitude() const; // Magnitude
    double getErrMagnitude() const; // Magnitude error

    double getRadialVelocity() const // Radial velocity
    {
        return radialVelocity;
    }

    double getParallex() const
    {
        return parallex;
    }

    const CatalogType::CatalogTypeInfo& getCatalogType() const; // + Katalog type  - nowy
    const std::string& getObjectIdInCatalog() const; // Identyfikator obiektu w katalogu
    const std::string& getObjectDescription() const; // Dodatkowe opisy komentarze dotyczace obiektu

    // -----------------------------------------------------

    void setRecordID(const unsigned int v);
    void setName(const std::string& v);
    void setDescription(const std::string& v);
    void setType(const ObjectType::ObjectTypeInfo& v);
    void setTypeDetails1(const std::string& v);
    void setTypeDetails2(const std::string& v);
    void setTypeDetails3(const std::string& v);
    void setConstelation(const Constelations::ConstelationInfo& v);

    void setRA(const double v);
    void setDC(const double v);
    void setPmRA(const double v);
    void setPmDC(const double v);
    void setEpRA(const double v);
    void setEpDC(const double v);
    void setMinErrRA(const double v);
    void setMinErrDC(const double v);
    void setErrMeanRA(const double v);
    void setErrMeanDC(const double v);
    void setErrMeanPmRA(const double v);
    void setErrMeanPmDC(const double v);
    void setMagnitude(const double v);
    void setErrMagnitude(const double v);

    void setRadialVelocity(const double v)
    {
        radialVelocity = v;
    }

    void setParallex(const double v)
    {
        parallex = v;
    }

    void setCatalogType(const CatalogType::CatalogTypeInfo& v);
    void setObjectIdInCatalog(const std::string& v);
    void setObjectDescription(const std::string& v);

    // -----------------------------------------------------

    tlinsAstroCatalogItem& operator=(const tlinsAstroCatalogItem& v);
    tlinsAstroCatalogItem(const tlinsAstroCatalogItem& v);
    tlinsAstroCatalogItem();
    virtual ~tlinsAstroCatalogItem();
};

}

#endif // TLINSASTROCATALOGITEM_H
