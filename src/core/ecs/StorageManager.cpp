//
// Created by Alex on 01/02/2024.
//

#include "orion/core/ecs/StorageManager.h"

namespace orion {

    u32 StorageManager::size() const {
        return m_storages.size();
    }

    void StorageManager::on_entity_created() {
        for (auto& s: m_storages) {
            s->on_entity_created();
        }
    }

} // orion