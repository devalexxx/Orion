//
// Created by Alex on 26/12/2023.
//

#include "core/DeferredRegistry.h"

namespace orion {

    std::map<std::string, std::vector<PtrMut<IDeferredRegistry>>> IDeferredRegistry::REGISTRIES {};

} // orion