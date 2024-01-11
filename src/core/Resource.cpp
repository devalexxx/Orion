//
// Created by Alex on 05/01/2024.
//

#include "core/Resource.h"

namespace orion {

    Path resource::of(Ref<String> filename) {
        return WORKING_DIRECTORY / filename;
    }

    Path resource::texture::of(Ref<String> filename) {
        return DIRECTORY / filename;
    }

    Path resource::shader::of(Ref<String> filename) {
        return DIRECTORY / filename;
    }
} // orion