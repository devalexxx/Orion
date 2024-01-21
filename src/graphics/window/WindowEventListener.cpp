//
// Created by Alex on 12/11/2023.
//

#include "orion/graphics/window/WindowEventListener.h"

namespace orion {

    WindowEventListener::WindowEventListener(Ref<std::shared_ptr<EventManager>> event_manager) : EventListener(event_manager) {
        bind(&WindowEventListener::on_position_change);
        bind(&WindowEventListener::on_size_change);
        bind(&WindowEventListener::on_close);
        bind(&WindowEventListener::on_refresh);
        bind(&WindowEventListener::on_focus);
        bind(&WindowEventListener::on_iconify);
        bind(&WindowEventListener::on_maximize);
        bind(&WindowEventListener::on_content_scale_change);
    }

}