#ifndef TLINSWMESSAGEBOX_H
#define TLINSWMESSAGEBOX_H

#include <QMessageBox>

class tlinsWMessageBox {
private:
    QMessageBox msgBox;

public:
    void run();
    tlinsWMessageBox(int bfontSize, int tFontSize, QString text);
};

#endif // TLINSWMESSAGEBOX_H
