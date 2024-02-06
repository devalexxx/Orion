//
// Created by Alex on 01/02/2024.
//

#ifndef ORION_COMPONENT_H
#define ORION_COMPONENT_H

#include "orion/core/type.h"

namespace orion {

    class BaseComponent {
    protected:
        static u32 get_next_type();
    private:
        static u32 TYPE_COUNT;
    };

    struct ComponentType {
        u32    id;
        String name;
    };

    template<typename T>
    class Component : public BaseComponent {
    public:
        static Ref<ComponentType> type_info();
    };

    template<typename T>
    Ref<ComponentType> Component<T>::type_info() {
        static ComponentType type_info = {
                BaseComponent::get_next_type(),
                typeid(T).name()
        };
        return type_info;
    }

} // orion

#endif //ORION_COMPONENT_H
