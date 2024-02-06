//
// Created by Alex on 01/02/2024.
//

#ifndef ORION_ENTITYMANAGER_H
#define ORION_ENTITYMANAGER_H

#include "orion/core/ecs/Entity.h"
#include "orion/core/ecs/Component.h"
#include <queue>

namespace orion {

    class EntityManager {
    public:
        [[nodiscard]] u32 size() const;

        Ref<Entity> emplace(u32 reserve);

        void update_signature(Ref<Entity> entity, u32 index, bool state);

        void on_component_register();

        [[nodiscard]] Ref<std::vector<Entity>> iter() const;

        void kill_entity(Ref<Entity> entity);

    private:
        std::vector<Entity> m_entities;
        std::queue<u32>     m_free_entities;
    };

} // orion

#endif //ORION_ENTITYMANAGER_H
