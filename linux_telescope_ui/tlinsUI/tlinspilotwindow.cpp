#include "tlinspilotwindow.h"
#include "ui_tlinspilotwindow.h"

#include <QDebug>
#include <QSettings>
#include <QSize>

tlinsPilotWindow::tlinsPilotWindow(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::tlinsPilotWindow)
{
    ui->setupUi(this);
}

void tlinsPilotWindow::moveEvent(QMoveEvent* event)
{
    xPos = event->pos().x();
    yPos = event->pos().y();
}

void tlinsPilotWindow::resizeEvent(QResizeEvent*)
{
}

void tlinsPilotWindow::fullWindow(int)
{
    QSettings settings("PilotWindow", "PilotWindow");
    settings.setValue("geometry", saveGeometry());
}

tlinsPilotWindow::~tlinsPilotWindow()
{
    delete ui;
}
