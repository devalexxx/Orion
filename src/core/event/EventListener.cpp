//
// Created by Alex on 15/11/2023.
//

#include "orion/core/event/EventListener.h"

#include <iostream>

namespace orion {
    EventListener::EventListener(Ref<std::shared_ptr<EventManager>> event_manager) : m_event_manager(event_manager) {}

    EventListener::~EventListener() {
        if (!m_event_manager.expired()) {
            auto event_manager = m_event_manager.lock();
            for (auto& id: m_handler_ids) {
                event_manager->unsubscribe(id);
            }
        }
    }
}

