//
// Created by Alex on 24/12/2023.
//

#ifndef ORION_TRANSFORM_H
#define ORION_TRANSFORM_H

#include "orion/math/Vector3.h"
#include "orion/math/Matrix4.h"
#include "orion/core/type.h"

namespace orion {


    class Transform {
    public:
        Transform();
        Transform(Vector3f position, Vector3f rotation, Vector3f scale);

        void set_position(Vector3f position);
        void set_rotation(Vector3f rotation);
        void set_scale   (Vector3f scale);

        [[nodiscard]] Ref<Vector3f> get_position() const;
        [[nodiscard]] Ref<Vector3f> get_rotation() const;
        [[nodiscard]] Ref<Vector3f> get_scale   () const;

        [[nodiscard]] Matrix4f get_matrix() const;
    private:
        Vector3f m_position {};
        Vector3f m_rotation {};
        Vector3f m_scale;
    };

} // orion

#endif //ORION_TRANSFORM_H
