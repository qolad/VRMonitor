#include <iostream>
#include <cstdio> 
#include <openvr.h>

int main(int argc, char* argv[]){
    std::string myString = "SteamOverylay";
    std::cout << "VR Monitor starting..." << std::endl;

    vr::EVRInitError error = vr::VRInitError_None;

    vr::IVRSystem* vrSystem = vr::VR_Init(&error, vr::VRApplication_Overlay);

    if (error != vr::VRInitError_None){
        std::cout << "OpenVR initialization failed: " << vr::VR_GetVRInitErrorAsEnglishDescription(error) << std::endl;
        return 1;
    }

    std::cout << "OpenVR initialized successfully!" << std::endl;

    std::string sKey = std::string("sample." ) + myString;

    vr::VROverlayHandle_t mainHandle = vr::k_ulOverlayHandleInvalid;
    vr::VROverlayHandle_t tumbnailHandle = vr::k_ulOverlayHandleInvalid;

    vr::VROverlayError  overlayError = vr::VROverlay()->CreateDashboardOverlay(sKey.c_str(), myString.c_str(), &mainHandle, &tumbnailHandle);

    if (overlayError != vr::VROverlayError_None){
        std::cout << "Overlay creation failed: " << vr::VROverlay()->GetOverlayErrorNameFromEnum(overlayError) << std::endl;

        
        vr::VR_Shutdown();
        return 1;
    }


    std::cout << "Overy created successfully!" << std::endl;

    std::cin.get();

    vr::VR_Shutdown();

    return 0;
}