//
// Created by Alex on 14/01/2024.
//

#ifndef ORION_PRIMITIVE_H
#define ORION_PRIMITIVE_H

#include "core/type.h"

namespace orion {

    class PackedVertex;
    using PackedVertexContainer = std::vector<PackedVertex>;

    enum class Primitive {
        TRIANGLE,
        SQUARE,
        CIRCLE,
        CUBE,
        SPHERE,
    };

    std::string to_string(Primitive primitive);

    namespace generator {

        std::pair<PackedVertexContainer, IndexContainer> index(Ref<PackedVertexContainer> vertices);

        PackedVertexContainer triangle_vertices();
        PackedVertexContainer square_vertices  ();
        PackedVertexContainer circle_vertices  (u32 v_count);
        PackedVertexContainer cube_vertices    ();
        PackedVertexContainer sphere_vertices  (u32 subdivisions);

    }

} // orion

#endif //ORION_PRIMITIVE_H
