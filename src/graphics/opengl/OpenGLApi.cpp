//
// Created by Alex on 26/12/2023.
//

#include "graphics/opengl/OpenGLApi.h"

#include "graphics/Shader.h"
#include "graphics/Texture.h"

#include "GL/glew.h"

#include <iostream>

namespace orion {

    bool OpenGLApi::is_loaded = false;

    void OpenGLApi::load() {
        glewExperimental = true;
        if (glewInit() != GLEW_OK) {
            std::cerr << "Could not initialize OpenGL API. \n";
            exit(EXIT_FAILURE);
        }

        Shader::REGISTRY.load();
        Texture::REGISTRY.load();

        is_loaded = true;
    }
} // orion