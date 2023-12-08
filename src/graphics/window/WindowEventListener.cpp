//
// Created by Alex on 12/11/2023.
//

#include "graphics/window/WindowEventListener.h"

namespace orion {

    WindowEventListener::WindowEventListener(const std::shared_ptr<EventManager>& e_manager) : EventListener(e_manager) {
        bind(&WindowEventListener::onPositionChange);
        bind(&WindowEventListener::onSizeChange);
        bind(&WindowEventListener::onClose);
        bind(&WindowEventListener::onRefresh);
        bind(&WindowEventListener::onFocus);
        bind(&WindowEventListener::onIconify);
        bind(&WindowEventListener::onMaximize);
        bind(&WindowEventListener::onContentScaleChange);
    }

}