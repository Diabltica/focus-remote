//
// Created by thoma on 18/08/2022.
//

// You may need to build the project (run Qt uic code generator) to get
// "ui_IHM.h" resolved

#include "ihm.hpp"
#include "ui_IHM.h"

IHM::IHM(QWidget* parent)
  : QWidget(parent)
  , ui(new Ui::IHM)
{
    ui->setupUi(this);
}

IHM::~IHM()
{
    delete ui;
}
