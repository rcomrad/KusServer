#include "web_base.hpp"

#include <stdexcept>

#include "nodes/node.hpp"

void
onto::WebBase::registrateNode(const std::string_view& a_name, Node& a_obj)
{
    if (m_storage.count(a_name))
    {
        // TODO: catch
        throw std::runtime_error("The node named '" + std::string(a_name) +
                                 "' has already been registered.");
    }
    m_storage[a_name] = &a_obj;
}

// std::string
// onto::WebBase::print() const noexcept
// {
//     std::string result;
//     for (auto& i : m_storage)
//     {
//         result += i.second->print();
//         result.push_back('\n');
//     }
//     return result;
// }

// void
// onto::WebBase::clearNotUsedNodes() noexcept
// {
//     std::erase_if(m_storage,
//                   [](const auto& item)
//                   {
//                       auto const& [key, value] = item;
//                       return value->isLonelyNode();
//                   });
// }
