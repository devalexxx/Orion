//
// Created by Alex on 09/12/2023.
//

#include "orion/graphics/Texture.h"

#include "orion/graphics/Image.h"
#include "orion/graphics/opengl/OpenGlApi.h"

#include "GL/glew.h"

namespace orion {

    DeferredRegistry<Texture> Texture::get_registry() {
        return REGISTRY;
    }

    std::shared_ptr<Texture> Texture::create_from_image(Ref<Image> image) {
        auto texture = std::shared_ptr<Texture>(new Texture());
        texture->set_data(image);
        return std::move(texture);
    }

    Texture::Texture() {
        gl_check(glGenTextures(1, &m_id));
    }

    Texture::~Texture() {
        gl_check(glDeleteTextures(1, &m_id));
    }

    void Texture::bind() const {
        gl_check(glBindTexture(GL_TEXTURE_2D, m_id));
    }

    void Texture::set_data(u32 width, u32 height, Ptr<u8> data) const {
        bind();

        gl_check(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<i32>(width), static_cast<i32>(height), 0, GL_RGBA, GL_UNSIGNED_BYTE, data));

        gl_check(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        gl_check(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));

        gl_check(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        gl_check(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

        unbind();
    }

    void Texture::set_data(Ref<Image> image) const {
        set_data(image.get_width(), image.get_height(), image.get_pixels());
    }

    uint32_t Texture::get_id() const {
        return m_id;
    }

    void Texture::unbind() {
        gl_check(glBindTexture(GL_TEXTURE_2D, 0));
    }

    DeferredRegistry<Texture> Texture::REGISTRY = DeferredRegistry<Texture>("opengl");

}
