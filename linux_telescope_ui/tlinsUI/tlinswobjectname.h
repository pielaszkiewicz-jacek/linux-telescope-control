#ifndef TLINSWOBJECTNAME_H
#define TLINSWOBJECTNAME_H

#include <QWidget>
#include <string>

namespace Ui {
class tlinsWObjectName;
}

class tlinsWObjectName : public QWidget {
    Q_OBJECT

public slots:
    void update();

signals:
    void valueChanged(std::string newValue);

public:
    std::string getValue() const;
    void setValue(const std::string& value);

public:
    explicit tlinsWObjectName(QWidget* parent = 0);
    ~tlinsWObjectName();

private:
    Ui::tlinsWObjectName* ui;
};

#endif // TLINSWOBJECTNAME_H
