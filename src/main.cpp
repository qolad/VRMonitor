#include <iostream>
#include <thread>
#include <cstdio>
#include <chrono> 
#include <filesystem>

#include <openvr.h>
#include <capture.h>
#include <fakeCapture.h>


int main(int argc, char* argv[]){
    std::string myString = "SteamOverylay";

    std::cout << "VR Monitor starting..." << std::endl;

    vr::EVRInitError error = vr::VRInitError_None;

    vr::IVRSystem* vrSystem = vr::VR_Init(&error, vr::VRApplication_Overlay);

    if (error != vr::VRInitError_None){
        std::cout << "OpenVR initialization failed: " << vr::VR_GetVRInitErrorAsEnglishDescription(error) << std::endl;
        return 1;
    }

    FakeCapture capture;

    if (!capture.start()){
        std::cout << "Failed to start capture!" << std::endl;

        vr::VR_Shutdown();
        return 1;
    }

    Frame frame;

    if (capture.getFrame(frame)){
        std::cout << "Captured frame: " << frame.width << "x" << frame.height << std::endl;
    }

    std::string sKey = std::string("sample." ) + myString;

    vr::VROverlayHandle_t mainHandle = vr::k_ulOverlayHandleInvalid;
    vr::VROverlayHandle_t tumbnailHandle = vr::k_ulOverlayHandleInvalid;

    vr::VROverlayError  overlayError = vr::VROverlay()->CreateDashboardOverlay(sKey.c_str(), myString.c_str(), &mainHandle, &tumbnailHandle);

    if (overlayError != vr::VROverlayError_None){
        std::cout << "Dashboard overlay creation failed: " << vr::VROverlay()->GetOverlayErrorNameFromEnum(overlayError) << std::endl;

        capture.stop();
        vr::VR_Shutdown();
        return 1;
    }

    std::cout << "Dashboard created successfully!" << std::endl;
    //std::cin.get();

    while (true){
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    capture.stop();
    vr::VR_Shutdown();

    return 0;
}