//
// Created by Alex on 09/12/2023.
//

#ifndef ORION_TEXTURE_H
#define ORION_TEXTURE_H

#include <memory>

#include "core/type.h"
#include "core/DeferredRegistry.h"

#include "opengl/OpenGlContextRequired.h"

namespace orion {

    class Image;

    class Texture : public OpenGlContextRequired {
    public:
        using Registry = DeferredRegistry<Texture>;

        static Registry get_registry();

        static std::shared_ptr<Texture> create_from_image(Ref<Image> image);

        ~Texture();

        static void unbind();

        void bind() const;

        void set_data(u32 width, u32 height, Ptr<u8> data) const;
        void set_data(Ref<Image> image) const;

        [[nodiscard]] u32 get_id() const;
    private:
        Texture();

        u32 m_id{};

        static Registry REGISTRY;
    };
}


#endif //ORION_TEXTURE_H
