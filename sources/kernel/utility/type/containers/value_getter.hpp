#pragma once

#include <map>
#include <unordered_map>
#include <vector>

namespace util
{

// TODO: static operator() - only in C++23
class ContainerValue
{
public:
    template <typename T>
    static inline const T& exec(
        const std::vector<T>& a_container,
        typename std::vector<T>::const_iterator a_iterator)
    {
        return *a_iterator;
    }

    template <typename Key, typename Value>
    static inline const Value& exec(
        const std::map<Key, Value>& a_container,
        typename std::map<Key, Value>::const_iterator a_iterator)
    {
        return a_iterator->second;
    }

    template <typename Key, typename Value>
    static inline const Value& exec(
        const std::unordered_map<Key, Value>& a_container,
        typename std::unordered_map<Key, Value>::const_iterator a_iterator)
    {
        return a_iterator->second;
    }
};

} // namespace util
