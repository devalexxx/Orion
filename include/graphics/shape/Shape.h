//
// Created by Alex on 09/12/2023.
//

#ifndef ORION_SHAPE_H
#define ORION_SHAPE_H

#include "graphics/Drawable.h"

#include "graphics/Shader.h"
#include "graphics/RenderContext.h"
#include "graphics/Transform.h"
#include "graphics/Color.h"

#include <memory>

namespace orion {

    class VertexArray;
    class Texture;

    class Shape: public Drawable {
    public:
        enum class SampleMode {
            TEXTURE       = 0,
            COLOR         = 1,
            UNIFORM_COLOR = 2,
        };

        Shape();

        [[nodiscard]] Ref<std::shared_ptr<Texture>> get_texture() const;
        [[nodiscard]] Ref<std::shared_ptr<Shader>>  get_shader () const;

        [[nodiscard]] RefMut<Transform> get_transform();

        void set_texture(std::shared_ptr<Texture> texture);
        void set_shader (std::shared_ptr<Shader> shader);
        void set_color  (Ref<Color> color);
        void set_color  (std::vector<Color> color);

        void set_sample_mode(SampleMode mode);

        void draw(Ref<RenderTarget> target, Ref<RenderContext> context) const override;

    protected:
        std::shared_ptr<VertexArray> m_vao;
        std::shared_ptr<Texture>     m_texture;
        std::shared_ptr<Shader>      m_shader;

        Transform m_transform;

        SampleMode m_sample_mode;

        Color m_color;

        RenderContext m_context;
    };

    namespace generator {

        std::vector<PackedVertex> circle_vertices(u32 v_count);

    }

} // orion

#endif //ORION_SHAPE_H
