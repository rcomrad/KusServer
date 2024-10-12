#include "web.hpp"

#include "core/logging/logging.hpp"

//--------------------------------------------------------------------------------

#define NODE_MACROS(_, type, ...)                                             \
    onto::type& onto::Web::get##type(const std::string_view& a_name) noexcept \
    {                                                                         \
        auto obj = searchNode<type>(a_name);                                  \
        if (!obj)                                                             \
        {                                                                     \
            LOG_ERROR("No '%s' node found.", a_name);                         \
        }                                                                     \
        return *obj;                                                          \
    }
#include "./nodes/node.ini"

// TODO: remove?
#define ONLY_SIMPLE_NODS
#define NODE_MACROS(_, type, ...)                            \
    if (a_type == #type)                                     \
    {                                                        \
        result = &dynamic_cast<Node&>(create##type(a_name)); \
    }

onto::Node&
onto::Web::createNode(const std::string_view& a_type,
                      const std::string_view& a_name)
{
    onto::Node* result;
#include "./nodes/node.ini"
    else
    {
        LOG_ERROR("Cant create node with '%s' type.", a_type);
        throw std::runtime_error("Undefined Node type.");
    }
    return *result;
}

#define ONLY_SIMPLE_NODS
#define NODE_MACROS(_, type, ...)                                     \
    void onto::Web::populate##type(                                   \
        const std::unordered_set<std::string_view>& a_names) noexcept \
    {                                                                 \
        for (auto i : a_names)                                        \
        {                                                             \
            create##type(i);                                          \
        }                                                             \
    }
#include "./nodes/node.ini"
