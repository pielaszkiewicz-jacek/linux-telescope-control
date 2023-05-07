#ifndef TLINSWASTROCATALOG_H
#define TLINSWASTROCATALOG_H

#include <QWidget>

namespace Ui {
class tlinsWAstroCatalog;
}

class tlinsWAstroCatalog : public QWidget {
    Q_OBJECT

public slots:
    void update();

signals:
    void valueChanged(std::string newValue);

public:
    bool setCurrent(const std::string& label);
    void setCurrent(const int idx);
    std::string getType() const;
    void disable();

public:
    explicit tlinsWAstroCatalog(QWidget* parent = 0);
    ~tlinsWAstroCatalog();

private:
    Ui::tlinsWAstroCatalog* ui;
};

#endif // TLINSWASTROCATALOG_H
