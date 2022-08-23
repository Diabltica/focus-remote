//
// Created by Diabltica on 18/08/2022.
//

// You may need to build the project (run Qt uic code generator) to get
// "ui_IHM.h" resolved

#include "ihm.hpp"
#include "ui_IHM.h"
#include <iostream>
#include <unistd.h>

IHM::IHM(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::IHM)
{
    ui->setupUi(this);
}

IHM::~IHM()
{
    delete ui;
}

void IHM::on_ConnectButton_clicked(void){
    if(!_isConnected){
        try {
            _connectedCamera.reset(new Camera);
            ui->ConnectButton->setText("Connected");
            _isConnected = true;
        } catch (CameraException e) {
            QString output(e.what());
            ui->ErrorLabel->setText("Erreur");
        }
    }else{
        _isConnected = false;
        _connectedCamera -> disconnect();
        _connectedCamera.reset();
        ui->ConnectButton->setText("Disconnected");
    }
}

void IHM::on_ZoomButton_clicked(void){
//    switch (_zoomIndex) {
//        case 1:
//            ui->ZoomButton->setIcon("icons/x1.png");
//    }
    QPixmap pixmap("icons/x1.png");
    QIcon ButtonIcon(pixmap);
//    ui->ZoomButton->setIcon(ButtonIcon);
//    ui->ZoomButton->setIconSize(pixmap.rect().size());
}