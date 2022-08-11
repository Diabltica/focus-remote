//
// Created by Diabltca on 02/08/2022.
//

#ifndef FOCUS_REMOTE_CAMERACONTROL_H
#define FOCUS_REMOTE_CAMERACONTROL_H

#include "EDSDK_Header/EDSDK.h"
#include "EDSDK_Header/EDSDKErrors.h"
#include "EDSDK_Header/EDSDKTypes.h"
#include "iostream"

using namespace std;

/**
 * FOCUS SPEC <br>
 * 13 step for setting 3   200ms delay <br>
 * 87 step for setting  2  100ms delay <br>
 * 395 step for setting 1  100ms delay <br>
 * <br>
 * 1 P3 = 30.385 P1 <br>
 * 1 P2 = 4.54 P1 <br>
 * 1 P3 = 6.69 P2 <br>
 */
#define B_STEP 30.384615384615383
#define M_STEP 4.540229885057471
#define WIDTH 5000
#define HEIGTH 3500
#define POSITION_STEP 10

class Camera {
private:
  EdsBaseRef *cameraRef;
  EdsError err = EDS_ERR_OK;
  EdsInt32 zoomIndex = 0;
  EdsPoint zoomCoordinate;
  int exposureIndex;
  const EdsUInt32 exposureValue[41] = {
      216, 219, 220, 221, 224, 227, 228, 229, 232, 235, 236, 237, 240, 243,
      244, 245, 248, 251, 252, 253, 0,   3,   4,   5,   8,   11,  12,  13,
      16,  19,  20,  21,  24,  27,  28,  29,  32,  35,  36,  37,  40};
  bool isOnScreen(char axis, int direction);

public:
  Camera();

  ~Camera();

  EdsError launchLiveView(EdsPropertyID outputScreen);

  /*
   * Place the focus in a knowned position
   * return the focus position
   */
  void resetFocusPosition(int *currentValue);

  /*
   * The position is between 0 and 395
   */
  EdsError focusControl(int newValue, int *currentValue);

  EdsError zoomControl();

  EdsError zoomPosition(char direction);
  EdsError exposureCompensation(char operation);
};
#endif // FOCUS_REMOTE_CAMERACONTROL_H
