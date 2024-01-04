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

    class Window :
            public GLFWWindowWrapper,
            public std::enable_shared_from_this<Window>,
            public RenderTarget
    {
    public:
        static std::shared_ptr<Window> create(const std::string& name);
        void display();

        void set_event_manager(Ref<std::shared_ptr<EventManager>> event_manager);
    private:
        explicit Window(Ref<std::string> name);

        std::weak_ptr<EventManager> m_event_manager;

        friend class WindowEventDispatcher;
    };
}


#endif //ORION_WINDOW_H
