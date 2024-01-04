//
// Created by Alex on 04/01/2024.
//

#include "graphics/opengl/OpenGlContextRequired.h"

#include <cassert>
#include "graphics/opengl/OpenGlContext.h"

namespace orion {

    OpenGlContextRequired::OpenGlContextRequired() {
        assert(OpenGlContext::is_any_current() && "This class require OpenGl context to instantiate");
    }

} // orion