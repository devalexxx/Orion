//
// Created by Alex on 03/02/2024.
//

#ifndef ORION_SYSTEM_H
#define ORION_SYSTEM_H

#include "orion/core/type.h"
#include "orion/core/ecs/QueryConstraint.h"

#include <functional>

namespace orion {

    class World;

    template<IncludeType IT, ExcludeType ET>
    class Query;

    class ISystem {
    public:
        template<class T>
        using BaseFunctorPtr = void(*)(T);
        template<class T>
        using BaseFunctor = std::function<void(T)>;

        virtual ~ISystem() = default;
        virtual void execute(RefMut<World> world) = 0;
    };

    class SystemDescriptor {
    public:
        explicit SystemDescriptor(std::unique_ptr<ISystem> system);

        RefMut<SystemDescriptor> set_name    (String name);
        RefMut<SystemDescriptor> set_before  (String before);
        RefMut<SystemDescriptor> set_after   (String after);
        RefMut<SystemDescriptor> set_priority(u32 priority);

    private:
        String m_name;
        String m_before;
        String m_after;
        u32    m_priority;

        std::unique_ptr<ISystem> m_system;

        friend class SystemManager;
        friend struct SystemSorter;
    };

    struct SystemSorter {
        // true swap
        bool operator()(Ref<SystemDescriptor> lhs, Ref<SystemDescriptor> rhs) {
            if (rhs.m_after == lhs.m_name || lhs.m_before == rhs.m_name)
                return true;

            return lhs.m_priority > rhs.m_priority;
        }
    };

    template<typename T>
    class System : public ISystem {};

    template<>
    class System<RefMut<World>> : public ISystem {
    public:
        using Functor = BaseFunctor<RefMut<World>>;
        explicit System(Functor&& fn);
        void execute(RefMut<World> world) override;
    private:
        Functor m_fn;
    };

    template<typename... Ts>
    class System<Query<Ts...>> : public ISystem {
    public:
        using Functor = BaseFunctor<Query<Ts...>>;
        explicit System(Functor&& fn);
        void execute(RefMut<World> world) override;
    private:
        Functor m_fn;
    };

    template<typename... Ts>
    System<Query<Ts...>>::System(Functor&& fn) : m_fn(fn) {}

    template<typename... Ts>
    void System<Query<Ts...>>::execute(RefMut<World> world) {
        m_fn(Query<Ts...>(world));
    }

} // orion

#endif //ORION_SYSTEM_H
