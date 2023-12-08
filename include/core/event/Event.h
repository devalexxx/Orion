//
// Created by Alex on 13/11/2023.
//

#ifndef ORION_EVENT_H
#define ORION_EVENT_H

#include <cstdlib>

namespace orion {

    class BaseEvent {
    public:
        virtual ~BaseEvent() = default;
    protected:
        static size_t getNextType();
    private:
        static size_t type_count;
    };

    template<typename EventType>
    class Event : public BaseEvent {
    public:
        explicit Event(const EventType& event);
        static size_t getType();
        const EventType& event;
    };

    template<typename EventType>
    Event<EventType>::Event(const EventType &event) : event(event) {}

    template<typename EventType>
    size_t Event<EventType>::getType() {
        static size_t type = BaseEvent::getNextType();
        return type;
    }

} // orion

#endif //ORION_EVENT_H
