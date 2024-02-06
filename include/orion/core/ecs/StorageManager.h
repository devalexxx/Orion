//
// Created by Alex on 01/02/2024.
//

#ifndef ORION_STORAGEMANAGER_H
#define ORION_STORAGEMANAGER_H

#include "orion/core/ecs/Component.h"
#include "orion/core/ecs/ComponentStorage.h"

#include "cassert"

namespace orion {

    class Entity;

    class StorageManager {
    public:
        [[nodiscard]] u32 size() const;

        template<typename T>
        [[nodiscard]] bool has_container() const;

        template<typename T>
        void add_container(u32 reserve);

        template<typename T>
        [[nodiscard]] u32 get_container_index() const;

        template<typename T, typename... Args>
        void assign(Ref<Entity> entity, Args... args);

        template<typename T>
        RefMut<T> get_component(Ref<Entity> entity);

        void on_entity_created();

    private:
        std::vector<std::shared_ptr<IComponentStorage>> m_storages;
        std::vector<u32>                                m_indexer;
    };

    template<typename T>
    bool StorageManager::has_container() const {
        return std::find(m_indexer.begin(), m_indexer.end(), Component<T>::type_info().id) != m_indexer.cend();
    }

    template<typename T>
    u32 StorageManager::get_container_index() const {
        assert(has_container<T>() && "You can't query unregister component.");
        return std::distance(
                m_indexer.cbegin(),
                std::find(m_indexer.begin(), m_indexer.end(), Component<T>::type_info().id)
        );
    }

    template<typename T>
    void StorageManager::add_container(u32 reserve) {
        m_storages.push_back(std::make_unique<ComponentStorage<T>>(reserve));
        m_indexer.push_back(Component<T>::type_info().id);
    }

    template<typename T, typename... Args>
    void StorageManager::assign(Ref<Entity> entity, Args... args) {
        auto casted = std::static_pointer_cast<ComponentStorage<T>>(m_storages[get_container_index<T>()]);

        assert(casted != nullptr);

        casted->assign(entity, std::forward<Args>(args)...);
    }

    template<typename T>
    RefMut<T> StorageManager::get_component(Ref<Entity> entity) {
        auto casted = std::static_pointer_cast<ComponentStorage<T>>(m_storages[get_container_index<T>()]);
        return casted->get_component(entity);
    }

} // orion

#endif //ORION_STORAGEMANAGER_H
