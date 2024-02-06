//
// Created by Alex on 01/02/2024.
//

#include "orion/core/ecs/Component.h"

namespace orion {

    u32 BaseComponent::TYPE_COUNT = 0;

    u32 BaseComponent::get_next_type() {
        return ++TYPE_COUNT;
    }

} // orion