//
// Created by Alex on 04/01/2024.
//

#include "orion/graphics/opengl/OpenGlContextRequired.h"

#include "orion/graphics/opengl/OpenGlContext.h"

#include <cassert>

namespace orion {

    OpenGlContextRequired::OpenGlContextRequired() {
        assert(OpenGlContext::is_any_current() && "This class require OpenGl context to instantiate");
    }

} // orion