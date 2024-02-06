//
// Created by Alex on 01/02/2024.
//

#ifndef ORION_ENTITY_H
#define ORION_ENTITY_H

#include "orion/core/type.h"

namespace orion {

    class Entity {
    public:
        explicit Entity(u32 reserve);

        void set_alive(bool state);

        [[nodiscard]] u32  get_index  () const;
        [[nodiscard]] u32  get_version() const;
        [[nodiscard]] bool is_alive   () const;

        [[nodiscard]] Ref<DynBitset> get_signature() const;

        void on_component_register();

    private:
        u32  m_index;
        u32  m_version;
        bool m_alive;

        DynBitset m_signature;

        static u32 ENTITY_COUNT;
        static u32 get_next_index();

        friend class EntityManager;
    };

} // orion

#endif //ORION_ENTITY_H
