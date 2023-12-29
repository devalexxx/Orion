//
// Created by Alex on 09/12/2023.
//

#ifndef ORION_IMAGE_H
#define ORION_IMAGE_H

#pragma once

#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "stb_image.h"

#include "core/type.h"

namespace orion {

    class Image {
    public:
        static Image load_from_file(Ptr<char> path);
        static Image load_from_file(Ptr<char> path, bool flip_v);

        [[nodiscard]] u32 get_width() const;
        [[nodiscard]] u32 get_height() const;

        [[nodiscard]] Ptr<u8> get_pixels() const;
    private:
        explicit Image(u32 width, u32 height, std::vector<u8> data);

        u32 m_width;
        u32 m_height;

        std::vector<u8> m_data;
    };

} // orion

#endif //ORION_IMAGE_H
