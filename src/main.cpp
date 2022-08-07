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
    Camera mainCamera;
    int currentValue = 0;
    mainCamera.launchLiveView(kEdsEvfOutputDevice_TFT);
    mainCamera.resetFocusPosition(&currentValue);
    cout<< currentValue <<endl;
    mainCamera.focusControl(300,&currentValue);
    mainCamera.focusControl(200,&currentValue);
    mainCamera.focusControl(100,&currentValue);
    mainCamera.focusControl(200,&currentValue);
    mainCamera.focusControl(300,&currentValue);
    mainCamera.focusControl(0,&currentValue);
    mainCamera.focusControl(395,&currentValue);
    system("pause");
}

