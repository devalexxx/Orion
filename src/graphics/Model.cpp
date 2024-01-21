//
// Created by Alex on 16/01/2024.
//

#include "orion/graphics/Model.h"

#include "orion/graphics/Primitive.h"
#include "orion/graphics/Mesh.h"

#include <fstream>
#include <sstream>
#include <functional>

#include <fmt/ostream.h>

namespace orion {

    Model Model::load_from_file(Ref<Path> path, bool index) {

        std::vector<Vector3f> tmp_vertex;
        std::vector<Vector2f> tmp_uv;
        std::vector<Vector3f> tmp_normal;
        std::vector<Vector3i> tmp_index;

        std::ifstream stream(path.c_str(), std::ios::in);
        if (stream.is_open()) {

            std::string line;
            while (std::getline(stream, line)) {
                char header[128];
                sscanf(line.c_str(), "%s", header);

                if (strcmp(header, "v") == 0) {
                    f32 x, y, z;
                    if (sscanf(line.c_str(), "v %f %f %f\n", &x, &y, &z) == 3)
                        tmp_vertex.emplace_back(x, y, z);
                    else {
                        fmt::print(stderr, "Failed to retrieve vertex from {}\n", fmt::streamed(path));
                        break;
                    }
                }
                else if (strcmp(header, "vn") == 0) {
                    f32 x, y, z;
                    if (sscanf(line.c_str(), "vn %f %f %f\n", &x, &y, &z) == 3)
                        tmp_normal.emplace_back(x, y, z);
                    else {
                        fmt::print(stderr, "Failed to retrieve normal from {}\n", fmt::streamed(path));
                        break;
                    }
                }
                else if (strcmp(header, "vt") == 0) {
                    f32 x, y;
                    if (sscanf(line.c_str(), "vt %f %f\n", &x, &y) == 2)
                        tmp_uv.emplace_back(x, y);
                    else {
                        fmt::print(stderr, "Failed to retrieve uv from {}\n", fmt::streamed(path));
                        break;
                    }
                }
                else if (strcmp(header, "f") == 0) {
                    i32 a, b, c, d, e, f, g, h, i;
                    if (sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d\n", &a, &b, &c, &d, &e, &f, &g, &h, &i) == 9) {
                        tmp_index.emplace_back(a, b, c);
                        tmp_index.emplace_back(e, f, g);
                        tmp_index.emplace_back(f, h, i);
                    }
                    else {
                        fmt::print(stderr, "Failed to retrieve uv from {}\nIt seems your object file is not triangulated.", fmt::streamed(path));
                        break;
                    }
                }
            }

            stream.close();
        }
        else
            fmt::print(stderr, "Unable to open {}. Are you in the right directory ?\n", fmt::streamed(path));

        PackedVertexContainer packed_vertices;
        packed_vertices.reserve(tmp_index.size());

        for (auto& idx: tmp_index) {
            packed_vertices.emplace_back(
                    tmp_vertex[idx.get_x() - 1],
                    tmp_uv    [idx.get_y() - 1],
                    tmp_normal[idx.get_z() - 1]
            );
        }

        if (index)
            return std::make_from_tuple<Model>(generator::index(packed_vertices));
        else
            return Model(std::move(packed_vertices));

    }

    Model::Model(PackedVertexContainer packed_vertices, IndexContainer indices) :
        m_packed_vertices(std::move(packed_vertices)),
        m_indices        (std::move(indices)),
        m_mesh           (Mesh::create(m_packed_vertices, m_indices.value()))
    {}

    Model::Model(PackedVertexContainer packed_vertices) :
        m_packed_vertices(std::move(packed_vertices)),
        m_indices        (std::nullopt),
        m_mesh           (Mesh::create(m_packed_vertices))
    {}

    std::shared_ptr<Mesh> Model::get_mesh() const {
        return m_mesh;
    }


} // orion