//
// Created by Alex on 01/02/2024.
//

#ifndef ORION_WORLD_H
#define ORION_WORLD_H

#include "orion/core/ecs/EntityManager.h"
#include "orion/core/ecs/StorageManager.h"
#include "orion/core/ecs/SystemManager.h"
#include "orion/core/ecs/QueryConstraint.h"

namespace orion {

    template<IncludeType IT, ExcludeType ET>
    class Query;

    class World {
    public:
        World();

        void update();

        Ref<Entity> create_entity();

        template<typename T, typename... Args>
        void emplace_component(Ref<Entity> entity, Args... args);

        template<typename T>
        void remove_component (Ref<Entity> entity);

        template<typename T>
        RefMut<SystemDescriptor> emplace_system(ISystem::BaseFunctorPtr<T> system);

//        template<typename T>
//        RefMut<SystemDescriptor> emplace_system(ISystem::BaseFunctor<T>&& system);

        template<typename I>
        Query<I, Exclude<>> query();

        template<typename I, typename E>
        Query<I, E> query();

        void kill_entity(Ref<Entity> entity);

        [[nodiscard]] Ref<std::vector<Entity>> entities() const;

    private:
        EntityManager  m_em;
        StorageManager m_sm;
        SystemManager  m_sym;

        template<IncludeType IT, ExcludeType ET>
        friend class Query;
    };

    template<typename T, typename... Args>
    void World::emplace_component(Ref<Entity> entity, Args... args) {
        if (!m_sm.has_container<T>()) {
            m_sm.add_container<T>(m_em.size());
            m_em.on_component_register();
        }

        m_sm.assign<T>(entity, std::forward<Args>(args)...);
        m_em.update_signature(entity, m_sm.get_container_index<T>(), true);
    }

    template<typename T>
    void World::remove_component(Ref<Entity> entity) {
        if (m_sm.has_container<T>())
            m_em.update_signature(entity, m_sm.get_container_index<T>(), false);
    }

    template<typename T>
    RefMut<SystemDescriptor> World::emplace_system(ISystem::BaseFunctorPtr<T> system) {
        return m_sym.emplace_system<T>(system);
    }

//    template<typename T>
//    RefMut<SystemDescriptor> World::emplace_system(ISystem::BaseFunctor<T> &&system) {
//        return m_sym.emplace_system<T>(system);
//    }

    template<typename I>
    Query<I, Exclude<>> World::query() {
        return Query<I, Exclude<>>(*this);
    }

    template<typename I, typename E>
    Query<I, E> World::query() {
        return Query<I, E>(*this);
    }

} // orion

#endif //ORION_WORLD_H
