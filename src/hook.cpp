extern "C" {
    #include "uiohook.h"
}

#include <iostream>
#include <wchar.h>
#include <stdio.h>

class Hook {
public:
    Hook();
};

bool logger_proc(unsigned int level, const char *format, ...) {
    bool status = false;

    va_list args;
    switch (level) {
        case LOG_LEVEL_INFO:
            va_start(args, format);
            status = vfprintf(stdout, format, args) >= 0;
            va_end(args);
            break;

        case LOG_LEVEL_WARN:
        case LOG_LEVEL_ERROR:
            va_start(args, format);
            status = vfprintf(stderr, format, args) >= 0;
            va_end(args);
            break;
    }

    return status;
}

void dispatch_proc(uiohook_event * const event) {

        if(event->type == EVENT_KEY_RELEASED)
            std::cout << "Keycode: " << event->data.keyboard.keycode;
        if(event->type == EVENT_KEY_TYPED)
            printf("Keychar: %lc", (wint_t) event->data.keyboard.keychar);

    switch (event->type) {
        case EVENT_KEY_PRESSED:
            // If the escape key is pressed, naturally terminate the program.
            if (event->data.keyboard.keycode == VC_ESCAPE) {
                int status = hook_stop();
                switch (status) {
                    case UIOHOOK_SUCCESS:
                        // Everything is ok.
                        break;

                    // System level errors.
                    case UIOHOOK_ERROR_OUT_OF_MEMORY:
                        logger_proc(LOG_LEVEL_ERROR, "Failed to allocate memory. (%#X)", status);
                        break;

                    case UIOHOOK_ERROR_X_RECORD_GET_CONTEXT:
                        // NOTE This is the only platform specific error that occurs on hook_stop().
                        logger_proc(LOG_LEVEL_ERROR, "Failed to get XRecord context. (%#X)", status);
                        break;

                    // Default error.
                    case UIOHOOK_FAILURE:
                    default:
                        logger_proc(LOG_LEVEL_ERROR, "An unknown hook error occurred. (%#X)", status);
                        break;
                }
            }
        case EVENT_KEY_RELEASED:
        case EVENT_KEY_TYPED:
            printf("    Rawcode: %#06x \n",event->data.keyboard.rawcode);
            break;
        case EVENT_MOUSE_PRESSED:
                std::cout << "Mouse Button: " << event->data.mouse.button << "  Mouse Clicks: " << event->data.mouse.clicks << "\n" ;
            break;
        case EVENT_MOUSE_RELEASED:
        case EVENT_MOUSE_CLICKED:
        case EVENT_MOUSE_MOVED:
        case EVENT_MOUSE_DRAGGED:
                std::cout << "MouseX: " << event->data.mouse.x << "    MouseY: " << event->data.mouse.y << "\n" ;
            break;

        case EVENT_MOUSE_WHEEL:
                std::cout<< "Mouse Wheel Rotation: " << event->data.wheel.rotation << "\n";
            break;

        default:
            break;
    }
}

Hook::Hook() {

    // Set the logger callback for library output.
    hook_set_logger_proc(&logger_proc);

    // Set the event callback for uiohook events.
    hook_set_dispatch_proc(&dispatch_proc);
    
    int status = hook_run();

    switch (status) {
        case UIOHOOK_SUCCESS:
            // Everything is ok.
            break;

        // System level errors.
        case UIOHOOK_ERROR_OUT_OF_MEMORY:
            logger_proc(LOG_LEVEL_ERROR, "Failed to allocate memory. (%#X)", status);
            break;


        // X11 specific errors.
        case UIOHOOK_ERROR_X_OPEN_DISPLAY:
            logger_proc(LOG_LEVEL_ERROR, "Failed to open X11 display. (%#X)", status);
            break;

        case UIOHOOK_ERROR_X_RECORD_NOT_FOUND:
            logger_proc(LOG_LEVEL_ERROR, "Unable to locate XRecord extension. (%#X)", status);
            break;

        case UIOHOOK_ERROR_X_RECORD_ALLOC_RANGE:
            logger_proc(LOG_LEVEL_ERROR, "Unable to allocate XRecord range. (%#X)", status);
            break;

        case UIOHOOK_ERROR_X_RECORD_CREATE_CONTEXT:
            logger_proc(LOG_LEVEL_ERROR, "Unable to allocate XRecord context. (%#X)", status);
            break;

        case UIOHOOK_ERROR_X_RECORD_ENABLE_CONTEXT:
            logger_proc(LOG_LEVEL_ERROR, "Failed to enable XRecord context. (%#X)", status);
            break;


        // Windows specific errors.
        case UIOHOOK_ERROR_SET_WINDOWS_HOOK_EX:
            logger_proc(LOG_LEVEL_ERROR, "Failed to register low level windows hook. (%#X)", status);
            break;


        // Darwin specific errors.
        case UIOHOOK_ERROR_AXAPI_DISABLED:
            logger_proc(LOG_LEVEL_ERROR, "Failed to enable access for assistive devices. (%#X)", status);
            break;

        case UIOHOOK_ERROR_CREATE_EVENT_PORT:
            logger_proc(LOG_LEVEL_ERROR, "Failed to create apple event port. (%#X)", status);
            break;

        case UIOHOOK_ERROR_CREATE_RUN_LOOP_SOURCE:
            logger_proc(LOG_LEVEL_ERROR, "Failed to create apple run loop source. (%#X)", status);
            break;

        case UIOHOOK_ERROR_GET_RUNLOOP:
            logger_proc(LOG_LEVEL_ERROR, "Failed to acquire apple run loop. (%#X)", status);
            break;

        case UIOHOOK_ERROR_CREATE_OBSERVER:
            logger_proc(LOG_LEVEL_ERROR, "Failed to create apple run loop observer. (%#X)", status);
            break;

        // Default error.
        case UIOHOOK_FAILURE:
        default:
            logger_proc(LOG_LEVEL_ERROR, "An unknown hook error occurred. (%#X)", status);
            break;
    }
}

int main() {
    Hook newHook;
}
