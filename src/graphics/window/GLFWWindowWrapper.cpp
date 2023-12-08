//
// Created by Alex on 12/11/2023.
//

#include "graphics/window/GLFWWindowWrapper.h"

#include <iostream>

namespace orion {
    GLFWWindowWrapper::GLFWWindowWrapper(int width, int height, const std::string &name, GLFWmonitor *monitor, GLFWwindow *share) :
        m_name(name)
    {
        if (count == 0)
            initialize();

        m_window = glfwCreateWindow(width, height, name.c_str(), monitor, share);
        if (!m_window) {
            std::cerr << "Window creation failed.\n";
            exit(EXIT_FAILURE);
        }

        count += 1;
    }

    GLFWWindowWrapper::~GLFWWindowWrapper() {
        glfwDestroyWindow(m_window);
        count -= 1;
        if (count == 0)
            glfwTerminate();
    }

    int GLFWWindowWrapper::count = 0;

    void GLFWWindowWrapper::initialize() {
        if (!glfwInit()) {
            std::cerr << "Could not initialize GLFW Library.\n";
            exit(EXIT_FAILURE);
        }
    }

    bool GLFWWindowWrapper::isClose() const {
        return glfwWindowShouldClose(m_window);
    }

    void GLFWWindowWrapper::close() {
        glfwSetWindowShouldClose(m_window, GLFW_TRUE);
    }

    void GLFWWindowWrapper::setName(const std::string &name) {
        m_name = name;
        glfwSetWindowTitle(m_window, m_name.c_str());
    }

    std::string GLFWWindowWrapper::getName() const {
        return m_name;
    }

    void GLFWWindowWrapper::setIcon(int t_count, const GLFWimage *images) {
        glfwSetWindowIcon(m_window, t_count, images);
    }

    Position2D GLFWWindowWrapper::getPosition() const {
        int x, y;
        glfwGetWindowPos(m_window, &x, &y);
        return {static_cast<float>(x), static_cast<float>(y)};
    }

    void GLFWWindowWrapper::setPosition(const Position2D &position) {
        glfwSetWindowPos(m_window, static_cast<int>(position.x), static_cast<int>(position.y));
    }

    Size2D GLFWWindowWrapper::getSize() const {
        int width, height;
        glfwGetWindowSize(m_window, &width, &height);
        return {static_cast<float>(width), static_cast<float>(height)};
    }

    void GLFWWindowWrapper::setSize(const Size2D &size) {
        glfwSetWindowSize(m_window, static_cast<int>(size.height), static_cast<int>(size.width));
    }

    void GLFWWindowWrapper::setSizeLimits(const Size2D& min, const Size2D& max) {
        glfwSetWindowSizeLimits(m_window, static_cast<int>(min.width), static_cast<int>(min.height), static_cast<int>(max.width), static_cast<int>(max.height));
    }
    void GLFWWindowWrapper::setAspectRatio(int numer, int denom) {
        glfwSetWindowAspectRatio(m_window, numer, denom);
    }

    Size2D GLFWWindowWrapper::getFramebufferSize() const {
        int width, height;
        glfwGetFramebufferSize(m_window, &width, &height);
        return {static_cast<float>(width), static_cast<float>(height)};
    }

    Size2D GLFWWindowWrapper::getFrameSize() const {
        int left, top, right, bottom;
        glfwGetWindowFrameSize(m_window, &left, &top, &right, &bottom);
        return {static_cast<float>(right - left), static_cast<float>(bottom - top)};
    }

    Scale2D GLFWWindowWrapper::getContentScale() const {
        float x, y;
        glfwGetWindowContentScale(m_window, &x, &y);
        return {x, y};
    }

    float GLFWWindowWrapper::getOpacity() const {
        return glfwGetWindowOpacity(m_window);
    }

    void GLFWWindowWrapper::setOpacity(float opacity) {
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

    void GLFWWindowWrapper::requestAttention() {
        glfwRequestWindowAttention(m_window);
    }

    GLFWmonitor *GLFWWindowWrapper::getMonitor() const {
        return glfwGetWindowMonitor(m_window);
    }

    void GLFWWindowWrapper::setMonitor(GLFWmonitor *monitor, const Position2D &position, const Size2D &size, int refresh_rate) {
        glfwSetWindowMonitor(m_window, monitor,
            static_cast<int>(position.x), static_cast<int>(position.y),
            static_cast<int>(size.width), static_cast<int>(size.height),
            refresh_rate
        );
    }

    int GLFWWindowWrapper::getAttribute(int attribute) {
        return glfwGetWindowAttrib(m_window, attribute);
    }

    void GLFWWindowWrapper::setAttribute(int attribute, int value) {
        glfwSetWindowAttrib(m_window, attribute, value);
    }

    void *GLFWWindowWrapper::getUserPointer() {
        return glfwGetWindowUserPointer(m_window);
    }

    void GLFWWindowWrapper::setUserPointer(void *ptr) {
        glfwSetWindowUserPointer(m_window, ptr);
    }

    void GLFWWindowWrapper::swapBuffers() {
        glfwSwapBuffers(m_window);
    }

    void GLFWWindowWrapper::pollEvents() {
        glfwPollEvents();
    }

    void GLFWWindowWrapper::waitEvents() {
        glfwWaitEvents();
    }

    void GLFWWindowWrapper::waitEventsTimeout(double timeout) {
        glfwWaitEventsTimeout(timeout);
    }

    void GLFWWindowWrapper::postEmptyEvent() {
        glfwPostEmptyEvent();
    }
}
