//
// Created by Alex on 13/11/2023.
//

#ifndef ORION_EVENT_H
#define ORION_EVENT_H

#include <cstdlib>

#include "core/type.h"

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
        explicit Event(Ref<EventType> event);
        static size_t getType();
        Ref<EventType> event;
    };

    template<typename EventType>
    Event<EventType>::Event(Ref<EventType> event) : event(event) {}

    template<typename EventType>
    size_t Event<EventType>::getType() {
        static size_t type = BaseEvent::getNextType();
        return type;
    }

} // orion

#endif //ORION_EVENT_H
