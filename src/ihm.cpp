//
// Created by Diabltica on 18/08/2022.
//

#include "ihm.hpp"
#include "ui_IHM.h"
#include <iostream>
#include <unistd.h>

IHM::IHM(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::IHM)
{
    ui->setupUi(this);
    _buttonState(false);
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
            ui->ExposureIndicator->setText(_exposureValue[_connectedCamera->getExposureIndex()]);
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
    _buttonState(_isConnected);
}

void
IHM::_buttonState(bool state)
{
    ui->zoomButton->setEnabled(state);
    ui->ExposureD->setEnabled(state);
    ui->ExposureI->setEnabled(state);
    ui->PositionD->setEnabled(state);
    ui->PositionU->setEnabled(state);
    ui->PositionR->setEnabled(state);
    ui->PositionL->setEnabled(state);
    ui->FocusMB->setEnabled(state);
    ui->FocusMM->setEnabled(state);
    ui->FocusMS->setEnabled(state);
    ui->FocusPB->setEnabled(state);
    ui->FocusPM->setEnabled(state);
    ui->FocusPS->setEnabled(state);
}

void
IHM::on_zoomButton_clicked(void)
{
    switch (_zoomIndex) {
        case 0:
            ui->zoomButton->setText("x5");
            _zoomIndex++;
            break;
        case 1:
            ui->zoomButton->setText("x10");
            _zoomIndex++;
            break;
        case 2:
            ui->zoomButton->setText("x1");
            _zoomIndex = 0;
            break;
    }
    _connectedCamera->zoomControl();
}

void
IHM::on_FocusPB_clicked(void)
{
    _connectedCamera->focusControl(int(_connectedCamera->getFocusValue() + B_STEP));
}

void
IHM::on_FocusPM_clicked(void)
{
    _connectedCamera->focusControl(int(_connectedCamera->getFocusValue() + M_STEP));
}

void
IHM::on_FocusPS_clicked(void)
{
    _connectedCamera->focusControl(int(_connectedCamera->getFocusValue() + 1));
}

void
IHM::on_FocusMB_clicked(void)
{
    _connectedCamera->focusControl(int(_connectedCamera->getFocusValue() - B_STEP));
}

void
IHM::on_FocusMM_clicked(void)
{
    _connectedCamera->focusControl(int(_connectedCamera->getFocusValue() - M_STEP));
}

void
IHM::on_FocusMS_clicked(void)
{
    _connectedCamera->focusControl(int(_connectedCamera->getFocusValue() - 1));
}

void
IHM::on_PositionD_pressed(void)
{
    _isPressed = true;
    while(_isPressed){
        _connectedCamera->zoomPosition('d');

    }

        _timer.start(1);
}

void
IHM::on_PositionD_released(void)
{
//    _isPressed = false;
_timer.stop();
}
void
IHM::on_PositionU_clicked(void)
{
    _connectedCamera->zoomPosition('u');
}

void
IHM::on_PositionR_clicked(void)
{
    _connectedCamera->zoomPosition('r');
}

void
IHM::on_PositionL_clicked(void)
{
    _connectedCamera->zoomPosition('l');
}

void
IHM::on_ExposureI_clicked(void)
{
    _connectedCamera->exposureCompensation('i');
    ui->ExposureIndicator->setText(_exposureValue[_connectedCamera->getExposureIndex()]);
}

void
IHM::on_ExposureD_clicked(void)
{
    _connectedCamera->exposureCompensation('d');
    ui->ExposureIndicator->setText(_exposureValue[_connectedCamera->getExposureIndex()]);
}