//
// Created by Diabltica on 30/07/2022.
//

#include "iostream"
#include "EDSDK.h"
#include "EDSDKTypes.h"
#include <iostream>

using namespace std;

EdsError initCamera();

int main(void)
{
    initCamera();
}

EdsError initCamera(){
    EdsError err = EDS_ERR_OK;
    EdsCameraListRef cameraList = NULL;
    EdsUInt32 count = 0;
    EdsCameraRef camera = nullptr;

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
        err = EdsGetChildAtIndex(cameraList, 0, &camera);
    }
    else {
        cout << "No Camera List" << endl;
    }
    return err;
}