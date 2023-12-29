//
// Created by Alex on 26/12/2023.
//

#include "graphics/opengl/OpenGLRequired.h"

#include "graphics/opengl/OpenGLApi.h"

namespace orion {
    OpenGLRequired::OpenGLRequired() {
        if (!OpenGLApi::is_loaded)
            OpenGLApi::load();
    }
} // orion