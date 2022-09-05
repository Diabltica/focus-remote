cmake_minimum_required(VERSION 3.17)
project(Focus_Remote)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH C:/Qt/6.3.1/mingw_64/lib/cmake)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6QuickControls2 REQUIRED)
find_package(Qt6Core REQUIRED)
find_package(Qt6Gui REQUIRED)
find_package(Qt6OpenGL REQUIRED)
find_package(Qt6Quick REQUIRED)
find_package(Qt6Qml REQUIRED)

message("Add Libraries")

add_library(EdsImage EDSDK/Dll/EdsImage.dll)

add_library(EDSDK SHARED IMPORTED EDSDK/Dll)

set_property(TARGET EDSDK PROPERTY
        IMPORTED_IMPLIB "C:/Users/thoma/CLionProjects/Focus-Remote/EDSDK/Dll/EDSDK.dll")

set_property(TARGET EDSDK PROPERTY
        IMPORTED_IMPLIB "C:/Users/thoma/CLionProjects/Focus-Remote/EDSDK/Dll/EDSDK.lib")


message("ADD Executable")
include_directories(Headers/EDSDK_Header)
set(SOURCES
        src/cameraControl.cpp
        src/configModule.cpp
        src/UI/ihm.cpp
        src/UI/ihm.ui)

set(TEST
#        test/Focus_Test.cpp
        test/Zoom_Test.cpp
        )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Focus_Remote
            MANUAL_FINALIZATION
            ${SOURCES}
            src/main.cpp
#            ${TEST}
            )
else()
    if(ANDROID)
        add_library(untitled2 SHARED
                ${PROJECT_SOURCES}
                )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(untitled2
                ${PROJECT_SOURCES}
                )
    endif()
endif()

target_link_libraries(Focus_Remote PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Focus_Remote PROPERTIES WIN32_EXECUTABLE TRUE)

install(TARGETS Focus_Remote
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Focus_Remote)
endif()

message("-- Linking EDSDK")


target_link_libraries(Focus_Remote LINK_PUBLIC EDSDK)


message("-- Linking EdsImage")
set_target_properties(EdsImage PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(Focus_Remote LINK_PUBLIC ${EdsImage})
target_link_libraries(Focus_Remote PRIVATE Qt6::Core Qt6::Quick Qt6::QuickControls2)

