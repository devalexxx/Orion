//
// Created by Alex on 15/12/2023.
//

#ifndef ORION_VIEW_H
#define ORION_VIEW_H

#include "omath.h"

namespace orion {

    class View {
    public:
        View();
        explicit View(Ref<Vector3f> position);
        View(Ref<Vector3f> position, Ref<Vector3f> rotation, Ref<Vector3f> scale, float fov, float ratio, float near, float far);

        void set_fov    (float fov);
        void set_ratio  (float ratio);
        void set_near   (float near);
        void set_far    (float far);

        [[nodiscard]] Ref<Vector3f> get_position() const;
        [[nodiscard]] Ref<Vector3f> get_rotation() const;
        [[nodiscard]] Ref<Vector3f> get_scale   () const;

        [[nodiscard]] Ref<Matrix4f> get_projection() const;
        [[nodiscard]] Ref<Matrix4f> get_view      () const;

        void set_position(Ref<Vector3f> position);

        void look_at      (Ref<Vector3f> target);
        void rotate       (float angle, Ref<Vector3f> axis);
        void rotate_around(float angle, Ref<Vector3f> target, Ref<Vector3f> axis);

        void update_view();

    private:
        Vector3f m_position;
        Vector3f m_rotation;
        Vector3f m_scale;

        Matrix4f m_view;
        Matrix4f m_projection;

        float m_fov;
        float m_ratio;
        float m_near;
        float m_far;

        void update_projection();
    };

}


#endif //ORION_VIEW_H
