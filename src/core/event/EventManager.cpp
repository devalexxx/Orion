//
// Created by Alex on 14/11/2023.
//

#include "orion/core/event/EventManager.h"

namespace orion {

    void EventManager::unsubscribe(size_t id) {
        std::lock_guard<std::mutex> l(m_mutex);
        size_t type = id / 10000;
        if (type < m_subscribers.size()) {
            auto it = m_subscribers[type].find(id);
            if(it != m_subscribers[type].cend())
                m_subscribers[type].erase(it);
        }
    }

    std::shared_ptr<EventManager> EventManager::create() {
        return std::shared_ptr<EventManager>(new EventManager());
    }
}