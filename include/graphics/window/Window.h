//
// Created by Alex on 12/11/2023.
//

#ifndef ORION_WINDOW_H
#define ORION_WINDOW_H

#include <string>
#include <memory>
#include <functional>

#include "GLFWWindowWrapper.h"
#include "graphics/RenderTarget.h"

namespace orion {

    class EventManager;
    class WindowEventDispatcher;

    enum class ClearMask {
        COLOR   = GL_COLOR_BUFFER_BIT,
        DEPTH   = GL_DEPTH_BUFFER_BIT,
        STENCIL = GL_STENCIL_BUFFER_BIT,
    };
    ClearMask operator|(ClearMask lhs, ClearMask rhs);

    class Window :
            public GLFWWindowWrapper,
            public std::enable_shared_from_this<Window>,
            public RenderTarget
    {
    public:
        static std::shared_ptr<Window> create(std::string name);

        void display();

        void clear(ClearMask mask);

        void set_event_manager(Ref<std::shared_ptr<EventManager>> event_manager);
    private:
        explicit Window(std::string name);

        std::weak_ptr<EventManager> m_event_manager;

        friend class WindowEventDispatcher;
    };
}


#endif //ORION_WINDOW_H
