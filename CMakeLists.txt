cmake_minimum_required(VERSION 3.16)

project(VRMonitor
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(VRMonitor
    src/main.cpp
)

# OpenVR headers
target_include_directories(VRMonitor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/third-party/openvr/headers
)

# OpenVR library
if(WIN32)

    target_link_libraries(VRMonitor PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/third-party/openvr/lib/win64/openvr_api.lib
    )

elseif(UNIX AND NOT APPLE)

    target_link_libraries(VRMonitor PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/third-party/openvr/lib/linux64/libopenvr_api.so
    )

else()

    message(FATAL_ERROR "Unsupported operating system")

endif()