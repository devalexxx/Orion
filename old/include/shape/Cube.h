//
// Created by Alex on 05/01/2024.
//

#ifndef ORION_CUBE_H
#define ORION_CUBE_H

#include "OldShape.h"

namespace orion {

    class Cube : public OldShape {
    public:
        Cube();
        explicit Cube(Ref<Vector3f> position);

        void draw(const RenderTarget &target, const RenderContext &context) const override;

    private:
        static std::vector<PackedVertex> default_shape;
    };

} // orion

#endif //ORION_CUBE_H
