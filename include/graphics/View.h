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
        View(Ref<Vector3f> position, Ref<Vector3f> rotation, Ref<Vector3f> scale, f32 fov, f32 ratio, f32 near, f32 far);

        void set_fov  (f32 fov);
        void set_ratio(f32 ratio);
        void set_near (f32 near);
        void set_far  (f32 far);

        [[nodiscard]] Ref<Vector3f> get_position() const;
        [[nodiscard]] Ref<Vector3f> get_rotation() const;
        [[nodiscard]] Ref<Vector3f> get_scale   () const;

        [[nodiscard]] Ref<Matrix4f> get_projection() const;
        [[nodiscard]] Ref<Matrix4f> get_view      () const;

        void look_at      (Ref<Vector3f> target);
        void translate    (Ref<Vector3f> translation);
        void rotate       (f32 angle, Ref<Vector3f> axis);
        void rotate_around(f32 angle, Ref<Vector3f> target, Ref<Vector3f> axis);

    private:
        Vector3f m_position;
        Vector3f m_rotation;
        Vector3f m_scale;

        Matrix4f m_view;
        Matrix4f m_projection;

        f32 m_fov;
        f32 m_ratio;
        f32 m_near;
        f32 m_far;

        void update_projection();
    };

}


#endif //ORION_VIEW_H
