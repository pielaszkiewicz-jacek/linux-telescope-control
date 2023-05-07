#ifndef TLINSVALUEABSTRACT_H
#define TLINSVALUEABSTRACT_H

class tlinsValueAbstract {
public:
    tlinsValueAbstract();

    virtual double getValue() const = 0;
    virtual ~tlinsValueAbstract()
    {
    }
};

#endif // TLINSVALUEABSTRACT_H
