#ifndef TLINSWPILOTVERTICALSTEPSDELTA_H
#define TLINSWPILOTVERTICALSTEPSDELTA_H

#include <QWidget>

namespace Ui {
class tlinsWPilotVerticalStepsDelta;
}

class tlinsWPilotVerticalStepsDelta : public QWidget
{
	Q_OBJECT

public:
	explicit tlinsWPilotVerticalStepsDelta(QWidget *parent = nullptr);
	~tlinsWPilotVerticalStepsDelta();

private:
	Ui::tlinsWPilotVerticalStepsDelta *ui;
};

#endif // TLINSWPILOTVERTICALSTEPSDELTA_H
