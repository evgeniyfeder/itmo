#pragma once
#include <exception>
#include <list>

namespace ef2
{
    template <class K, class V, int N = 100>
    class lru_cache_t
    {
    public:
        V get(K const & key)
        {
            assert(m.size() <= N && m.size() == order.size());
            auto it = m.find(key);
            const size_t old_size = m.size();

            if (it == m.end())
                throw std::invalid_argument("cache hasn't this element");

            if (it->second.ptr_to_list != order.begin())
            {
                order.erase(it->second.ptr_to_list);
                order.push_front(key);
                it->second.ptr_to_list = order.begin();
            }

            assert(old_size == m.size() && old_size == order.size() && key == *order.cbegin());
            return it->second.value;
        }

        void put(K const & key, V && value)
        {
            assert(m.find(key) == m.end() && m.size() <= N && m.size() == order.size());

            if (m.size() == N)
                remove_oldest();

            order.push_front(key);
            m.insert({key, {value, order.begin()}});
            assert(m.find(key) != m.end() && m.size() <= N && m.size() == order.size());
        }

    private:
        void remove_oldest()
        {
            assert(m.size() == N);

            K key_to_delete = order.back();
            order.pop_back();
            m.erase(key_to_delete);

            assert(m.size() == N - 1);
        }

        using key_list_t = std::list<K>;
        using key_list_iterator_t = typename std::list<K>::iterator;

        struct map_value
        {
            V value;
            key_list_iterator_t ptr_to_list;
        };

        std::unordered_map<K, map_value> m;
        key_list_t order;
    };
}