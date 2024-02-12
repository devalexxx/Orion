//
// Created by Alex on 03/02/2024.
//

#include <cassert>
#include "orion/core/ecs/System.h"

namespace orion {

    SystemDescriptor::SystemDescriptor(std::unique_ptr<ISystem> system) :
        m_priority(0),
        m_system(std::move(system))
    {}

    RefMut<SystemDescriptor> SystemDescriptor::set_name(String name) {
        assert(name != m_before && name != m_after);
        m_name = std::move(name);
        return *this;
    }

    RefMut<SystemDescriptor> SystemDescriptor::set_before(String before) {
        assert(before != m_after && before != m_name);
        m_before = std::move(before);
        return *this;
    }

    RefMut<SystemDescriptor> SystemDescriptor::set_after(orion::String after) {
        assert(after != m_before && after != m_name);
        m_after = std::move(after);
        return *this;
    }

    RefMut<SystemDescriptor> SystemDescriptor::set_priority(orion::u32 priority) {
        m_priority = priority;
        return *this;
    }

    System<RefMut<World>>::System(Functor<value_type> &&fn) : m_fn(fn) {}

    void System<RefMut<World>>::execute(RefMut<World> world) {
        m_fn(world);
    }
} // orion