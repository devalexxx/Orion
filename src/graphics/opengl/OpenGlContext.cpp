//
// Created by Alex on 04/01/2024.
//

#include "graphics/opengl/OpenGlContext.h"

#include "graphics/opengl/OpenGlApi.h"

#include "graphics/Texture.h"
#include "graphics/Shader.h"
#include "graphics/VertexArray.h"

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

            auto it = IDeferredRegistry::REGISTRIES.find("opengl");
            if (it != IDeferredRegistry::REGISTRIES.cend()) {
                for (auto registry: it->second) {
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
            auto it = IDeferredRegistry::REGISTRIES.find("opengl");
            if (it != IDeferredRegistry::REGISTRIES.cend()) {
                for (auto registry: it->second) {
                    registry->reset();
                }
            }
        }
    }

} // orion