#include "web.hpp"

#include <iostream>
#include <sstream>

#include "core/logging/logging.hpp"

#include "utility/string/parser.hpp"
#include "utility/string/slicer.hpp"

#include "decoder.hpp"

//--------------------------------------------------------------------------------

onto::Web::Web() noexcept
{
    populate(m_types, {"int", "float", "double", "bool", "char"});
    // populate(m_functions, {"int", "double", "while"});
    populate(m_operators, {"if", "for", "while"});
    create
}

#define NODE_MACROS(type, ...) \
    if (i[0] == #type)         \
    {                          \
        create##type(i[1]);    \
        continue;              \
    }

void
onto::Web::applyDump(std::string&& a_dump) noexcept
{
    std::string data_storage = std::move(a_dump);
    auto words               = util::Parser::getWords(data_storage);
    for (auto i : words)
    {
#include "./nodes/all_node_macro_call.ini"
    }
}

void
onto::Web::applyData(const std::string& a_data) noexcept
{
    Decoder::process(*this, a_data);
}

//--------------------------------------------------------------------------------

#define NODE_MACROS(type, storage)                                            \
    onto::type& onto::Web::get##type(const std::string_view& a_name) noexcept \
    {                                                                         \
        auto obj_opt = get_node(a_name);                                      \
        if (!obj_opt.has_value())                                             \
        {                                                                     \
            LOG_ERROR("No '%s' node found.", a_name);                         \
        }                                                                     \
        return dynamic_cast<type&>(obj_opt.value());                          \
    }
#include "./nodes/all_node_macro_call.ini"


// void
// onto::Web::connect(const std::string_view& a_node_name_1,
//                    const std::string_view& a_node_name_2,
//                    Relation a_relation) noexcept
// {
// }

void
onto::Web::connect(Node& a_node_1, Node& a_node_2, Relation a_relation) noexcept
{
    a_node_1.addNeighbor(a_node_2, a_relation);
}

// void
// onto::Web::connect(const std::string_view& a_node_1_name,
//                    const std::string_view& a_node_2_name,
//                    Relation a_relation) noexcept
// {
//     auto node1_opt = get_node(a_node_1_name);
//     auto node2_opt = get_node(a_node_2_name);
//     if (!node1_opt.has_value())
//     {
//         LOG_ERROR("No node with name '%s' in web.", a_node_1_name);
//     }
//     else if (!node2_opt.has_value())
//     {
//         LOG_ERROR("No node with name '%s' in web.", a_node_2_name);
//     }
//     else
//     {
//         node1_opt.value().addNeighbor(node2_opt.value(), a_relation);
//     }
// }
