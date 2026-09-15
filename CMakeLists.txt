cmake_minimum_required(VERSION 3.16)

project(VRMonitor
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(VRMonitor
    src/main.cpp
    src/fakeCapture.cpp
)

target_include_directories(VRMonitor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/third-party/openvr/headers
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
)

if(WIN32)

    target_link_libraries(VRMonitor PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/third-party/openvr/lib/win64/openvr_api.lib
    )

    add_custom_command(TARGET VRMonitor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/third-party/openvr/bin/win64/openvr_api.dll"
            "$<TARGET_FILE_DIR:VRMonitor>"
    )

elseif(UNIX AND NOT APPLE)

    target_link_libraries(VRMonitor PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/third-party/openvr/lib/linux64/libopenvr_api.so
    )

else()

    message(FATAL_ERROR "Unsupported operating system")

endif()