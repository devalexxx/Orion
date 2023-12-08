//
// Created by Alex on 07/11/2023.
//

#ifndef ORION_GAMEOBJECT_H
#define ORION_GAMEOBJECT_H

#define MAX_COMPONENTS 16
#define MAX_GAMEOBJECT_CHILDS 16

#include <string>
#include <optional>
#include <type_traits>
#include <array>
#include <unordered_map>

#include "AbstractComponent.h"

namespace orion {

    class GameObject : public std::enable_shared_from_this<GameObject> {
    public:

        /**
         *
         * @param name
         * @return
         */
        static std::shared_ptr<GameObject> create(const std::string& name);


        /**
         *
         */
        void start();


        /**
         *
         * @param dt
         */
        void update(float dt);


        /**
         *
         * @return
         */
        [[nodiscard]] const std::string& getName() const;


        /**
         *
         * @param name
         */
        void setName(const std::string& name);

        /**
         * @brief Return the component if present in GameObject.
         * @note Always use it as std::weak_ptr to avoid memory leak.
         * @tparam T Component type
         * @return The requested component or null_ptr if not exist
         */
        template<typename T, typename std::enable_if_t<std::is_base_of<AbstractComponent, T>::value, bool> = true>
        std::shared_ptr<T> getComponent() const;


        /**
         *
         * @tparam T
         * @tparam Args
         * @param args
         */
        template<typename T, typename ...Args, typename std::enable_if_t<std::is_base_of<AbstractComponent, T>::value, bool> = true>
        void addComponent(Args&& ...args);


        /**
         *
         * @param name
         */
        void removeComponent(const std::string& name);


        /**
         *
         * @return
         */
        GameObject* getParent() const;


        /**
         *
         * @param name
         */
        void appendChild(const std::string& name);


        /**
         *
         * @param index
         * @return
         */
        GameObject* getChild(size_t index) const;


        /**
         *
         * @param index
         */
        void removeChild(size_t index);

    private:
        GameObject() = default;

        std::string m_name;

        std::shared_ptr<GameObject> m_parent;

        std::array<std::shared_ptr<GameObject>, MAX_GAMEOBJECT_CHILDS> m_childs;
        size_t m_child_count {0};

        std::array<std::shared_ptr<AbstractComponent>, MAX_COMPONENTS> m_components;
        size_t m_component_count {0};

        std::unordered_map<std::string, size_t> m_components_indexer {};
        std::unordered_map<size_t, std::string> m_components_indexer_rev {};
    };




    template<typename T, typename std::enable_if_t<std::is_base_of<AbstractComponent, T>::value, bool>>
    std::shared_ptr<T> GameObject::getComponent() const {
        auto it = m_components_indexer.find(typeid(T).name());
        if (it != m_components_indexer.cend())
            return std::static_pointer_cast<T>(m_components[it->second]);
        else
            return nullptr;
    }

    template<typename T, typename ...Args, typename std::enable_if_t<std::is_base_of<AbstractComponent, T>::value, bool>>
    void GameObject::addComponent(Args&& ...args) {
        if (m_component_count < MAX_COMPONENTS) {
            std::string name = typeid(T).name();
            auto it = m_components_indexer.find(name);

            if (it == m_components_indexer.cend()) {
                m_components_indexer.emplace(name, m_component_count);
                m_components_indexer_rev.emplace(m_component_count, name);

                m_components[m_component_count] = std::make_shared<T>(std::forward<Args>(args)...);
                m_components[m_component_count]->gameObject = shared_from_this();
                m_component_count += 1;
            }
        }
    }
}


#endif //ORION_GAMEOBJECT_H
