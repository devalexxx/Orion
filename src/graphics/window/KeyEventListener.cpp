//
// Created by Alex on 20/11/2023.
//

#include "graphics/window/KeyEventListener.h"

namespace orion {
    KeyEventListener::KeyEventListener(const std::shared_ptr<EventManager> &e_manager) : EventListener(e_manager) {
        bind(&KeyEventListener::onEvent);
    }

    void KeyEventListener::onEvent(const Input::KeyEvent &event) {
        if(event.repeat) {
            onRepeat(event);
            onPressed(event);
        }
        else if (event.pressed)
            onPressed(event);
        else
            onRelease(event);
    }
} // orion