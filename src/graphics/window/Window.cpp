//
// Created by Alex on 12/11/2023.
//

#include "graphics/window/Window.h"

#include <iostream>

#include "graphics/window/WindowEventDispatcher.h"
#include "graphics/opengl/OpenGlApi.h"

namespace orion {

    ClearMask operator|(ClearMask lhs, ClearMask rhs) {
        return (ClearMask)(std::underlying_type<ClearMask>::type (lhs) | std::underlying_type<ClearMask>::type (rhs));
    }

    std::shared_ptr<Window> Window::create(Ref<std::string> name) {
        auto p = std::shared_ptr<Window>(new Window(name));
        return std::move(p);
    }

    void Window::display() {
        swap_buffers();
        poll_events();
        m_frame_swap = !m_frame_swap;
    }

    void Window::clear(ClearMask mask) {
        #ifdef ORION_DEBUG
            OpenGlApi::CALL_TRACE = {};
        #endif
        glClear(std::underlying_type<ClearMask>::type (mask));
    }

    Window::Window(Ref<std::string> name) : GLFWWindowWrapper(1024, 768, name, nullptr, nullptr) {
        glfwSetErrorCallback    (WindowEventDispatcher::error_callback);
        glfwSetJoystickCallback (WindowEventDispatcher::joystick_callback);
        glfwSetMonitorCallback  (WindowEventDispatcher::monitor_callback);

        glfwSetWindowPosCallback            (m_window, WindowEventDispatcher::window_position_callback);
        glfwSetWindowSizeCallback           (m_window, WindowEventDispatcher::window_size_callback);
        glfwSetWindowCloseCallback          (m_window, WindowEventDispatcher::window_close_callback);
        glfwSetWindowRefreshCallback        (m_window, WindowEventDispatcher::window_refresh_callback);
        glfwSetWindowFocusCallback          (m_window, WindowEventDispatcher::window_focus_callback);
        glfwSetWindowIconifyCallback        (m_window, WindowEventDispatcher::window_iconify_callback);
        glfwSetWindowMaximizeCallback       (m_window, WindowEventDispatcher::window_maximize_callback);
        glfwSetWindowContentScaleCallback   (m_window, WindowEventDispatcher::window_content_scale_callback);

        glfwSetFramebufferSizeCallback      (m_window, WindowEventDispatcher::framebuffer_size_callback);

        glfwSetMouseButtonCallback          (m_window, WindowEventDispatcher::mouse_button_callback);
        glfwSetCursorPosCallback            (m_window, WindowEventDispatcher::cursor_position_callback);
        glfwSetCursorEnterCallback          (m_window, WindowEventDispatcher::cursor_enter_callback);
        glfwSetScrollCallback               (m_window, WindowEventDispatcher::scroll_callback);

        glfwSetKeyCallback                  (m_window, WindowEventDispatcher::key_callback);
        glfwSetCharCallback                 (m_window, WindowEventDispatcher::character_callback);
        glfwSetCharModsCallback             (m_window, WindowEventDispatcher::character_mods_callback);

        glfwSetDropCallback                 (m_window, WindowEventDispatcher::drop_callback);

        set_user_pointer(this);
    }

    void Window::set_event_manager(Ref<std::shared_ptr<EventManager>> event_manager) {
        m_event_manager = event_manager;
    }
}
