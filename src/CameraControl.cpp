//
// Created by Diabltica on 02/08/2022.
//

#include "CameraControl.h"
#include <unistd.h>

Camera::Camera()
{
    EdsCameraListRef cameraList = nullptr;
    EdsUInt32 count = 0;
    err = EdsInitializeSDK();
    if (err != EDS_ERR_OK) { // UTILISER DES THROWS
        cout << "SDK INITIALISATION FAILED WAIT FOR EXIT" << endl;
        exit(84);
    }
    err = EdsGetCameraList(&cameraList);
    if (err != EDS_ERR_OK) {
        exit(err);
    }
    err = EdsGetChildCount(cameraList, &count);
    if (count == 0) {
        err = EDS_ERR_DEVICE_NOT_FOUND;
        exit(err);
    }
    err = EdsGetChildAtIndex(cameraList, 0, &cameraRef);
    err = EdsOpenSession(cameraRef);

    EdsGetPropertyData(cameraRef,
                       kEdsPropID_Evf_ZoomPosition,
                       0,
                       sizeof(EdsPoint),
                       &zoomCoordinate);
    exposureIndex = 20;
    EdsSetPropertyData(cameraRef,
                       kEdsPropID_ExposureCompensation,
                       0,
                       sizeof(EdsUInt32),
                       &exposureValue[exposureIndex]);
}

Camera::~Camera()
{
    EdsCloseSession(cameraRef);
    EdsRelease(cameraRef);
    EdsTerminateSDK();
}

EdsError
Camera::launchLiveView(EdsPropertyID outputScreen)
{
    EdsUInt32 device;
    err = EdsGetPropertyData(
      cameraRef, kEdsPropID_Evf_OutputDevice, 0, sizeof(device), &device);

    if (err == EDS_ERR_OK) {
        device |= outputScreen;
        err = EdsSetPropertyData(cameraRef,
                                 kEdsPropID_Evf_OutputDevice,
                                 outputScreen,
                                 sizeof(device),
                                 &device);
    }
    return err;
}

EdsError
Camera::focusControl(int newValue, int* currentValue)
{
    int indexModifier = 32768;
    int delta = *currentValue - newValue;
    if (delta < 0) {
        delta = -delta;
        indexModifier = 0;
    }
    int r;
    int Bmove = delta / B_STEP;
    r = delta % (int)B_STEP;
    int Mmove = r / M_STEP;
    r = delta % int(M_STEP);

    for (int i = 0; i < Bmove; i++) {
        EdsSendCommand(
          cameraRef, kEdsCameraCommand_DriveLensEvf, indexModifier + 3);
        usleep(200000);
    }
    for (int i = 0; i < Mmove; i++) {
        EdsSendCommand(
          cameraRef, kEdsCameraCommand_DriveLensEvf, indexModifier + 2);
        usleep(100000);
    }
    for (int i = 0; i < r; i++) {
        EdsSendCommand(
          cameraRef, kEdsCameraCommand_DriveLensEvf, indexModifier + 1);
        usleep(100000);
    }
    *currentValue = newValue;
}

void
Camera::resetFocusPosition(int* currentValue)
{
    for (int i = 0; i < 13; ++i) {
        EdsSendCommand(
          cameraRef, kEdsCameraCommand_DriveLensEvf, kEdsEvfDriveLens_Near3);
        usleep(200000);
    }
    *currentValue = 395;
}

EdsError
Camera::zoomControl()
{
    EdsInt32 zoom[3] = { 1, 5, 10 };
    if (zoomIndex == 2) {
        zoomIndex = 0;
    } else {
        zoomIndex++;
    }
    err = EdsSetPropertyData(
      cameraRef, kEdsPropID_Evf_Zoom, 0, sizeof(EdsUInt32), &zoom[zoomIndex]);
    return err;
}
EdsError
Camera::zoomPosition(char direction)
{
    switch (direction) {
        case 'u':
            if (isOnScreen('v', 1)) {
                zoomCoordinate.y += POSITION_STEP;
            }
            break;
        case 'd':
            if (isOnScreen('v', -1)) {
                zoomCoordinate.y -= POSITION_STEP;
            }
            break;
        case 'r':
            if (isOnScreen('h', 1)) {
                zoomCoordinate.x += POSITION_STEP;
            }
            break;
        case 'l':
            if (isOnScreen('h', -1)) {
                zoomCoordinate.x -= POSITION_STEP;
            }
            break;
        default:
            break;
    }
    err = EdsSetPropertyData(cameraRef,
                             kEdsPropID_Evf_ZoomPosition,
                             0,
                             sizeof(EdsPoint),
                             &zoomCoordinate);
    return err;
}
bool
Camera::isOnScreen(char axis, int direction)
{
    if (axis == 'v' && direction == 1) { // Vertical axis
        return (zoomCoordinate.y + POSITION_STEP <= HEIGTH);
    } else if (axis == 'v') {
        return (zoomCoordinate.y - POSITION_STEP >= 0);
    } else if (direction == 1) { // Horizontal axis
        return (zoomCoordinate.x + POSITION_STEP <= WIDTH);
    } else {
        return (zoomCoordinate.x - POSITION_STEP >= 0);
    }
}

EdsError
Camera::exposureCompensation(char operation)
{
    if (operation == 'd') { // Increase
        if (exposureIndex - 1 >= 0) {
            exposureIndex -= 1;
            err = EdsSetPropertyData(cameraRef,
                                     kEdsPropID_ExposureCompensation,
                                     0,
                                     sizeof(EdsUInt32),
                                     &exposureValue[exposureIndex]);
        }
    } else if (operation == 'i') {
        if (exposureIndex + 1 <= 41) {
            exposureIndex += 1;
            err = EdsSetPropertyData(cameraRef,
                                     kEdsPropID_ExposureCompensation,
                                     0,
                                     sizeof(EdsUInt32),
                                     &exposureValue[exposureIndex]);
        }
    }
    return err;
}
