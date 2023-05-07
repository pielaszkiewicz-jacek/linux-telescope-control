#ifndef TLINSWASTROOBJECTTYPE_H
#define TLINSWASTROOBJECTTYPE_H

#include <QWidget>

namespace Ui {
class tlinsWAstroObjectType;
}

class tlinsWAstroObjectType : public QWidget {
    Q_OBJECT

public slots:
    void update();

signals:
    void valueChanged(std::string newValue);

public:
    bool setCurrent(const std::string& label);
    void setCurrent(const int idx);
    std::string getType() const;

public:
    explicit tlinsWAstroObjectType(QWidget* parent = 0);
    ~tlinsWAstroObjectType();

private:
    Ui::tlinsWAstroObjectType* ui;
};

#endif // TLINSWASTROOBJECTTYPE_H
