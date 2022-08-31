//
// Created by Diabltica on 18/08/2022.
//

// You may need to build the project (run Qt uic code generator) to get
// "ui_IHM.h" resolved

#include "ihm.hpp"
#include "ui_IHM.h"
#include <iostream>
#include <unistd.h>

IHM::IHM(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::IHM)
{
    ui->setupUi(this);
}

IHM::~IHM()
{
    delete ui;
}

void
IHM::on_ConnectButton_clicked(void)
{
    if (!_isConnected) {
        try {
            _connectedCamera.reset(new Camera);
            ui->ConnectButton->setText("Connected");
            _connectedCamera->launchLiveView(kEdsEvfOutputDevice_TFT);
            _isConnected = true;
        } catch (CameraException e) {
            QString output;
            output = e.what();
            ui->ErrorLabel->setText("Erreur " + output);
        }
    } else {
        _isConnected = false;
        _connectedCamera->disconnect();
        _connectedCamera.reset();
        ui->ConnectButton->setText("Disconnected");
    }
}

void
IHM::on_zoomButton_clicked(void)
{
    switch (_zoomIndex) {
        case 0:
            ui->zoomButton->setText("x1");
            _zoomIndex++;
            break;
        case 1:
            ui->zoomButton->setText("x5");
            _zoomIndex++;
            break;
        case 2:
            ui->zoomButton->setText("x10");
            _zoomIndex = 0;
            break;
    }
}