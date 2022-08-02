//
// Created by Diabltica on 30/07/2022.
//


#include "EDSDK_Header/EDSDK.h"
#include "EDSDK_Header/EDSDKTypes.h"
#include "EDSDK_Header/EDSDKErrors.h"
#include "CameraControl.h"
using namespace std;


int main(void)
{
    EdsCameraRef cameraRef = nullptr;
    EdsError err = EDS_ERR_OK;

    err = initCamera(&cameraRef);

    launchLiveView(&cameraRef, kEdsEvfOutputDevice_TFT);

    system("pause");
    destroy(&cameraRef);
}

