//
// Created by Alex on 15/11/2023.
//

#include "core/event/EventListener.h"

#include <iostream>

namespace orion {
    EventListener::EventListener(const std::shared_ptr<EventManager>& event_manager) : m_event_manager(event_manager) {}

    EventListener::~EventListener() {
        if (!m_event_manager.expired()) {
            auto e_manager = m_event_manager.lock();
            for (auto& id: m_handler_ids) {
                e_manager->unsubscribe(id);
            }
        }
    }
}

