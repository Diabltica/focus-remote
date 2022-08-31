//
// Created by Diabltica on 18/08/2022.
//
#ifndef IHM_H
#define IHM_H

#include "CameraControl.hpp"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class IHM; }
QT_END_NAMESPACE

class IHM : public QMainWindow
{
    Q_OBJECT

  public:
    IHM(QWidget *parent = nullptr);
    ~IHM();

  private slots:
    void on_ConnectButton_clicked(void);
    void on_zoomButton_clicked(void);

  private:
    std::unique_ptr <Camera> _connectedCamera;
    bool _isConnected = false;
    int _zoomIndex = 0;
    Ui::IHM *ui;
};
#endif // IHM_H
