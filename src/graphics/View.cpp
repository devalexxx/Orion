//
// Created by Alex on 15/12/2023.
//

#include "graphics/View.h"

#include "iostream"

namespace orion {

    View::View(Ref<Vector3f> position, Ref<Vector3f> rotation, Ref<Vector3f> scale, float fov, float ratio, float near, float far) :
            m_position(position),
            m_rotation(rotation),
            m_scale(scale),
            m_fov(fov),
            m_ratio(ratio),
            m_near(near),
            m_far(far)
    {
        look_at(Vector3f::zero());
        update_projection();
    }

    orion::View::View() :
        View(Vector3f::zero(), Vector3f::zero(), Vector3f::one(), 45.f, 4.f / 3.f, 0.1f, 100.f)
    {}

    View::View(Ref<Vector3f> position) :
        View(position, Vector3f::zero(), Vector3f::one(), 45.f, 4.f / 3.f, 0.1f, 100.f)
    {}

    void View::set_fov(const float fov) {
        m_fov = fov;
        update_projection();
    }

    void View::set_ratio(const float ratio) {
        m_ratio = ratio;
        update_projection();
    }

    void View::set_near(const float near) {
        m_near = near;
        update_projection();
    }

    void View::set_far(const float far) {
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

    void View::set_position(Ref<Vector3f> position) {
        m_position = position;
    }

    void View::look_at(Ref<Vector3f> target) {
        m_view = ::orion::look_at(m_position, target, Vector3f::UP);
        m_rotation = euler_angle(m_view);
    }

    void View::rotate(float angle, Ref<Vector3f> axis) {
        m_view = ::orion::rotate(m_view, angle, axis);
        m_rotation = euler_angle(m_view);
    }

    void View::rotate_around(float angle, Ref<Vector3f> target, Ref<Vector3f> axis) {

    }

    void View::update_projection() {
        m_projection = perspective(rad(m_fov), m_ratio, m_near, m_far);
    }

    void View::update_view() {
        auto translation = translate(Matrix4f::identity(), -m_position);

        auto r_x = ::orion::rotate(m_rotation.get_x(), Vector3f::RIGHT);
        auto r_y = ::orion::rotate(m_rotation.get_y(), Vector3f::UP);
        auto r_z = ::orion::rotate(m_rotation.get_z(), Vector3f::FORWARD);
        auto rotation = r_x * r_y * r_z;

        auto rot = Matrix4f::identity();
        rot[0] = rotation[2];
        rot[1] = rotation[0];
        rot[2] = rotation[1];

        m_view = translation * rot;
    }

}
