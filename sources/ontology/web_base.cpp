#include "web_base.hpp"

// #include <iostream>
// #include <sstream>

#include "core/logging/logging.hpp"

boost::optional<onto::Node&>
onto::WebBase::get_node(const std::string_view& a_name) const noexcept
{
    auto it = m_storage.find(a_name);
    boost::optional<onto::Node&> result;
    if (it != m_storage.end())
    {
        result = *it->second;
    }
    else
    {
        LOG_WARNING("No '%s' node.", a_name);
    }
    return result;
}

// void
// onto::WebBase::createNode(const std::string& a_type,
//                           const std::string& a_name) noexcept
// {
// }

// void
// onto::Web::connect(const std::string_view& a_node_name_1,
//                    const std::string_view& a_node_name_2,
//                    Relation a_relation) noexcept
// {
// }
