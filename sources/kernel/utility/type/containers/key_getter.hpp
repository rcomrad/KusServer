#pragma once

#include <map>
#include <unordered_map>
#include <vector>

namespace util
{

// TODO: static operator() - only in C++23
class ContainerKey
{
public:
    template <typename T>
    static inline int exec(const std::vector<T>& a_container,
                           typename std::vector<T>::const_iterator a_iterator)
    {
        return a_iterator - a_container.begin();
    }

    template <typename Key, typename Value>
    static inline const Key& exec(
        const std::map<Key, Value>& a_container,
        typename std::map<Key, Value>::const_iterator a_iterator)
    {
        return a_iterator->first;
    }

    template <typename Key, typename Value>
    static inline const Key& exec(
        const std::unordered_map<Key, Value>& a_container,
        typename std::unordered_map<Key, Value>::const_iterator a_iterator)
    {
        return a_iterator->first;
    }
};

} // namespace util
