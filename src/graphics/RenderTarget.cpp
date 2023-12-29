//
// Created by Alex on 23/12/2023.
//

#include "graphics/RenderTarget.h"

#include "graphics/Drawable.h"
#include "graphics/VertexArray.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"

#include <iostream>

namespace orion {

    void RenderTarget::draw(const Drawable& drawable, const RenderContext& context) const {
        drawable.draw(*this, context);
    }

    void RenderTarget::draw(Ref<VertexArray> vao, Ref<RenderContext> context) const {
        static auto last_context = std::ref(RenderContext::DEFAULT);

        auto& shader = context.m_shader;
        if (shader) {
//            if (shader != last_context.get().m_shader) {
                shader->use();

                if (shader->has_uniform("view"))
                    shader->set_uniform("view", m_view.get_view());

                if (shader->has_uniform("projection"))
                    shader->set_uniform("projection", m_view.get_projection());
//            }

            auto& texture = context.m_texture;
            if (texture) {
//                if (texture != last_context.get().m_texture) {
                    apply_texture(*texture, *shader);
//                }
            }


            vao.draw(context.m_draw_mode);

            if (last_context.get() != context)
                last_context = std::ref(context);
        }
        else
            std::cerr << "Unable to render vao " << vao.m_id << " because no shader was provide.\n";
    }

    RefMut<View> RenderTarget::get_view() {
        return m_view;
    }

    void RenderTarget::apply_texture(Ref<Texture> texture, Ref<Shader> shader) const {
        if (shader.has_uniform("texture_sampler")) {
            glActiveTexture(GL_TEXTURE0);
            texture.bind();
            shader.set_uniform("texture_sampler", 0);
        }
    }
}