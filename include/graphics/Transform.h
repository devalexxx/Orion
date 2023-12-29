//
// Created by Alex on 24/12/2023.
//

#ifndef ORION_TRANSFORM_H
#define ORION_TRANSFORM_H

#include "math/Vector3.h"
#include "math/Matrix4.h"
#include "core/type.h"

namespace orion {


    class Transform {
    public:
        Transform();
        Transform(Ref<Vector3f> position, Ref<Vector3f> rotation, Ref<Vector3f> scale);

        void set_position(Ref<Vector3f> position);
        void set_rotation(Ref<Vector3f> rotation);
        void set_scale   (Ref<Vector3f> scale);

        [[nodiscard]] Matrix4f get_matrix() const;
    private:
        Vector3f m_position {};
        Vector3f m_rotation {};
        Vector3f m_scale;
    };

} // orion

#endif //ORION_TRANSFORM_H
