//
// Created by Alex on 01/02/2024.
//

#include "orion/core/ecs/SystemManager.h"

namespace orion {

    SystemManager::SystemManager(RefMut<World> world) : m_world(world) {}

    void SystemManager::update() {
        std::sort(m_systems.begin(), m_systems.end(), SystemSorter{});
        for (auto& s: m_systems) {
            s.m_system->execute(m_world);
        }
    }

} // orion