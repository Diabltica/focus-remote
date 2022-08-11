//
// Created by Diabltica on 30/07/2022.
//


#include "EDSDK_Header/EDSDK.h"
#include "EDSDK_Header/EDSDKTypes.h"
#include "EDSDK_Header/EDSDKErrors.h"
#include "CameraControl.h"
#include <unistd.h>
using namespace std;


int main(void)
{
    Camera mainCamera;
    int currentValue = 0;
    mainCamera.launchLiveView(kEdsEvfOutputDevice_TFT);
    mainCamera.resetFocusPosition(&currentValue);
    mainCamera.focusControl(250,&currentValue);
    for (int i = 0; i < 50; ++i) {
      mainCamera.zoomPosition('r');
    }
  mainCamera.zoomControl();
  for (int i = 0; i < 50; ++i) {
    mainCamera.zoomPosition('r');
  }
  mainCamera.zoomControl();
//  for (int i = 0; i < 50; ++i) {
//    mainCamera.zoomPosition('r');
//  }
  system("pause");
}

