//
// Created by Diabltica on 02/08/2022.
//

#include "CameraControl.h"


EdsError initCamera(EdsBaseRef* cameraRef){
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
        err = EdsGetChildAtIndex(cameraList, 0, cameraRef);
        err = EdsOpenSession(*cameraRef);
    }
    else {
        cout << "No Camera List" << endl;
    }
    return err;
}

EdsError destroy(EdsBaseRef* cameraRef){
    EdsError err = EDS_ERR_OK;
    err = EdsCloseSession(*cameraRef);

    if(err = EDS_ERR_OK){
        err = EdsRelease(*cameraRef);
    }

    if (err = EDS_ERR_OK){
        err = EdsTerminateSDK();
    }
    return err;
}

EdsError launchLiveView(EdsBaseRef* cameraRef, EdsPropertyID outputScreen){
    EdsError err = EDS_ERR_OK;

    EdsUInt32 device;
    err = EdsGetPropertyData(*cameraRef,
                             kEdsPropID_Evf_OutputDevice,
                             0,
                             sizeof(device),
                             &device);

    if (err == EDS_ERR_OK){
        device |= outputScreen;
        err = EdsSetPropertyData(*cameraRef,
                                 kEdsPropID_Evf_OutputDevice,
                                 outputScreen,
                                 sizeof(device),
                                 &device);
    }

    return err;
}

EdsError focusControl(EdsBaseRef* cameraRef, int newValue){
    EdsError err = EDS_ERR_OK;

    return err;
}