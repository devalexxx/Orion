//
// Created by Alex on 04/01/2024.
//

#include "graphics/opengl/OpenGlContext.h"

#include "graphics/opengl/OpenGlApi.h"

#include "graphics/Texture.h"
#include "graphics/Shader.h"

#include <iostream>

namespace orion {

    OpenGlContext::Context OpenGlContext::get_current() {
        return glfwGetCurrentContext();
    }

    void OpenGlContext::set_current(Context context) {
        if (get_current() != context) {
            glfwMakeContextCurrent(context);

            if (!OpenGlApi::is_loaded)
                OpenGlApi::load();

            auto it = IDeferredRegistry::REGISTRIES.find("opengl");
            if (it != IDeferredRegistry::REGISTRIES.cend()) {
                for (auto dr: it->second) {
                    dr->load();
                }
            }
        }
    }

    bool OpenGlContext::is_any_current() {
        return get_current() != nullptr;
    }

    void OpenGlContext::on_any_destroy(Context context) {
        if (context == get_current()) {
            auto it = IDeferredRegistry::REGISTRIES.find("opengl");
            if (it != IDeferredRegistry::REGISTRIES.cend()) {
                for (auto dr: it->second) {
                    dr->reset();
                }
            }
        }
    }

} // orion