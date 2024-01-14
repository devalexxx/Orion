//
// Created by Alex on 13/01/2024.
//

#ifndef ORION_SPHERE_H
#define ORION_SPHERE_H

#include "OldShape.h"

namespace orion {

    class Sphere : public OldShape {
    public:
        Sphere();
        explicit Sphere(Ref<Vector3f> position);

        void draw(const RenderTarget &target, const RenderContext &context) const override;

    private:
        static std::vector<PackedVertex> default_shape;
    };

} // orion

#endif //ORION_SPHERE_H
