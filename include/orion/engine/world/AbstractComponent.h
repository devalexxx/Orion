//
// Created by Alex on 07/11/2023.
//

#ifndef ORION_ABSTRACTCOMPONENT_H
#define ORION_ABSTRACTCOMPONENT_H

#include <memory>
#include <iostream>

namespace orion {
    class GameObject;

    class AbstractComponent {
    public:
        virtual ~AbstractComponent() = default;
        virtual void start() = 0;
        virtual void update(float dt) = 0;
    protected:
        std::weak_ptr<GameObject> gameObject;
    private:
        friend class GameObject;
    };
}


#endif //ORION_ABSTRACTCOMPONENT_H
