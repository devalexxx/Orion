//
// Created by Alex on 23/12/2023.
//

#include "graphics/PackedVertex.h"

namespace orion {

    PackedVertex::PackedVertex(Ref<Vector3f> position, Ref<Vector2f> uv, Ref<Vector3f> normal) :
        position(position),
        normal(normal),
        uv(uv)
    {}

    PackedVertex::PackedVertex(Ref<Vector3f> position) : position(position) {}

    PackedVertex::PackedVertex(Ref<Vector3f> position, Ref<Vector3f> normal) : position(position), normal(normal) {}

    PackedVertex::PackedVertex(Ref<Vector3f> position, Ref<Vector2f> uv) : position(position), uv(uv) {}

    Pair<Ptr<f32>, u32> to_float_array(Ref<PackedVertexContainer> v) {
        return std::make_pair(reinterpret_cast<const f32*>(v.data()), v.size() * 8);
    }
}