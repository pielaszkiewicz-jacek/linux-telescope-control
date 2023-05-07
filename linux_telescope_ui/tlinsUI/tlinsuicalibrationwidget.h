#ifndef TLINSUICALIBRATIONWIDGET_H
#define TLINSUICALIBRATIONWIDGET_H

#include "tlinsastrosearchwindow.h"
#include "tlinscalibrationitemmodel.h"
#include "tlinscommunicationthread.h"
#include "tlinswcoordinatedeclination.h"
#include "tlinswcoordinatedegris.h"
#include "tlinswcoordinatehourangle.h"

#include <QWidget>

#include <thread>

#include <Eigen/Dense>
#include <Eigen/Geometry>

namespace Ui {
class tlinsUICalibrationWidget;
}

class tlinsUICalibrationWidget : public QWidget {
    Q_OBJECT

public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

public:
    enum class uiChanges {
        NO_CHANGES = 0,
        START_CALIBRATION = 1,
        SET_REFERENCE = 2,
        CONFIRM_REFERENCE = 3,
        CLOSE_CALIBRATION = 4,
    };

private:
    // Licznik obiektow referencyjnych
    int oCount;
    std::unique_ptr<std::thread> debugThread;
    std::atomic<bool> debugThreadBusy;

private:
    void closeCalibration();
    void setReferenceObject(const int row = -1);
    void setReferenceObject2(const int row = -1);
    void setVelocityMesarument(const int row = -1);
    void closeVelocityMesarument(const int row = -1);

    enum class testDataType { REF = 1,
        SPEED = 2,
        CLOSE_SPEED = 3,
        CLOSE_CALIB = 4 };

    struct testData {
        testDataType type;
        int deltaTime;

        double xRef;
        double yRef;

        double xV;
        double yV;

        int row;
        int vRow;

        virtual ~testData() = default;
        testData() = default;
        testData(const testData& v) = default;
        testData& operator=(const testData& v) = default;
    };
    unsigned int currentRefObjectRow;

    Eigen::Matrix3d attitude;

public:
    void calibrationStatusEmit(std::string m, uiChanges uiCh);
    void updateRowStatusEmit(const TlinsAstroBase::tlinsAstroCalibrationItem::calibrationStatus status, int row);

signals:
    void updateRowStatus(TlinsAstroBase::tlinsAstroCalibrationItem::calibrationStatus status, int row);
    void calibrationStatus(std::string, uiChanges uiCh);

public slots:
    void updateRowStatusSlot(const TlinsAstroBase::tlinsAstroCalibrationItem::calibrationStatus status, int row);
    void calibrationStatusSlot(std::string str, uiChanges uiCh);
    void on_btSetReference_clicked();
    void on_btCloseCalibration_clicked();
    void on_btStartCalibration_clicked();

    void checkBoxEnableDebugSlot();

    void on_pbGenerateMatrix_clicked();

    void asDeferredClicked();
    void confirmDeferred_clicked();
    void errorsStateChanged(bool s);
    void on_btSave_clicked();
    void on_btMoveUp_clicked();
    void on_btMoveDown_clicked();
    void on_btSearchObject_clicked();
    void on_btRemoveObject_clicked();
    void dataSelected();
    void on_btLoad_clicked();

public:
    explicit tlinsUICalibrationWidget(QWidget* parent = nullptr);
    ~tlinsUICalibrationWidget();

private:
    tlinsAstroSearchWindow searchWindow;
    tlinsCalibrationItemModel dataModel;

    Ui::tlinsUICalibrationWidget* ui;
};

#endif // TLINSUICALIBRATIONWIDGET_H
