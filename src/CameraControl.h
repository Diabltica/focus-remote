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

/*
 * Init the SDK, search for pluged camera and Open a session
 * OUT : Camera's reference
 */
EdsError initCamera(EdsBaseRef* CameraRef);

/*
 * Close communication with the camera
 * IN : Camera's reference
 */
EdsError destroy(EdsBaseRef* CameraRef);

/*
 * Launch the live view
 * IN : cameraRef - Camera's reference
 *      outputScreen - the choosen output screen TFT or PC
 */
EdsError launchLiveView(EdsBaseRef* cameraRef, EdsPropertyID outputScreen);
#endif //FOCUS_REMOTE_CAMERACONTROL_H
