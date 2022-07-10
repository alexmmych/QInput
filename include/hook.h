extern "C" {
    #include "uiohook.h"
}
#pragma once
#include "mainwindow.h"

#include <iterator>

class Hook {
public:
    Hook();
    void RunHook();
    static void StopHook();
    static short unsigned int Keycode;
};