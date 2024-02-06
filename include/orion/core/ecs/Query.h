//
// Created by Alex on 02/02/2024.
//

#ifndef ORION_QUERY_H
#define ORION_QUERY_H

#include "orion/core/ecs/QueryConstraint.h"
#include "orion/core/ecs/World.h"

#include <fmt/core.h>
#include <algorithm>

namespace orion {

    template<IncludeType IT, ExcludeType ET = Exclude<>>
    class Query {
    public:
        using storage_type = std::vector<Pair<Ref<Entity>, typename IT::filtered_value_type>>;

        explicit Query(RefMut<World> world);

        RefMut<storage_type> iter();

    private:
        storage_type  m_storage;
        RefMut<World> m_world;
    };

    template<IncludeType IT, ExcludeType ET>
    Query<IT, ET>::Query(RefMut<World> world) : m_world(world) {

        std::array<u32, IT::size()> include;
        IT().foreach([&, this](const auto& elem, size_t i) {
            using type = std::decay_t<decltype(elem)>;

            if constexpr (is_marker<typename type::value_type>::value) {
                include[i] = m_world.m_sm.get_container_index<typename type::value_type::value_type>();
            }
            else {
                include[i] = m_world.m_sm.get_container_index<typename type::value_type>();
            }
        });

        std::array<u32, ET::size()> exclude;
        ET().foreach([&, this](const auto& elem, size_t i) {
            using type = std::decay_t<decltype(elem)>;

            exclude[i] = m_world.m_sm.get_container_index<typename type::value_type>();
        });

        for (auto id: include) {
            ORION_ASSERT(std::find(exclude.begin(), exclude.end(), id) == exclude.end(), "You can't have component in both include and exclude ({}).", id);
        }

        for (const auto& entity: m_world.m_em.iter()) {

            if (std::ranges::all_of(exclude.begin(), exclude.end(), [&](u32 comp) {return !entity.get_signature()[comp];})) {

                if (std::ranges::all_of(include.begin(), include.end(), [&](u32 comp) {return entity.get_signature()[comp];})) {

                    using tuple_type_info = typename IT::filtered_types_info;

                    auto parse_and_emplace = [&]<typename Tuple, size_t... Ints>(std::index_sequence<Ints...>) {

                        m_storage.emplace_back(
                                entity,
                                typename IT::filtered_value_type(m_world.m_sm.get_component<typename std::tuple_element_t<Ints, Tuple>::value_type>(entity)...)
                        );
                    };

                    parse_and_emplace.template operator()<tuple_type_info>(std::make_index_sequence<std::tuple_size_v<tuple_type_info>>());
                }
            }
        }
    }

    template<IncludeType IT, ExcludeType ET>
    RefMut<typename Query<IT, ET>::storage_type> Query<IT, ET>::iter() {
        return m_storage;
    }

} // orion

#endif //ORION_QUERY_H
