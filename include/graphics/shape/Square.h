//
// Created by Alex on 29/12/2023.
//

#ifndef ORION_SQUARE_H
#define ORION_SQUARE_H

#include "Shape.h"
#include "graphics/Transform.h"

namespace orion {

    class Square : public Shape {
    public:
        Square();
        explicit Square(Ref<Vector3f> position);

        void draw(const RenderTarget &target, const RenderContext &context) const override;

    private:
        static std::shared_ptr<VertexArray> default_vao;
        static std::vector<PackedVertex>    default_shape;
    };

} // orion

#endif //ORION_SQUARE_H
