//
// Created by Alex on 20/11/2023.
//

#include "orion/graphics/window/KeyEventListener.h"

namespace orion {
    KeyEventListener::KeyEventListener(Ref<std::shared_ptr<EventManager>> e_manager) : EventListener(e_manager) {
        bind(&KeyEventListener::on_event);
    }

    void KeyEventListener::on_event(Ref<Input::KeyEvent> event) {
        if(event.repeat) {
            on_repeat(event);
            on_pressed(event);
        }
        else if (event.pressed)
            on_pressed(event);
        else
            on_release(event);
    }
} // orion