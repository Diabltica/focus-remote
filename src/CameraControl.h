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

class Camera {
private:
    EdsBaseRef *cameraRef;
    EdsError err = EDS_ERR_OK;
    EdsInt32 zoomIndex = 0;
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

    EdsError ZoomControl();
};

#define Bstep 30.384615384615383
#define Mstep 4.540229885057471
/*
 * FOCUS SPEC
 * 13 step for setting 3   200ms delay
 * 87 step for setting  2  100ms delay
 * 395 step for setting 1  100ms delay
 *
 * 1 P3 = 30.385 P1
 * 1 P2 = 4.54 P1
 * 1 P3 = 6.69 P2
*/
#endif //FOCUS_REMOTE_CAMERACONTROL_H
