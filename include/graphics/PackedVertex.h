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
        PackedVertex(Ref<Vector3f> position, Ref<Vector3f> normal, Ref<Vector2f> uv);
    };

    std::pair<const f32*, u32> to_float_array(Ref<std::vector<PackedVertex>> v);

}

#endif //ORION_PACKEDVERTEX_H
