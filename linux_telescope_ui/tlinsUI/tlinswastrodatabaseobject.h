#ifndef TLINSWASTRODATABASEOBJECT_H
#define TLINSWASTRODATABASEOBJECT_H

#include "tlinswastrocatalog.h"
#include "tlinswastroobjecttype.h"
#include "tlinswcatalogobjecttype.h"
#include "tlinswconstelation.h"
#include "tlinswcoordinatedeclination.h"
#include "tlinswcoordinatedegris.h"
#include "tlinswcoordinatehourangle.h"
#include "tlinswdecimalvalue.h"
#include "tlinswobjectname.h"
#include <tlinsastrocatalogitem.h>

#include <QVBoxLayout>
#include <QWidget>
#include <memory>

namespace Ui {
class tlinsWAstroDatabaseObject;
}

class tlinsWAstroDatabaseObject : public QWidget {
    Q_OBJECT

private:
    tlinsWDecimalValue* centralEpochRa;
    tlinsWDecimalValue* centralEpochDc;

    QVBoxLayout* lobjCatalogObjectId;

    QVBoxLayout* lcentralEpochRa;
    QVBoxLayout* lcentralEpochDc;

public:
    void setMinimalInfo();
    void setReadOnly(const bool v);

public:
    void blockCatalogInfo(bool block);
    TlinsAstroBase::tlinsAstroCatalogItem getCatalogItem();
    void setCatalogItem(const TlinsAstroBase::tlinsAstroCatalogItem& v);
    void resetCatalogItem();
    void disableaTab(const int idx, const bool v);

public:
    explicit tlinsWAstroDatabaseObject(QWidget* parent = nullptr);
    ~tlinsWAstroDatabaseObject();

private:
    Ui::tlinsWAstroDatabaseObject* ui;
};

#endif // TLINSWASTRODATABASEOBJECT_H
