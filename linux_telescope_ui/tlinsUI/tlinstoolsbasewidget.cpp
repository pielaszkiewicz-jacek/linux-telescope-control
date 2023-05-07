#include "tlinstoolsbasewidget.h"
#include "ui_tlinstoolsbasewidget.h"

#include <QGridLayout>

tlinsToolsBaseWidget::tlinsToolsBaseWidget(QWidget* widget,
    const QString& title,
    const QString& icon_,
    QWidget* parent)
    : QWidget(parent)
    , icon { icon_ }
    , ui(new Ui::tlinsToolsBaseWidget)
{
    ui->setupUi(this);

    ui->icon->setIcon(icon);

    // Ustawienie widgeta
    gl.addWidget(widget);
    ui->widget->setLayout(&gl);

    // Tytul
    ui->title->setText(title);
}

tlinsToolsBaseWidget::~tlinsToolsBaseWidget()
{
    delete ui;
}
