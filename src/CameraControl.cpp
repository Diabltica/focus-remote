//
// Created by Diabltica on 02/08/2022.
//

#include "CameraControl.h"


EdsError initCamera(EdsBaseRef* CameraRef){
    EdsError err = EDS_ERR_OK;
    EdsCameraListRef cameraList = NULL;
    EdsUInt32 count = 0;
    err = EdsInitializeSDK();
    if (err == EDS_ERR_OK) {
        cout << "SDK INITIALIZED" << endl;
    } else {
        cout << "SDK INITIALISATION FAILED WAIT FOR EXIT" << endl;
        exit(84);
    }
    err = EdsGetCameraList(&cameraList);
    if (err == EDS_ERR_OK) {
        cout << "Camera List Ok" << endl;
        err = EdsGetChildCount(cameraList, &count);
        cout << "Count : " << count << endl;
        if (count == 0) {
            err = EDS_ERR_DEVICE_NOT_FOUND;
            return err;
        }
        cout << "It worked" << endl;
        err = EdsGetChildAtIndex(cameraList, 0, CameraRef);
        if(err = EDS_ERR_OK){
            err = EdsOpenSession(*CameraRef);
        }
    }
    else {
        cout << "No Camera List" << endl;
    }
    return err;
}

EdsError destroy(EdsBaseRef* CameraRef){
    EdsError err = EDS_ERR_OK;
    err = EdsCloseSession(*CameraRef);

    if(err = EDS_ERR_OK){
        err = EdsRelease(*CameraRef);
    }

    if (err = EDS_ERR_OK){
        err = EdsTerminateSDK();
    }
    return err;
}