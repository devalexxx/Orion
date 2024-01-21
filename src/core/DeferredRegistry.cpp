//
// Created by Alex on 26/12/2023.
//

#include "orion/core/DeferredRegistry.h"

namespace orion {

    RefMut<IDeferredRegistry::Registries> IDeferredRegistry::get_registries() {
        static Registries registries {};
        return registries;
    }

} // orion