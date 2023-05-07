#include "tlinstoolbarbutton.h"
#include "ui_tlinstoolbarbutton.h"

#include <qdebug.h>
#include <tlinsuimainwindow.h>

tlinsToolBarButton::tlinsToolBarButton(const QString& iconName,
    const QString& title,
    std::function<void()> fun_,
    tlinsUIMainWindow* parent_,
    QWidget* parent)
    : QWidget { parent }
    , icon { iconName }
    , fun { fun_ }
    , parent { parent_ }
    , ui { new Ui::tlinsToolBarButton }
{
    ui->setupUi(this);
    ui->toolButton->setIcon(icon);
    ui->toolButton->setText(title);
    ui->toolButton->setChecked(false);
}

void tlinsToolBarButton::setChecked(const bool v)
{
    if (v) {
        ui->toolButton->setChecked(true);
    } else {
        ui->toolButton->setChecked(false);
    }
}

void tlinsToolBarButton::buttonPressed()
{
    fun();
    parent->setCurrentWidget(this);
}

tlinsToolBarButton::~tlinsToolBarButton()
{
    delete ui;
}
