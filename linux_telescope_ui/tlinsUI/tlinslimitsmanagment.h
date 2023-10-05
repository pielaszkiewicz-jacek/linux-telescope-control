#ifndef TLINSLIMITSMANAGMENT_H
#define TLINSLIMITSMANAGMENT_H

#include <QWidget>

namespace Ui {
class tlinsLimitsManagmentWidget;
}

class tlinsLimitsManagmentWidget : public QWidget {
    Q_OBJECT

private:
    double rX;
    double rY;
    double rZ;

    double rAlfa;
    double rBeta;

    double lX;
    double lY;
    double lZ;

    double lAlfa;
    double lBeta;

public:
    explicit tlinsLimitsManagmentWidget(QWidget* parent = nullptr);
    ~tlinsLimitsManagmentWidget();

public slots:
    void slotUpdateLeftPositionInfo(const double x, const double y, const double z, const double alfa, const double beta);
    void slotUpdateRightPositionInfo(const double x, const double y, const double z, const double alfa, const double beta);
    void slotStatus(const QString msg);
    void on_pbStart_clicked();
    void on_pbStop_clicked();
    void on_pbDevLeft_clicked();
    void on_pbDevRight_clicked();

    void newLimit();
    void addLimit();
    void removeLimit();
    void storeLimit();
    void loadLimit();

signals:
    void updateLeftPositionInfo(const double x, const double y, const double z, const double alfa, const double beta);
    void updateRightPositionInfo(const double x, const double y, const double z, const double alfa, const double beta);
    void status(const QString msg);

private:
    Ui::tlinsLimitsManagmentWidget* ui;
};

#endif // TLINSLIMITSMANAGMENT_H
