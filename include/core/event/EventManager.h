//
// Created by Alex on 14/11/2023.
//

#ifndef ORION_EVENTMANAGER_H
#define ORION_EVENTMANAGER_H

#include <mutex>
#include <functional>

#include "Event.h"

namespace orion {

    class EventManager {
    public:
        template <class EventType>
        using call_type = std::function<void(const EventType&)>;

        explicit EventManager() = default;

        template <typename EventType>
        size_t subscribe(call_type<EventType> callable);

        void unsubscribe(size_t id);

        template <typename EventType>
        void emit(const EventType& event);

    private:
        template<typename EventType>
        class CallbackWrapper {
        public:
            explicit CallbackWrapper(EventManager::call_type<EventType> callable);
            void operator() (const BaseEvent& event);
        private:
            EventManager::call_type<EventType> m_callable;
        };

        std::mutex m_mutex {};
        std::vector<std::unordered_map<size_t, call_type<BaseEvent>>> m_subscribers;

    };

    template<typename EventType>
    size_t EventManager::subscribe(EventManager::call_type<EventType> callable) {
        std::lock_guard<std::mutex> l(m_mutex);
        static size_t count = 0;
        size_t type = Event<EventType>::getType();
        if (type >= m_subscribers.size())
            m_subscribers.resize(type + 1);
        auto it = m_subscribers[type].emplace(type * 10000 + (++count), CallbackWrapper<EventType>(callable));
        return it.first->first;
    }

    template<typename EventType>
    void EventManager::emit(const EventType &event) {
        std::lock_guard<std::mutex> l(m_mutex);
        size_t type = Event<EventType>::getType();
        if (type >= m_subscribers.size()) {
            m_subscribers.resize(type + 1);
            return;
        }
        Event<EventType> wrapper(event);
        for (auto& it : m_subscribers[type]) {
                it.second(wrapper);
        }
    }

    template<typename EventType>
    void EventManager::CallbackWrapper<EventType>::operator()(const BaseEvent &event) {
        m_callable(static_cast<const Event<EventType>&>(event).event);
    }

    template<typename EventType>
    EventManager::CallbackWrapper<EventType>::CallbackWrapper(EventManager::call_type<EventType> callable) : m_callable(callable) {}
}


#endif //ORION_EVENTMANAGER_H
