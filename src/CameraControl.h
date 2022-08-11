//
// Created by thoma on 02/08/2022.
//

#ifndef FOCUS_REMOTE_CAMERACONTROL_H
#define FOCUS_REMOTE_CAMERACONTROL_H

#include "iostream"
#include "EDSDK_Header/EDSDK.h"
#include "EDSDK_Header/EDSDKTypes.h"
#include "EDSDK_Header/EDSDKErrors.h"

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

    bool isOnScreen(char axis, int direction);
  public:
    Camera();

    ~Camera();


    EdsError launchLiveView(EdsPropertyID outputScreen);


    /*
    * Place the focus in a knowned position
    * return the focus position
    */
    void resetFocusPosition(int* currentValue);


    /*
     * The position is between 0 and 395
     */
    EdsError focusControl(int newValue, int* currentValue);

    EdsError zoomControl();

    EdsError zoomPosition(char direction);
};

#endif //FOCUS_REMOTE_CAMERACONTROL_H
