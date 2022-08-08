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

EdsError Camera::focusControl(int newValue, int *currentValue) {
  int indexModifier = 32768;
  int delta = *currentValue - newValue;
  if (delta < 0) {
    delta = -delta;
    indexModifier = 0;
  }
  int r;
  int Bmove = delta / Bstep;
  r = delta % (int)Bstep;
  int Mmove = r / Mstep;
  r = delta % int(Mstep);

  for (int i = 0; i < Bmove; i++) {
    EdsSendCommand(*cameraRef,
                   kEdsCameraCommand_DriveLensEvf,
                   indexModifier + 3);
    usleep(200000);
  }
  for (int i = 0; i < Mmove; i++) {
    EdsSendCommand(*cameraRef,
                   kEdsCameraCommand_DriveLensEvf,
                   indexModifier + 2);
    usleep(100000);
  }
  for (int i = 0; i < r; i++) {
    EdsSendCommand(*cameraRef,
                   kEdsCameraCommand_DriveLensEvf,
                   indexModifier + 1);
    usleep(100000);
  }
  *currentValue = newValue;
}

void Camera::resetFocusPosition(int *currentValue) {
  for (int i = 0; i < 13; ++i) {
    EdsSendCommand(*cameraRef,
                   kEdsCameraCommand_DriveLensEvf,
                   kEdsEvfDriveLens_Near3);
    usleep(200000);
  }
  *currentValue = 395;
}
