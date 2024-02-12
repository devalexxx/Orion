//
// Created by Alex on 01/02/2024.
//

#ifndef ORION_SYSTEMMANAGER_H
#define ORION_SYSTEMMANAGER_H

#include "orion/core/type.h"
#include "orion/core/ecs/System.h"
#include "orion/core/ecs/QueryConstraint.h"

#include <functional>
#include <algorithm>

namespace orion {

    class World;

    class SystemManager {
    public:

        explicit SystemManager(RefMut<World> world);

        void update();

        template<typename T>
        RefMut<SystemDescriptor> emplace_system(typename ISystem::Functor<T>&& system);

        template<DerivedSystem T, typename... Args>
        RefMut<SystemDescriptor> emplace_system(Args... args);

    private:
        std::vector<SystemDescriptor> m_systems;

        RefMut<World> m_world;
    };

    template<typename T>
    RefMut<SystemDescriptor> SystemManager::emplace_system(typename ISystem::Functor<T>&& system) {
        return m_systems.emplace_back(std::make_unique<System<T>>(std::move(system)));
    }

    template<DerivedSystem T, typename... Args>
    RefMut<SystemDescriptor> SystemManager::emplace_system(Args... args) {
        return m_systems.emplace_back(std::make_unique<T>(args...));
    }

} // orion

#endif //ORION_SYSTEMMANAGER_H
