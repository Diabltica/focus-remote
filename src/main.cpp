//
// Created by Diabltica on 30/07/2022.
//


#include "EDSDK_Header/EDSDK.h"
#include "EDSDK_Header/EDSDKTypes.h"
#include "CameraControl.h"
using namespace std;


int main(void)
{
    EdsCameraRef CameraRef = nullptr;
    initCamera(&CameraRef);
    destroy(&CameraRef);
}

