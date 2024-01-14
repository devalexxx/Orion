//
// Created by Alex on 23/12/2023.
//

#ifndef ORION_TRIANGLE_H
#define ORION_TRIANGLE_H

#include "OldShape.h"
#include "graphics/Transform.h"

namespace orion {

    class VertexArray;

    class Triangle : public OldShape {
    public:
        Triangle();
        explicit Triangle(Ref<Vector3f> position);

        void draw(const RenderTarget &target, const RenderContext &context) const override;

    private:
        static std::vector<PackedVertex> default_shape;
    };

} // orion

#endif //ORION_TRIANGLE_H
