//
// Created by Alex on 26/12/2023.
//

#include "graphics/opengl/OpenGlApi.h"

#include "GL/glew.h"

#include <iostream>
#include <cassert>

#include "graphics/opengl/OpenGlContext.h"

namespace orion {

    bool OpenGlApi::is_loaded = false;

    void OpenGlApi::load() {

        assert(OpenGlContext::is_any_current() && "You can't load OpenGl api without OpenGl context.");

        glewExperimental = true;
        if (glewInit() != GLEW_OK) {
            std::cerr << "Could not initialize OpenGL API. \n";
            exit(EXIT_FAILURE);
        }

        is_loaded = true;
    }
} // orion