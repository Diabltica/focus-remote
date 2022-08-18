//
// Created by thoma on 18/08/2022.
//

#ifndef FOCUS_REMOTE_CAMERACONTROL_HPP
#define FOCUS_REMOTE_CAMERACONTROL_HPP
#include "EDSDK_Header/EDSDK.h"
#include "EDSDK_Header/EDSDKErrors.h"
#include "EDSDK_Header/EDSDKTypes.h"
#include "iostream"
#include <stdlib.h>

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
constexpr float B_STEP = 395 / 13;
constexpr float M_STEP = 395 / 87;
constexpr int WIDTH = 5000;
constexpr int HEIGTH = 3500;
constexpr int POSITION_STEP = 10;

class CameraException : public std::exception {
  private:
    int _code;
  public:
    CameraException(int code) {
        this->_code = code;
    }
    char* what () {
        char _exCode[10];
        return itoa(_code,_exCode,16);
    }
};

class Camera
{
  private:
    EdsBaseRef _cameraRef;
    EdsError _err = EDS_ERR_OK;
    EdsInt32 _zoomIndex = 0;
    EdsPoint _zoomCoordinate;
    int _exposureIndex;
    const EdsUInt32 _exposureValue[41] = {
        216, 219, 220, 221, 224, 227, 228, 229, 232, 235, 236, 237, 240, 243,
        244, 245, 248, 251, 252, 253, 0,   3,   4,   5,   8,   11,  12,  13,
        16,  19,  20,  21,  24,  27,  28,  29,  32,  35,  36,  37,  40
    };
    bool _isOnScreen(char axis, int direction);
    void _isError();

  public:
    Camera();

    ~Camera();

    void launchLiveView(EdsPropertyID outputScreen);

    /**
     * Place the focus in a knowned position
     * return the focus position
     */
    void resetFocusPosition(int* currentValue);

    /**
     * The position is between 0 and 395
     */
    void focusControl(int newValue, int* currentValue);

    void zoomControl();

    void zoomPosition(char direction);
    void exposureCompensation(char operation);
};
#endif // FOCUS_REMOTE_CAMERACONTROL_HPP
