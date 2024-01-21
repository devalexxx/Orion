//
// Created by Alex on 16/01/2024.
//

#ifndef ORION_MODEL_H
#define ORION_MODEL_H

#include "orion/core/type.h"

#include <optional>

namespace orion {

    struct PackedVertex;
    using PackedVertexContainer = std::vector<PackedVertex>;

    class Mesh;

    class Model {
    public:
        static Model load_from_file(Ref<Path> path, bool index = false);

        explicit Model(PackedVertexContainer packed_vertices);
        Model(PackedVertexContainer packed_vertices, IndexContainer indices);

        [[nodiscard]] std::shared_ptr<Mesh> get_mesh() const;

    private:
        PackedVertexContainer m_packed_vertices;
        std::optional<IndexContainer> m_indices;

        std::shared_ptr<Mesh> m_mesh;
    };

} // orion

#endif //ORION_MODEL_H
