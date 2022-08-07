//
// Created by Diabltica on 02/08/2022.
//

#include "CameraControl.h"
#include <unistd.h>

Camera::Camera() {
    EdsCameraListRef cameraList = NULL;
    EdsUInt32 count = 0;
    err = EdsInitializeSDK();
    if (err == EDS_ERR_OK) {
    } else {
        cout << "SDK INITIALISATION FAILED WAIT FOR EXIT" << endl;
        exit(84);
    }
    err = EdsGetCameraList(&cameraList);
    if (err == EDS_ERR_OK) {
        err = EdsGetChildCount(cameraList, &count);
        if (count == 0) {
            err = EDS_ERR_DEVICE_NOT_FOUND;
            exit(err);
        }
        EdsGetChildAtIndex(cameraList, 0, cameraRef);
        err = EdsOpenSession(*cameraRef);
    } else {
        exit(err);
    }
}

Camera::~Camera() {
    EdsCloseSession(*cameraRef);
    EdsRelease(*cameraRef);
    EdsTerminateSDK();
}

EdsError Camera::launchLiveView(EdsPropertyID outputScreen) {
    EdsError err = EDS_ERR_OK;

    EdsUInt32 device;
    err = EdsGetPropertyData(*cameraRef,
                             kEdsPropID_Evf_OutputDevice,
                             0,
                             sizeof(device),
                             &device);

    if (err == EDS_ERR_OK) {
        device |= outputScreen;
        err = EdsSetPropertyData(*cameraRef,
                                 kEdsPropID_Evf_OutputDevice,
                                 outputScreen,
                                 sizeof(device),
                                 &device);
    }

    return err;
}

EdsError Camera::focusControl(int newValue, int* currentValue) {
    bool isNear = false;
    int delta = *currentValue - newValue;
    if(delta < 0){
        isNear = true;
        delta = -delta;
    }
    int r;
    int Bmove = delta / Bstep;
    r = delta % (int)Bstep;
    int Mmove = r / Mstep;
    r = delta % int(Mstep);
    cout <<"Bmove: " << Bmove<<"  Mmove: "<< Mmove << "  Smove: " << r <<endl;
    for (int i = 0; i < Bmove; i++) {
        this->move(isNear,3);
    }
    for (int i = 0; i < Mmove; i++) {
        this->move(isNear,2);
    }
    for (int i = 0; i < r; i++) {
        this->move(isNear,1);
    }
    *currentValue = newValue;
}

void Camera::resetFocusPosition(int* currentValue) {
    for (int i = 0; i < 13; ++i) {
        EdsSendCommand(*cameraRef,kEdsCameraCommand_DriveLensEvf,kEdsEvfDriveLens_Near3);
        usleep(200000);
    }
    *currentValue = 395;
}

void Camera::move(bool direction, int size) {
    if (!direction){
        switch (size) {
            case 1:
                EdsSendCommand(*cameraRef,kEdsCameraCommand_DriveLensEvf,kEdsEvfDriveLens_Far1);
                usleep(100000);
                break;
            case 2:
                EdsSendCommand(*cameraRef,kEdsCameraCommand_DriveLensEvf,kEdsEvfDriveLens_Far2);
                usleep(100000);
                break;
            case 3:
                EdsSendCommand(*cameraRef,kEdsCameraCommand_DriveLensEvf,kEdsEvfDriveLens_Far3);
                usleep(200000);
                break;
            default:
                break;
        }
    }else{
        switch (size) {
            case 1:
                EdsSendCommand(*cameraRef,kEdsCameraCommand_DriveLensEvf,kEdsEvfDriveLens_Near1);
                usleep(100000);
                break;
            case 2:
                EdsSendCommand(*cameraRef,kEdsCameraCommand_DriveLensEvf,kEdsEvfDriveLens_Near2);
                usleep(100000);
                break;
            case 3:
                EdsSendCommand(*cameraRef,kEdsCameraCommand_DriveLensEvf,kEdsEvfDriveLens_Near3);
                usleep(200000);
                break;
            default:
                break;
        }
    }
}
