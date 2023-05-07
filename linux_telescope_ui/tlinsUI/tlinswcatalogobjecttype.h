#ifndef TLINSWCATALOGOBJECTTYPE_H
#define TLINSWCATALOGOBJECTTYPE_H

#include <QWidget>

namespace Ui {
class tlinsWCatalogObjectType;
}

class tlinsWCatalogObjectType : public QWidget {
    Q_OBJECT

public slots:
    void update();

signals:
    void valueChanged(std::string newValue);

public:
    std::string getID() const;
    void setID(const std::string& id);
    void disable();

public:
    explicit tlinsWCatalogObjectType(QWidget* parent = 0);
    ~tlinsWCatalogObjectType();

private:
    Ui::tlinsWCatalogObjectType* ui;
};

#endif // TLINSWCATALOGOBJECTTYPE_H
