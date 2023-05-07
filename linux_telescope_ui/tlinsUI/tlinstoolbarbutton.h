#ifndef TLINSTOOLBARBUTTON_H
#define TLINSTOOLBARBUTTON_H

#include <QIcon>
#include <QWidget>
#include <functional>

namespace Ui {
class tlinsToolBarButton;
}

class tlinsUIMainWindow;

class tlinsToolBarButton : public QWidget {
    Q_OBJECT

private:
    QIcon icon;
    std::function<void()> fun;
    tlinsUIMainWindow* parent;

public slots:
    void buttonPressed();

public:
    void setChecked(const bool v);

public:
    explicit tlinsToolBarButton(const QString& iconName,
        const QString& title,
        std::function<void()> fun,
        tlinsUIMainWindow* parent_,
        QWidget* parent = nullptr);
    ~tlinsToolBarButton();

private:
    Ui::tlinsToolBarButton* ui;
};

#endif // TLINSTOOLBARBUTTON_H
