//
// Created by Diabltica on 18/08/2022.
//
#ifndef IHM_H
#define IHM_H

#include "CameraControl.hpp"

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class IHM;
}
QT_END_NAMESPACE

class IHM : public QMainWindow
{
    Q_OBJECT

  public:
    IHM(QWidget* parent = nullptr);
    ~IHM();

  private slots:
    void on_ConnectButton_clicked(void);
    void on_zoomButton_clicked(void);
    void on_FocusPB_clicked(void);
    void on_FocusPM_clicked(void);
    void on_FocusPS_clicked(void);
    void on_FocusMB_clicked(void);
    void on_FocusMM_clicked(void);
    void on_FocusMS_clicked(void);
    void on_PositionL_clicked(void);
    void on_PositionR_clicked(void);
    void on_PositionU_clicked(void);
    void on_PositionD_pressed(void);
    void on_ExposureI_clicked(void);
    void on_ExposureD_clicked(void);
    void on_PositionD_released(void);

  private:
    std::unique_ptr<Camera> _connectedCamera;
    bool _isConnected = false;
    int _zoomIndex = 0;
    bool _isPressed = false;
    QTimer _timer;
    const char* _exposureValue[41] = {
        "-5",     "-4 2/3", "-4 1/2", "-4 1/3", "-4",     "-3 2/3", "-3 1/2",
        "-3 1/3", "-3",     "-2 2/3", "-2 1/2", "-2 1/3", "-2",     "-1 2/3",
        "-1 1/2", "-1 1/3", "-1",     "-0 2/3", "-0 1/2", "-0 1/3", "0",
        "0 1/3",  "0 1/2",  "0 2/3",  "1",      "1 1/3",  "1 1/2",  "1 2/3",
        "2",      "2 1/3",  "2 1/2",  "2 2/3",  "3",      "3 1/3",  "3 1/2",
        "3 2/3",  "4",      "4 1/3",  "4 1/2",  "4 2/3",  "5"
    };

    void _buttonState(bool state);

    Ui::IHM* ui;
};
#endif // IHM_H
