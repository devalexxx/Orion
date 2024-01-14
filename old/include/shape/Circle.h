//
// Created by Alex on 12/01/2024.
//

#ifndef ORION_CIRCLE_H
#define ORION_CIRCLE_H

#include "OldShape.h"

namespace orion {

    class Circle : public OldShape {
    public:
        Circle();
        explicit Circle(Ref<Vector3f> position);

        void draw(const RenderTarget &target, const RenderContext &context) const override;

    private:
        static std::vector<PackedVertex> default_shape;
    };

} // orion

#endif //ORION_CIRCLE_H
