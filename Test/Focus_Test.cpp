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
  int newValue;
  for (int i = 0; i < 6; ++i) {
    newValue = currentValue - 50;
    cout<< "Current value: " << currentValue << " - New value: " << newValue << endl;
    mainCamera.focusControl(newValue,&currentValue);
  }
  for (int i = 0; i < 6; ++i) {
    newValue = currentValue + 50;
    cout<< "Current value: " << currentValue << " - New value: " << newValue << endl;
    mainCamera.focusControl(newValue,&currentValue);
  }
  cout<< "Current value: " << currentValue << " - New value: 0" << endl;
  mainCamera.focusControl(0,&currentValue);
  cout<< "Current value: " << currentValue << " - New value: 395" << endl;
  mainCamera.focusControl(395,&currentValue);
}
