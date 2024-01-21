//
// Created by Alex on 20/11/2023.
//

#ifndef ORION_KEYEVENTLISTENER_H
#define ORION_KEYEVENTLISTENER_H

#include "orion/core/event/EventListener.h"

#include "WindowEvent.h"

namespace orion {

    class KeyEventListener : public EventListener {
    public:
        explicit KeyEventListener(Ref<std::shared_ptr<EventManager>> e_manager);
        virtual void on_event  (Ref<Input::KeyEvent> event);
        virtual void on_pressed(Ref<Input::KeyEvent> event) {};
        virtual void on_release(Ref<Input::KeyEvent> event) {};
        virtual void on_repeat (Ref<Input::KeyEvent> event) {};
    };

} // orion

#endif //ORION_KEYEVENTLISTENER_H
