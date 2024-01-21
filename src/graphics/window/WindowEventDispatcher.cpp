//
// Created by Alex on 12/11/2023.
//

#include "orion/graphics/window/WindowEventDispatcher.h"

#include "orion/graphics/window/Window.h"
#include "orion/graphics/window/WindowEvent.h"
#include "orion/core/event/EventManager.h"

namespace orion {
    void WindowEventDispatcher::error_callback(int error, const char *description) {
        fmt::print(stderr, "Error: {}", description);
    }

    void WindowEventDispatcher::window_position_callback(GLFWwindow *window, int xpos, int ypos) {
        auto w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))->shared_from_this();

        static Vector2i last = {0, 0};

        WindowPositionEvent event = {
            {w},
            last,
            {xpos, ypos}
        };

        if (!w->m_event_manager.expired())
            w->m_event_manager.lock()->emit(event);

        last = {xpos, ypos};
    }

    void WindowEventDispatcher::window_size_callback(GLFWwindow *window, int width, int height) {
        auto w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))->shared_from_this();

        static Vector2i last = {0, 0};

        WindowSizeEvent event = {
            {w},
            last,
            {width, height}
        };

        if (!w->m_event_manager.expired())
            w->m_event_manager.lock()->emit(event);

//        w->get_view().set_ratio((f32)width / (f32)height);

        last = {width, height};
    }

    void WindowEventDispatcher::window_close_callback(GLFWwindow *window) {
        auto w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))->shared_from_this();

        WindowCloseEvent event = {{w}};

        if (!w->m_event_manager.expired())
            w->m_event_manager.lock()->emit(event);
    }

    void WindowEventDispatcher::window_refresh_callback(GLFWwindow *window) {
        auto w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))->shared_from_this();

        WindowRefreshEvent event = {{w}};

        if (!w->m_event_manager.expired())
            w->m_event_manager.lock()->emit(event);
    }

    void WindowEventDispatcher::window_focus_callback(GLFWwindow *window, int focused) {
        auto w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))->shared_from_this();

        WindowFocusEvent event = {{w}, focused > 0};

        if (!w->m_event_manager.expired())
            w->m_event_manager.lock()->emit(event);
    }

    void WindowEventDispatcher::window_iconify_callback(GLFWwindow *window, int iconified) {
        auto w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))->shared_from_this();

        WindowIconifyEvent event = {{w}, iconified > 0};

        if (!w->m_event_manager.expired())
            w->m_event_manager.lock()->emit(event);
    }

    void WindowEventDispatcher::window_maximize_callback(GLFWwindow *window, int maximized) {
        auto w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))->shared_from_this();

        WindowMaximizeEvent event = {{w}, maximized > 0};

        if (!w->m_event_manager.expired())
            w->m_event_manager.lock()->emit(event);
    }

    void WindowEventDispatcher::window_content_scale_callback(GLFWwindow* window, float xscale, float yscale) {
        auto w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))->shared_from_this();

        static Vector2f last = {0.0, 0.0};

        WindowContentScaleEvent event = {
                {w},
                last,
                {xscale, yscale}
        };

        if (!w->m_event_manager.expired())
            w->m_event_manager.lock()->emit(event);

        last = {xscale, yscale};
    }

    void WindowEventDispatcher::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        auto w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))->shared_from_this();
    }

    void WindowEventDispatcher::mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
        auto w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))->shared_from_this();

        Input::MouseButtonEvent event = {
                {w},
                static_cast<Input::MouseButton>(button),
                action == GLFW_PRESS,
                (mods & GLFW_MOD_SHIFT) == GLFW_MOD_SHIFT,
                (mods & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL,
                (mods & GLFW_MOD_ALT) == GLFW_MOD_ALT,
                (mods & GLFW_MOD_SUPER) == GLFW_MOD_SUPER,
                (mods & GLFW_MOD_CAPS_LOCK) == GLFW_MOD_CAPS_LOCK,
                (mods & GLFW_MOD_NUM_LOCK) == GLFW_MOD_NUM_LOCK,
        };

        if (!w->m_event_manager.expired())
            w->m_event_manager.lock()->emit(event);
    }

    void WindowEventDispatcher::cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
        auto w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))->shared_from_this();

        static Vector2d last = {0.0, 0.0};

        Input::CursorPositionEvent event = {
                {w},
                last,
                {xpos, ypos}
        };

        if (!w->m_event_manager.expired())
            w->m_event_manager.lock()->emit(event);

        last = {xpos, ypos};
    }

    void WindowEventDispatcher::cursor_enter_callback(GLFWwindow *window, int entered) {
        auto w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))->shared_from_this();

        Input::CursorEnterEvent event = {{w}, entered > 0};

        if (!w->m_event_manager.expired())
            w->m_event_manager.lock()->emit(event);
    }

    void WindowEventDispatcher::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
        auto w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))->shared_from_this();

        static Vector2d last = {0.0, 0.0};

        Input::ScrollEvent event = {
                {w},
                last,
                {xoffset, yoffset}
        };

        if (!w->m_event_manager.expired())
            w->m_event_manager.lock()->emit(event);

        last = {xoffset, yoffset};
    }

    void WindowEventDispatcher::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        auto w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))->shared_from_this();

        Input::KeyEvent event = {
                {w},
                static_cast<Input::Key>(key),
                scancode,
                action == GLFW_PRESS,
                action == GLFW_REPEAT,
                (mods & GLFW_MOD_SHIFT) == GLFW_MOD_SHIFT,
                (mods & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL,
                (mods & GLFW_MOD_ALT) == GLFW_MOD_ALT,
                (mods & GLFW_MOD_SUPER) == GLFW_MOD_SUPER,
                (mods & GLFW_MOD_CAPS_LOCK) == GLFW_MOD_CAPS_LOCK,
                (mods & GLFW_MOD_NUM_LOCK) == GLFW_MOD_NUM_LOCK,
        };

        if (!w->m_event_manager.expired())
            w->m_event_manager.lock()->emit(event);
    }

    void WindowEventDispatcher::character_callback(GLFWwindow *window, unsigned int codepoint) {
        auto w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))->shared_from_this();
    }

    void WindowEventDispatcher::character_mods_callback(GLFWwindow *window, unsigned int codepoint, int mods) {
        auto w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))->shared_from_this();
    }

    void WindowEventDispatcher::drop_callback(GLFWwindow *window, int count, const char **paths) {
        auto w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))->shared_from_this();
    }

    void WindowEventDispatcher::monitor_callback(GLFWmonitor *monitor, int event) {

    }

    void WindowEventDispatcher::joystick_callback(int jid, int event) {

    }
}