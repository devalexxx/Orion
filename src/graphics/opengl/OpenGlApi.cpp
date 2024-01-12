//
// Created by Alex on 26/12/2023.
//

#include "graphics/opengl/OpenGlApi.h"

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

    bool OpenGlApi::is_enable(EnableCapability cap) {
        return glIsEnabled(std::underlying_type<EnableCapability>::type(cap)) == GL_TRUE;
    }

    void OpenGlApi::set_depth_function(DepthFunction func) {
        if (is_enable(EnableCapability::DEPTH_TEST))
            glDepthFunc(std::underlying_type<DepthFunction>::type(func));
        else
            std::cerr << "You may enable EnableCapability::DEPTH_TEST to use depth func\n";
    }

    void OpenGlApi::set_enable(EnableCapability cap) {
        if (!is_enable(cap))
            glEnable(std::underlying_type<EnableCapability>::type(cap));
    }

    void OpenGlApi::set_disable(EnableCapability cap) {
        if (is_enable(cap))
            glDisable(std::underlying_type<EnableCapability>::type(cap));
    }
} // orion