//
// Created by Alex on 14/01/2024.
//

#include "orion/graphics/Primitive.h"

#include "orion/graphics/PackedVertex.h"

#include <functional>

namespace orion {

    std::string to_string(Primitive primitive) {
        switch (primitive) {
            case Primitive::TRIANGLE:
                return "triangle";
            case Primitive::SQUARE:
                return "square";
            case Primitive::CIRCLE:
                return "circle";
            case Primitive::CUBE:
                return "cube";
            case Primitive::SPHERE:
                return "sphere";
        }
    }

    namespace generator {


        Pair<PackedVertexContainer, IndexContainer> index(Ref<PackedVertexContainer> vertices) {
            PackedVertexContainer vert;
            IndexContainer        indices;

            for (auto &packed: vertices) {
                auto found = std::find(vert.begin(), vert.end(), packed);
                if (found != vert.end()) {
                    indices.push_back(std::distance(vert.begin(), found));
                } else {
                    vert.push_back(packed);
                    indices.push_back(vert.size() - 1);
                }
            }

            return std::make_pair(std::move(vert), std::move(indices));
        }

        PackedVertexContainer triangle_vertices() {
            return {{
                PackedVertex(Vector3f(0.0f, 1.0f, 0.0f),Vector2f(0.5f, 1.0f)),
                PackedVertex(Vector3f(-1.0f, -1.0f, 0.0f),Vector2f(0.0f, 0.0f)),
                PackedVertex(Vector3f(1.0f, -1.0f, 0.0f),Vector2f(1.0f, 0.0f))
            }};
        }

        PackedVertexContainer square_vertices() {
            return {{
                PackedVertex(Vector3f(-1.0f,  1.0f,  0.0f), Vector2f(1.0f, 1.0f)),
                PackedVertex(Vector3f( 1.0f, -1.0f,  0.0f), Vector2f(0.0f, 0.0f)),
                PackedVertex(Vector3f( 1.0f,  1.0f,  0.0f), Vector2f(0.0f, 1.0f)),
                PackedVertex(Vector3f(-1.0f,  1.0f,  0.0f), Vector2f(1.0f, 1.0f)),
                PackedVertex(Vector3f(-1.0f, -1.0f,  0.0f), Vector2f(1.0f, 0.0f)),
                PackedVertex(Vector3f( 1.0f, -1.0f,  0.0f), Vector2f(0.0f, 0.0f)),
            }};
        }

        PackedVertexContainer circle_vertices(u32 v_count) {
            PackedVertexContainer ret;

            f32 angle = 360.0f / v_count;

            u32 triangle_count = v_count - 2;

            std::vector<Vector3f> temp;

            for (u32 i = 0; i < v_count; i++) {
                f32 current_angle = angle * i;
                f32 x = cos(radian(current_angle));
                f32 y = sin(radian(current_angle));
                f32 z = 0.0f;

                temp.emplace_back(x, y, z);
            }

            static auto mapper = std::bind(map_range<3, f32>, std::placeholders::_1, -1.f, 1.f, 0.f, 1.f);
            for (u32 i = 0; i < triangle_count; i++) {
                ret.emplace_back(temp[0], Vector2f(mapper(temp[0])));
                ret.emplace_back(temp[i + 1], Vector2f(mapper(temp[i + 1])));
                ret.emplace_back(temp[i + 2], Vector2f(mapper(temp[i + 2])));
            }

            return std::move(ret);
        }

