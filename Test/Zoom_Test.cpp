//
// Created by Diabltica on 08/08/2022.
//

#include "../EDSDK_Header/EDSDK.h"
#include "../EDSDK_Header/EDSDKTypes.h"
#include "../EDSDK_Header/EDSDKErrors.h"
#include "../src/CameraControl.h"
using namespace std;


int main(void)
{
  Camera mainCamera;
  int currentValue = 0;
  mainCamera.launchLiveView(kEdsEvfOutputDevice_TFT);
  mainCamera.resetFocusPosition(&currentValue);
  mainCamera.focusControl(250,&currentValue);
  system("pause");
  mainCamera.zoomControl();
  system("pause");
  mainCamera.zoomControl();
  system("pause");
  mainCamera.zoomControl();
  system("pause");
  for (int i = 0; i < 50; ++i) {
    mainCamera.zoomPosition('r');
  }
  mainCamera.zoomControl();
  mainCamera.zoomControl();
  for (int i = 0; i < 50; ++i) {
    mainCamera.zoomPosition('d');
  }
  mainCamera.zoomControl();
  system("pause");
}