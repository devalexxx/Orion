//
// Created by Alex on 12/11/2023.
//

#ifndef ORION_GLFWWINDOWWRAPPER_H
#define ORION_GLFWWINDOWWRAPPER_H

#include <string>

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include "core/type.h"
#include "math/Vector2.h"

namespace orion {
    class GLFWWindowWrapper {
    public:
        explicit GLFWWindowWrapper(int width, int height, Ref<std::string> name, PtrMut<GLFWmonitor> monitor, PtrMut<GLFWwindow> share);
        virtual ~GLFWWindowWrapper();

        [[nodiscard]] bool is_close() const;
        void close();
        void open();

        void set_name(Ref<std::string> name);
        [[nodiscard]] Ref<std::string> get_name() const;

        void set_icon(int t_count, Ptr<GLFWimage> images);

        [[nodiscard]] Vector2i get_position() const;
        void set_position(Ref<Vector2i> position);

        [[nodiscard]] Vector2i get_size() const;
        void set_size(Ref<Vector2i> size);

        void set_size_limits(Ref<Vector2i> min, Ref<Vector2i> max);
        void set_aspect_ratio(int numer, int denom);

        [[nodiscard]] Vector2i get_framebuffer_size() const;

        [[nodiscard]] Vector2i get_frame_size() const;

        [[nodiscard]] Vector2f get_content_scale() const;

        [[nodiscard]] float get_opacity() const;
        void set_opacity(float opacity);

        void iconify();
        void restore();
        void maximize();
        void show();
        void hide();
        void focus();
        void request_attention();

        [[nodiscard]] PtrMut<GLFWmonitor> get_monitor() const;
        void set_monitor(PtrMut<GLFWmonitor> monitor, Ref<Vector2i> position, Ref<Vector2i> size, int refresh_rate);

        int get_attribute(int attribute);
        void set_attribute(int attribute, int value);

        PtrMut<void> get_user_pointer();
        void         set_user_pointer(PtrMut<void> ptr);

        void swap_buffers();

        static void poll_events();
        static void wait_events();
        static void wait_events_timeout(double timeout);
        static void post_empty_event();

        static void enable_vsync ();
        static void disable_vsync();

    protected:
        PtrMut<GLFWwindow> m_window;
        std::string        m_name;

    private:
        static int  COUNT;
        static void initialize();
    };
}




#endif //ORION_GLFWWINDOWWRAPPER_H
