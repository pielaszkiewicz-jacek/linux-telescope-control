#ifndef TLINSASTROOBJECTCOORDINATE_H
#define TLINSASTROOBJECTCOORDINATE_H

#include "tlinswcoordinatedeclination.h"
#include "tlinswcoordinatedegris.h"
#include "tlinswcoordinatehourangle.h"
#include "tlinswdecimalvalue.h"
#include <QVBoxLayout>
#include <QWidget>

namespace Ui {
class tlinsAstroObjectCoordinate;
}

class tlinsAstroObjectCoordinate : public QWidget {
    Q_OBJECT

public:
    explicit tlinsAstroObjectCoordinate(QWidget* parent = 0);
    ~tlinsAstroObjectCoordinate();

private:
    Ui::tlinsAstroObjectCoordinate* ui;

    tlinsWCoordinateHourAngle raMinErr;
    QVBoxLayout lraMinErr;
    tlinsWCoordinateDeclination dcMinErr;
    QVBoxLayout ldcMinErr;

    tlinsWCoordinateHourAngle raMeanErr;
    QVBoxLayout lraMeanErr;
    tlinsWCoordinateDeclination dcMeanErr;
    QVBoxLayout ldcMeanErr;

    tlinsWDecimalValue raCentralEpoch;
    QVBoxLayout lraCentralEpoch;

    tlinsWDecimalValue dcCentralEpoch;
    QVBoxLayout ldcCentralEpoch;

    tlinsWCoordinateHourAngle raProperMotion;
    QVBoxLayout lraProperMotion;
    tlinsWCoordinateDeclination dcProperMotion;
    QVBoxLayout ldcProperMotion;

    tlinsWCoordinateHourAngle raProperMotionError;
    QVBoxLayout lraProperMotionError;
    tlinsWCoordinateDeclination dcProperMotionError;
    QVBoxLayout ldcProperMotionError;
};

#endif // TLINSASTROOBJECTCOORDINATE_H
