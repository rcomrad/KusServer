#pragma once

#include <typeindex>
#include <typeinfo>
#include <unordered_map>

#include "kernel/framework/logger/include_me.hpp"

namespace core
{

class MultitypeStorage
{
public:
    template <typename T>
    void put(T& a_ref)
    {
        auto& tid  = typeid(T*);
        auto indx = std::type_index(tid);
        if (m_references.count(indx))
        {
            THROW("Type already stored in container '%s'", tid.name());
        }
        m_references.emplace(indx, reinterpret_cast<void*>(&a_ref));
    }

    template <typename T>
    T& get()
    {
        auto& tid  = typeid(T*);
        auto indx = std::type_index(tid);
        auto it   = m_references.find(indx);
        if (it == m_references.end())
        {
            THROW("No such type in container '%s'", tid.name());
        }
        return *reinterpret_cast<T*>(it->second);
    }

private:
    std::unordered_map<std::type_index, void*> m_references;
};

} // namespace core
