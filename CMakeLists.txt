cmake_minimum_required(VERSION 3.5)

project(keyboard-listener VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_COMPILER "g++")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/hook.cpp
        include/mainwindow.h
        include/uiohook.h
        src/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(keyboard-listener
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET keyboard-listener APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(keyboard-listener SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(keyboard-listener
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(keyboard-listener PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

#Directories
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#libuihook copy:
if(UNIX AND NOT APPLE)
    pkg_check_modules(X11 REQUIRED x11)
    target_include_directories(keyboard-listener PRIVATE "${X11_INCLUDE_DIRS}")
    target_link_libraries(keyboard-listener PRIVATE "${X11_LDFLAGS}")

    pkg_check_modules(XTST REQUIRED xtst)
    target_include_directories(keyboard-listener PRIVATE "${XTST_INCLUDE_DIRS}")
    target_link_libraries(keyboard-listener PRIVATE "${XTST_LDFLAGS}")

    option(USE_XKB_COMMON "X Keyboard Common Extension (default: ON)" ON)
    if(USE_XKB_COMMON)
        pkg_check_modules(XKB_COMMON REQUIRED xkbcommon-x11)
        add_compile_definitions(keyboard-listener PRIVATE USE_XKB_COMMON)
        target_include_directories(keyboard-listener PRIVATE "${XKB_COMMON_INCLUDE_DIRS}")
        target_link_libraries(keyboard-listener PRIVATE "${XKB_COMMON_LDFLAGS}")

        pkg_check_modules(X11_XCB REQUIRED x11-xcb)
        target_include_directories(keyboard-listener PRIVATE "${X11_XCB_INCLUDE_DIRS}")
        target_link_libraries(keyboard-listener PRIVATE "${X11_XCB_LDFLAGS}")
    endif()

    option(USE_XKB_FILE "X Keyboard File Extension (default: ON)" ON)
    if(USE_XKB_FILE)
        pkg_check_modules(XKB_FILE REQUIRED xkbfile)
        add_compile_definitions(keyboard-listener PRIVATE USE_XKB_FILE)
        target_include_directories(keyboard-listener PRIVATE "${XKB_FILE_INCLUDE_DIRS}")
        target_link_libraries(keyboard-listener PRIVATE "${XKB_FILE_LDFLAGS}")
    endif()

    option(USE_XT "X Toolkit Extension (default: ON)" ON)
    if(USE_XT)
        pkg_check_modules(XT REQUIRED xt)
        add_compile_definitions(keyboard-listener PRIVATE USE_XT)
        target_include_directories(keyboard-listener PRIVATE "${XT_INCLUDE_DIRS}")
        target_link_libraries(keyboard-listener PRIVATE "${XT_LDFLAGS}")
    endif()


    option(USE_XF86MISC "XFree86-Misc X Extension (default: OFF)" OFF)
    if(USE_XF86MISC)
        pkg_check_modules(XF86MISC REQUIRED Xxf86misc)
        add_compile_definitions(keyboard-listener PRIVATE USE_XF86MISC)
        target_include_directories(keyboard-listener PRIVATE "${XF86MISC_INCLUDE_DIRS}")
        target_link_libraries(keyboard-listener PRIVATE "${XF86MISC_LDFLAGS}")
    endif()

    option(USE_XRANDR "XRandR Extension (default: OFF)" OFF)
    if(USE_XRANDR)
        pkg_check_modules(XRANDR REQUIRED xrandr)
        add_compile_definitions(keyboard-listener PRIVATE USE_XRANDR)
        target_include_directories(keyboard-listener PRIVATE "${XRANDR_INCLUDE_DIRS}")
        target_link_libraries(keyboard-listener PRIVATE "${XRANDR_LDFLAGS}")
    endif()

    option(USE_XINERAMA "Xinerama Extension (default: ON)" ON)
    if(USE_XINERAMA)
        pkg_check_modules(XINERAMA REQUIRED xinerama)
        add_compile_definitions(keyboard-listener PRIVATE USE_XINERAMA)
        target_include_directories(keyboard-listener PRIVATE "${XINERAMA_INCLUDE_DIRS}")
        target_link_libraries(keyboard-listener PRIVATE "${XINERAMA_LDFLAGS}")
    endif()

    option(USE_XRECORD_ASYNC "XRecord Asynchronous API (default: OFF)" OFF)
    if(USE_XRECORD_ASYNC)
        add_compile_definitions(keyboard-listener PRIVATE USE_XRECORD_ASYNC)
    endif()

    option(USE_XTEST "XTest API (default: ON)" ON)
    if(USE_XTEST)
        # XTest API is provided by Xtst
        add_compile_definitions(keyboard-listener PRIVATE USE_XTEST)
    endif()

    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        option(USE_EVDEV "Generic Linux input driver (default: ON)" ON)
        if(USE_EVDEV)
            add_compile_definitions(keyboard-listener PRIVATE USE_EVDEV)
        endif()
    endif()
endif()

set_target_properties(keyboard-listener PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(keyboard-listener)
endif()
