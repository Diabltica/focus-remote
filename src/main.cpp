//
// Created by Diabltica on 30/07/2022.
//


#include "ihm.hpp"
#include <QApplication>

int
main(int argc,char **argv)
{
    QApplication app(argc, argv);
    IHM mainWindow;
    mainWindow.setWindowState(Qt::WindowMaximized);
    mainWindow.show();
    return app.exec();
}
