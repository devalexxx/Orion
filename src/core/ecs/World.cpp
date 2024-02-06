//
// Created by Alex on 01/02/2024.
//

#include "orion/core/ecs/World.h"

namespace orion {

    World::World() : m_sym(*this) {}

    Ref<Entity> World::create_entity() {
        return m_em.emplace(m_sm.size());
    }

    void World::update() {
        m_sym.update();
    }

    void World::kill_entity(Ref<Entity> entity) {
        m_em.kill_entity(entity);
    }

    Ref<std::vector<Entity>> World::entities() const {
        return m_em.iter();
    }

} // orion