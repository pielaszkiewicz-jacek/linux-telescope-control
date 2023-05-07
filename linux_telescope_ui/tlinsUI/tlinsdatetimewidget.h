#ifndef TLINSDATETIMEWIDGET_H
#define TLINSDATETIMEWIDGET_H

#include <QWidget>

namespace Ui {
class tlinsDateTimeWidget;
}

class tlinsDateTimeWidget : public QWidget {
    Q_OBJECT

private slots:
    void acceptedSlot();

public slots:
    void setStatusSlot(std::string str);

signals:
    void setStatus(std::string);

public:
    explicit tlinsDateTimeWidget(QWidget* parent = nullptr);
    ~tlinsDateTimeWidget();

private:
    Ui::tlinsDateTimeWidget* ui;
};

#endif // TLINSDATETIMEWIDGET_H
