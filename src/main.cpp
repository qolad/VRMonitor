#include <iostream>
#include <cstdio> 
#include <filesystem>
#include <openvr.h>

namespace fs = std::filesystem;

int main(int argc, char* argv[]){
    std::string myString = "SteamOverylay";
    std::cout << "VR Monitor starting..." << std::endl;

    const fs::path imagePath = fs::absolute("image.png");
    
    vr::EVRInitError error = vr::VRInitError_None;

    vr::IVRSystem* vrSystem = vr::VR_Init(&error, vr::VRApplication_Overlay);

    if (error != vr::VRInitError_None){
        std::cout << "OpenVR initialization failed: " << vr::VR_GetVRInitErrorAsEnglishDescription(error) << std::endl;
        return 1;
    }


    std::string sKey = std::string("sample." ) + myString;

    vr::VROverlayHandle_t mainHandle = vr::k_ulOverlayHandleInvalid;
    vr::VROverlayHandle_t tumbnailHandle = vr::k_ulOverlayHandleInvalid;

    vr::VROverlayError  overlayError = vr::VROverlay()->CreateDashboardOverlay(sKey.c_str(), myString.c_str(), &mainHandle, &tumbnailHandle);

    if (overlayError != vr::VROverlayError_None){
        std::cout << "Dashboard overlay creation failed: " << vr::VROverlay()->GetOverlayErrorNameFromEnum(overlayError) << std::endl;

        
        vr::VR_Shutdown();
        return 1;
    }


    std::cout << "Dashboard created successfully!" << std::endl;


    vr::VROverlay()->SetOverlayFromFile(mainHandle, imagePath.string().c_str());

   if (overlayError != vr::VROverlayError_None){
        std::cout << "Failed to load image: " << vr::VROverlay()->GetOverlayErrorNameFromEnum(overlayError) << std::endl;
    }else{
        std::cout << "Image loaded successfully!" << std::endl;
    }
    
    std::cin.get();

    vr::VR_Shutdown();

    return 0;
}