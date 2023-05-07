#ifndef TLINSWCONSTELATION_H
#define TLINSWCONSTELATION_H

#include <QWidget>

namespace Ui {
class tlinsWConstelation;
}

class tlinsWConstelation : public QWidget {
    Q_OBJECT

public slots:
    void update();

signals:
    void valueChanged(std::string newValue);

public:
    bool setCurrent(const std::string& label);
    void setCurrent(const int idx);
    std::string getConstelation() const;

public:
    explicit tlinsWConstelation(QWidget* parent = 0);
    ~tlinsWConstelation();

private:
    Ui::tlinsWConstelation* ui;
};

#endif // TLINSWCONSTELATION_H
