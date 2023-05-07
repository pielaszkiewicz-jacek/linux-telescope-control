#include "tlinswmessagebox.h"

#include <QFont>
#include <QMessageBox>
#include <qmessagebox.h>

void tlinsWMessageBox::run()
{
    msgBox.exec();
}

tlinsWMessageBox::tlinsWMessageBox(int, int tFontSize, QString text)
{
    msgBox.addButton(QMessageBox::Ok);
    //    QFont f = msgBox.button(QMessageBox::Ok)->font();

    //    f.setPointSize(tFontSize);
    //    msgBox.button(QMessageBox::Ok)->setFont(f);

    msgBox.setText(text);
}
