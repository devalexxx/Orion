//
// Created by Alex on 15/11/2023.
//

#ifndef ORION_EVENTLISTENER_H
#define ORION_EVENTLISTENER_H

#include <memory>
#include "EventManager.h"
#include <iostream>

namespace orion {

    class EventListener {

        template<typename Derived, typename EventType>
        using EventHandler = void(Derived::*)(Ref<EventType>);

    public:
        explicit EventListener(Ref<std::shared_ptr<EventManager>> event_manager);
        ~EventListener();

    protected:
        template<typename Derived, typename EventType>
        void bind(EventHandler<Derived, EventType> fn);

    private:
        std::weak_ptr<EventManager> m_event_manager;
        std::vector<size_t> m_handler_ids;
    };

    template<typename Derived, typename EventType>
    void EventListener::bind(EventHandler<Derived, EventType> fn) {
        if (!m_event_manager.expired()) {
            auto ptr = m_event_manager.lock();
            size_t id = m_event_manager.lock()->subscribe<EventType>(
                    [this, fn](const EventType &e) {
                        (static_cast<Derived *>(this)->*fn)(e);
                    }
            );
            m_handler_ids.push_back(id);
        }
    }
}


#endif //ORION_EVENTLISTENER_H
