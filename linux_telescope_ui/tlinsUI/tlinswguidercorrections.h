#ifndef TLINSWGUIDERCORRECTIONS_H
#define TLINSWGUIDERCORRECTIONS_H

#include <QWidget>

namespace Ui {
class tlinsWGuiderCorrections;
}

class tlinsWGuiderCorrections : public QWidget
{
	Q_OBJECT

public:
	explicit tlinsWGuiderCorrections(QWidget *parent = nullptr);
	~tlinsWGuiderCorrections();

private:
	Ui::tlinsWGuiderCorrections *ui;
};

#endif // TLINSWGUIDERCORRECTIONS_H
