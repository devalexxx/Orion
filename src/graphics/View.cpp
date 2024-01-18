//
// Created by Alex on 15/12/2023.
//

#include "graphics/View.h"

namespace orion {

    orion::View::View() :
        View(Vector3f::zero(), Vector3f::zero(), Vector3f::one(), 45.f, 4.f / 3.f, 0.1f, 100.f)
    {}

    View::View(Vector3f position) :
            View(std::move(position), Vector3f::zero(), Vector3f::one(), 45.f, 4.f / 3.f, 0.1f, 100.f)
    {}

    View::View(Vector3f position, Vector3f rotation, Vector3f scale, f32 fov, f32 ratio, f32 near, f32 far) :
            m_position(std::move(position)),
            m_rotation(std::move(rotation)),
            m_scale   (std::move(scale)),
            m_fov     (fov),
            m_ratio   (ratio),
            m_near    (near),
            m_far     (far)
    {
        look_at(Vector3f::zero());
        update_projection();
    }

    void View::set_fov(const f32 fov) {
        m_fov = fov;
        update_projection();
    }

    void View::set_ratio(const f32 ratio) {
        m_ratio = ratio;
        update_projection();
    }

    void View::set_near(const f32 near) {
        m_near = near;
        update_projection();
    }

    void View::set_far(const f32 far) {
        m_far = far;
        update_projection();
    }

    Ref<Vector3f> View::get_position() const {
        return m_position;
    }

    Ref<Vector3f> View::get_rotation() const {
        return m_rotation;
    }

    Ref<Vector3f> View::get_scale() const {
        return m_scale;
    }

    Ref<Matrix4f> View::get_projection() const {
        return m_projection;
    }

    Ref<Matrix4f> View::get_view() const {
        return m_view;
    }

    void View::look_at(Ref<Vector3f> target) {
        m_view = ::orion::look_at(m_position, target, Vector3f::UP);
        m_rotation = euler_angle(m_view);
    }

    void View::translate(Ref<Vector3f> translation) {
        m_view = ::orion::translate(m_view, translation);
        m_position = m_position + translation;
    }

    void View::rotate(f32 angle, Ref<Vector3f> axis) {
        m_view = ::orion::rotate(m_view, angle, axis);
        m_rotation = euler_angle(m_view);
    }

    void View::rotate_around(f32 angle, Ref<Vector3f> target, Ref<Vector3f> axis) {

    }

    void View::update_projection() {
        m_projection = perspective(radian(m_fov), m_ratio, m_near, m_far);
    }

}
