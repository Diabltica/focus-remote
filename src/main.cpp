//
// Created by Diabltica on 30/07/2022.
//

#include "CameraControl.hpp"
#include "EDSDK_Header/EDSDK.h"
#include "ihm.hpp"
#include <QApplication>
#include <QtQuick>
#include <QtQuickControls2/qquickstyle.h>

int
main(int argc,char **argv)
{
//    try {
//        Camera mainCamera;
//
//        int currentValue = 0;
//        mainCamera.launchLiveView(kEdsEvfOutputDevice_TFT);
//        mainCamera.resetFocusPosition(&currentValue);
//        mainCamera.focusControl(250, &currentValue);
//        for (int i = 0; i < 20; ++i) {
//            mainCamera.exposureCompensation('i');
//        }
//        system("pause");
//        for (int i = 0; i < 41; ++i) {
//            mainCamera.exposureCompensation('d');
//        }
//        system("pause");
//
//    } catch (CameraException e) {
//        std::cout << e.what();
//    }
    QApplication app(argc, argv);
    QQuickStyle::setStyle("Material");
    IHM mainWindow;
    mainWindow.setWindowState(Qt::WindowMaximized);
    mainWindow.show();
    return app.exec();
}
