#include "web_base.hpp"

// #include <iostream>
// #include <sstream>

void
onto::WebBase::registrateNode(const std::string_view& a_name,
                              Node& a_obj) noexcept
{
    m_storage[a_name] = &a_obj;
}

std::string
onto::WebBase::print() const noexcept
{
    std::string result;
    for (auto& i : m_storage)
    {
        result += i.second->print();
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
