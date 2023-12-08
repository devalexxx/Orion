//
// Created by Alex on 12/11/2023.
//

#ifndef ORION_GLFWWINDOWWRAPPER_H
#define ORION_GLFWWINDOWWRAPPER_H

#include <string>

#include <GLFW/glfw3.h>
#include "core/Position.h"
#include "core/Size.h"

namespace orion {
    class GLFWWindowWrapper {
    public:
        explicit GLFWWindowWrapper(int width, int height, const std::string& name, GLFWmonitor* monitor, GLFWwindow* share);
        virtual ~GLFWWindowWrapper();

        [[nodiscard]] bool isClose() const;
        void close();

        void setName(const std::string& name);
        [[nodiscard]] std::string getName() const;

        void setIcon(int t_count, const GLFWimage* images);

        [[nodiscard]] Position2D getPosition() const;
        void setPosition(const Position2D& position);

        [[nodiscard]] Size2D getSize() const;
        void setSize(const Size2D& size);

        void setSizeLimits(const Size2D& min, const Size2D& max);
        void setAspectRatio(int numer, int denom);

        [[nodiscard]] Size2D getFramebufferSize() const;

        [[nodiscard]] Size2D getFrameSize() const;

        [[nodiscard]] Scale2D getContentScale() const;

        [[nodiscard]] float getOpacity() const;
        void setOpacity(float opacity);

        void iconify();
        void restore();
        void maximize();
        void show();
        void hide();
        void focus();
        void requestAttention();

        [[nodiscard]] GLFWmonitor* getMonitor() const;
        void setMonitor(GLFWmonitor* monitor, const Position2D& position, const Size2D& size, int refresh_rate);

        int getAttribute(int attribute);
        void setAttribute(int attribute, int value);

        void* getUserPointer();
        void setUserPointer(void* ptr);

        void swapBuffers();

        static void pollEvents();
        static void waitEvents();
        static void waitEventsTimeout(double timeout);
        static void postEmptyEvent();

    protected:
        GLFWwindow* m_window;
        std::string m_name;

    private:
        static int count;
        static void initialize();
    };
}




#endif //ORION_GLFWWINDOWWRAPPER_H
