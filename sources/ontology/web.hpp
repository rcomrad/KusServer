#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "nodes/node_include.hpp"

#include "web_base.hpp"

namespace onto
{

class Web : public WebBase
{
private:
    std::string generateKey(const std::string_view& a_name)
    {
        return std::string(a_name);
    }
    std::string generateKey(Communication& a_comm)
    {
        return a_comm.getNextDataName();
    }

public:
    std::string print() const noexcept;
    std::string serialize() const noexcept;

    void clearNotUsedNodes() noexcept;

#define NODE_MACROS(_, type, storage)                              \
    template <typename T, typename... Args>                        \
    type& create##type(T&& a_first_arg, Args&&... arg) noexcept    \
    {                                                              \
        auto [it, inserted] = m_##storage##s.try_emplace(          \
            generateKey(a_first_arg), std::forward<T>(a_first_arg), \
            std::forward<Args>(arg)...);                           \
        registrateNode(it->first, it->second);                     \
        return it->second;                                         \
    }
#include "./nodes/node.ini"

#define NODE_MACROS(_, type, ...) \
    type& get##type(const std::string_view& a_name) noexcept;
#include "./nodes/node.ini"

    // Node& createNode(const std::string_view& a_type,
    //                  const std::string_view& a_name);

#define ONLY_SIMPLE_NODS
#define NODE_MACROS(_, type, ...)                       \
    void populate##type(const std::string_view& a_name, \
                        const std::vector<std::string_view>& a_data) noexcept;
#include "./nodes/node.ini"

private:
    using WebBase::clearNotUsedNodes;

    template <class T>
    using NodeContainer = std::unordered_map<std::string, T>;

#define NODE_MACROS(_, type, storage) NodeContainer<type> m_##storage##s;
#include "./nodes/node.ini"
}; // namespace onto

} // namespace onto
