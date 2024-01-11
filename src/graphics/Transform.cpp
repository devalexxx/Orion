//
// Created by Alex on 24/12/2023.
//

#include "graphics/Transform.h"
#include "omath.h"

namespace orion {

    Transform::Transform() : m_scale(Vector3f(1)) {}

    orion::Transform::Transform(Ref<Vector3f> position, Ref<Vector3f> rotation, Ref<Vector3f> scale) :
        m_position(position),
        m_rotation(rotation),
        m_scale(scale)
    {}

    void Transform::set_position(Ref<Vector3f> position) {
        m_position = position;
    }

    void Transform::set_rotation(Ref<Vector3f> rotation) {
        m_rotation = rotation;
    }

    void Transform::set_scale(Ref<Vector3f> scale) {
        m_scale = scale;
    }

    Matrix4f Transform::get_matrix() const {
        auto translation = translate(Matrix4f::identity(), m_position);

        auto r_x = ::orion::rotate(m_rotation.get_x(), Vector3f::RIGHT);
        auto r_y = ::orion::rotate(m_rotation.get_y(), Vector3f::UP);
        auto r_z = ::orion::rotate(m_rotation.get_z(), Vector3f::FORWARD);
        auto rotation = r_x * r_y * r_z;

        auto rot = Matrix4f::identity();
        rot[0] = rotation[2];
        rot[1] = rotation[0];
        rot[2] = rotation[1];

        auto scale = orion::scale(Matrix4f::identity(), m_scale);

        return translation * rotation * scale;
    }

    Ref<Vector3f> Transform::get_position() const {
        return m_position;
    }

    Ref<Vector3f> Transform::get_rotation() const {
        return m_rotation;
    }

    Ref<Vector3f> Transform::get_scale() const {
        return m_scale;
    }

} // orion