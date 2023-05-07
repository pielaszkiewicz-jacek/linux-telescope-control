#ifndef TLINSTOOLSBASEWIDGET_H
#define TLINSTOOLSBASEWIDGET_H

#include <QIcon>
#include <QVBoxLayout>
#include <QWidget>

namespace Ui {
class tlinsToolsBaseWidget;
}

class tlinsToolsBaseWidget : public QWidget {
    Q_OBJECT

    QVBoxLayout gl;
    QIcon icon;

public:
    explicit tlinsToolsBaseWidget(QWidget* widget,
        const QString& title,
        const QString& icon,
        QWidget* parent = nullptr);
    ~tlinsToolsBaseWidget();

private:
    Ui::tlinsToolsBaseWidget* ui;
};

#endif // TLINSTOOLSBASEWIDGET_H
