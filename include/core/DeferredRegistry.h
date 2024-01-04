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
#include <map>

#include "type.h"
#include "Indexer.h"

namespace orion {

    class IDeferredRegistry {
    public:
        static std::map<std::string, std::vector<PtrMut<IDeferredRegistry>>> REGISTRIES;

        virtual void load () = 0;
        virtual void reset() = 0;
    };

    template<typename T>
    class DeferredRegistry : public IDeferredRegistry {
    public:
        using Initializer = std::function<void(RefMut<DeferredRegistry<T>>)>;

        explicit DeferredRegistry(Ref<std::string> category);
        DeferredRegistry(Ref<std::string> category, Initializer&& initializer);

        void load () override;
        void reset() override;

        std::shared_ptr<T> add(Ref<std::string> name, std::shared_ptr<T> ptr);

        std::shared_ptr<T> remove(const std::string& name);
        std::shared_ptr<T> get   (const std::string& name) const;

        [[nodiscard]] bool exist(const std::string& name) const;

        [[nodiscard]] bool is_loaded() const;
    private:
        std::vector<std::shared_ptr<T>> m_storage {};
        Indexer<std::string, u32>       m_indexer {};
        Initializer                     m_initializer {};

        bool m_is_loaded;
    };

    template<typename T>
    DeferredRegistry<T>::DeferredRegistry(Ref<std::string> category, DeferredRegistry::Initializer &&initializer) : m_initializer(initializer), m_is_loaded(false) {
        auto it = IDeferredRegistry::REGISTRIES.find(category);
        if (it != IDeferredRegistry::REGISTRIES.cend()) {
            it->second.push_back(this);
        }
        else {
            IDeferredRegistry::REGISTRIES.emplace(category, std::vector<PtrMut<IDeferredRegistry>> {{this}});
        }
    }

    template<typename T>
    DeferredRegistry<T>::DeferredRegistry(Ref<std::string> category) : m_is_loaded(false) {
        auto it = IDeferredRegistry::REGISTRIES.find(category);
        if (it != IDeferredRegistry::REGISTRIES.cend()) {
            it->second.push_back(this);
        }
        else {
            IDeferredRegistry::REGISTRIES.emplace(category, std::vector<PtrMut<IDeferredRegistry>> {{this}});
        }
    }

    template<typename T>
    void DeferredRegistry<T>::load() {
        if (!m_is_loaded) {
            if (m_initializer) {
                m_initializer(*this);
            }
            m_is_loaded = true;
        }
    }

    template<typename T>
    void DeferredRegistry<T>::reset() {
        if (m_is_loaded) {
            m_storage.clear();
            m_indexer.reset();
            m_is_loaded = false;
        }
    }

    template<typename T>
    std::shared_ptr<T> DeferredRegistry<T>::add(Ref<std::string> name, std::shared_ptr<T> ptr) {
        if (!m_indexer.exist(name)) {
            m_storage.push_back(ptr);
            m_indexer.emplace(name, m_storage.size() - 1);
        }
        else
            std::cerr << "Could not add object " << name << " to register because this name is already register\n";
        return std::move(ptr);
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
    bool DeferredRegistry<T>::exist(const std::string &name) const {
        return m_indexer.get_by_key(name) != std::nullopt;
    }

    template<typename T>
    bool DeferredRegistry<T>::is_loaded() const {
        return m_is_loaded;
    }

} // orion

#endif //ORION_DEFERREDREGISTRY_H
