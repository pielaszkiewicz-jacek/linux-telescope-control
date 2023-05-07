#ifndef TLINSSINGLECOORDINATE_H
#define TLINSSINGLECOORDINATE_H

#include <QWidget>

namespace Ui {
class tlinsSingleCoordinate;
}

class tlinsSingleCoordinate : public QWidget
{
    Q_OBJECT

public:
    explicit tlinsSingleCoordinate(QWidget *parent = 0);
    ~tlinsSingleCoordinate();

private:
    Ui::tlinsSingleCoordinate *ui;
};

#endif // TLINSSINGLECOORDINATE_H
