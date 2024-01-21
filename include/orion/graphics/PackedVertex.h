//
// Created by Alex on 23/12/2023.
//

#ifndef ORION_PACKEDVERTEX_H
#define ORION_PACKEDVERTEX_H

#include <vector>

#include "orion/omath.h"
#include "orion/core/type.h"
#include "orion/math/Vector.h"


namespace orion {

    struct PackedVertex {
        Vector3f position;
        Vector3f normal {};
        Vector2f uv     {};

        explicit PackedVertex(Vector3f position);
        PackedVertex(Vector3f position, Vector3f normal);
        PackedVertex(Vector3f position, Vector2f uv);
        PackedVertex(Vector3f position, Vector2f uv, Vector3f normal);

        friend inline bool operator==(Ref<PackedVertex> lhs, Ref<PackedVertex> rhs) {
            return rhs.position == lhs.position && rhs.normal == lhs.normal && rhs.uv == lhs.uv;
        }

        friend inline bool operator!=(Ref<PackedVertex> lhs, Ref<PackedVertex> rhs) {
            return !(lhs == rhs);
        }
    };

    using PackedVertexContainer = std::vector<PackedVertex>;

    Pair<Ptr<f32>, u32> to_float_array(Ref<PackedVertexContainer> v);

}

#endif //ORION_PACKEDVERTEX_H
