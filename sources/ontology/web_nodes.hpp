#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

#include "nodes/function.hpp"
#include "nodes/node.hpp"
#include "nodes/operator.hpp"
#include "nodes/type.hpp"
#include "nodes/variable.hpp"

#include "command.hpp"
#include "web_base.hpp"

namespace onto
{

class WebNodes : public WebBase
{
public:
#define NODE_MACROS(type, storage)                               \
    template <typename T>                                        \
    type& create##type(T& arg) noexcept                          \
    {                                                            \
        const auto& node_name = Command::getNodeName(arg);       \
        const auto empl_res   = storage.emplace(node_name, arg); \
        auto& obj             = empl_res.first->second;          \
        registrateNode(node_name, obj);                          \
        return obj;                                              \
    }
#include "./nodes/all_node_macro_call.ini"

#define NODE_MACROS(type, ...) \
    type& get##type(const std::string_view& a_name) noexcept;
#include "./nodes/all_node_macro_call.ini"

    Node& createNode(const std::string_view& a_type,
                    const std::string_view& a_name) noexcept;

#define NODE_MACROS(type, ...) \
    void populate##type(       \
        const std::unordered_set<std::string_view>& a_names) noexcept;
#include "./nodes/all_node_macro_call.ini"

private:
    template <class T>
    using NodeContainer = std::unordered_map<std::string, T>;

#define NODE_MACROS(type, storage) NodeContainer<type> storage;
#include "./nodes/all_node_macro_call.ini"
}; // namespace onto

} // namespace onto
