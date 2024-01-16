//
// Created by Alex on 23/12/2023.
//

#include "graphics/RenderTarget.h"

#include "graphics/Drawable.h"
#include "graphics/VertexArray.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"

#include <fmt/core.h>

namespace orion {

    void RenderTarget::draw(const Drawable& drawable, const RenderContext& context) const {
        drawable.draw(*this, context);
    }

    void RenderTarget::draw(Ref<VertexArray> vao, Ref<RenderContext> context) const {
        static auto last_context = std::ref(RenderContext::DEFAULT);
        static bool frame_swap = true;

        auto& shader = context.m_shader;
        if (shader) {
            if (shader != last_context.get().m_shader) {
                shader->use();
            }

            if (m_frame_swap != frame_swap) {
                if (shader->has_uniform("view"))
                    shader->set_uniform("view", m_view.get_view());

                if (shader->has_uniform("projection"))
                    shader->set_uniform("projection", m_view.get_projection());

                frame_swap = m_frame_swap;
            }

            auto& texture = context.m_texture;
            if (texture) {
                if (texture != last_context.get().m_texture) {
                    if (shader->has_uniform("texture_sampler")) {
                        glActiveTexture(GL_TEXTURE0);
                        texture->bind();
                        shader->set_uniform("texture_sampler", 0);
                    }
                }
            }

            vao.draw(context.m_draw_mode);

            if (last_context.get() != context)
                last_context = std::ref(context);
        }
        else
            fmt::print(stderr, "Unable to render vao {} because no shader was provide.\n", vao.m_id);
    }

    RefMut<View> RenderTarget::get_view() {
        return m_view;
    }
}