//
// Created by Diabltica on 30/07/2022.
//

#include "CameraControl.hpp"
#include "EDSDK_Header/EDSDK.h"
#include "EDSDK_Header/EDSDKErrors.h"
#include "EDSDK_Header/EDSDKTypes.h"
#include <unistd.h>

int
main(void)
{
    try {
        Camera mainCamera;

        int currentValue = 0;
        mainCamera.launchLiveView(kEdsEvfOutputDevice_TFT);
        mainCamera.resetFocusPosition(&currentValue);
        mainCamera.focusControl(250, &currentValue);
        for (int i = 0; i < 20; ++i) {
            mainCamera.exposureCompensation('i');
        }
        system("pause");
        for (int i = 0; i < 41; ++i) {
            mainCamera.exposureCompensation('d');
        }
        system("pause");

    } catch (CameraException e) {
        std::cout << e.what();
    }
}
