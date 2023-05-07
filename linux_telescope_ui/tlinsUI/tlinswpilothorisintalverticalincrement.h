#ifndef TLINSWPILOTHORISINTALVERTICALINCREMENT_H
#define TLINSWPILOTHORISINTALVERTICALINCREMENT_H

#include <QWidget>
#include <QJsonObject>
#include <tlinspilotshortcutsdefinitioninterface.h>


namespace Ui {
class tlinsWPilotHorisintalVerticalIncrement;
}

class tlinsWPilotHorisintalVerticalIncrement : public QWidget,
                                               public TlinsAstroBase:: tlinsPilotShortcutsDefinitionInterface
{
	Q_OBJECT

public slots:
//	void horisontalAxisSelected();
//	void verticalAxisSelected();

public:
	virtual void setParameters( const QJsonObject &doc );
	virtual void getParameters( QJsonObject &doc );
	virtual QWidget *getWidget();
	virtual void reset();
	virtual TlinsAstroBase:: tlinsPilotShortcutsDefinitionValidMode getValidMode();

	explicit tlinsWPilotHorisintalVerticalIncrement(QWidget *parent = nullptr);
	~tlinsWPilotHorisintalVerticalIncrement();

private:
	Ui::tlinsWPilotHorisintalVerticalIncrement *ui;
};

#endif // TLINSWPILOTHORISINTALVERTICALINCREMENT_H
