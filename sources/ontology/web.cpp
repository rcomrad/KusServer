#include "web.hpp"

#include <map>
#include <type_traits>

#include "core/logging/logging.hpp"
#include "core/logging/table_printer.hpp"

#include "relation.hpp"

//--------------------------------------------------------------------------------

template <typename T>
auto
getSorted(const T& a_storage)
{
    using key   = std::remove_cvref_t<decltype(std::begin(a_storage)->first)>;
    using value = std::remove_cvref_t<decltype(std::begin(a_storage)->second)>;
    std::map<key, value> result{a_storage.begin(), a_storage.end()};
    return result;
}

namespace onto
{
template <typename T>
void
foo_print(std::string& result, const char* a_type_name, const T& storage)
{
    const int buf_size = 300;
    const int width    = 12;

    char buffer[buf_size];

    // snprintf(ptr, buf_size, "%-*s |", width, a_type_name);
    // result += buffer;

    char* ptr = buffer;
    ptr += snprintf(ptr, buf_size, "%-*s|", width, a_type_name);
    for (int i = 0; i < RELATION_COUNT; ++i)
    {
        if (i == int(Relation::NUN) || i == int(Relation::MIDDLE) ||
            i == int(Relation::MAX))
            continue;
        ptr += snprintf(ptr, buf_size, "%-*s|", width, getRelationName(i));
    }
    result += buffer;

    result.push_back('\n');
    for (auto& i : storage)
    {
        result += i.second.print();
        result.push_back('\n');
    }

    // snprintf(ptr, buf_size, "%-*s |", width, a_type_name);
    // result += buffer;
    result += "----------------------------------------------------------------"
              "----------------------------------------------------------------"
              "----------------------------------------------------------------"
              "\n";
}
} // namespace onto

#define NODE_MACROS(type, __, storage)                       \
    if (!m_##storage##s.empty())                             \
    {                                                        \
        foo_print(result, #type, getSorted(m_##storage##s)); \
    }

std::string
onto::Web::print() const noexcept
{
    std::string result;
    result += "================================================================"
              "================================================================"
              "================================================================"
              "\n";
#include "./nodes/node.ini"
    result += "================================================================"
              "================================================================"
              "================================================================"
              "\n";
    return result;

    // std::cout << core::TablePrinter::print(
    //                  m_variables, {"id", "name", "surname", "weight", "high",
    //                                "building_numder", "x", "y",
    //                                "street_name"})
    //           << std::endl;
}

#define NODE_MACROS(_, __, storage)               \
    if (!m_##storage##s.empty())                  \
    {                                             \
        for (auto& i : getSorted(m_##storage##s)) \
        {                                         \
            result += i.second.serialize();       \
            result.push_back(';');                \
        }                                         \
    }

std::string
onto::Web::serialize() const noexcept
{
    std::string result;
#include "./nodes/node.ini"
    return result;
}

#define NODE_MACROS(_, __, storage) clearNotUsedNodes(m_##storage##s);

void
onto::Web::clearNotUsedNodes() noexcept
{
#include "./nodes/node.ini"
}

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
// #define ONLY_SIMPLE_NODS
// #define NODE_MACROS(_, type, ...)                            \
//     if (a_type == #type)                                     \
//     {                                                        \
//         result = &dynamic_cast<Node&>(create##type(a_name)); \
//     }

// onto::Node&
// onto::Web::createNode(const std::string_view& a_type,
//                       const std::string_view& a_name)
// {
//     onto::Node* result;
// #include "./nodes/node.ini"
//     else
//     {
//         LOG_ERROR("Cant create node with '%s' type.", a_type);
//         throw std::runtime_error("Undefined Node type.");
//     }
//     return *result;
// }

#define ONLY_SIMPLE_NODS
#define NODE_MACROS(_, type, ...)                             \
    void onto::Web::populate##type(                           \
        const std::string_view& a_name,                       \
        const std::vector<std::string_view>& a_data) noexcept \
    {                                                         \
        create##type(a_name, a_data);                         \
    }
#include "./nodes/node.ini"
