//
// Created by Alex on 12/11/2023.
//

#include "graphics/window/GLFWWindowWrapper.h"

#include "graphics/opengl/OpenGlContext.h"

#include <fmt/core.h>

namespace orion {
    GLFWWindowWrapper::GLFWWindowWrapper(int width, int height, Ref<std::string> name, PtrMut<GLFWmonitor> monitor, PtrMut<GLFWwindow> share) :
        m_name(name)
    {
        if (COUNT == 0)
            initialize();

        m_window = glfwCreateWindow(width, height, name.c_str(), monitor ? monitor : glfwGetPrimaryMonitor(), share);
        if (!m_window) {
            fmt::print(stderr, "Window creation failed.\n");
            exit(EXIT_FAILURE);
        }

        OpenGlContext::set_current(m_window);

        COUNT += 1;
    }

    GLFWWindowWrapper::~GLFWWindowWrapper() {
        OpenGlContext::on_any_destroy(m_window);
        glfwDestroyWindow(m_window);
        COUNT -= 1;
        if (COUNT == 0)
            glfwTerminate();
    }

    int GLFWWindowWrapper::COUNT = 0;

    void GLFWWindowWrapper::initialize() {
        if (!glfwInit()) {
            fmt::print(stderr, "Could not initialize GLFW.\n");
            exit(EXIT_FAILURE);
        }

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    }

    bool GLFWWindowWrapper::is_close() const {
        return glfwWindowShouldClose(m_window);
    }

    void GLFWWindowWrapper::close() {
        glfwSetWindowShouldClose(m_window, GLFW_TRUE);
    }

    void GLFWWindowWrapper::open() {
        glfwSetWindowShouldClose(m_window, GLFW_FALSE);
    }

    void GLFWWindowWrapper::set_name(Ref<std::string> name) {
        m_name = name;
        glfwSetWindowTitle(m_window, m_name.c_str());
    }

    Ref<std::string> GLFWWindowWrapper::get_name() const {
        return m_name;
    }

    void GLFWWindowWrapper::set_icon(int t_count, Ptr<GLFWimage> images) {
        glfwSetWindowIcon(m_window, t_count, images);
    }

    Vector2i GLFWWindowWrapper::get_position() const {
        int x, y;
        glfwGetWindowPos(m_window, &x, &y);
        return {x, y};
    }

    void GLFWWindowWrapper::set_position(Ref<Vector2i> position) {
        glfwSetWindowPos(m_window, position.get_x(), position.get_y());
    }

    Vector2i GLFWWindowWrapper::get_size() const {
        int width, height;
        glfwGetWindowSize(m_window, &width, &height);
        return {width, height};
    }

    void GLFWWindowWrapper::set_size(Ref<Vector2i> size) {
        glfwSetWindowSize(m_window, size.get_x(), size.get_y());
    }

    void GLFWWindowWrapper::set_size_limits(Ref<Vector2i> min, Ref<Vector2i> max) {
        glfwSetWindowSizeLimits(m_window, min.get_x(), min.get_y(), max.get_x(), max.get_y());
    }
    void GLFWWindowWrapper::set_aspect_ratio(int numer, int denom) {
        glfwSetWindowAspectRatio(m_window, numer, denom);
    }

    Vector2i GLFWWindowWrapper::get_framebuffer_size() const {
        int width, height;
        glfwGetFramebufferSize(m_window, &width, &height);
        return {width, height};
    }

    Vector2i GLFWWindowWrapper::get_frame_size() const {
        int left, top, right, bottom;
        glfwGetWindowFrameSize(m_window, &left, &top, &right, &bottom);
        return {right - left, bottom - top};
    }

    Vector2f GLFWWindowWrapper::get_content_scale() const {
        float x, y;
        glfwGetWindowContentScale(m_window, &x, &y);
        return {x, y};
    }

    float GLFWWindowWrapper::get_opacity() const {
        return glfwGetWindowOpacity(m_window);
    }

    void GLFWWindowWrapper::set_opacity(float opacity) {
        glfwSetWindowOpacity(m_window, opacity);
    }

    void GLFWWindowWrapper::iconify() {
        glfwIconifyWindow(m_window);
    }

    void GLFWWindowWrapper::restore() {
        glfwRestoreWindow(m_window);
    }

    void GLFWWindowWrapper::maximize() {
        glfwMaximizeWindow(m_window);
    }

    void GLFWWindowWrapper::show() {
        glfwShowWindow(m_window);
    }

    void GLFWWindowWrapper::hide() {
        glfwHideWindow(m_window);
    }

    void GLFWWindowWrapper::focus() {
        glfwFocusWindow(m_window);
    }

    void GLFWWindowWrapper::request_attention() {
        glfwRequestWindowAttention(m_window);
    }

    GLFWmonitor *GLFWWindowWrapper::get_monitor() const {
        return glfwGetWindowMonitor(m_window);
    }

    void GLFWWindowWrapper::set_monitor(PtrMut<GLFWmonitor> monitor, Ref<Vector2i> position, Ref<Vector2i> size, int refresh_rate) {
        glfwSetWindowMonitor(m_window, monitor,
            position.get_x(), position.get_y(),
            size.get_x(), size.get_y(),
            refresh_rate
        );
    }

    int GLFWWindowWrapper::get_attribute(int attribute) {
        return glfwGetWindowAttrib(m_window, attribute);
    }

    void GLFWWindowWrapper::set_attribute(int attribute, int value) {
        glfwSetWindowAttrib(m_window, attribute, value);
    }

    PtrMut<void> GLFWWindowWrapper::get_user_pointer() {
        return glfwGetWindowUserPointer(m_window);
    }

    void GLFWWindowWrapper::set_user_pointer(PtrMut<void> ptr) {
        glfwSetWindowUserPointer(m_window, ptr);
    }

    void GLFWWindowWrapper::swap_buffers() {
        glfwSwapBuffers(m_window);
    }

    void GLFWWindowWrapper::poll_events() {
        if (COUNT > 0)
            glfwPollEvents();
        else
            fmt::print(stderr, "You can't poll event before initialize GLFW.");
    }

    void GLFWWindowWrapper::wait_events() {
        if (COUNT > 0)
            glfwWaitEvents();
        else
            fmt::print(stderr, "You can't wait for event before initialize GLFW.");
    }

    void GLFWWindowWrapper::wait_events_timeout(double timeout) {
        if (COUNT > 0)
            glfwWaitEventsTimeout(timeout);
        else
            fmt::print(stderr, "You can't set event timeout before initialize GLFW.");
    }

    void GLFWWindowWrapper::post_empty_event() {
        if (COUNT > 0)
            glfwPostEmptyEvent();
        else
            fmt::print(stderr, "You can't post empty event before initialize GLFW.");
    }

    void GLFWWindowWrapper::enable_vsync() {
        if (OpenGlContext::is_any_current())
            glfwSwapInterval(1);
        else
            fmt::print(stderr, "You can't enable vsync on non existing context.");
    }

    void GLFWWindowWrapper::disable_vsync() {
        if (OpenGlContext::is_any_current())
            glfwSwapInterval(0);
        else
            fmt::print(stderr, "You can't enable vsync on non existing context.");
    }
}
