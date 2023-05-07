#ifndef TLINSENVIRONMENT_H
#define TLINSENVIRONMENT_H

class tlinsEnvironment {
private:
    // Cisnienie atmosferyczne (HPa)
    double ambientPressure;

    // Temperatura
    double temperature;

    // Wilgotnosc
    double realHumidity;

    // Efektywny kolor
    double effectiveColor;

public:
    static tlinsEnvironment& getInstance()
    {
        static tlinsEnvironment instance {};
        return instance;
    }

    double getAmbientPressure() const
    {
        return ambientPressure;
    }

    double getTemperature() const
    {
        return temperature;
    }

    double getRealHumidity() const
    {
        return realHumidity;
    }

    double getEffectiveColor() const
    {
        return effectiveColor;
    }

    void setAmbientPressure(const double v)
    {
        ambientPressure = v;
    }

    void setTemperature(const double v)
    {
        temperature = v;
    }

    void setRealHumidity(const double v)
    {
        realHumidity = v;
    }

    void setEffectiveColor(const double v)
    {
        effectiveColor = v;
    }

    virtual ~tlinsEnvironment();

private:
    tlinsEnvironment();
};

#endif // TLINSENVIRONMENT_H
