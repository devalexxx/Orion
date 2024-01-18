//
// Created by Alex on 26/12/2023.
//

#ifndef ORION_DEFERREDREGISTRY_H
#define ORION_DEFERREDREGISTRY_H

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include <functional>
#include <map>

#include <fmt/core.h>

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

        explicit DeferredRegistry(std::string category);
        DeferredRegistry(std::string category, Initializer&& initializer);

        void load () override;
        void reset() override;

        std::shared_ptr<T> add(std::string name, std::shared_ptr<T> ptr);

        std::shared_ptr<T> remove(Ref<std::string> name);
        std::shared_ptr<T> get   (Ref<std::string> name) const;

        [[nodiscard]] bool exist(Ref<std::string> name) const;

        [[nodiscard]] bool is_loaded() const;
    private:
        std::vector<std::shared_ptr<T>> m_storage {};
        Indexer<std::string, u32>       m_indexer {};
        Initializer                     m_initializer {};

        bool m_is_loaded;
    };

    template<typename T>
    DeferredRegistry<T>::DeferredRegistry(std::string category, DeferredRegistry::Initializer &&initializer) : m_initializer(initializer), m_is_loaded(false) {
        auto it = IDeferredRegistry::REGISTRIES.find(category);
        if (it != IDeferredRegistry::REGISTRIES.cend()) {
            it->second.push_back(this);
        }
        else {
            IDeferredRegistry::REGISTRIES.emplace(std::move(category), std::vector<PtrMut<IDeferredRegistry>> {{this}});
        }
    }

    template<typename T>
    DeferredRegistry<T>::DeferredRegistry(std::string category) : m_is_loaded(false) {
        auto it = IDeferredRegistry::REGISTRIES.find(category);
        if (it != IDeferredRegistry::REGISTRIES.cend()) {
            it->second.push_back(this);
        }
        else {
            IDeferredRegistry::REGISTRIES.emplace(std::move(category), std::vector<PtrMut<IDeferredRegistry>> {{this}});
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
    std::shared_ptr<T> DeferredRegistry<T>::add(std::string name, std::shared_ptr<T> ptr) {
        if (!m_indexer.exist(name)) {
            m_storage.push_back(ptr);
            m_indexer.emplace(std::move(name), m_storage.size() - 1);
        }
        else
            fmt::print(stderr, "Could not add object {} to register because this name is already register\n", name);
        return std::move(ptr);
    }

    template<typename T>
    std::shared_ptr<T> DeferredRegistry<T>::remove(Ref<std::string> name) {
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
            fmt::print(stderr, "Object {} does not exist in this registry\n", name);
            return nullptr;
        }
    }

    template<typename T>
    std::shared_ptr<T> DeferredRegistry<T>::get(Ref<std::string> name) const {
        auto opt = m_indexer.get_by_key(name);
        if (opt != std::nullopt)
            return m_storage[opt->second];
        else {
            fmt::print(stderr, "Object {} does not exist in this registry\n", name);
            return nullptr;
        }
    }

    template<typename T>
    bool DeferredRegistry<T>::exist(Ref<std::string> name) const {
        return m_indexer.get_by_key(name) != std::nullopt;
    }

    template<typename T>
    bool DeferredRegistry<T>::is_loaded() const {
        return m_is_loaded;
    }

} // orion

#endif //ORION_DEFERREDREGISTRY_H
