#include <gtest/gtest.h>
#include "cache/cache.h"

TEST(LRU, EvictionWorks) {
    Cache<int, int, LRUPolicy<int>> cache(2);

    cache.put(1, 10);
    cache.put(2, 20);

    cache.get(1); // делаем 1 "recent"

    cache.put(3, 30); // вытеснит 2

    EXPECT_TRUE(cache.contains(1));
    EXPECT_FALSE(cache.contains(2));
    EXPECT_TRUE(cache.contains(3));
}

TEST(LRU, CapacityLimit) {
    Cache<int, int, LRUPolicy<int>> cache(1);

    cache.put(1, 10);
    cache.put(2, 20);

    EXPECT_FALSE(cache.contains(1));
    EXPECT_TRUE(cache.contains(2));
}


TEST(FIFO, EvictsFirstInserted) {
    Cache<int, int, FIFOPolicy<int>> cache(2);

    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);

    EXPECT_FALSE(cache.contains(1));
    EXPECT_TRUE(cache.contains(2));
    EXPECT_TRUE(cache.contains(3));
}

TEST(FIFO, GetDoesNotAffectOrder) {
    Cache<int, int, FIFOPolicy<int>> cache(2);

    cache.put(1, 10);
    cache.get(1);
    cache.put(2, 20);
    cache.put(3, 30);

    EXPECT_FALSE(cache.contains(1));
}


TEST(LFU, LeastFrequentlyUsedEvicted) {
    Cache<int, int, LFUPolicy<int>> cache(2);

    cache.put(1, 10);
    cache.put(2, 20);

    cache.get(1);
    cache.get(1);

    cache.put(3, 30);

    EXPECT_FALSE(cache.contains(2));
    EXPECT_TRUE(cache.contains(1));
    EXPECT_TRUE(cache.contains(3));
}

TEST(LFU, FrequencyIncrease) {
    Cache<int, int, LFUPolicy<int>> cache(2);

    cache.put(1, 10);

    auto v1 = cache.get(1);
    auto v2 = cache.get(1);

    EXPECT_TRUE(v1.has_value());
    EXPECT_TRUE(v2.has_value());
}


TEST(Cache, GetNonExistingReturnsNullopt) {
    Cache<int, int, LRUPolicy<int>> cache(2);

    EXPECT_FALSE(cache.get(999).has_value());
}

TEST(Cache, ClearWorks) {
    Cache<int, int, LRUPolicy<int>> cache(2);

    cache.put(1, 10);
    cache.put(2, 20);

    cache.clear();

    EXPECT_FALSE(cache.contains(1));
    EXPECT_FALSE(cache.contains(2));
}

TEST(Cache, UpdateValue) {
    Cache<int, int, LRUPolicy<int>> cache(2);

    cache.put(1, 10);
    cache.put(1, 99);

    EXPECT_EQ(cache.get(1).value(), 99);
}

TEST(Cache, DifferentTypes) {
    Cache<std::string, double, LRUPolicy<std::string>> cache(2);

    cache.put("pi", 3.14);

    EXPECT_TRUE(cache.contains("pi"));
    EXPECT_DOUBLE_EQ(cache.get("pi").value(), 3.14);
}
