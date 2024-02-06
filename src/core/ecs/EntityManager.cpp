//
// Created by Alex on 01/02/2024.
//

#include "orion/core/ecs/EntityManager.h"

namespace orion {

    u32 EntityManager::size() const {
        return m_entities.size();
    }

    Ref<Entity> EntityManager::emplace(u32 reserve) {
        if (m_free_entities.empty())
            return m_entities.emplace_back(reserve);
        else {
            auto index = m_free_entities.front();
            m_free_entities.pop();
            m_entities[index].set_alive(true);
            return m_entities[index];
        }
    }

    void EntityManager::update_signature(Ref<Entity> entity, u32 index, bool state) {
        m_entities[entity.m_index].m_signature[index] = state;
    }

    void EntityManager::on_component_register() {
        for (auto& e: m_entities) {
            e.on_component_register();
        }
    }

    Ref<std::vector<Entity>> EntityManager::iter() const {
        return m_entities;
    }

    void EntityManager::kill_entity(Ref<Entity> entity) {
        m_entities[entity.m_index].set_alive(false);
        m_free_entities.push(entity.m_index);
    }

} // orion