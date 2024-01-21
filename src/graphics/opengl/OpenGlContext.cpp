//
// Created by Alex on 04/01/2024.
//

#include "orion/graphics/opengl/OpenGlContext.h"

#include "orion/graphics/opengl/OpenGlApi.h"

#include "orion/graphics/Texture.h"
#include "orion/graphics/Shader.h"
#include "orion/graphics/VertexArray.h"

#include <iostream>

namespace orion {

    OpenGlContext::Context OpenGlContext::get_current() {
        return glfwGetCurrentContext();
    }

    void OpenGlContext::set_current(Context context) {
        if (get_current() != context) {
            glfwMakeContextCurrent(context);

            if (!OpenGlApi::IS_LOADED)
                OpenGlApi::load();

            auto& registries = IDeferredRegistry::get_registries();
            auto opengl_registries = registries.find("opengl");
            if (opengl_registries != registries.cend()) {
                for (auto registry: opengl_registries->second) {
                    registry->load();
                }
            }
        }
    }

    bool OpenGlContext::is_any_current() {
        return get_current() != nullptr;
    }

    void OpenGlContext::on_any_destroy(Context context) {

        VertexArray ::CURRENT_BOUND = 0;
        VertexBuffer::CURRENT_BOUND = 0;
        Shader      ::CURRENT_USE   = 0;

        if (context == get_current()) {
            auto& registries = IDeferredRegistry::get_registries();
            auto opengl_registries = registries.find("opengl");
            if (opengl_registries != registries.cend()) {
                for (auto registry: opengl_registries->second) {
                    registry->reset();
                }
            }
        }
    }

} // orion