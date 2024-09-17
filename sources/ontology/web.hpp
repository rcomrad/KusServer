#pragma once

#include <boost/optional/optional.hpp>

#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

#include "core/logging/logging.hpp"

#include "nodes/function.hpp"
#include "nodes/node.hpp"
#include "nodes/operator.hpp"
#include "nodes/type.hpp"
#include "nodes/variable.hpp"

#include "command.hpp"
#include "relation.hpp"
#include "web_base.hpp"

namespace onto
{

class Web : public WebBase
{
public:
    Web() noexcept;

    void applyDump(std::string&& a_dump) noexcept;
    void applyData(const std::string& a_data) noexcept;

#define NODE_MACROS(type, storage)                                    \
    template <typename T>                                             \
    type& create##type(T& arg) noexcept                               \
    {                                                                 \
        return createNode(storage, Command::getNodeName(args), args); \
    }
#include "./nodes/all_node_macro_call.ini"

#define NODE_MACROS(type, ...) \
    type& get##type(const std::string_view& a_name) noexcept;
#include "./nodes/all_node_macro_call.ini"

private:
#define NODE_MACROS(type, storage) NodeContainer<type> name;
#include "./nodes/all_node_macro_call.ini"

    // template <typename T>
    // void populate(NodeContainer<T>& a_storage,
    //               const std::unordered_set<std::string_view>& a_names)
    //               noexcept
    // {
    //     for (const auto& name : a_names)
    //     {
    //         Command c;
    //         c.m_name = name;
    //         createNode(a_storage, c);
    //     }
    // }

    // template <typename T, typename... Args>
    // T& createNode(NodeContainer<T>& a_storage, Args... args) noexcept
    // {
    //     auto it = a_storage.emplace(a_command.m_name, T(args...)).first;
    //     m_storage[it->first] = dynamic_cast<Node*>(&it->second);
    //     return it->second;
    // }
    void createNode(const std::string& a_type,
                    const std::string& a_name) noexcept;
}; // namespace onto

} // namespace onto
