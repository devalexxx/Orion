//
// Created by Alex on 23/12/2023.
//

#ifndef ORION_PACKEDVERTEX_H
#define ORION_PACKEDVERTEX_H

#include <vector>

#include "omath.h"
#include "core/type.h"

namespace orion {

    struct PackedVertex {
        Vector3f position;
        Vector3f normal {};
        Vector2f uv     {};

        explicit PackedVertex(Ref<Vector3f> position);
        PackedVertex(Ref<Vector3f> position, Ref<Vector3f> normal);
        PackedVertex(Ref<Vector3f> position, Ref<Vector2f> uv);
        PackedVertex(Ref<Vector3f> position, Ref<Vector2f> uv, Ref<Vector3f> normal);

        friend inline bool operator==(Ref<PackedVertex> lhs, Ref<PackedVertex> rhs) {
            return rhs.position == lhs.position && rhs.normal == lhs.normal && rhs.uv == lhs.uv;
        }

        friend inline bool operator!=(Ref<PackedVertex> lhs, Ref<PackedVertex> rhs) {
            return !(lhs == rhs);
        }
    };

    using PackedVertexContainer = std::vector<PackedVertex>;

    std::pair<const f32*, u32> to_float_array(Ref<PackedVertexContainer> v);

}

#endif //ORION_PACKEDVERTEX_H
