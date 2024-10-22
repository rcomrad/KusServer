#include "web_nodes.hpp"

#include "core/logging/logging.hpp"

//--------------------------------------------------------------------------------

#define NODE_MACROS(type, storage)                    \
    onto::type& onto::WebNodes::get##type(            \
        const std::string_view& a_name) noexcept      \
    {                                                 \
        auto obj_opt = get_node<type>(a_name);        \
        if (!obj_opt.has_value())                     \
        {                                             \
            LOG_ERROR("No '%s' node found.", a_name); \
        }                                             \
        return obj_opt.value();                       \
    }
#include "./nodes/all_node_macro_call.ini"

#define NODE_MACROS(type, ...)                            \
    if (a_type == #type)                                  \
    {                                                     \
        return dynamic_cast<Node&>(create##type(a_name)); \
    }

onto::Node&
onto::WebNodes::createNode(const std::string_view& a_type,
                           const std::string_view& a_name) noexcept
{
#include "./nodes/all_node_macro_call.ini"
    LOG_ERROR("Cant create node with '%s' type.", a_type);
    static Node null_result(Node::Kind::NUN, "NUN");
    return null_result;
}

#define NODE_MACROS(type, storage)                                    \
    void onto::WebNodes::populate##type(                              \
        const std::unordered_set<std::string_view>& a_names) noexcept \
    {                                                                 \
        for (auto i : a_names)                                        \
        {                                                             \
            create##type(i);                                          \
        }                                                             \
    }
#include "./nodes/all_node_macro_call.ini"
