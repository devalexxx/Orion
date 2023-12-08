//
// Created by Alex on 20/11/2023.
//

#ifndef ORION_KEYEVENTLISTENER_H
#define ORION_KEYEVENTLISTENER_H

#include "core/event/EventListener.h"

#include "WindowEvent.h"

namespace orion {

    class KeyEventListener : public EventListener {
    public:
        explicit KeyEventListener(const std::shared_ptr<EventManager>& e_manager);
        virtual void onEvent(const Input::KeyEvent& event);
        virtual void onPressed(const Input::KeyEvent& event) {};
        virtual void onRelease(const Input::KeyEvent& event) {};
        virtual void onRepeat(const Input::KeyEvent& event) {};
    };

} // orion

#endif //ORION_KEYEVENTLISTENER_H
