//
// Created by Alex on 01/02/2024.
//

#ifndef ORION_COMPONENTSTORAGE_H
#define ORION_COMPONENTSTORAGE_H

#include "orion/core/type.h"

#include "orion/core/ecs/Entity.h"

namespace orion {

    class IComponentStorage {
    public:
        virtual void on_entity_created() = 0;
    };

    template<typename T>
    class ComponentStorage : public IComponentStorage {
    public:
        explicit ComponentStorage(u32 reserve);

        template<typename C = T, typename... Args>
        void assign(Ref<Entity> entity, Args... args);

        RefMut<T> get_component(Ref<Entity> entity);

        void on_entity_created() override;

    private:
        std::vector<T> m_components;
    };

    template<typename T>
    RefMut<T> ComponentStorage<T>::get_component(Ref<Entity> entity) {
        return m_components[entity.get_index()];
    }

    template<typename T>
    ComponentStorage<T>::ComponentStorage(u32 reserve) : m_components(std::vector<T>(reserve)) {}

    template<typename T>
    template<typename C, typename... Args>
    void ComponentStorage<T>::assign(Ref<Entity> entity, Args... args) {
        m_components[entity.get_index()] = T{std::forward<Args>(args)...};
    }

    template<typename T>
    void ComponentStorage<T>::on_entity_created() {
        m_components.resize(m_components.size() + 1);
    }

} // orion

#endif //ORION_COMPONENTSTORAGE_H
