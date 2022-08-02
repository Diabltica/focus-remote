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

EdsError destroy(EdsBaseRef* CameraRef);
#endif //FOCUS_REMOTE_CAMERACONTROL_H
