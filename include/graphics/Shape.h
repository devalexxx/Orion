//
// Created by Alex on 14/01/2024.
//

#ifndef ORION_SHAPE_H
#define ORION_SHAPE_H

#include "graphics/RenderContext.h"
#include "graphics/Drawable.h"
#include "graphics/Transform.h"
#include "graphics/Color.h"

#include <memory>

namespace orion {

    class Mesh;
    class Shader;
    class Texture;

    enum class Primitive;

    class Shape : public Drawable {
    public:
        enum class SampleMode {
            TEXTURE       = 0,
            COLOR         = 1,
            UNIFORM_COLOR = 2,
        };

        explicit Shape(std::shared_ptr<Mesh> mesh, bool use_attr = false);
        explicit Shape(Primitive primitive);

        [[nodiscard]] RefMut<Transform> get_transform();

        void set_texture(std::shared_ptr<Texture> texture);
        void set_shader (std::shared_ptr<Shader> shader);
        void set_color  (Color color);
        void set_color  (std::vector<Color> color);

        void set_sample_mode(SampleMode mode);

        void draw(Ref<RenderTarget> target, Ref<RenderContext> context) const override;

    private:
        std::shared_ptr<Mesh>    m_mesh;
        std::shared_ptr<Shader>  m_shader;
        std::shared_ptr<Texture> m_texture;

        Transform     m_transform;
        SampleMode    m_sample_mode;
        Color         m_color;
        RenderContext m_context;
    };

} // orion

#endif //ORION_SHAPE_H
