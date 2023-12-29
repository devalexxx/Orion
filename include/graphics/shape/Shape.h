//
// Created by Alex on 09/12/2023.
//

#ifndef ORION_SHAPE_H
#define ORION_SHAPE_H

#include "graphics/Drawable.h"

#include "graphics/Shader.h"
#include "graphics/RenderContext.h"
#include "graphics/Transform.h"

#include <memory>

namespace orion {

    class VertexArray;
    class Texture;

    class Shape: public Drawable {
    public:
        Shape();

        [[nodiscard]] Ref<std::shared_ptr<Texture>> get_texture() const;
        [[nodiscard]] Ref<std::shared_ptr<Shader>>  get_shader () const;

        [[nodiscard]] RefMut<Transform> get_transform();

        void set_texture(std::shared_ptr<Texture> texture);
        void set_shader (std::shared_ptr<Shader> shader);

    protected:
        std::shared_ptr<VertexArray> m_vao;
        std::shared_ptr<Texture>     m_texture;
        std::shared_ptr<Shader>      m_shader;

        Transform m_transform;

        RenderContext m_context;
    };

} // orion

#endif //ORION_SHAPE_H
