//
// Created by Alex on 26/12/2023.
//

#ifndef ORION_DEFERREDREGISTRY_H
#define ORION_DEFERREDREGISTRY_H

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include <iostream>
#include <functional>

#include "type.h"
#include "Indexer.h"

namespace orion {

    template<typename T>
    class DeferredRegistry {
    public:
        using Initializer = std::function<void(RefMut<DeferredRegistry<T>>)>;

        DeferredRegistry();
        explicit DeferredRegistry(Initializer&& initializer);

        void load();

        void add(Ref<std::string> name, std::shared_ptr<T> ptr);

        std::shared_ptr<T> remove(const std::string& name);
        std::shared_ptr<T> get   (const std::string& name) const;

        [[nodiscard]] bool is_loaded() const;
    private:
        std::vector<std::shared_ptr<T>> m_storage {};
        Indexer<std::string, u32>       m_indexer {};
        Initializer                     m_initializer {};

        bool m_is_loaded;
    };

    template<typename T>
    DeferredRegistry<T>::DeferredRegistry(DeferredRegistry::Initializer &&initializer) : m_initializer(initializer), m_is_loaded(false) {}

    template<typename T>
    DeferredRegistry<T>::DeferredRegistry() : m_is_loaded(false) {}

    template<typename T>
    void DeferredRegistry<T>::load() {
        m_is_loaded = true;
        if (m_initializer)
            m_initializer(*this);
    }

    template<typename T>
    void DeferredRegistry<T>::add(Ref<std::string> name, std::shared_ptr<T> ptr) {
        if (!m_indexer.exist(name)) {
            m_storage.push_back(std::move(ptr));
            m_indexer.emplace(name, m_storage.size() - 1);
        }
        else
            std::cerr << "Could not add object " << name << " to register because this name is already register\n";
    }

    template<typename T>
    std::shared_ptr<T> DeferredRegistry<T>::remove(const std::string &name) {
        auto opt = m_indexer.get_by_key(name);
        if (opt != std::nullopt) {
            auto ret = m_storage[opt->second];
            m_storage[opt->second] = m_storage[m_storage.size() - 1];

            auto moved = m_indexer.get_by_value(m_storage.size() - 1);
            m_indexer.set(moved->first, opt->second);
            m_indexer.remove(opt->first);

            m_storage.pop_back();
            return ret;
        }
        else {
            std::cerr << "Object " << name << " does not exist in this registry\n";
            return nullptr;
        }
    }

    template<typename T>
    std::shared_ptr<T> DeferredRegistry<T>::get(const std::string &name) const {
        auto opt = m_indexer.get_by_key(name);
        if (opt != std::nullopt)
            return m_storage[opt->second];
        else {
            std::cerr << "Object " << name << " does not exist in this registry\n";
            return nullptr;
        }
    }

    template<typename T>
    bool DeferredRegistry<T>::is_loaded() const {
        return m_is_loaded;
    }

} // orion

#endif //ORION_DEFERREDREGISTRY_H
