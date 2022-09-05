//
// Created by Diabltica on 30/07/2022.
//


#include "src/UI/ihm.hpp"
#include <QApplication>
#include "Headers/configModule.hpp"

int
main(int argc,char **argv)
{
    config a;
    a.loadConfig();

    QApplication app(argc, argv);
    IHM mainWindow;
    mainWindow.setWindowState(Qt::WindowMaximized);
    mainWindow.show();
//    return app.exec();
    return 0;
}
