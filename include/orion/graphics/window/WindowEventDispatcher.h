//
// Created by Alex on 12/11/2023.
//

#ifndef ORION_WINDOWEVENTDISPATCHER_H
#define ORION_WINDOWEVENTDISPATCHER_H

#include "orion/core/type.h"

struct GLFWwindow;
struct GLFWmonitor;

namespace orion {
    class WindowEventDispatcher {
    private:
        static void error_callback(int error, Ptr<char> description);

        static void window_position_callback     (PtrMut<GLFWwindow> window, int xpos, int ypos);
        static void window_size_callback         (PtrMut<GLFWwindow> window, int width, int height);
        static void window_close_callback        (PtrMut<GLFWwindow> window);
        static void window_refresh_callback      (PtrMut<GLFWwindow> window);
        static void window_focus_callback        (PtrMut<GLFWwindow> window, int focused);
        static void window_iconify_callback      (PtrMut<GLFWwindow> window, int iconified);
        static void window_maximize_callback     (PtrMut<GLFWwindow> window, int maximized);
        static void window_content_scale_callback(PtrMut<GLFWwindow> window, float xscale, float yscale);

        static void framebuffer_size_callback(PtrMut<GLFWwindow> window, int width, int height);

        static void mouse_button_callback   (PtrMut<GLFWwindow> window, int button, int action, int mods);
        static void cursor_position_callback(PtrMut<GLFWwindow> window, double xpos, double ypos);
        static void cursor_enter_callback   (PtrMut<GLFWwindow> window, int entered);
        static void scroll_callback         (PtrMut<GLFWwindow> window, double xoffset, double yoffset);

        static void key_callback           (PtrMut<GLFWwindow> window, int key, int scancode, int action, int mods);
        static void character_callback     (PtrMut<GLFWwindow> window, unsigned int codepoint);
        static void character_mods_callback(PtrMut<GLFWwindow> window, unsigned int codepoint, int mods);

        static void drop_callback(PtrMut<GLFWwindow> window, int count, const char** paths);

        static void monitor_callback(PtrMut<GLFWmonitor> monitor, int event);

        static void joystick_callback(int jid, int event);


        friend class Window;
    };
}

#endif //ORION_WINDOWEVENTDISPATCHER_H
