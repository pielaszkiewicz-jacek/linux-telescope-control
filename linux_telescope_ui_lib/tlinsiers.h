#ifndef TLINSIERS_H
#define TLINSIERS_H

namespace TlinsAstroBase {

class tlinsIERS {
private:
    int year;
    int month;
    int day;
    double pmx;
    double pmy;
    double deltaUt;
    double dPsi;
    double dEpsilon;
    double dx;
    double dy;

public:
    tlinsIERS(const tlinsIERS& v);
    tlinsIERS();
    virtual ~tlinsIERS();
    tlinsIERS& operator=(const tlinsIERS& v);

    int getYear() const;
    int getMonth() const;
    int getDay() const;
    double getPmx() const;
    double getPmy() const;
    double getDeltaUt() const;
    double getDPsi() const;
    double getDEpsilon() const;
    double getDx() const;
    double getDy() const;

    //
    // SET
    //
    void setYear(int v);
    void setMonth(int v);
    void setDay(int v);
    void setPmx(double v);
    void setPmy(double v);
    void setDeltaUt(double v);
    void setDPsi(double v);
    void setDEpsilon(double v);
    void setDx(double v);
    void setDy(double v);
};

}

#endif // TLINSIERS_H
