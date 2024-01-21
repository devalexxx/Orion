//
// Created by Alex on 09/12/2023.
//

#include "orion/graphics/Image.h"

namespace orion {

    Image Image::load_from_file(Ptr<char> path) {
        return load_from_file(path, false);
    }

    Image Image::load_from_file(Ptr<char> path, bool flip_v) {
        i32 w, h, n;
        stbi_set_flip_vertically_on_load(flip_v);
        auto data = stbi_load(path, &w, &h, &n, 4);
        stbi_set_flip_vertically_on_load(false);
        auto v = std::vector<u8>(data, data + (w * h * 4));
        stbi_image_free(data);

        return Image(w, h, std::move(v));
    }

    Image::Image(u32 width, u32 height, std::vector<u8> data) :
        m_width(width),
        m_height(height),
        m_data(std::move(data))
    {}

    u32 Image::get_width() const {
        return m_width;
    }

    u32 Image::get_height() const {
        return m_height;
    }

    Ptr<u8> Image::get_pixels() const {
        return m_data.data();
    }

    Image Image::load_from_file(Ref<Path> path) {
        return load_from_file(path.c_str());
    }

    Image Image::load_from_file(Ref<Path> path, bool flip_v) {
        return load_from_file(path.c_str(), flip_v);
    }

} // orion