//
// Created by Alex on 13/11/2023.
//

#include "orion/core/event/Event.h"

namespace orion {
    size_t BaseEvent::type_count = 0;

    size_t BaseEvent::getNextType() {
        return ++type_count;
    }
} // orion