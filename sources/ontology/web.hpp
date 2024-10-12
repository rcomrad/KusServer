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
public:
#define NODE_MACROS(_, type, storage)                                          \
    template <typename... Args>                                                \
    type& create##type(const std::string_view& a_name, Args&&... arg) noexcept \
    {                                                                          \
        auto [it, inserted] = m_##storage##s.try_emplace(                      \
            std::string(a_name), a_name, std::forward<Args>(arg)...);          \
        registrateNode(it->first, it->second);                                 \
        return it->second;                                                     \
    }
#include "./nodes/node.ini"

#define NODE_MACROS(_, type, ...) \
    type& get##type(const std::string_view& a_name) noexcept;
#include "./nodes/node.ini"

    Node& createNode(const std::string_view& a_type,
                     const std::string_view& a_name);

#define ONLY_SIMPLE_NODS
#define NODE_MACROS(_, type, ...) \
    void populate##type(          \
        const std::unordered_set<std::string_view>& a_names) noexcept;
#include "./nodes/node.ini"

private:
    template <class T>
    using NodeContainer = std::unordered_map<std::string, T>;

#define NODE_MACROS(_, type, storage) NodeContainer<type> m_##storage##s;
#include "./nodes/node.ini"
}; // namespace onto

} // namespace onto
