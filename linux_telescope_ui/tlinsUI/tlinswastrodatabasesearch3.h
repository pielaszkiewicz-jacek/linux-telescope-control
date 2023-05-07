#ifndef TLINSWASTRODATABASESEARCH3_H
#define TLINSWASTRODATABASESEARCH3_H

#include "tlinswastrocatalog.h"
#include "tlinswastroobjecttype.h"
#include "tlinswcatalogobjecttype.h"
#include "tlinswconstelation.h"
#include "tlinswcoordinatedeclination.h"
#include "tlinswcoordinatedegris.h"
#include "tlinswcoordinatehourangle.h"
#include "tlinswdecimalvalue.h"
#include "tlinswobjectname.h"

#include <QVBoxLayout>
#include <QWidget>

namespace Ui {
class tlinsWAstroDatabaseSearch3;
}

class tlinsWAstroDatabaseSearch3 : public QWidget {
    Q_OBJECT

private slots:
    void disableEnableRA();
    void disableEnableDC();
    void disableEnableRadius();
    void disableEnableMagnitudeFrom();
    void disableEnableMagnitudeTo();
    void disableEnableCatalog();
    void disableEnableObjectType();
    void disableEnableObjectName();
    void disableEnableObjectIdInCatalog();
    void disableEnableObjectConstelation();

public:
    std::string getCondition() const;

public:
    explicit tlinsWAstroDatabaseSearch3(QWidget* parent = 0);
    ~tlinsWAstroDatabaseSearch3();

private:
    Ui::tlinsWAstroDatabaseSearch3* ui;
};

#endif // TLINSWASTRODATABASESEARCH3_H
