//
// Created by Alex on 01/02/2024.
//

#include "orion/core/ecs/Entity.h"

namespace orion {

    Entity::Entity(u32 reserve) :
        m_index    (get_next_index()),
        m_version  (0),
        m_signature(DynBitset(reserve, false)),
        m_alive    (true)
    {}

    void Entity::set_alive(bool state) {
        if (!m_alive && state) {
            m_signature.clear();
            m_version += 1;
        }
        m_alive = state;
    }

    u32 Entity::get_index() const {
        return m_index;
    }

    u32 Entity::get_version() const {
        return m_version;
    }

    bool Entity::is_alive() const {
        return m_alive;
    }

    Ref<DynBitset> Entity::get_signature() const {
        return m_signature;
    }

    void Entity::on_component_register() {
        m_signature.push_back(false);
    }

    u32 Entity::ENTITY_COUNT = 0;

    u32 Entity::get_next_index() {
        return ENTITY_COUNT++;
    }

} // orion