        PackedVertexContainer cube_vertices() {
            return {{
                PackedVertex(Vector3f(-1.0f,  1.0f,  1.0f), Vector2f(1.0f, 1.0f),Vector3f::FORWARD),
                PackedVertex(Vector3f( 1.0f, -1.0f,  1.0f), Vector2f(0.0f, 0.0f),Vector3f::FORWARD),
                PackedVertex(Vector3f( 1.0f,  1.0f,  1.0f), Vector2f(0.0f, 1.0f),Vector3f::FORWARD),
                PackedVertex(Vector3f( 1.0f, -1.0f,  1.0f), Vector2f(1.0f, 1.0f),Vector3f::DOWN),
                PackedVertex(Vector3f(-1.0f, -1.0f, -1.0f), Vector2f(0.0f, 0.0f),Vector3f::DOWN),
                PackedVertex(Vector3f( 1.0f, -1.0f, -1.0f), Vector2f(0.0f, 1.0f),Vector3f::DOWN),
                PackedVertex(Vector3f(-1.0f, -1.0f,  1.0f), Vector2f(1.0f, 1.0f),Vector3f::LEFT),
                PackedVertex(Vector3f(-1.0f,  1.0f, -1.0f), Vector2f(0.0f, 0.0f),Vector3f::LEFT),
                PackedVertex(Vector3f(-1.0f, -1.0f, -1.0f), Vector2f(0.0f, 1.0f),Vector3f::LEFT),
                PackedVertex(Vector3f( 1.0f,  1.0f, -1.0f), Vector2f(1.0f, 1.0f),Vector3f::BACK),
                PackedVertex(Vector3f(-1.0f, -1.0f, -1.0f), Vector2f(0.0f, 0.0f),Vector3f::BACK),
                PackedVertex(Vector3f(-1.0f,  1.0f, -1.0f), Vector2f(0.0f, 1.0f),Vector3f::BACK),
                PackedVertex(Vector3f( 1.0f,  1.0f,  1.0f), Vector2f(1.0f, 1.0f),Vector3f::RIGHT),
                PackedVertex(Vector3f( 1.0f, -1.0f, -1.0f), Vector2f(0.0f, 0.0f),Vector3f::RIGHT),
                PackedVertex(Vector3f( 1.0f,  1.0f, -1.0f), Vector2f(0.0f, 1.0f),Vector3f::RIGHT),
                PackedVertex(Vector3f(-1.0f,  1.0f,  1.0f), Vector2f(1.0f, 1.0f),Vector3f::UP),
                PackedVertex(Vector3f( 1.0f,  1.0f, -1.0f), Vector2f(0.0f, 0.0f),Vector3f::UP),
                PackedVertex(Vector3f(-1.0f,  1.0f, -1.0f), Vector2f(0.0f, 1.0f),Vector3f::UP),
                PackedVertex(Vector3f(-1.0f,  1.0f,  1.0f), Vector2f(1.0f, 1.0f),Vector3f::FORWARD),
                PackedVertex(Vector3f(-1.0f, -1.0f,  1.0f), Vector2f(1.0f, 0.0f),Vector3f::FORWARD),
                PackedVertex(Vector3f( 1.0f, -1.0f,  1.0f), Vector2f(0.0f, 0.0f),Vector3f::FORWARD),
                PackedVertex(Vector3f( 1.0f, -1.0f,  1.0f), Vector2f(1.0f, 1.0f),Vector3f::DOWN),
                PackedVertex(Vector3f(-1.0f, -1.0f,  1.0f), Vector2f(1.0f, 0.0f),Vector3f::DOWN),
                PackedVertex(Vector3f(-1.0f, -1.0f, -1.0f), Vector2f(0.0f, 0.0f),Vector3f::DOWN),
                PackedVertex(Vector3f(-1.0f, -1.0f,  1.0f), Vector2f(1.0f, 1.0f),Vector3f::LEFT),
                PackedVertex(Vector3f(-1.0f,  1.0f,  1.0f), Vector2f(1.0f, 0.0f),Vector3f::LEFT),
                PackedVertex(Vector3f(-1.0f,  1.0f, -1.0f), Vector2f(0.0f, 0.0f),Vector3f::LEFT),
                PackedVertex(Vector3f( 1.0f,  1.0f, -1.0f), Vector2f(1.0f, 1.0f),Vector3f::BACK),
                PackedVertex(Vector3f( 1.0f, -1.0f, -1.0f), Vector2f(1.0f, 0.0f),Vector3f::BACK),
                PackedVertex(Vector3f(-1.0f, -1.0f, -1.0f), Vector2f(0.0f, 0.0f),Vector3f::BACK),
                PackedVertex(Vector3f( 1.0f,  1.0f,  1.0f), Vector2f(1.0f, 1.0f),Vector3f::RIGHT),
                PackedVertex(Vector3f( 1.0f, -1.0f,  1.0f), Vector2f(1.0f, 0.0f),Vector3f::RIGHT),
                PackedVertex(Vector3f( 1.0f, -1.0f, -1.0f), Vector2f(0.0f, 0.0f),Vector3f::RIGHT),
                PackedVertex(Vector3f(-1.0f,  1.0f,  1.0f), Vector2f(1.0f, 1.0f),Vector3f::UP),
                PackedVertex(Vector3f( 1.0f,  1.0f,  1.0f), Vector2f(1.0f, 0.0f),Vector3f::UP),
                PackedVertex(Vector3f( 1.0f,  1.0f, -1.0f), Vector2f(0.0f, 0.0f),Vector3f::UP),
            }};
        }

        inline void subdivide(RefMut<PackedVertexContainer> ret, Ref<Vector3f> a, Ref<Vector3f> b, Ref<Vector3f> c, i32 depth) {
            if (depth == 0) {
                ret.emplace_back(normalize(a));
                ret.emplace_back(normalize(b));
                ret.emplace_back(normalize(c));
                return;
            }

            auto ab = normalize(a + b);
            auto ac = normalize(a + c);
            auto bc = normalize(b + c);

            subdivide(ret, normalize(a), ab, ac, depth - 1);
            subdivide(ret, ab, normalize(b), bc, depth - 1);
            subdivide(ret, bc, normalize(c), ac, depth - 1);
            subdivide(ret, ab, bc, ac, depth - 1);
        }

        PackedVertexContainer sphere_vertices(u32 subdivisions) {

            PackedVertexContainer ret;

            i32 count = 0;

            std::vector<Vector3f> i_vertices = {
                    {-1, 1,  0},
                    {1,  1,  0},
                    {-1, -1, 0},
                    {1,  -1, 0},
                    {0,  -1, 1},
                    {0,  1,  1},
                    {0,  -1, -1},
                    {0,  1,  -1},
                    {1,  0,  -1},
                    {1,  0,  1},
                    {-1, 0,  -1},
                    {-1, 0,  1}
            };

            std::vector<i32> i_indices = {
                    0, 11, 5, 0, 5, 1, 0, 1, 7, 0,
                    7, 10, 0, 10, 11, 1, 5, 9, 5, 11,
                    4, 11, 10, 2, 10, 7, 6, 7, 1, 8,
                    3, 9, 4, 3, 4, 2, 3, 2, 6, 3,
                    6, 8, 3, 8, 9, 4, 9, 5, 2, 4,
                    11, 6, 2, 10, 8, 6, 7, 9, 8, 1
            };

            for (size_t i = 0; i < i_indices.size(); i += 3) {
                count += 1;

                auto v1 = i_vertices[i_indices[i]];
                auto v2 = i_vertices[i_indices[i + 1]];
                auto v3 = i_vertices[i_indices[i + 2]];

                subdivide(ret, v1, v2, v3, subdivisions);
            }

            return std::move(ret);
        }

    }
}

// orion