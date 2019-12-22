#include "gtest/gtest.h"
#include <lru_cache/lru_cache.h>

TEST(SomeAdditions, OneAddition)
{
    ef2::lru_cache_t<int, int> cache;
    cache.put(0, 1);
    ASSERT_EQ(cache.get(0), 1);
    ASSERT_ANY_THROW(cache.get(1));
}

TEST(SomeAdditions, FiveAddition)
{
    ef2::lru_cache_t<int, int> cache;
    cache.put(0, 1);
    cache.put(1, 5);
    cache.put(2, 10);

    ASSERT_EQ(cache.get(0), 1);
    ASSERT_EQ(cache.get(1), 5);
    ASSERT_EQ(cache.get(2), 10);
}

TEST(CacheOverflow, Two)
{
    ef2::lru_cache_t<std::string, int, 2> cache;
    cache.put("0", 1);
    cache.put("1", 5);
    cache.put("2", 10);

    ASSERT_ANY_THROW(cache.get("0"));
    ASSERT_EQ(cache.get("2"), 10);
    ASSERT_EQ(cache.get("1"), 5);

    cache.put("0", 1);
    ASSERT_ANY_THROW(cache.get("2"));

}