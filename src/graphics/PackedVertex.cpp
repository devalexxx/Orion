//
// Created by Alex on 23/12/2023.
//

#include "orion/graphics/PackedVertex.h"

namespace orion {

    PackedVertex::PackedVertex(Vector3f position, Vector2f uv, Vector3f normal) :
        position(position),
        normal(normal),
        uv(uv)
    {}

    PackedVertex::PackedVertex(Vector3f position) : position(position) {}

    PackedVertex::PackedVertex(Vector3f position, Vector3f normal) : position(position), normal(normal) {}

    PackedVertex::PackedVertex(Vector3f position, Vector2f uv) : position(position), uv(uv) {}

    Pair<Ptr<f32>, u32> to_float_array(Ref<PackedVertexContainer> v) {
        return std::make_pair(reinterpret_cast<const f32*>(v.data()), v.size() * 8);
    }
}