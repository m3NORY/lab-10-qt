#pragma once
#include <unordered_map>
#include <optional>
#include "policies.h"

/*
 * Шаблонный кэш с политикой вытеснения
 */
template<typename Key, typename Value, typename EvictionPolicy>
class Cache {
    std::unordered_map<Key, Value> data_;
    EvictionPolicy policy_;
    size_t capacity_;

public:
    constexpr explicit Cache(size_t capacity)
        : capacity_(capacity) {}

    void put(const Key& key, const Value& value) {
        if (data_.count(key)) {
            data_[key] = value;
            policy_.touch(key);
            return;
        }

        if (data_.size() >= capacity_) {
            Key evicted = policy_.evict();
            data_.erase(evicted);
        }

        data_[key] = value;
        policy_.touch(key);
    }

    std::optional<Value> get(const Key& key) {
        if (!data_.count(key)) return std::nullopt;
        policy_.touch(key);
        return data_[key];
    }

    bool contains(const Key& key) const {
        return data_.count(key) > 0;
    }

    void clear() {
        data_.clear();
    }
};