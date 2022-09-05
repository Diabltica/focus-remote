//
// Created by Diabltica on 02/08/2022.
//

#include "Headers/cameraControl.hpp"
#include <unistd.h>

Camera::Camera()
{
    EdsCameraListRef cameraList = nullptr;
    EdsUInt32 count = 0;
    _err = EdsInitializeSDK();
    if (_err != EDS_ERR_OK) {
        throw CameraException(_err);
    }
    _err = EdsGetCameraList(&cameraList);
    if (_err != EDS_ERR_OK) {
        throw CameraException(_err);
    }
    _err = EdsGetChildCount(cameraList, &count);
    if (count == 0) {
        _err = EDS_ERR_DEVICE_NOT_FOUND;
        throw CameraException(_err);
    }
    EdsGetChildAtIndex(cameraList, 0, &_cameraRef);
    _err = EdsOpenSession(_cameraRef);

    EdsGetPropertyData(_cameraRef,
                       kEdsPropID_Evf_ZoomPosition,
                       0,
                       sizeof(EdsPoint),
                       &_zoomCoordinate);

    _exposureIndex = 20;
    EdsSetPropertyData(_cameraRef,
                       kEdsPropID_ExposureCompensation,
                       0,
                       sizeof(EdsUInt32),
                       &_exposureValue[_exposureIndex]);
}

Camera::~Camera()
{
    disconnect();
}

void
Camera::launchLiveView(EdsPropertyID outputScreen)
{
    EdsUInt32 device;
    _err = EdsGetPropertyData(
      _cameraRef, kEdsPropID_Evf_OutputDevice, 0, sizeof(device), &device);

    if (_err == EDS_ERR_OK) {
        device |= outputScreen;
        _err = EdsSetPropertyData(_cameraRef,
                                  kEdsPropID_Evf_OutputDevice,
                                  outputScreen,
                                  sizeof(device),
                                  &device);
    }
    _isError();
}

void
Camera::disconnect(void)
{
    EdsCloseSession(_cameraRef);
    EdsRelease(_cameraRef);
    EdsTerminateSDK();
}

void
Camera::focusControl(int newValue)
{
    int indexModifier = 32768;
    int delta = this->_focusValue - newValue;
    if (delta < 0) {
        delta = -delta;
        indexModifier = 0;
    }
    int r;
    int Bmove = delta / B_STEP;
    r = delta % (int)B_STEP;
    int Mmove = r / M_STEP;
    r = delta % int(M_STEP);

    for (int i = 0; i < Bmove; i++) {
        EdsSendCommand(
          _cameraRef, kEdsCameraCommand_DriveLensEvf, indexModifier + 3);
        usleep(200000);
    }
    for (int i = 0; i < Mmove; i++) {
        EdsSendCommand(
          _cameraRef, kEdsCameraCommand_DriveLensEvf, indexModifier + 2);
        usleep(100000);
    }
    for (int i = 0; i < r; i++) {
        EdsSendCommand(
          _cameraRef, kEdsCameraCommand_DriveLensEvf, indexModifier + 1);
        usleep(100000);
    }
    this->_focusValue = newValue;
}

void
Camera::resetFocusPosition(int* currentValue)
{
    for (int i = 0; i < 13; ++i) {
        EdsSendCommand(
          _cameraRef, kEdsCameraCommand_DriveLensEvf, kEdsEvfDriveLens_Near3);
        usleep(200000);
    }
    *currentValue = 395;
}

void
Camera::zoomControl()
{
    EdsInt32 zoom[3] = { 1, 5, 10 };
    if (_zoomIndex == 2) {
        _zoomIndex = 0;
    } else {
        _zoomIndex++;
    }
    _err = EdsSetPropertyData(
      _cameraRef, kEdsPropID_Evf_Zoom, 0, sizeof(EdsUInt32), &zoom[_zoomIndex]);

    _isError();
}

void
Camera::zoomPosition(char direction)
{
    switch (direction) {
        case 'u':
            if (_isOnScreen('v', 1)) {
                _zoomCoordinate.y -= POSITION_STEP;
            }
            break;
        case 'd':
            if (_isOnScreen('v', -1)) {
                _zoomCoordinate.y += POSITION_STEP;
            }
            break;
        case 'r':
            if (_isOnScreen('h', 1)) {
                _zoomCoordinate.x += POSITION_STEP;
            }
            break;
        case 'l':
            if (_isOnScreen('h', -1)) {
                _zoomCoordinate.x -= POSITION_STEP;
            }
            break;
        default:
            break;
    }
    _err = EdsSetPropertyData(_cameraRef,
                              kEdsPropID_Evf_ZoomPosition,
                              0,
                              sizeof(EdsPoint),
                              &_zoomCoordinate);
    _isError();
}

bool
Camera::_isOnScreen(char axis, int direction)
{
    if (axis == 'v' && direction == 1) { // Vertical axis
        return (_zoomCoordinate.y - POSITION_STEP <= HEIGTH);
    } else if (axis == 'v') {
        return (_zoomCoordinate.y + POSITION_STEP >= 0);
    } else if (direction == 1) { // Horizontal axis
        return (_zoomCoordinate.x + POSITION_STEP <= WIDTH);
    } else {
        return (_zoomCoordinate.x - POSITION_STEP >= 0);
    }
}

void
Camera::exposureCompensation(char operation)
{
    if (operation == 'd') { // Increase
        if (_exposureIndex - 1 >= 0) {
            _exposureIndex --;
            _err = EdsSetPropertyData(_cameraRef,
                                      kEdsPropID_ExposureCompensation,
                                      0,
                                      sizeof(EdsUInt32),
                                      &_exposureValue[_exposureIndex]);
        }
    } else if (operation == 'i') {
        if (_exposureIndex + 1 <= 40) {
            _exposureIndex ++;
            _err = EdsSetPropertyData(_cameraRef,
                                      kEdsPropID_ExposureCompensation,
                                      0,
                                      sizeof(EdsUInt32),
                                      &_exposureValue[_exposureIndex]);
        }
    }
}

void
Camera::_isError()
{
    if (_err != EDS_ERR_OK) {
        throw CameraException(_err);
    }
}

int
Camera::getFocusValue()
{
    return this->_focusValue;
}

int
Camera::getExposureIndex()
{
    return this->_exposureIndex;
}

int
Camera::getZoomIndex(){
    return this->_zoomIndex;
}

EdsPoint
Camera::getZoomCoordinate(){
    return this->_zoomCoordinate;
}