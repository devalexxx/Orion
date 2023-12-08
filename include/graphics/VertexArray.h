//
// Created by Alex on 01/12/2023.
//

#ifndef ORION_VERTEXARRAY_H
#define ORION_VERTEXARRAY_H

#include <vector>

namespace orion {

    class Vertex;

    class VertexArray {
    private:
        std::vector<Vertex> m_vertices;
    };

} // orion

#endif //ORION_VERTEXARRAY_H
