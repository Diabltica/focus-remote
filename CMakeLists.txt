cmake_minimum_required(VERSION 3.22)
project(Focus_Remote)

set(CMAKE_CXX_STANDARD 14)

message("Add Libraries")

add_library(EdsImage EDSDK/Dll/EdsImage.dll)

add_library(EDSDK SHARED IMPORTED EDSDK/Dll)

set_property(TARGET EDSDK PROPERTY
        IMPORTED_IMPLIB "C:/Users/thoma/CLionProjects/Focus-Remote/EDSDK/Dll/EDSDK.dll")

#set_property(TARGET EDSDK PROPERTY
#        IMPORTED_LOCATION "C:/Users/thoma/CLionProjects/Focus-Remote/EDSDK/Dll/EdsImage.dll")

set_property(TARGET EDSDK PROPERTY
        IMPORTED_IMPLIB "C:/Users/thoma/CLionProjects/Focus-Remote/EDSDK/Dll/EDSDK.lib")


message("ADD Executable")
include_directories(src/EDSDK_Header)

add_executable(Focus_Remote
        src/main.cpp
        src/CameraControl.cpp)
message("-- Linking EDSDK")


target_link_libraries(Focus_Remote LINK_PUBLIC EDSDK)


message("-- Linking EdsImage")
set_target_properties(EdsImage PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(Focus_Remote LINK_PUBLIC ${EdsImage})

