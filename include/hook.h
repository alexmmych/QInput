extern "C" {
    #include "uiohook.h"
}

class Hook {
public:
    Hook();
    void RunHook();
    static uint16_t Keycode;

};