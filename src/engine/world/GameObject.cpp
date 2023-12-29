//
// Created by Alex on 07/11/2023.
//

#include <iostream>

#include "engine/world/GameObject.h"
#include "engine/world/Transform.h"

namespace orion {

    std::shared_ptr<GameObject> GameObject::create(const std::string &name) {
        auto p = std::shared_ptr<GameObject>(new GameObject());
        p->m_name = name;
        p->m_parent = nullptr;
        return std::move(p);
    }

    void GameObject::start() {
//        addComponent<Transform>(glm::vec3(0.f), glm::quat(1.f, 0.f, 0.f, 0.f), glm::vec3(1.f));

        for (size_t i = 0; i < m_component_count; ++i) {
            m_components.at(i)->start();
        }
    }

    void GameObject::update(float dt) {
        for (size_t i = 0; i < m_component_count; ++i) {
            m_components.at(i)->update(dt);
        }
    }

    const std::string& GameObject::getName() const {
        return m_name;
    }

    void GameObject::setName(const std::string &name) {
        m_name = name;
    }

    void GameObject::removeComponent(const std::string& name) {
        auto it = m_components_indexer.find(name);
        if (it != m_components_indexer.cend()) {
            auto last_it = m_components_indexer_rev.find(m_component_count - 1);

            m_components_indexer[last_it->second] = it->second;
            m_components_indexer_rev[it->second] = last_it->second;
            m_components[it->second].reset();
            m_components[it->second] = std::move(m_components[last_it->first]);

            m_components_indexer.erase(it->first);
            m_components_indexer_rev.erase(last_it->first);
        }
    }

    GameObject* GameObject::getParent() const {
        if (m_parent != nullptr)
            return m_parent.get();
        else
            return nullptr;
    }

    void GameObject::appendChild(const std::string& name) {
        if (m_child_count < MAX_GAMEOBJECT_CHILDS) {
            m_childs[m_child_count] = create(name);
            m_childs[m_child_count]->m_parent = shared_from_this();
            m_child_count++;
        }
    }

    GameObject *GameObject::getChild(size_t index) const {
        if (index < m_child_count)
            return m_childs[index].get();
        else
            return nullptr;
    }

    void GameObject::removeChild(size_t index) {
        if (index < m_child_count) {
            m_childs[index].reset();
            m_child_count--;
            if(index < m_child_count) {
                m_childs[index] = std::move(m_childs[m_child_count]);
            }
        }
    }
}
