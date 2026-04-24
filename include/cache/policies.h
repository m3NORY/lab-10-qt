#pragma once
#include <unordered_map>
#include <list>
#include <stdexcept>

/*
 * Базовый интерфейс политики вытеснения
 */
template<typename Key>
class IEvictionPolicy {
public:
    virtual ~IEvictionPolicy() = default;
    virtual void touch(const Key& key) = 0;
    virtual Key evict() = 0;
    virtual void erase(const Key& key) = 0;
};

/* ================= LRU ================= */
template<typename Key>
class LRUPolicy : public IEvictionPolicy<Key> {
    std::list<Key> order_;
    std::unordered_map<Key, typename std::list<Key>::iterator> map_;
public:
    void touch(const Key& key) override {
        if (map_.count(key)) {
            order_.erase(map_[key]);
        }
        order_.push_front(key);
        map_[key] = order_.begin();
    }

    Key evict() override {
        if (order_.empty()) throw std::runtime_error("empty policy");
        Key k = order_.back();
        order_.pop_back();
        map_.erase(k);
        return k;
    }

    void erase(const Key& key) override {
        if (!map_.count(key)) return;
        order_.erase(map_[key]);
        map_.erase(key);
    }
};

/* ================= FIFO ================= */
template<typename Key>
class FIFOPolicy : public IEvictionPolicy<Key> {
    std::list<Key> order_;
public:
    void touch(const Key& key) override {
        order_.push_back(key);
    }

    Key evict() override {
        if (order_.empty()) throw std::runtime_error("empty policy");
        Key k = order_.front();
        order_.pop_front();
        return k;
    }

    void erase(const Key& key) override {
        order_.remove(key);
    }
};

/* ================= LFU ================= */
template<typename Key>
class LFUPolicy : public IEvictionPolicy<Key> {
    std::unordered_map<Key, int> freq_;
public:
    void touch(const Key& key) override {
        freq_[key]++;
    }

    Key evict() override {
        if (freq_.empty()) throw std::runtime_error("empty policy");

        auto min_it = freq_.begin();
        for (auto it = freq_.begin(); it != freq_.end(); ++it) {
            if (it->second < min_it->second)
                min_it = it;
        }

        Key k = min_it->first;
        freq_.erase(min_it);
        return k;
    }

    void erase(const Key& key) override {
        freq_.erase(key);
    }
};