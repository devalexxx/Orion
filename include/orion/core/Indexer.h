//
// Created by Alex on 26/12/2023.
//

#ifndef ORION_INDEXER_H
#define ORION_INDEXER_H

#include "type.h"

#include <unordered_map>
#include <iostream>
#include <optional>

namespace orion {

    template<typename K, typename V>
    class Indexer {
    public:
        Indexer() = default;

        bool emplace(K key, V value);

        bool set(K key, V value);
        bool remove(Ref<K> key);

        void reset();

        std::optional<std::pair<const K, V>> get_by_key  (Ref<K> key)   const;
        std::optional<std::pair<const K, V>> get_by_value(Ref<V> value) const;

        bool exist(Ref<K> key) const;
    private:
        std::unordered_map<K, V> m_default {};
        std::unordered_map<V, K> m_reverse {};
    };

    template<typename K, typename V>
    void Indexer<K, V>::reset() {
        m_default.clear();
        m_reverse.clear();
    }

    template<typename K, typename V>
    bool Indexer<K, V>::emplace(K key, V value) {
        if (m_default.find(key) == m_default.cend()) {
            m_default.emplace(key, value);
            m_reverse.emplace(std::move(value), std::move(key));
            return true;
        }
        return false;
    }

    template<typename K, typename V>
    bool Indexer<K, V>::set(K key, V value) {
        auto it = m_default.find(key);
        if (it != m_default.cend()) {
            it->second = std::move(value);
            m_reverse.find(it->second)->second = std::move(key);
            return true;
        }
        return false;
    }

    template<typename K, typename V>
    bool Indexer<K, V>::remove(Ref<K> key) {
        auto it = m_default.find(key);
        if (it != m_default.cend()) {
            m_reverse.erase(it->second);
            m_default.erase(it->first);
            return true;
        }
        return false;
    }

    template<typename K, typename V>
    std::optional<std::pair<const K, V>> Indexer<K, V>::get_by_key(Ref<K> key) const {
        auto it = m_default.find(key);
        if (it != m_default.cend()) {
            return std::make_optional(std::make_pair(it->first, it->second));
        }
        else
            return std::nullopt;
    }

    template<typename K, typename V>
    std::optional<std::pair<const K, V>> Indexer<K, V>::get_by_value(Ref<V> value) const {
        auto it = m_reverse.find(value);
        if (it != m_reverse.cend()) {
            return std::make_optional(std::make_pair(it->second, it->first));
        }
        else
            return std::nullopt;
    }

    template<typename K, typename V>
    bool Indexer<K, V>::exist(Ref<K> key) const {
        return m_default.find(key) != m_default.cend();
    }

} // orion

#endif //ORION_INDEXER_H
